//
//  config.cpp
//  danceApp_V8
//
//  Created by Julia Eichler on 22.08.12.
//
//

#include "config.h"
#include "ofMain.h"

config::config() {
    bdisplayUserData        = false;
    bmultiWindow            = false;
    
    // timing
    decisionTime            = 5;
    slideShowDuration       = 8;
    latencySlide            = 3;
    
    // presets
    mainWindowWidth         = 1024;
    mainWindowHeight        = 768;
    
    // rotation
    rotateZ                 = 270;
    
    fps                     = 60;
    
    // sizes
    iconSize                = 25;
    iconDistance            = 60;
    distanceFeet            = 70/2;
    distanceMoveSalsa       = 140;
    distanceMoveJive        = 65;
    distanceMoveWaltz       = 60;
    distanceMoveTwoSalsa    = 140;
    distanceMoveTwoJive     = 110;
    distanceMoveTwoWaltz    = 60;
    
    
    // <-- declaration of dance IDs in config.h
    
    pink.r   = 239;     pink.g   =  61;     pink.b   = 111;
    yellow.r = 240;     yellow.g = 230;     yellow.b =   8;
    blue.r   = 110;     blue.g   = 200;     blue.b   = 200;
    
    /*
    // Circles
    circleWaltzA.x = 251;       circleWaltzA.y = 198;
    circleSalsaA.x = 516;       circleSalsaA.y = 423;
    circleJiveA.x  = 762;        circleJiveA.y = 189;
    circleRadiusA  = 155;
    
    circleWaltzB.x = 228;       circleWaltzB.y = 452;
    circleSalsaB.x = 519;       circleSalsaB.y = 390;
    circleJiveB.x  = 809;       circleJiveB.y  = 325;
    circleCorner.x = 860;       circleCorner.y = 655;
    circleRadiusB = 140;
     */
    // Circles
    circleWaltzA.x = 430;       circleWaltzA.y = 198;
    circleSalsaA.x = 290;       circleSalsaA.y = 423;
    circleJiveA.x  = 100;        circleJiveA.y = 200;
    circleRadiusA  = 120;
    
    circleWaltzB.x = 540;       circleWaltzB.y = 452;
    circleSalsaB.x = 290;       circleSalsaB.y = 423;
    circleJiveB.x  =  60;       circleJiveB.y  = 370;
    circleCorner.x =  70;       circleCorner.y = 630;
    circleRadiusB = 110;

}