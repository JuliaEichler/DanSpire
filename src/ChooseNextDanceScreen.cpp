//
//  ChooseNextDanceScreen.cpp
//  danceApp_V23
//
//  Created by Julia Eichler on 25.08.12.
//
//

#include "ChooseNextDanceScreen.h"

//--------------------------------------------------------------
void ChooseNextDanceScreen::setup()
{
    image.loadImage("img/after_dancing-01.png");    
    
    // Circles
    circle.resize(4);
    
    circle[waltzDanceId].x = config.circleWaltzB.x;       circle[waltzDanceId].y = config.circleWaltzB.y;
    circle[salsaDanceId].x = config.circleSalsaB.x;       circle[salsaDanceId].y = config.circleSalsaB.y;
    circle[jiveDanceId].x  = config.circleJiveB.x;        circle[jiveDanceId].y  = config.circleJiveB.y;
    circle[cornerId].x     = config.circleCorner.x;       circle[cornerId].y     = config.circleCorner.y;
    
    radius = config.circleRadiusB;
    
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
    
    timer = 0;
}


//--------------------------------------------------------------
void ChooseNextDanceScreen::update(float dt)
{
    
}

//--------------------------------------------------------------
void ChooseNextDanceScreen::draw()
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
}

//--------------------------------------------------------------
void ChooseNextDanceScreen::checkUserPosition(int _currUserId, float _currUserPosX, float _currUserPosY, int _numberOfUsers)
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
            
            // start counting
            if(i == cornerId) timer++;
        }
        else
        {
            if(config.bdisplayUserData)
            {
                circle__info << "Circle " << ofToString(i) << ": outside - for user " << ofToString(n) << endl;
                ofDrawBitmapString(circle__info.str(), 10, 35+i*15 +n*50);
            }
            userCircleVote[i] = false; // doesn't vote for this circle
            
            // reset timer
            if(i == cornerId) timer = 0;
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
int ChooseNextDanceScreen::makeDanceSelection(int _numberOfUsers)
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
            ofSetColor(config.yellow);
            handwritten.drawStringCentered("Want to dance more?", ofGetWindowWidth()*0.47+2, ofGetWindowHeight()*0.25+2);
            ofSetColor(255);
            handwritten.drawStringCentered("Want to dance more?", ofGetWindowWidth()*0.47, ofGetWindowHeight()*0.25);
            ofPopMatrix();
            
            // stop all playing music
            ofSoundStopAll();
            break;
            
        case 1:
            // great you've chosed a dance
            playMusic(circleID);
            
            // wait some time for the users to decide
            int timePassed, timeLeft, delay;
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
                    
                case cornerId:
                    timePassed = (timer/config.fps)*1000 ; // frames to ms
                    break;
            }
            
            // add small delay
            delay = 2;
            
            // count down
            timeLeft = decisionTime+delay - (timePassed/1000);
            if(timeLeft <= decisionTime)
            {
                ofPushMatrix();
                ofRotateZ(353);
                ofSetColor(config.yellow);
                handwritten.drawStringCentered(ofToString(timeLeft), ofGetWindowWidth()/2-17, ofGetWindowHeight()*0.25+2);
                ofSetColor(255);
                handwritten.drawStringCentered(ofToString(timeLeft), ofGetWindowWidth()/2-20, ofGetWindowHeight()*0.25);
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
    if(numberOfUsers<1) ofSoundStopAll();
    
    // return
    return returnValue;
}

//--------------------------------------------------------------
void ChooseNextDanceScreen::playMusic(int songID)
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
void ChooseNextDanceScreen::sceneWillAppear( ofxScene * fromScreen )
{
    
}

//--------------------------------------------------------------
// scene notifications
void ChooseNextDanceScreen::sceneWillDisappear( ofxScene * toScreen )
{
    ofSoundStopAll();
    cout << "next dance screen -- stop all" << endl;
}
