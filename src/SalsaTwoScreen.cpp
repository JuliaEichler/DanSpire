//
//  SalsaTwoScreen.cpp
//  danceApp_V31
//
//  Created by Julia Eichler on 30.08.12.
//
//

#include "SalsaTwoScreen.h"


//--------------------------------------------------------------
void SalsaTwoScreen::setup()
{
    mainWindowWidth = config.mainWindowWidth;
    
    player.loadSound("sounds/Salsa_instructions.mp3");
    player.setVolume(0.75f);
    player.setMultiPlay(false);
    
    intervall1 = 800; // in ms
    intervall1 = roundUp(intervall1/100);
    intervall2 = 500; // quicker
    intervall2 = roundUp(intervall2/100);
    
    startPlayerPos_R1   =  23000;   // individual
    stopPlayerPos_R1    =  41800;
    startPlayerPos_R2   =  47500;   // move forwards
    stopPlayerPos_R2    =  64999;
    startPlayerPos_R3   =  65000;   // partner
    stopPlayerPos_R3    =  90000;
    startPlayerPos_R4   =  90001;   // faster
    stopPlayerPos_R4    = 112800;
    startPlayerPos_R1 = roundUp(startPlayerPos_R1 /100);
    stopPlayerPos_R1  = roundUp(stopPlayerPos_R1  /100);
    startPlayerPos_R2 = roundUp(startPlayerPos_R2 /100);
    stopPlayerPos_R2  = roundUp(stopPlayerPos_R2  /100);
    startPlayerPos_R3 = roundUp(startPlayerPos_R3 /100);
    stopPlayerPos_R3  = roundUp(stopPlayerPos_R3  /100);
    startPlayerPos_R4 = roundUp(startPlayerPos_R4 /100);
    stopPlayerPos_R4  = roundUp(stopPlayerPos_R4  /100);
    
    prevPlayerPos = startPlayerPos_R1;
    
    // CHOREOGRAPHY --------------------------------------------
    currentStep = 0;
    isStart = true;
    
    boxWidth    = 0;
    boxHeight   = 300;
    role = salsaChoreo.init(0, 0, boxWidth, boxHeight, "Salsa");
    
    // position of each couple
    cX1 = config.mainWindowWidth/4-boxHeight/3;
    cY1 = config.mainWindowHeight/2;
    cX2 = config.mainWindowWidth*3/4-boxHeight+boxHeight/3;
    
    // lift icon - resize
    newIconSize = config.iconSize;
    biconWasBig = false;
}


//--------------------------------------------------------------
void SalsaTwoScreen::update(float dt)
{
    ofSoundUpdate();
}

