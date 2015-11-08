//
//  Filters.cpp
//  VoiceRecordPlayObjectiveC
//
//  Created by Apple on 20/10/15.
//  Copyright (c) 2015 B. Lake. All rights reserved.
//

#include "Filters.h"



void filterSignal(float* input, float *output, float* filter, int signalsize, int filtersize){
    
    int temp = (filtersize - 1) / 2;
    float temp2 = 0;
    for (int i = temp; i < signalsize - temp; i++){
        temp2 = 0;
        for (int j = (-1*temp); j<=temp; j++){
            temp2 += (input[i + j] * filter[temp + j]);
        }
        output[i] = temp2;
    }
    
}