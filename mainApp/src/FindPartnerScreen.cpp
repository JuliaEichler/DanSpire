//
//  FindPartnerScreen.cpp
//  danceApp_V39
//
//  Created by Julia Eichler on 02.09.12.
//
//

#include "FindPartnerScreen.h"

void FindPartnerScreen::setup()
{
    img.loadImage("img/before_dancing-08.png");
}


void FindPartnerScreen::update(float dt)
{
    
}

void FindPartnerScreen::draw()
{
    float imageWidth = ofGetWindowHeight() * img.width / img.height;
    float xPos = ofGetWindowWidth()/2 - imageWidth/2;
    img.draw(xPos, 0, imageWidth, ofGetWindowHeight());
}

//scene notifications
// reset our scene when we appear
void FindPartnerScreen::sceneWillAppear( ofxScene * fromScreen )
{
    
}

//scene notifications
void FindPartnerScreen::sceneWillDisappear( ofxScene * toScreen )
{
    
}