//--------------------------------------------------------------
void SalsaTwoScreen::draw()
{
    currentPlayerPos = player.getPositionMS();
    
    if(player.getPosition() < 1.0)
    {
        currentPlayerPos = roundUp(currentPlayerPos/100);
        //cout << currentPlayerPos << endl;
        
        if(currentPlayerPos >= startPlayerPos_R1
           && currentPlayerPos <= stopPlayerPos_R1)
        {
            updateChoreoPosition(role, currentStep, true, true, false, false);
            
            if(prevPlayerPos+intervall1 >= currentPlayerPos-4
               && prevPlayerPos+intervall1 <= currentPlayerPos)
            {
                currentStep++;
                if(currentStep > 5) currentStep = 0;
                isStart = false;
                
                prevPlayerPos = currentPlayerPos;
                
                // reset history
                footPositions.clear();
            }
        }else if (currentPlayerPos >= stopPlayerPos_R1
                  && currentPlayerPos <= startPlayerPos_R2)
        {
            standardPosition(role, 5, cX1, cY1, cX2, cY1);
            
        }
        else if (currentPlayerPos >= startPlayerPos_R2
                 && currentPlayerPos <= stopPlayerPos_R2)
        {
            if(currentPlayerPos >= startPlayerPos_R2
               && currentPlayerPos <= startPlayerPos_R2+4)
            {
                standardPosition(role, 5, cX1, cY1, cX1, cY1);
                
                footPositions.clear();
            }
            if(currentPlayerPos >= startPlayerPos_R2
               && currentPlayerPos < startPlayerPos_R2+intervall1)
            {
                mStepA = 5;
                mStepB = 4;
                
                // leader 1
                ofPushMatrix();
                ofTranslate(cX1, cY1);
                ofRotateZ(config.rotateZ);
                mFootA = moveForwardsMaster(role, mStepA, 'm');
                ofPopMatrix();
                
                // follower 1
                ofPushMatrix();
                ofTranslate(cX2+boxHeight, cY1);
                ofRotateZ(config.rotateZ);
                moveForwardsSlave(mFootA, role, mStepA, 'f');
                ofPopMatrix();
            }
            if(currentPlayerPos >= startPlayerPos_R2+intervall1
               && currentPlayerPos <= startPlayerPos_R2+intervall1+4)
            {
                footPositions.clear();
            }
            if(currentPlayerPos >= startPlayerPos_R2+intervall1
               && currentPlayerPos < startPlayerPos_R2+intervall1+intervall1)
            {
                // leader 1
                ofPushMatrix();
                ofTranslate(cX1, cY1);
                ofRotateZ(config.rotateZ);
                Foot(mFootA.x, mFootA.y, getStepSide(role, mStepA), 'm', config.iconSize);  // right foot
                mFootB = moveForwardsMaster(role, mStepB, 'm');                             // left foot
                ofPopMatrix();
                
                // follower 1
                ofPushMatrix();
                ofTranslate(cX2, cY1);
                ofRotateZ(config.rotateZ);
                Foot(mFootA.x, mFootA.y-2*config.distanceMoveTwoSalsa, getStepSide(role, mStepA), 'f', config.iconSize); // left
                ofTranslate(0, boxHeight);
                moveForwardsSlave(mFootB, role, mStepB, 'f');                                                    // right
                ofPopMatrix();
            }
            if(currentPlayerPos >= startPlayerPos_R2+intervall1+intervall1)
            {
                // leader 1
                ofPushMatrix();
                ofTranslate(cX1, cY1);
                ofRotateZ(config.rotateZ);
                mGender = 'm';
                Foot(mFootA.x, mFootA.y, getStepSide(role, mStepA), mGender, config.iconSize);
                Foot(mFootB.x, mFootB.y, getStepSide(role, mStepB), mGender, config.iconSize);
                Hand(mFootA.x+180, mFootA.y+65, 'r', mGender, config.iconSize);
                Hand(mFootB.x-160, mFootB.y+50, 'l', mGender, config.iconSize);
                ofPopMatrix();
                
                // follower 1
                ofPushMatrix();
                ofTranslate(cX2, cY1);
                ofRotateZ(config.rotateZ);
                mGender = 'f';
                Foot(mFootA.x, mFootA.y-2*config.distanceMoveTwoSalsa, getStepSide(role, mStepA), mGender, config.iconSize);
                Foot(mFootB.x, mFootB.y-2*config.distanceMoveTwoSalsa, getStepSide(role, mStepB), mGender, config.iconSize);
                Hand(mFootA.x+180, mFootA.y-2*config.distanceMoveTwoSalsa-55, 'r', mGender, config.iconSize);
                Hand(mFootB.x-130, mFootB.y-2*config.distanceMoveTwoSalsa-80, 'l', mGender, config.iconSize);
                ofPopMatrix();
            }
        }
        else if(currentPlayerPos >= startPlayerPos_R3
                && currentPlayerPos <= stopPlayerPos_R3)
        {
            if(currentPlayerPos >= startPlayerPos_R3
               && currentPlayerPos <= startPlayerPos_R3+4)
            {
                prevPlayerPos = currentPlayerPos;
                currentStep = 0;
                footPositions.clear();
            }
            
            //cout << currentPlayerPos << " -> do " << currentStep << " :: prev " << positionPrev << " - curr " << positionCurr << " :: prevStep of side: " << previousSideStep << endl;
            
            updateChoreoPosition(role, currentStep, true, false, true, false);
            
            //cout << prevPlayerPos << " + " << intervall << " >=< " << currentPlayerPos << endl;
            if(prevPlayerPos+intervall1 >= currentPlayerPos-4
               && prevPlayerPos+intervall1 <= currentPlayerPos)
            {
                
                currentStep++;
                if(currentStep > 5) currentStep = 0;
                isStart = false;
                
                prevPlayerPos = currentPlayerPos;
                
                // reset history
                footPositions.clear();
            }
        }
        else if(currentPlayerPos >= startPlayerPos_R4
                && currentPlayerPos <= stopPlayerPos_R4)
        {
            if(currentPlayerPos >= startPlayerPos_R4
               && currentPlayerPos <= startPlayerPos_R4+4)
            {
                prevPlayerPos = currentPlayerPos;
                currentStep = 0;
                footPositions.clear();
            }
            
            //cout << currentPlayerPos << " -> do " << currentStep << " :: prev " << positionPrev << " - curr " << positionCurr << " :: prevStep of side: " << previousSideStep << endl;
            
            updateChoreoPosition(role, currentStep, true, false, true, false);
            
            //cout << prevPlayerPos << " + " << intervall << " >=< " << currentPlayerPos << endl;
            if(prevPlayerPos+intervall2 >= currentPlayerPos-4
               && prevPlayerPos+intervall2 <= currentPlayerPos)
            {
                
                currentStep++;
                if(currentStep > 5) currentStep = 0;
                isStart = false;
                
                prevPlayerPos = currentPlayerPos;
                
                // reset history
                footPositions.clear();
            }
        }
        else if(currentPlayerPos <= stopPlayerPos_R4
                && currentPlayerPos != 0)
        {
            standardPosition(role, 5, cX1, cY1, cX2, cY1);
        }
    }
}

