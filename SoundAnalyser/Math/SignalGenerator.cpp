//
//  SignalGenerater.cpp
//  SoundAnalyser
//
//  Created by Apple on 04/11/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#include "SignalGenerator.hpp"
#include "SignalDefinitions.h"
#include <math.h>
#include <random>

const float PI = 3.14159265359;

void GenerateSignals(float f1, float f2, float std)
{
    float dt = 1.0f / 8000.0f;
    for (int i = 0; i < SIGNAL_LENGTH; i++) {
        testSignalNoise[i] = float(rand() % 100000 - 50000)/50000.0f * std;
        testSignalDoubleSinus[i] = cosf(2 * PI * f1 * i * dt) + cosf(2 * PI * f2 * i * dt);;
        testSignalDoubleSinusInNoise[i] = testSignalDoubleSinus[i] + testSignalNoise[i];
    }
    
    for (int i = 5; i < SIGNAL_LENGTH; i++) {
        testSignalARMA[i] = testSignalNoise[i] - (0.6 * testSignalARMA[i-2] + 0.4 * testSignalARMA[i-4] + 0.5 * testSignalARMA[i-5]);
    }
    
}