//
//  Filters.h
//  VoiceRecordPlayObjectiveC
//
//  Created by Apple on 20/10/15.
//  Copyright (c) 2015 B. Lake. All rights reserved.
//

#ifndef __VoiceRecordPlayObjectiveC__Filters__
#define __VoiceRecordPlayObjectiveC__Filters__

#include <stdio.h>



void filterSignal(float* input, float *output, float* filter, int signalsize, int filtersize);

#endif /* defined(__VoiceRecordPlayObjectiveC__Filters__) */
