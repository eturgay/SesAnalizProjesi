//
//  Fft.hpp
//  VoiceRecordPlayObjectiveC
//
//  Created by Apple on 31/10/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#ifndef FftImplementations_hpp
#define FftImplementations_hpp

#include <stdio.h>


// Straightforward implementation of DFT formula - will be used to double chck FFT
void DFT(float* input, float* outputReal, float* outputImaginer, int N);
void FFT(float* input, float* outputReal, float* outputImaginer, int N);
void ABS(float* inputR, float* inputI, float* outputAbs, int N);
void PeridogramCalc(float* inputAbs, float* outputPrd, int N);

#endif /* FftImplementations_hpp */
