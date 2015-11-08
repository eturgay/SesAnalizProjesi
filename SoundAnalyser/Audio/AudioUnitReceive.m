//
//  AudioUnitReceive.m
//  VoiceRecordPlayObjectiveC
//
//  Created by Apple on 28/10/15.
//  Copyright (c) 2015 B. Lake. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AudioUnitReceive.h"
#import "../Math/SignalDefinitions.h"


AudioUnit *audioUnit = NULL;
bool AudioUnitStarted = false;
float *convertedSampleBuffer = NULL;

int signalLength;
float fValue0;
float fValue5;
float fValue20;


int initAudioSession() {
    audioUnit = (AudioUnit*)malloc(sizeof(AudioUnit));
    
    if(AudioSessionInitialize(NULL, NULL, NULL, NULL) != noErr) {
        return 1;
    }
    
    if(AudioSessionSetActive(true) != noErr) {
        return 1;
    }
    
    UInt32 sessionCategory = kAudioSessionCategory_PlayAndRecord;
    if(AudioSessionSetProperty(kAudioSessionProperty_AudioCategory,
                               sizeof(UInt32), &sessionCategory) != noErr) {
        return 1;
    }
    
    Float32 bufferSizeInSec = 0.02f;
    if(AudioSessionSetProperty(kAudioSessionProperty_PreferredHardwareIOBufferDuration,
                               sizeof(Float32), &bufferSizeInSec) != noErr) {
        return 1;
    }
    
    UInt32 overrideCategory = 1;
    if(AudioSessionSetProperty(kAudioSessionProperty_OverrideCategoryDefaultToSpeaker,
                               sizeof(UInt32), &overrideCategory) != noErr) {
        return 1;
    }
    
    // There are many properties you might want to provide callback functions for:
    // kAudioSessionProperty_AudioRouteChange
    // kAudioSessionProperty_OverrideCategoryEnableBluetoothInput
    // etc.
    
    return 0;
}
OSStatus renderCallback(void *userData, AudioUnitRenderActionFlags *actionFlags,
                        const AudioTimeStamp *audioTimeStamp, UInt32 busNumber,
                        UInt32 numFrames, AudioBufferList *buffers) {
    
    OSStatus status = AudioUnitRender(*audioUnit, actionFlags, audioTimeStamp,
                                      1, numFrames, buffers);
    if(status != noErr) {
        return status;
    }
    
    if(convertedSampleBuffer == NULL) {
        // Lazy initialization of this buffer is necessary because we don't
        // know the frame count until the first callback
        convertedSampleBuffer = (float*)malloc(sizeof(float) * numFrames);
    }
    
    SInt16 *inputFrames = (SInt16*)(buffers->mBuffers->mData);
    
    //shift signal
    for(int i = (SIGNAL_LENGTH - 1); i >= numFrames; i--) {
        signal1[i] = signal1[i - numFrames];
    }
    // If your DSP code can use integers, then don't bother converting to
    // floats here, as it just wastes CPU. However, most DSP algorithms rely
    // on floating point, and this is especially true if you are porting a
    // VST/AU to iOS.
    for(int i = 0; i < numFrames; i++) {
        signal1[i] = (float)inputFrames[i] / 32768;
    }
    
    // Now we have floating point sample data from the render callback! We
    // can send it along for further processing, for example:
    // plugin->processReplacing(convertedSampleBuffer, NULL, sampleFrames);
    
    // Assuming that you have processed in place, we can now write the
    // floating point data back to the input buffer.
    for(int i = 0; i < numFrames; i++) {
        // Note that we multiply by 32767 here, NOT 32768. This is to avoid
        // overflow errors (and thus clipping).
        inputFrames[i] = (SInt16)(convertedSampleBuffer[i] * 32767);
    }
    //@emre
    signalLength = numFrames;
    fValue0 = signal1[0];
    fValue5 = signal1[5];
    fValue20 = signal1[20];
    
    return noErr;
}

