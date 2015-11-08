 //
//  ProcessSignal.cpp
//  VoiceRecordPlayObjectiveC
//
//  Created by Apple on 21/10/15.
//  Copyright (c) 2015 B. Lake. All rights reserved.
//

#include "ProcessSignal.h"
#include "FftImplementations.hpp"
#include "Filters.h"
#include "SignalModelling.hpp"
#include "SignalGenerator.hpp"

float F1[] = {0.05, 0.1, 0.2, 0.3, 0.2, 0.1, 0.05};

void GenerateTestSignals()
{
    GenerateSignals(500, 800, 5);
    for (int i = 0; i < SIGNAL_LENGTH; i++) {
        //signal1[i]  = testSignalNoise[i];
        //signal1[i]  = testSignalDoubleSinus[i];
        signal1[i]  = testSignalDoubleSinusInNoise[i];
        // signal1[i]  = testSignalARMA[i];
    }
    
}

void PrepareGraph1ForPlot(){
    for (int i = 0; i < SIGNAL_LENGTH; i++){
        if (signal1[i] > -10.0f)
            Graph1Data[i] = signal1[i] * 2 + 20;
        else
            Graph1Data[i] = 0;
    }
    //
}
void PrepareGraph2ForPlot(fType ftype){
    if (ftype == ftReal)
    {
        for (int i = 0; i < (SIGNAL_FFT_LENGTH/2); i++){
            if (signal1FR[i] > -20)
                Graph2Data[i] = signal1FR[i]  + 20;
            else
                Graph2Data[i] = 0;
        }
    }
    else if (ftype == ftAbs)
    {
        for (int i = 0; i < (SIGNAL_FFT_LENGTH/2); i++){
                Graph2Data[i] = 0.001*signal1FA[i];
        }
    }
    else if (ftype == ftPeriodogram)
    {
        for (int i = 0; i < (SIGNAL_FFT_LENGTH/2); i++){
            Graph2Data[i] = signal1FPRDGRM[i];
        }
    }
    else if (ftype == ftARMA)
    {
        for (int i = 0; i < (SIGNAL_FFT_LENGTH/2); i++){
            Graph2Data[i] = spectrumEstimate[i]*10.0f;
        }
    }
}

float sAc[]  = {1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 1, 2 ,3 ,4, 3, 2, 1, 2, 3, 4, 3, 2, 1, 2, 3, 2 ,1 ,2};

void Process1(){
    //filterSignal(signal1, signal2, F1, SIGNAL_LENGTH, 7);
    PrepareGraph1ForPlot();}

void Process2(fType ftype)
{
    switch (ftype) {
        case ftReal:
            DFT(signal1, signal1FR, signal1FI, SIGNAL_FFT_LENGTH);
            break;
        case ftAbs:
            DFT(signal1, signal1FR, signal1FI, SIGNAL_FFT_LENGTH);
            ABS(signal1FR, signal1FI, signal1FA, SIGNAL_FFT_LENGTH);
            break;
        case ftPeriodogram:
            DFT(signal1, signal1FR, signal1FI, SIGNAL_FFT_LENGTH);
            ABS(signal1FR, signal1FI, signal1FA, SIGNAL_FFT_LENGTH);
            PeridogramCalc(signal1FA, signal1FPRDGRM, SIGNAL_FFT_LENGTH);
            break;
        case ftARMA:
            EstimateARMASpectrum(signal1, autoCorr, aCoeff, spectrumEstimate, SIGNAL_LENGTH, 16, errorHistory);
            //EstimateARMASpectrum(sAc, autoCorr, aCoeff, spectrumEstimate, 28, 3, errorHistory);
            break;
            
        default:
            break;
    }
    PrepareGraph2ForPlot(ftype);
}



float f1[] = {0.3, 0.4, 0.3};
float s1[] = {0.1, 0.5, 0.1, 0.5, 0.1, 0.5, 0.1, 0.5};
float s2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float s3[] = {1.0, 2.0, 3.0, 4.0};
float s3FR[] = {0.0, 0.0, 0.0, 0.0};
float s3FI[] = {0.0, 0.0, 0.0, 0.0};


float rVal[]  = {8, 5, 4, 3, 2, 1, 0, 0, 0, 0};
float ap[]    = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float error[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float c[]     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float A[10][10];

//
void TestREstimate()
{
    
    EstimateARMASpectrum(sAc, autoCorr, aCoeff, spectrumEstimate, 28, 3, errorHistory);
    
    EstimateAutoCorrelationValues(sAc, rVal, 4, 3);
    A[0][0] =  1;A[0][1] = -1;A[0][2] =  2;A[0][3] = -1;A[0][4] = 3;
    A[1][0] =  1;A[1][1] =  1;A[1][2] =  1;A[1][3] =  1;A[1][4] = 1;
    A[2][0] = -1;A[2][1] =  2;A[2][2] =  4;A[2][3] = -1;A[2][4] = 0;
    A[3][0] =  0;A[3][1] =  2;A[3][2] =  0;A[3][3] =  1;A[3][4] = 2;
    A[4][0] =  3;A[4][1] =  4;A[4][2] =  1;A[4][3] =  0;A[4][4] = 2;
    c[0] = 16;
    c[1] = 15;
    c[2] = 11;
    c[3] = 18;
    c[4] = 24;
    float TotalError = RLS(A, c, ap, 5);
}

void TestCase1(){
    DFT(s3, s3FR, s3FI, 4);
    filterSignal(s1, s2, f1, 8, 3);
    TestREstimate();
}