//--------------------------------------------------------------
//scene notifications
// reset our scene when we appear
void SalsaTwoScreen::sceneWillAppear( ofxScene * fromScreen )
{
    ofSoundStopAll();
    ofSoundSetVolume(0.75);
    prevPlayerPos = startPlayerPos_R1;
    
    player.play();
}

//--------------------------------------------------------------
//scene notifications
void SalsaTwoScreen::sceneWillDisappear( ofxScene * toScreen )
{
    
}

//--------------------------------------------------------------
void SalsaTwoScreen::startSound()
{
    player.play();
    cout << "start player" << endl;
}


//--------------------------------------------------------------
int SalsaTwoScreen::getPlayerPositionMS()
{
    return player.getPositionMS();
}

//--------------------------------------------------------------
float SalsaTwoScreen::getPlayerPosition()
{
    return player.getPosition();
}

void SalsaTwoScreen::standardPosition(vector< vector<int> > choreo, int position, int x1, int y1, int x2, int y2)
{
    ofPushMatrix();
    ofTranslate(x1, y1);
    ofRotateZ(config.rotateZ);
    getChoreoPosition(position, 'm', true, choreo, true);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(x2, y1);
    ofRotateZ(config.rotateZ);
    getChoreoPosition(position, 'f', true, choreo, true);
    ofPopMatrix();
}

