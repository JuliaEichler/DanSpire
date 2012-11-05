#include "ofMain.h"
#include "config.h"
#include "testApp.h"
#include "ofxFensterManager.h"
#include "ofAppGlutWindow.h"

//========================================================================

// uncomment for multiWindow option
/*
int main( ){
	ofSetupOpenGL(ofxFensterManager::get(), 1024, 768, OF_WINDOW);			// <-------- setup the GL context
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunFensterApp(new testApp());
}
*/

// uncomment for fullscreen mode (toggle)
int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofRunApp(new testApp());
}
