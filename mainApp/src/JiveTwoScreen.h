#include "ofMain.h"
#include "config.h"

#include "ofxFensterManager.h"

#include "ofxScene.h"
#include "ofxAnimatableFloat.h"

#include "choreography.h"
#include "foot.h"
#include "hand.h"

class JiveTwoScreen : public ofxScene{
    
public:
    
    void setup();
    void update(float dt);
    void draw();
    
    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * toScreen );
    
    void startSound();
    void resetPlayer();
    int getPlayerPositionMS();
    float getPlayerPosition();
    
    void standardPosition(vector< vector<int> > choreo, int position, int x1, int y1, int x2, int y2);
    void getChoreoPosition(int step, char gender, bool displayPrevious, vector< vector<int> > choreo, bool bdisplayIcon, bool bisStart);
    void updateChoreoPosition(vector< vector<int> > choreo, int step, bool bdisplayPrevious, bool bdisplayIcon, bool bcloser, bool bbox);
    void tweenPositionMaster(vector<ofVec2f> footPositions, ofVec2f positionUpdate, ofVec2f positionPrev, ofVec2f positionCurr, vector< vector<int> > choreo, int step, char side, char gender, bool bdisplayIcon, bool bdisplayMaster, bool bdisplayPrevious, bool bmoveForward, bool bcloser);
    void tweenPositionSlave(vector<ofVec2f> fP, ofVec2f posUpdate, ofVec2f positionCurr, vector< vector<int> > choreo, int step, char side, char gender, bool bdisplayIcon, bool bdisplayPrevious, bool bmoveForward, bool bcloser);
    ofVec2f moveForwardsMaster(vector< vector<int> > choreo, int mStep, char gender);
    void moveForwardsSlave(ofVec2f target, vector< vector<int> > choreo, int mStep, char gender);
    
    ofVec2f getStepPosition(vector< vector<int> > choreo, int step);
    char getStepSide(vector< vector<int> > choreo, int step);
    void createIcon(vector<ofVec2f> fP, vector< vector<int> > choreo, int step, char gender);
    void createIcon(ofVec2f position, vector< vector<int> > choreo, int step, char gender);
    
    int roundUp(float number);
    string getIcon(int iconId, char gender);
    
    config                  config;
    int                     mainWindowWidth;
    
    ofImage                 icon;
    
    ofSoundPlayer           player;
    int                     currentPlayerPos;
    
    int                     startPlayerPos_R1, stopPlayerPos_R1,
                            startPlayerPos_R2, stopPlayerPos_R2,
                            startPlayerPos_R3, stopPlayerPos_R3,
                            startPlayerPos_R4, stopPlayerPos_R4;
    int                     prevPlayerPos;
    int                     intervall, intervall1, intervall2, intervall3;
    
    Choreography            jiveChoreo;
    int                     boxWidth, boxHeight;
    vector< vector<int> >   role;
    int                     distanceFeet;
    int                     cX1, cX2, cY1;
    
    int                     currentStep, previousStep;
    bool                    isStart;
    
    // history
    vector<ofVec2f>         footPositions;
    ofVec2f                 positionCurr, positionPrev;
    ofVec2f                 positionUpdate;
    int                     previousSideStep;
    
    // move forwards
    int                     mDistance;
    int                     mStepA, mStepB;
    ofVec2f                 mFootA, mFootB;
    char                    mGender;
    
    ofVec2f                 previousHandPos;
    
    // lift
    int                     newIconSize;
    bool                    biconWasBig;
    
    int                     rotateDegree;
};