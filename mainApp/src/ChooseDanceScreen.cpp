//
//  ChooseDanceScreen.cpp
//  danceApp_V7
//
//  Created by Julia Eichler on 21.08.12.
//
//

#include "ChooseDanceScreen.h"

//--------------------------------------------------------------
void ChooseDanceScreen::setup()
{
    image.loadImage("img/before_dancing-03.png");
    
    // Circles
    circle.resize(3);
    circle[waltzDanceId].x = config.circleWaltzA.x;       circle[waltzDanceId].y = config.circleWaltzA.y;
    circle[salsaDanceId].x = config.circleSalsaA.x;       circle[salsaDanceId].y = config.circleSalsaA.y;
    circle[jiveDanceId].x  = config.circleJiveA.x;        circle[jiveDanceId].y  = config.circleJiveA.y;
    
    radius = config.circleRadiusA;
    
    userCircleVote.resize(circle.size());
    
    // Players
    salsa.loadSound("sounds/Salsa_music.mp3");
    salsa.setVolume(0.75f);
    salsa.setMultiPlay(false);
    waltz.loadSound("sounds/Waltz_music.mp3");
    waltz.setVolume(0.75f);
    waltz.setMultiPlay(false);
    jive.loadSound("sounds/Jive_music.mp3");
    jive.setVolume(0.75f);
    jive.setMultiPlay(false);
    
    // Text
    font.loadFont("fonts/Carton-Slab.otf", 32);
    handwritten.loadFont("fonts/Mission-Script.otf", 92);
    
    timeLeft = 100; // set random high value for start up
}


//--------------------------------------------------------------
void ChooseDanceScreen::update(float dt)
{
    
}

//--------------------------------------------------------------
void ChooseDanceScreen::draw()
{
    // background image
    float imageWidth = ofGetWindowHeight() * image.width / image.height;
    float xPos = ofGetWindowWidth()/2 - imageWidth/2;
    image.draw(xPos, 0, imageWidth, ofGetWindowHeight());
    
    // danceType circles
    ofSetColor(255, 255, 255, 0);       if(config.bdisplayUserData) ofSetColor(255, 255, 255, 170);
    for(int i=0; i<circle.size(); i++) {
        ofCircle(circle[i].x, circle[i].y, radius);
    }
    
    ofPushMatrix();
    ofRotateZ(353);
    ofSetColor(config.pink);
    handwritten.drawStringCentered("Choose one dance!", ofGetWindowWidth()*0.43+2, ofGetWindowHeight()*0.9+2);
    ofSetColor(255);
    handwritten.drawStringCentered("Choose one dance!", ofGetWindowWidth()*0.43, ofGetWindowHeight()*0.9);
    ofPopMatrix();
}

//--------------------------------------------------------------
void ChooseDanceScreen::checkUserPosition(int _currUserId, float _currUserPosX, float _currUserPosY, int _numberOfUsers)
{
    // PARAMETERS ---------------------------------------------------------
    int n = _currUserId;
    float posX = _currUserPosX;
    float posY = _currUserPosY;
    numberOfUsers = _numberOfUsers;
    
    // CHECK WHETHER IN CIRCLE AND IF SO PLAY SONG ------------------------
    insideCircleId.resize(numberOfUsers);
    
    for(int i=0; i < circle.size(); i++)
    {
        float dist = ofDist(posX, posY, circle[i].x, circle[i].y);
        int offset = 0; // radius*20/100
        
        stringstream circle__info;
        if(dist < radius+offset)
        {
            if(config.bdisplayUserData)
            {
                circle__info << "Circle " << ofToString(i) << ": inside  - for user " << ofToString(n) << endl;
                ofDrawBitmapString(circle__info.str(), 10, 35+i*15 +n*50);
            }
            userCircleVote[i] = true;   // votes for this circle
        }
        else
        {
            if(config.bdisplayUserData)
            {
                circle__info << "Circle " << ofToString(i) << ": outside - for user " << ofToString(n) << endl;
                ofDrawBitmapString(circle__info.str(), 10, 35+i*15 +n*50);
            }
            userCircleVote[i] = false; // doesn't vote for this circle
        }
    }
    
    // store user's vote
    insideCircleId[n] = 100;    // default value 100 - no vote
    for(int i=0; i<circle.size(); i++)
    {
        if(userCircleVote[i]) insideCircleId[n] = i;
    }
    
}

