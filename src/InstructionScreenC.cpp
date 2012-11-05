//
//  InstructionScreenC.cpp
//  danceApp_V9
//
//  Created by Julia Eichler on 22.08.12.
//
//

#include "InstructionScreenC.h"

void InstructionScreenC::setup()
{
    image.loadImage("img/before_dancing-07.png");
    
    playerVolume = 0.75f;
}


void InstructionScreenC::update(float dt)
{
    // fade out sound
    playerVolume -= 0.0025f;
}

void InstructionScreenC::draw()
{
    float imageWidth = ofGetWindowHeight() * image.width / image.height;
    float xPos = ofGetWindowWidth()/2 - imageWidth/2;
    image.draw(xPos, 0, imageWidth, ofGetWindowHeight());
    
    // fade out sound
    ofSoundSetVolume(playerVolume);
}

//scene notifications
// reset our scene when we appear
void InstructionScreenC::sceneWillAppear( ofxScene * fromScreen )
{
}

//scene notifications
void InstructionScreenC::sceneWillDisappear( ofxScene * toScreen )
{
    ofSoundStopAll();
    cout << "instruction c - stop all" << endl;
}