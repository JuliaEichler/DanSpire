#include "ofMain.h"
#include "config.h"

#include "ofxScene.h"
#include "ofxAnimatableFloat.h"

#include "ofxCenteredTrueTypeFont.h"

class ChooseNextDanceScreen : public ofxScene{
    
    public:
        
        void setup();
        void update(float dt);
        void draw();
        
        void checkUserPosition(int _currUserId, float _currUserPosX, float _currUserPosY, int _numberOfUsers);
        int makeDanceSelection(int _numberOfUsers);
        void playMusic(int songID);
        
        // scene notifications
        void sceneWillAppear( ofxScene * fromScreen );
        void sceneWillDisappear( ofxScene * toScreen );
        
        // config
        config                  config;
        
        // image
        ofImage                 image;
        
        // circles
        int                     radius;
        
        // sound
        vector<ofVec2f>         circle;    
        ofSoundPlayer           salsa;
        ofSoundPlayer           waltz;
        ofSoundPlayer           jive;
        static const int        salsaDanceId = config::salsaDanceId;
        static const int        jiveDanceId  = config::jiveDanceId;
        static const int        waltzDanceId = config::waltzDanceId;
        static const int        cornerId     = config::cornerId;
        vector<int>             insideCircleId;
        vector<int>             userCircleVote;
        vector<bool>            bPrevInsideCircle;
        vector<bool>            bPlayerPaused;
        
        // text
        ofxCenteredTrueTypeFont font, handwritten;
        
        // parameters
        int                     numberOfUsers;
        int                     decisionTime;
    
        int                     timer;
};
