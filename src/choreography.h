//
//  choreography.h
//  danceApp_V14
//
//  Created by Julia Eichler on 24.08.12.
//
//

#ifndef __danceApp_V25__Choreography__
#define __danceApp_V25__Choreography__

#include <iostream>

#pragma mark once

#include "ofMain.h"

class Choreography{
    
public:
    
    Choreography();
    
    vector< vector<int> > init(int x, int y, int width, int height, string type);
};

#endif /* defined(__danceApp_V25__Choreography__) */
