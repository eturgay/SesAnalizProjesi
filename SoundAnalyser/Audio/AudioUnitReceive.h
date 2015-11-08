//
//  AudioUnitReceive.h
//  VoiceRecordPlayObjectiveC
//
//  Created by Apple on 28/10/15.
//  Copyright (c) 2015 B. Lake. All rights reserved.
//

#ifndef VoiceRecordPlayObjectiveC_AudioUnitReceive_h
#define VoiceRecordPlayObjectiveC_AudioUnitReceive_h

#import <AVFoundation/AVFoundation.h>

extern AudioUnit *audioUnit;
extern bool AudioUnitStarted;

extern int signalLength;
extern float fValue0;
extern float fValue5;
extern float fValue20;

int initAudioSession();
int initAudioStreams(AudioUnit *audioUnit);
int startAudioUnit(AudioUnit *audioUnit);
int stopProcessingAudio(AudioUnit *audioUnit);


#endif
