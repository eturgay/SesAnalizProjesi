//
//  Vectors.cpp
//  SoundAnalyser
//
//  Created by Apple on 04/11/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#include "Vectors.hpp"

float vectormult(float* a, float* b, int length){
    float temp = 0;
    for (int i = 0; i < length; i++) {
        temp += (a[i] * b[i]);
    }
    return temp;
}
