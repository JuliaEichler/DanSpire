//
//  RestrictUserNumber.cpp
//  danceApp_V31
//
//  Created by Julia Eichler on 30.08.12.
//
//

#include "RestrictUserNumber.h"

void RestrictUserNumber::setup()
{
    // Text
    handwritten.loadFont("fonts/Mission-Script.otf", 92);
    handwritten2.loadFont("fonts/Mission-Script.otf", 70);
}


void RestrictUserNumber::update(float dt)
{
    
}

void RestrictUserNumber::draw()
{
    ofPushMatrix();
    ofRotateZ(353);
    ofSetColor(config.blue);
    handwritten.drawStringCentered("Oh sorry!", ofGetWindowWidth()*0.45+2, ofGetWindowHeight()*0.4+2);
    ofSetColor(255);
    handwritten.drawStringCentered("Oh sorry!", ofGetWindowWidth()*0.45, ofGetWindowHeight()*0.4);
    
    ofSetColor(config.blue);
    handwritten2.drawStringCentered("Until now there's", ofGetWindowWidth()*0.45+2, ofGetWindowHeight()*0.65+2);
    ofSetColor(255);
    handwritten2.drawStringCentered("Until now there's", ofGetWindowWidth()*0.45, ofGetWindowHeight()*0.65);
    
    ofSetColor(config.blue);
    handwritten2.drawStringCentered("only space for 4.", ofGetWindowWidth()*0.45+2, ofGetWindowHeight()*0.8+2);
    ofSetColor(255);
    handwritten2.drawStringCentered("only space for 4.", ofGetWindowWidth()*0.45, ofGetWindowHeight()*0.8);
    ofPopMatrix();
}

//scene notifications
// reset our scene when we appear
void RestrictUserNumber::sceneWillAppear( ofxScene * fromScreen )
{
    
}

//scene notifications
void RestrictUserNumber::sceneWillDisappear( ofxScene * toScreen )
{
    
}
