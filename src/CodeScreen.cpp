//
//  CodeScreen.cpp
//  danceApp_V31
//
//  Created by Julia Eichler on 30.08.12.
//
//

#include "CodeScreen.h"

void CodeScreen::setup()
{
    image.loadImage("img/after_dancing-03.png");
    
    font.loadFont("fonts/Carton-Slab.otf", 36);
    
    // SERIAL --------------------------------------------------
    serial.setup("/dev/tty.usbserial-A100RZK8", 9600);
    serial.flush();
}


void CodeScreen::update(float dt)
{
}

void CodeScreen::draw()
{
    float imageWidth = ofGetWindowHeight() * image.width / image.height;
    float xPos = ofGetWindowWidth()/2 - imageWidth/2;
    image.draw(xPos, 0, imageWidth, ofGetWindowHeight());
    
    
    // CODE ---------------------------------------------------
    // retrieve
    buf = new unsigned char[7];
    serial.readBytes(buf, 7);
    if(code == "") code = ofToString(buf);
    if(code == "") code = generateCode();

    // display
    ofPushMatrix();
    ofRotateZ(350);
    ofSetColor(config.pink);
    font.drawStringCentered(code, ofGetWindowWidth()*0.46-17, ofGetWindowHeight()*0.8+2);
    ofSetColor(255);
    font.drawStringCentered(code, ofGetWindowWidth()*0.46-20, ofGetWindowHeight()*0.8);
    ofPopMatrix();
}

//scene notifications
// reset our scene when we appear
void CodeScreen::sceneWillAppear( ofxScene * fromScreen )
{
    code = "";
}

//scene notifications
void CodeScreen::sceneWillDisappear( ofxScene * toScreen )
{
    
}

string CodeScreen::generateCode(){
    char $code[7];
    time_t now = time(NULL);
	struct tm *ts2 = localtime(&now);
	//strftime($code, sizeof($code), "%H%M-%d", ts2);
    strftime($code, sizeof($code), "%H%M", ts2);
    cout << $code << endl;
    string genCode = string($code);
    
    return genCode;
}