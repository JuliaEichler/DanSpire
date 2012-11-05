#include "ofMain.h"

#include "ofxScene.h"
#include "ofxAnimatableFloat.h"

class InstructionScreenB : public ofxScene{
    
public:
    
    void setup();
    void update(float dt);
    void draw();
    
    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * toScreen );
    
    void isWaltz();
    
    ofImage image;
    
    bool    bisWaltz;
    float   playerVolume;    
    
};
