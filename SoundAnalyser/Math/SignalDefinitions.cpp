//
//  SignalDefinitions.cpp
//  VoiceRecordPlayObjectiveC
//
//  Created by Apple on 21/10/15.
//  Copyright (c) 2015 B. Lake. All rights reserved.
//

#include "SignalDefinitions.h"


float signal1[SIGNAL_LENGTH];
float signal1FR[SIGNAL_FFT_LENGTH];
float signal1FI[SIGNAL_FFT_LENGTH];
float signal1FA[SIGNAL_FFT_LENGTH];
float signal1FPRDGRM[SIGNAL_FFT_LENGTH];
float signal1FARMA[SIGNAL_FFT_LENGTH];

float Graph1Data[SIGNAL_LENGTH];
float Graph2Data[SIGNAL_FFT_LENGTH];


float autoCorr[MAX_MODEL_ORDER];
float aCoeff[MAX_MODEL_ORDER];
float spectrumEstimate[SIGNAL_FFT_LENGTH];
float errorHistory[MAX_ITERATION];


float testSignalNoise[SIGNAL_LENGTH];
float testSignalDoubleSinus[SIGNAL_LENGTH];
float testSignalDoubleSinusInNoise[SIGNAL_LENGTH];
float testSignalARMA[SIGNAL_LENGTH];

