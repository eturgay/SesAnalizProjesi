//
//  SignalModelling.hpp
//  SoundAnalyser
//
//  Created by Apple on 03/11/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#ifndef SignalModelling_hpp
#define SignalModelling_hpp

#include <stdio.h>

void EstimateAutoCorrelationValues(float* inputSignal, float* outAutoCorrelation, int signalLength, int autoCorrelationDepth);
float RLS(float A[10][10], float* c, float* ap, int order);
void EstimateARMASpectrum(float* inputSignal , float* autoCorrEst, float*acoeffEst, float* spectrumestimate,
                                                         int signalLength, int modelOrder, float* errorhistory);

#endif /* SignalModelling_hpp */
