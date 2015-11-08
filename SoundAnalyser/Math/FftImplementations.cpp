//
//  Fft.cpp
//  VoiceRecordPlayObjectiveC
//
//  Created by Apple on 31/10/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#include "FftImplementations.hpp"
#include <math.h>
const float PI = 3.14159265359;

// Straightforward implementation of DFT formula - will be used to double chck FFT
void DFT(float* input, float* outputReal, float* outputImaginer, int N)
{
    float tempR, tempI;
    float tetaN = -2 * PI / N;
    for (int k = 0; k < N; k++)
    {
        tempR = 0;
        tempI = 0;
        for (int t = 0; t < N; t++)
        {
            tempR += input[t] * cosf(tetaN*t*k);
            tempI += input[t] * sinf(tetaN*t*k);
            
        }
        outputReal[k] = tempR;
        outputImaginer[k] = tempI;
        
    }
}
void ABS(float* inputR, float* inputI, float* outputAbs, int N)
{
    for (int k = 0; k < N; k++)
    {
        outputAbs[k] = (inputR[k] * inputR[k]) + (inputI[k] * inputI[k]);
        
    }
    
}

void PeridogramCalc(float* inputAbs, float* outputPrd, int N)
{
    for (int k = 0; k < N; k++)
    {
        outputPrd[k] = 0.8f * outputPrd[k] + 0.2f * inputAbs[k];
        
    }
    
}
void FFT(float* input, float* outputReal, float* outputImaginer, int N)
{
}
