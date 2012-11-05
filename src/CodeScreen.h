//
//  CodeScreen.h
//  danceApp_V31
//
//  Created by Julia Eichler on 30.08.12.
//
//

#ifndef __danceApp_V31__CodeScreen__
#define __danceApp_V31__CodeScreen__

#include <iostream>

#include "ofMain.h"
#include "config.h"

#include "ofxScene.h"
#include "ofxAnimatableFloat.h"

#include "ofxCenteredTrueTypeFont.h"

class CodeScreen : public ofxScene{
    
public:
    
    void setup();
    void update(float dt);
    void draw();
    
    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * toScreen );
    
    string generateCode();

    
    ofImage                 image;
    
    // text
    ofxCenteredTrueTypeFont font;
    
    config                  config;
    
    ofSerial                serial;
    unsigned char*          buf;
    string                  code;
};


#endif /* defined(__danceApp_V31__CodeScreen__) */