int initAudioStreams(AudioUnit *audioUnit) {
    UInt32 audioCategory = kAudioSessionCategory_PlayAndRecord;
    if(AudioSessionSetProperty(kAudioSessionProperty_AudioCategory,
                               sizeof(UInt32), &audioCategory) != noErr) {
        return 1;
    }
    
    UInt32 overrideCategory = 1;
    if(AudioSessionSetProperty(kAudioSessionProperty_OverrideCategoryDefaultToSpeaker,
                               sizeof(UInt32), &overrideCategory) != noErr) {
        // Less serious error, but you may want to handle it and bail here
    }
    
    AudioComponentDescription componentDescription;
    componentDescription.componentType = kAudioUnitType_Output;
    componentDescription.componentSubType = kAudioUnitSubType_RemoteIO;
    componentDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
    componentDescription.componentFlags = 0;
    componentDescription.componentFlagsMask = 0;
    AudioComponent component = AudioComponentFindNext(NULL, &componentDescription);
    if(AudioComponentInstanceNew(component, audioUnit) != noErr) {
        return 1;
    }
    
    UInt32 enable = 1;
    if(AudioUnitSetProperty(*audioUnit,
                            kAudioOutputUnitProperty_EnableIO,
                            kAudioUnitScope_Input,
                            1,
                            &enable,
                            sizeof(UInt32)) != noErr) {
        return 1;
    }
    
    
    AURenderCallbackStruct callbackStruct;
    callbackStruct.inputProc = renderCallback; // Render function
    callbackStruct.inputProcRefCon = NULL;
    if(AudioUnitSetProperty(*audioUnit,
                            kAudioUnitProperty_SetRenderCallback,
                            kAudioUnitScope_Input,
                            0,
                            &callbackStruct,
                            sizeof(AURenderCallbackStruct)) != noErr) {
        return 1;
    }
    
    AudioStreamBasicDescription streamDescription;
    // You might want to replace this with a different value, but keep in mind that the
    // iPhone does not support all sample rates. 8kHz, 22kHz, and 44.1kHz should all work.
    streamDescription.mSampleRate = 22000;
    // Yes, I know you probably want floating point samples, but the iPhone isn't going
    // to give you floating point data. You'll need to make the conversion by hand from
    // linear PCM <-> float.
    streamDescription.mFormatID = kAudioFormatLinearPCM;
    // This part is important!
    streamDescription.mFormatFlags = kAudioFormatFlagIsSignedInteger |
    kAudioFormatFlagsNativeEndian |
    kAudioFormatFlagIsPacked;
    // Not sure if the iPhone supports recording >16-bit audio, but I doubt it.
    streamDescription.mBitsPerChannel = 16;
    // 1 sample per frame, will always be 2 as long as 16-bit samples are being used
    streamDescription.mBytesPerFrame = 2;
    // Record in mono. Use 2 for stereo, though I don't think the iPhone does true stereo recording
    streamDescription.mChannelsPerFrame = 1;
    streamDescription.mBytesPerPacket = streamDescription.mBytesPerFrame *
    streamDescription.mChannelsPerFrame;
    // Always should be set to 1
    streamDescription.mFramesPerPacket = 1;
    // Always set to 0, just to be sure
    streamDescription.mReserved = 0;
    
    // Set up input stream with above properties
    if(AudioUnitSetProperty(*audioUnit,
                            kAudioUnitProperty_StreamFormat,
                            kAudioUnitScope_Input,
                            0,
                            &streamDescription,
                            sizeof(streamDescription)) != noErr) {
        return 1;
    }
    
    // Ditto for the output stream, which we will be sending the processed audio to
    if(AudioUnitSetProperty(*audioUnit,
                            kAudioUnitProperty_StreamFormat,
                            kAudioUnitScope_Output,
                            1,
                            &streamDescription,
                            sizeof(streamDescription)) != noErr) {
        return 1;
    }
    
    return 0;
}


int startAudioUnit(AudioUnit *audioUnit) {
    if(AudioUnitInitialize(*audioUnit) != noErr) {
        return 1;
    }
    
    if(AudioOutputUnitStart(*audioUnit) != noErr) {
        return 1;
    }
    
    AudioUnitStarted = true;
    
    return 0;
}


int stopProcessingAudio(AudioUnit *audioUnit) {
    if(AudioOutputUnitStop(*audioUnit) != noErr) {
        return 1;
    }
    
    if(AudioUnitUninitialize(*audioUnit) != noErr) {
        return 1;
    }
    
    *audioUnit = NULL;
    AudioUnitStarted = false;
    return 0;
}

