#include "videoApp.h"

void videoApp::setup()
{
    ofSetDataPathRoot("../Resources/data/");
    
    //serial.setup("/dev/tty.usbmodemfd141", 9600);
    //serial.setup("/dev/tty.usbmodemfa131", 9600);
    serial.setup("/dev/tty.usbmodem1a21", 9600);
    serial.flush();
    byte = 0;
    
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    
    screenHeight = float(ofGetScreenHeight());
    salsa.loadMovie("Salsa.mp4");
    jive.loadMovie("Jive.mp4");
    waltz.loadMovie("Waltz.mp4");
    
    movieWidth = ofGetWindowWidth();
    movieHeight = ofGetWindowHeight();
    
    logo.loadImage("logo_screen.png");
}

void videoApp::update()
{
	salsa.idleMovie();
    jive.idleMovie();
    waltz.idleMovie();
}

void videoApp::draw()
{
    // LOGO ---------------------------------
    logoWidth = ofGetWindowWidth()/2;
    logoHeight = logoWidth * logo.height / logo.width;
    logo.draw(ofGetWindowWidth()/2-logoWidth/2, ofGetWindowHeight()/2-logoHeight/2, logoWidth, logoHeight);
    
    // SERIAL -------------------------------
    byte = serial.readByte();
    if ( byte == OF_SERIAL_NO_DATA )
        cout << "no data was read" << endl;
    else if ( byte == OF_SERIAL_ERROR )
        cout << "an error occurred" << endl;
    else
        cout << "myByte is " << byte << endl;
    
    if(byte == 10 && !salsa.isPlaying())
    {
        jive.stop();
        waltz.stop();
        salsa.play();
    }
    if(byte == 11 && !jive.isPlaying())
    {
        salsa.stop();
        waltz.stop();
        jive.play();
    }
    if(byte == 12 && !waltz.isPlaying())
    {
        salsa.stop();
        jive.stop();
        waltz.play();
    }
    if(byte == 255)
    {
        salsa.stop();
        jive.stop();
        waltz.stop();
    }
    
    if(salsa.isPlaying())   salsa.draw(0, 0, movieWidth, movieHeight);
    if(jive.isPlaying())    jive.draw( 0, 0, movieWidth, movieHeight);
    if(waltz.isPlaying())   waltz.draw(0, 0, movieWidth, movieHeight);
}


//--------------------------------------------------------------
void videoApp::keyPressed(int key) {
    if (key == 'F' || key == 'f')
    {
        ofToggleFullscreen();
    }
}