#include "ofMain.h"
#include "ofxScene.h"
#include "ofxAnimatableFloat.h"

class WelcomeScreenB : public ofxScene{
    
    
	void setup();
	void update(float dt);
	void draw();
    
	//scene notifications
	void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * toScreen );
    
	ofImage welcomeImg;
};
