//
//  config.h
//  danceApp_V8
//
//  Created by Julia Eichler on 22.08.12.
//
//

#ifndef __danceApp_V8__config__
#define __danceApp_V8__config__

#include <iostream>

#include "ofMain.h"

class config{
    
    public:
        
        config();
        
        bool                bdisplayUserData;
        bool                bmultiWindow;
    
        int                 decisionTime;
        int                 slideShowDuration; // visibility per slide in sec
        int                 latencySlide;
    
        static const int    salsaDanceId = 0;
        static const int    jiveDanceId  = 1;
        static const int    waltzDanceId = 2;
        static const int    cornerId     = 3;
    
        int                 mainWindowWidth, mainWindowHeight;
        int                 rotateZ;
        int                 fps;
    
        int                 iconSize, iconDistance;
        int                 distanceFeet;
        int                 distanceMoveSalsa, distanceMoveJive, distanceMoveWaltz;
        int                 distanceMoveTwoSalsa, distanceMoveTwoJive, distanceMoveTwoWaltz;
    
        ofColor             pink, yellow, blue;
    
        ofVec2f             circleWaltzA, circleWaltzB;
        ofVec2f             circleSalsaA, circleSalsaB;
        ofVec2f             circleJiveA, circleJiveB;
        ofVec2f             circleCorner;
        int                 circleRadiusA, circleRadiusB;
};

#endif /* defined(__danceApp_V8__config__) */
