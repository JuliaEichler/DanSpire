//
//  WelcomeScreenB.cpp
//  danceApp_V6
//
//  Created by Julia Eichler on 21.08.12.
//
//

#include "WelcomeScreenB.h"

void WelcomeScreenB::setup()
{
    welcomeImg.loadImage("img/before_dancing-02.png");
}


void WelcomeScreenB::update(float dt)
{
    
}

void WelcomeScreenB::draw()
{
    float imageWidth = ofGetWindowHeight() * welcomeImg.width / welcomeImg.height;
    float xPos = ofGetWindowWidth()/2 - imageWidth/2;
    welcomeImg.draw(xPos, 0, imageWidth, ofGetWindowHeight());
}

//scene notifications
// reset our scene when we appear
void WelcomeScreenB::sceneWillAppear( ofxScene * fromScreen )
{
    
}

//scene notifications
void WelcomeScreenB::sceneWillDisappear( ofxScene * toScreen )
{
    
}
