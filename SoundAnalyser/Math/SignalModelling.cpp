//
//  SignalModelling.cpp
//  SoundAnalyser
//
//  Created by Apple on 03/11/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#include "SignalModelling.hpp"
#include "Vectors.hpp"
#include <math.h>
const float PI = 3.14159265359;

void EstimateAutoCorrelationValues(float* inputSignal, float* outAutoCorrelation, int signalLength, int autoCorrelationDepth)
{
    float temp = 0;
    for (int k = 0; k <= autoCorrelationDepth; k++) {
        temp = 0;
        for (int t = 0; t < (signalLength - k); t++) {
            temp += inputSignal[t] * inputSignal[t+k];
            outAutoCorrelation[k] = temp / (float)(signalLength - k);
        }
    }
}

float RLS(float A[10][10], float* c, float* ap, int order ){
    float error[50];
    float mu = 0.05;
    for (int i = 0; i < 500; i++) {
        for (int k = 0; k < order; k++) {
            error[k] = vectormult(A[k],ap,order) - c[k];
        }
        for (int k = 0; k < order; k++) {
            ap[k] -= mu * vectormult(A[k],error,order);
        }
        
    }
    return vectormult(error, error, 5); // Total Error
}

float R[20][20];
float r[20];
float errorT[20];
void EstimateARMASpectrum(float* inputSignal, float* autoCorrEst, float*aCoeffEst, float* spectrumEstimate,
                          int signalLength, int modelOrder, float* errorHistory)
{
    
    EstimateAutoCorrelationValues(inputSignal, autoCorrEst, signalLength, modelOrder);
    
    // Zeroise aCoeffEst coeffs
    for (int k = 0; k < modelOrder; k++) {
        aCoeffEst[k] = 0;
    }
    // Costruct A
    for (int k = 0; k < modelOrder; k++) {
        for (int i = 0; i < (modelOrder - k); i++) {
            R[k][i + k] = autoCorrEst[i];
        }
        for (int i = 0; i < k; i++) {
            R[k][i] = autoCorrEst[k-i];
        }
        
    }
    // Construct c
    for (int k = 0; k < modelOrder; k++) {
        r[k] = autoCorrEst[k+1];
    }
    //
    float mu = 0.001;
    for (int i = 0; i < 500; i++) {
        for (int k = 0; k < modelOrder; k++) {
            errorT[k] = vectormult(R[k], aCoeffEst, modelOrder) - r[k];
        }
        for (int k = 0; k < modelOrder; k++) {
            aCoeffEst[k] -= mu * vectormult(R[k],errorT, modelOrder);
        }
        errorHistory[i] = vectormult(errorT, errorT, modelOrder); // Total Error
    }
    //
    //construct spectrumEstimate
    float w, temp;
    float realPart;
    float imagPart;
    for (int i = 0; i < 512; i++) {
        w = i * 1.0 * PI / 512.0f;
        realPart = 0;
        imagPart = 0;
        for (int k = 0; k < modelOrder; k++) {
            realPart += aCoeffEst[k] * cos(w * k);
            imagPart += -1 * aCoeffEst[k] * sin(w * k);
        }
        temp = (1 + realPart) * (1 + realPart) + (imagPart * imagPart);
        spectrumEstimate[i] = 1.0f / sqrtf(temp);
    }
    
    
}

