//
//  KioskScreen.cpp
//  danceApp_V23
//
//  Created by Julia Eichler on 25.08.12.
//
//

#include "KioskScreen.h"

void KioskScreen::setup()
{
    image.loadImage("img/after_dancing-02.png");
}


void KioskScreen::update(float dt)
{
}

void KioskScreen::draw()
{
    float imageWidth = ofGetWindowHeight() * image.width / image.height;
    float xPos = ofGetWindowWidth()/2 - imageWidth/2;
    image.draw(xPos, 0, imageWidth, ofGetWindowHeight());
}

//scene notifications
// reset our scene when we appear
void KioskScreen::sceneWillAppear( ofxScene * fromScreen )
{
}

//scene notifications
void KioskScreen::sceneWillDisappear( ofxScene * toScreen )
{
    
}