//--------------------------------------------------------------
void SalsaTwoScreen::getChoreoPosition(int step, char gender, bool displayPrevious, vector< vector<int> > choreo, bool bdisplayIcon)
{
    // CURRENT POSITION ----------------------------------------
    char side;
    if(choreo[step][2] == 0)
    {
        positionCurr.x = choreo[step][0]-config.distanceFeet;
        side = 'l';
    }
    else
    {
        positionCurr.x = choreo[step][0]+config.distanceFeet;
        side = 'r';
    }
    positionCurr.y = choreo[step][1];
    
    // DISPLAY STEP --------------------------------------------
    // set color
    ofSetColor(255);
    if(displayPrevious) ofSetColor(255, 127);
    
    Foot(positionCurr.x, positionCurr.y, side, gender, config.iconSize);
    
    int nextStep = step+2;
    if(nextStep == 6) nextStep = 0;
    if(nextStep == 7) nextStep = 1;
    
    if(bdisplayIcon) createIcon(positionCurr, choreo, nextStep, gender);
    
    // PREVIOUS STEP -------------------------------------------
    if(displayPrevious)
    {
        previousStep = step-1;
        if(previousStep == -1) previousStep = 5;
        getChoreoPosition(previousStep, gender, false, choreo, bdisplayIcon);
    }
}

//--------------------------------------------------------------
void SalsaTwoScreen::updateChoreoPosition(vector< vector<int> > choreo, int step, bool bdisplayPrevious, bool bdisplayIcon, bool bcloser, bool bbox)
{
    // CURRENT POSITION ------------------------
    char side;
    if(choreo[step][3] == 5)
    {
        
    }
    if(choreo[step][2] == 0)
    {
        positionCurr.x = choreo[step][0]-config.distanceFeet;
        side = 'l';
    }
    else
    {
        positionCurr.x = choreo[step][0]+config.distanceFeet;
        side = 'r';
    }
    positionCurr.y = choreo[step][1];
    
    
    // TWEEN ---------------------------------
    // determine previous position (origin of the transition)
    previousSideStep = step-2;
    if(previousSideStep == -2) previousSideStep = 4;
    if(previousSideStep == -1) previousSideStep = 5;
    
    // get position of previous step
    if(choreo[previousStep][2] == 0)
    {
        positionPrev.x = choreo[previousSideStep][0]-config.distanceFeet;
    }else{
        positionPrev.x = choreo[previousSideStep][0]+config.distanceFeet;
    }
    positionPrev.y = choreo[previousSideStep][1];
    
    // get distance
    int d=0;
    if(bcloser) d=config.distanceMoveTwoSalsa;
    
    // init master
    tweenPositionMaster(footPositions, positionUpdate, positionPrev, positionCurr, choreo, step, side, 'm', bdisplayIcon, false, bdisplayPrevious, false, bcloser);
    
    int alphaBox = 170;
    // leader 1
    ofPushMatrix();
    ofTranslate(cX1+d, cY1);
    ofRotateZ(config.rotateZ);
    if(bbox)
    {
        ofSetColor(255, alphaBox);
        ofNoFill();
        ofSetLineWidth(3);
        ofRect(0, 0, boxWidth, boxHeight);
        ofFill();
    }
    tweenPositionSlave(footPositions, positionUpdate, positionCurr, choreo, step, side, 'm', bdisplayIcon, bdisplayPrevious, false, bcloser);
    ofPopMatrix();
    
    // follower 1
    ofPushMatrix();
    ofTranslate(cX2-d, cY1);
    ofRotateZ(config.rotateZ);
    if(bbox)
    {
        ofSetColor(255, alphaBox);
        ofNoFill();
        ofSetLineWidth(3);
        ofRect(0, 0, boxWidth, boxHeight);
        ofFill();
    }
    tweenPositionSlave(footPositions, positionUpdate, positionCurr, choreo, step, side, 'f', bdisplayIcon, bdisplayPrevious, false, bcloser);
    ofPopMatrix();
}

