//
//  InstructionScreenB.cpp
//  danceApp_V9
//
//  Created by Julia Eichler on 22.08.12.
//
//

#include "InstructionScreenB.h"

void InstructionScreenB::setup()
{
    image.loadImage("img/before_dancing-06.png");
    
    bisWaltz = false;
    playerVolume = 0.75f;
}


void InstructionScreenB::update(float dt)
{
    if(bisWaltz)
        playerVolume -= 0.0025f;
    else
        playerVolume = 0.75f;
}

void InstructionScreenB::draw()
{    
    float imageWidth = ofGetWindowHeight() * image.width / image.height;
    float xPos = ofGetWindowWidth()/2 - imageWidth/2;
    image.draw(xPos, 0, imageWidth, ofGetWindowHeight());
    
    // fade out sound
    if(bisWaltz) ofSoundSetVolume(playerVolume);
}

//scene notifications
// reset our scene when we appear
void InstructionScreenB::sceneWillAppear( ofxScene * fromScreen )
{
}

//scene notifications
void InstructionScreenB::sceneWillDisappear( ofxScene * toScreen )
{
    if(bisWaltz) ofSoundStopAll();
}

void InstructionScreenB::isWaltz()
{
    bisWaltz = true;
}