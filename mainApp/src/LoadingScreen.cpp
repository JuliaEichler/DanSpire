//
//  LoadingScreen.cpp
//  danceApp_V9
//
//  Created by Julia Eichler on 22.08.12.
//
//

#include "LoadingScreen.h"

void LoadingScreen::setup()
{
    image.loadImage("img/before_dancing-04.png");
}


void LoadingScreen::update(float dt)
{
    
}

void LoadingScreen::draw()
{
    float imageWidth = ofGetWindowHeight() * image.width / image.height;
    float xPos = ofGetWindowWidth()/2 - imageWidth/2;
    image.draw(xPos, 0, imageWidth, ofGetWindowHeight());
}

//scene notifications
// reset our scene when we appear
void LoadingScreen::sceneWillAppear( ofxScene * fromScreen )
{
}

//scene notifications
void LoadingScreen::sceneWillDisappear( ofxScene * toScreen )
{
    
}