//
//  RestrictUserNumber.h
//  danceApp_V31
//
//  Created by Julia Eichler on 30.08.12.
//
//

#ifndef __danceApp_V31__RestrictUserNumber__
#define __danceApp_V31__RestrictUserNumber__

#include <iostream>

#include "ofMain.h"
#include "config.h"

#include "ofxScene.h"
#include "ofxAnimatableFloat.h"

#include "ofxCenteredTrueTypeFont.h"

class RestrictUserNumber : public ofxScene{
    
    
	void setup();
	void update(float dt);
	void draw();
    
	//scene notifications
	void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * toScreen );
    
    config                  config;
        
    // text
    ofxCenteredTrueTypeFont handwritten, handwritten2;
};


#endif /* defined(__danceApp_V31__RestrictUserNumber__) */
