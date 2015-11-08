//
//  SignalDefinitions.h
//  VoiceRecordPlayObjectiveC
//
//  Created by Apple on 21/10/15.
//  Copyright (c) 2015 B. Lake. All rights reserved.
//

#ifndef __VoiceRecordPlayObjectiveC__SignalDefinitions__
#define __VoiceRecordPlayObjectiveC__SignalDefinitions__

#include <stdio.h>

#define MAX_ELEMENT_NUMBER 882000

#define SIGNAL_LENGTH 8192
#define SIGNAL_FFT_LENGTH 1024
#define MAX_MODEL_ORDER 20
#define MAX_ITERATION 1000


extern float signal1[SIGNAL_LENGTH];
extern float signal1FR[SIGNAL_FFT_LENGTH];
extern float signal1FI[SIGNAL_FFT_LENGTH];
extern float signal1FA[SIGNAL_FFT_LENGTH];
extern float signal1FPRDGRM[SIGNAL_FFT_LENGTH];
extern float signal1FARMA[SIGNAL_FFT_LENGTH];

extern float Graph1Data[SIGNAL_LENGTH];
extern float Graph2Data[SIGNAL_FFT_LENGTH];

extern float autoCorr[MAX_MODEL_ORDER];
extern float aCoeff[MAX_MODEL_ORDER];
extern float spectrumEstimate[SIGNAL_FFT_LENGTH];
extern float errorHistory[MAX_ITERATION];

extern float testSignalNoise[SIGNAL_LENGTH];
extern float testSignalDoubleSinus[SIGNAL_LENGTH];
extern float testSignalDoubleSinusInNoise[SIGNAL_LENGTH];
extern float testSignalARMA[SIGNAL_LENGTH];


enum fType
{
    ftReal = 0,
    ftAbs  = 1,
    ftPeriodogram = 2,
    ftARMA = 3,
};



#endif /* defined(__VoiceRecordPlayObjectiveC__SignalDefinitions__) */
