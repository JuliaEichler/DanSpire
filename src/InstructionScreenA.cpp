//
//  InstructionScreenA.cpp
//  danceApp_V9
//
//  Created by Julia Eichler on 22.08.12.
//
//

#include "InstructionScreenA.h"

void InstructionScreenA::setup()
{
    image.loadImage("img/before_dancing-05.png");
}


void InstructionScreenA::update(float dt)
{
    
}

void InstructionScreenA::draw()
{
    float imageWidth = ofGetWindowHeight() * image.width / image.height;
    float xPos = ofGetWindowWidth()/2 - imageWidth/2;
    image.draw(xPos, 0, imageWidth, ofGetWindowHeight());
}

//scene notifications
// reset our scene when we appear
void InstructionScreenA::sceneWillAppear( ofxScene * fromScreen )
{
}

//scene notifications
void InstructionScreenA::sceneWillDisappear( ofxScene * toScreen )
{
    
}