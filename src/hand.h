//
//  Hand.h
//  danceApp_V25
//
//  Created by Julia Eichler on 26.08.12.
//
//

#ifndef __danceApp_V25__Hand__
#define __danceApp_V25__Hand__

#include <iostream>

#pragma mark once

#include "ofMain.h"

class Hand{
    
public:
    
    Hand(float _xpos, float _ypos, char _side, char _gender, int _size);
    
    ofColor     color;
    ofVec2f     position;
    char        side, gender;
    int         size;
    
    ofImage     handShape;
};

#endif /* defined(__danceApp_V25__Hand__) */