//--------------------------------------------------------------
void SalsaTwoScreen::tweenPositionMaster(vector<ofVec2f> fP, ofVec2f posUpdate, ofVec2f positionPrev, ofVec2f positionCurr, vector< vector<int> > choreo, int step, char side, char gender, bool bdisplayIcon, bool bdisplayMaster, bool bdisplayPrevious, bool bmoveForward, bool bcloser)
{
    if(fP.size() == 0)
    {
        fP.resize(1);
        posUpdate = positionPrev;
    }
    if(posUpdate != positionCurr)
    {
        for(int i=0; i<fP.size()-1; i++)
        {
            fP[i] = fP[i+1];
        }
        fP.push_back(posUpdate);
        
        
        if(posUpdate.x < positionCurr.x)
        {
            posUpdate.x += 15;
            if(posUpdate.x > positionCurr.x) posUpdate.x = positionCurr.x;
        }
        else if(posUpdate.x > positionCurr.x)  {
            posUpdate.x -= 15;
            if(posUpdate.x < positionCurr.x) posUpdate.x = positionCurr.x;
        }
        
        if(posUpdate.y < positionCurr.y)
        {
            posUpdate.y += 15;
            if(posUpdate.y > positionCurr.y) posUpdate.y = positionCurr.y;
        }
        else if(posUpdate.y > positionCurr.y)
        {
            posUpdate.y -= 15;
            if(posUpdate.y < positionCurr.y) posUpdate.y = positionCurr.y;
        }
        
        
        int last = fP.size()-1;
        
        int distTotal = ofDist(positionPrev.x, positionPrev.y, positionCurr.x, positionCurr.y);
        int distUpdate = ofDist(fP.at(last).x, fP.at(last).y, positionCurr.x, positionCurr.y);
        int alpha = 255-255*distUpdate/distTotal;
        if(bmoveForward) alpha = 255;
        ofSetColor(255, 255, 255, alpha);
        
        if(bdisplayMaster)
        {
            Foot(fP.at(last).x, fP.at(last).y, side, gender, config.iconSize);
            
            if(bdisplayIcon) createIcon(fP, choreo, step, gender);
        }
    }
    else
    {
        if(bdisplayMaster)
        {
            // display step -----------------------------------------------------------------
            Foot(positionCurr.x, positionCurr.y, side, gender, config.iconSize);
            
            if(bdisplayIcon) createIcon(positionCurr, choreo, step, gender);
        }
    }
    
    if(bdisplayPrevious)
    {
        // PREVIOUS STEP --------------------------------------------
        previousStep = step-1;
        if(previousStep == -1) previousStep = 5;
        
        // get position
        ofVec2f previousStepPos;
        if(choreo[previousStep][2] == 0)
        {
            previousStepPos.x = choreo[previousStep][0]-config.distanceFeet;
            side = 'l';
        }
        else
        {
            previousStepPos.x = choreo[previousStep][0]+config.distanceFeet;
            side = 'r';
        }
        previousStepPos.y = choreo[previousStep][1];
        
        // display step
        ofSetColor(255, 127);
        if(bdisplayMaster) Foot(previousStepPos.x, previousStepPos.y, side, gender, config.iconSize);
        ofSetColor(255, 255);
    }
    
    // STORE values globally ----------------------------------
    footPositions       = fP;
    positionUpdate      = posUpdate;
}