//--------------------------------------------------------------
int ChooseDanceScreen::makeDanceSelection(int _numberOfUsers)
{
    int returnValue = 404;
    
    // PARAMETERS ---------------------------------------------------------
    numberOfUsers   = _numberOfUsers;
    decisionTime    = config.decisionTime;
    
    // WHICH MUSIC SHOULD BE PLAYED? --------------------------------------
    // check votes for every user and create stats
    vector<int> circleVotes(circle.size());
    //cout << ofToString(insideCircleId) << " by " << ofToString(numberOfUser) << endl;
    for(int n=0; n<numberOfUsers; n++)
    {
        if(insideCircleId[n] != 100) circleVotes[insideCircleId[n]] += 1;
    }
    //cout << ofToString(circleVotes) << endl;
    
    // check which cirlce won
    int maxVotes = 0;
    int circleID = 100;
    for(int j=0; j<circleVotes.size(); j++)
    {
        if(circleVotes[j] > maxVotes)
        {
            maxVotes = circleVotes[j];
            circleID = j;
        }
    }
    // How often is maxValue in circleVotes?
    int equalVotes = 0;
    for(int j=0; j<circleVotes.size(); j++)
    {
        if(maxVotes != 0 && circleVotes[j] == maxVotes) equalVotes++;
    }
    //cout << circleID << " with " << maxVotes << " - (" << equalVotes << ")" << endl;
    
    switch (equalVotes) {
        case 0:
            // you need to decide!
            ofPushMatrix();
            ofRotateZ(353);
            ofSetColor(config.pink);
            handwritten.drawStringCentered("Choose one dance!", ofGetWindowWidth()*0.43+2, ofGetWindowHeight()*0.9+2);
            ofSetColor(255);
            handwritten.drawStringCentered("Choose one dance!", ofGetWindowWidth()*0.43, ofGetWindowHeight()*0.9);
            ofPopMatrix();
            
            // stop all playing music
            ofSoundStopAll();
            break;
            
        case 1:
            // great you've chosed a dance
            playMusic(circleID);
            
            // wait some time for the users to decide
            switch (circleID) {
                case waltzDanceId:
                    timePassed = waltz.getPositionMS();
                    break;
                    
                case jiveDanceId:
                    timePassed = jive.getPositionMS();
                    break;
                    
                case salsaDanceId:
                    timePassed = salsa.getPositionMS();
                    break;
            }
            
            // add small delay
            delay = 2;
            
            // count down
            timeLeft = decisionTime+delay - (timePassed/1000);
            if(timeLeft <= decisionTime)
            {
                //font.drawStringCentered(ofToString(timeLeft), ofGetWindowWidth()/2, ofGetWindowHeight()*1/7);
                ofPushMatrix();
                ofRotateZ(353);
                ofSetColor(config.pink);
                handwritten.drawStringCentered(ofToString(timeLeft), ofGetWindowWidth()/2-17, ofGetWindowHeight()/4+2);
                ofSetColor(255);
                handwritten.drawStringCentered(ofToString(timeLeft), ofGetWindowWidth()/2-20, ofGetWindowHeight()/4);
                ofPopMatrix();
            }
            if(timeLeft == 0)
            {
                //cout << "over" << endl;
                returnValue = circleID;
            }
            
            break;
            
        default:
            // in all other cases
            // you need to come to an agreement
                        
            // stop all playing music
            ofSoundStopAll();
            break;
    }
    
    // stop music if user disappeared without leaving the circle
    // but continue playing when this happened at countdown 0 and despite of that send danceId -- semi bug fix
    if(numberOfUsers<1 && timeLeft <= 1){
        returnValue = circleID;
    }else if(numberOfUsers<1 && timeLeft > 0){
        ofSoundStopAll();
    }
    
    // return
    return returnValue;
}

//--------------------------------------------------------------
void ChooseDanceScreen::playMusic(int songID)
{
    // check if it's the currently chosen song that's being played
    // if not, stop the playback
    int playingSongId = 100;
    if(waltz.getIsPlaying())    playingSongId = waltzDanceId;
    if(jive.getIsPlaying())     playingSongId = jiveDanceId;
    if(salsa.getIsPlaying())    playingSongId = salsaDanceId;
    if(songID != playingSongId) ofSoundStopAll();
    
    // play the currently chosen song
    if(!salsa.getIsPlaying() && !waltz.getIsPlaying() && !jive.getIsPlaying())
    {
        switch (songID) {
            case waltzDanceId:
                salsa.stop();
                jive.stop();
                waltz.play();
                break;
                
            case jiveDanceId:
                salsa.stop();
                waltz.stop();
                jive.play();
                break;
                
            case salsaDanceId:
                jive.stop();
                waltz.stop();
                salsa.play();
                break;
        }
    }
}

//--------------------------------------------------------------
// scene notifications
// reset our scene when we appear
void ChooseDanceScreen::sceneWillAppear( ofxScene * fromScreen )
{
    
}

//--------------------------------------------------------------
// scene notifications
void ChooseDanceScreen::sceneWillDisappear( ofxScene * toScreen )
{
    
}
