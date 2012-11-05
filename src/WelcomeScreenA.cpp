//
//  WelcomeScreenA.cpp
//  danceApp_V6
//
//  Created by Julia Eichler on 21.08.12.
//
//

#include "WelcomeScreenA.h"

void WelcomeScreenA::setup()
{
    welcomeImg.loadImage("img/before_dancing-01.png");
}


void WelcomeScreenA::update(float dt)
{
    
}

void WelcomeScreenA::draw()
{
    float imageWidth = ofGetWindowHeight() * welcomeImg.width / welcomeImg.height;
    float xPos = ofGetWindowWidth()/2 - imageWidth/2;
    welcomeImg.draw(xPos, 0, imageWidth, ofGetWindowHeight());
}

//scene notifications
// reset our scene when we appear
void WelcomeScreenA::sceneWillAppear( ofxScene * fromScreen )
{
    
}

//scene notifications
void WelcomeScreenA::sceneWillDisappear( ofxScene * toScreen )
{
    
}