//--------------------------------------------------------------
void SalsaTwoScreen::tweenPositionSlave(vector<ofVec2f> fP, ofVec2f posUpdate, ofVec2f positionCurr, vector< vector<int> > choreo, int step, char side, char gender, bool bdisplayIcon, bool bdisplayPrevious, bool bmoveForward, bool bcloser)
{
    // if lift
    if(choreo[step][3] == 5 && !bmoveForward)
    {
        fP.at(fP.size()-1) = positionCurr;
        posUpdate          = positionCurr;
        positionPrev       = positionCurr;
    }
    //cout << step << " - prev: " << positionPrev << " - curr: " << positionCurr << " --> update: " << posUpdate << "     out: " << fP.at(fP.size()-1) << endl;
    
    if (posUpdate != positionCurr)
    {
        int last = fP.size()-1;
        
        ofSetColor(255, 255, 255, 255);
        
        /*int distTotal = ofDist(positionPrev.x, positionPrev.y, positionCurr.x, positionCurr.y);
         int distUpdate = ofDist(fP.at(last).x, fP.at(last).y, positionCurr.x, positionCurr.y);
         //int alpha = ofMap(distUpdate, 0, distTotal, 75, 255);
         //int alpha = 255-255*distUpdate/distTotal;
         //ofSetColor(255, 255, 255, alpha);*/
        
        if(bmoveForward && gender == 'f')
        {
            Foot(fP.at(last).x, -fP.at(last).y, side, gender, config.iconSize);
        }else{
            Foot(fP.at(last).x, fP.at(last).y, side, gender, config.iconSize);
        }
        
        //alpha = 255;
        //if(distUpdate < distTotal/4) alpha = 0;
        if(bdisplayIcon) createIcon(fP, choreo, step, gender);
        //ofSetColor(255, 255, 255, 255);
    }
    else
    {
        int last = fP.size()-1;
        
        if(bmoveForward && gender == 'f')
        {
            Foot(fP.at(last).x, -fP.at(last).y, side, gender, config.iconSize);
        }
        else
        {
            // if lift
            if(choreo[step][3] == 5 && !bmoveForward)
            {
                if(bdisplayIcon) createIcon(fP, choreo, step, gender);
                
                if(!biconWasBig && newIconSize  < config.iconSize+5) newIconSize += 1;
                if(                newIconSize == config.iconSize+5) biconWasBig = true;
                if( biconWasBig && newIconSize >= config.iconSize)   newIconSize -= 1;
            }else{
                // reset
                biconWasBig = false;
                newIconSize = config.iconSize;
            }
            Foot(fP.at(last).x, fP.at(last).y, side, gender, newIconSize);
        }
        
        //if(bdisplayIcon) createIcon(fP, choreo, step, gender);
    }
    
    if(bdisplayPrevious)
    {
        // PREVIOUS STEP --------------------------------------------
        previousStep = step-1;
        if(previousStep == -1) previousStep = 5;
        
        // get position
        ofVec2f previousStepPos;
        if(choreo[previousStep][2] == 0)
        {
            previousStepPos.x = choreo[previousStep][0]-config.distanceFeet;
            side = 'l';
        }
        else
        {
            previousStepPos.x = choreo[previousStep][0]+config.distanceFeet;
            side = 'r';
        }
        previousStepPos.y = choreo[previousStep][1];
        
        // display step
        ofSetColor(255, 127);
        Foot(previousStepPos.x, previousStepPos.y, side, gender, config.iconSize);
        int futureStep = previousStep+2;
        if(futureStep == 6) futureStep = 0;
        if(futureStep == 7) futureStep = 1;
        if(bdisplayIcon) createIcon(previousStepPos, choreo, futureStep, gender);
        ofSetColor(255, 255);
    }
}

//--------------------------------------------------------------
ofVec2f SalsaTwoScreen::moveForwardsMaster(vector< vector<int> > choreo, int mStep, char gender)
{
    ofVec2f origin = getStepPosition(choreo, mStep);
    char side = getStepSide(choreo, mStep);
    ofVec2f target;
    target.x = origin.x;
    target.y = origin.y+config.distanceMoveTwoSalsa;
    
    if(footPositions.size() == 0) positionUpdate = origin;
    if(positionUpdate != target)
    {
        tweenPositionMaster(footPositions, positionUpdate, origin, target, choreo, mStep, side, gender, false, true, false, true, false);
    }else{
        Foot(target.x, target.y, side, gender, config.iconSize);
    }
    
    return target;
}

//--------------------------------------------------------------
void SalsaTwoScreen::moveForwardsSlave(ofVec2f target, vector< vector<int> > choreo, int mStep, char gender)
{
    ofVec2f origin = getStepPosition(choreo, mStep);
    char side = getStepSide(choreo, mStep);
    ofVec2f oldtarget = target;
    
    if(positionUpdate != target)
    {
        tweenPositionSlave(footPositions, positionUpdate, target, choreo, mStep, side, gender, false, false, true, false);
    }
    else
    {
        if(gender == 'f')
        {
            ofPushMatrix();
            if(side == 'r') ofTranslate(0, -boxHeight);
            Foot(footPositions.at(footPositions.size()-1).x, footPositions.at(footPositions.size()-1).y - 2*config.distanceMoveTwoSalsa, side, gender, config.iconSize);
            ofPopMatrix();
        }
        else{
            Foot(footPositions.at(footPositions.size()-1).x, footPositions.at(footPositions.size()-1).y, side, gender, config.iconSize);
        }
    }
}

//--------------------------------------------------------------
ofVec2f SalsaTwoScreen::getStepPosition(vector< vector<int> > choreo, int step)
{
    ofVec2f position;
    if(choreo[step][2] == 0)
    {
        position.x = choreo[step][0]-config.distanceFeet;
    }
    else
    {
        position.x = choreo[step][0]+config.distanceFeet;
    }
    position.y = choreo[step][1];
    
    return position;
}

//--------------------------------------------------------------
char SalsaTwoScreen::getStepSide(vector< vector<int> > choreo, int step)
{
    char side;
    if(choreo[step][2] == 0)
    {
        side = 'l';
    }
    else
    {
        side = 'r';
    }
    
    return side;
}

//--------------------------------------------------------------
void SalsaTwoScreen::createIcon(vector<ofVec2f> fP, vector< vector<int> > choreo, int step, char gender)
{
    int last = fP.size()-1;
    
    if(getIcon(choreo[step][3], gender) != "")
    {
        icon.loadImage(getIcon(choreo[step][3], gender));
        int iconWidth = icon.width*config.iconSize/100;
        int iconHeight = icon.height*config.iconSize/100;
        if(gender == 'f'){
            icon.draw(fP.at(last).x - iconWidth/2, fP.at(last).y-120, iconWidth, iconHeight);
        }else{
            icon.draw(fP.at(last).x - iconWidth/2, fP.at(last).y+60, iconWidth, iconHeight);
        }
    }
}

//--------------------------------------------------------------
void SalsaTwoScreen::createIcon(ofVec2f position, vector< vector<int> > choreo, int step, char gender)
{
    if(getIcon(choreo[step][3], gender) != "")
    {
        icon.loadImage(getIcon(choreo[step][3], gender));
        int iconWidth = icon.width*config.iconSize/100;
        int iconHeight = icon.height*config.iconSize/100;
        if(gender == 'f'){
            icon.draw(position.x - iconWidth/2, position.y-120, iconWidth, iconHeight);
        }else{
            icon.draw(position.x - iconWidth/2, position.y+60, iconWidth, iconHeight);
        }
    }
}

//--------------------------------------------------------------
int SalsaTwoScreen::roundUp(float number)
{
    number += 0.5;  // to round up correctly
    return (int)number;
}

//--------------------------------------------------------------
string SalsaTwoScreen::getIcon(int iconId, char gender)
{
    string role;
    if (gender == 'f') {
        role = "follower";
    }else{
        role = "leader";
    }
    string iconName;
    
    switch (iconId) {
        case 0:
            iconName = "";
            break;
            
        case 1:
            iconName = "arrow-down";
            break;
            
        case 2:
            iconName = "arrow-up";
            break;
            
        case 3:
            iconName = "arrow-right";
            break;
            
        case 4:
            iconName = "arrow-left";
            break;
            
        case 5:
            iconName = "stop";
            break;
            
        case 6:
            iconName = "arrow-right-round";
            break;
            
        case 7:
            iconName = "arrow-left-round";
            break;
    }
    
    if(iconName == "")
    {
        return "";
    }
    else
    {
        return "img/Icons/icon_"+iconName+"_"+role+".png";
    }
}