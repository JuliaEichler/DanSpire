#pragma once

#include "ofMain.h"
#include "config.h"

#include "ofxFensterManager.h"

#include "ofxOpenCv.h"
#include "ofxKinect.h"

#include "ofxAnimatableFloat.h"
#include "ofxSceneManager.h"

// scenes
#include "WelcomeScreenA.h"
#include "WelcomeScreenB.h"
#include "ChooseDanceScreen.h"
#include "LoadingScreen.h"
#include "InstructionScreenA.h"
#include "InstructionScreenB.h"
#include "InstructionScreenC.h"
#include "SalsaScreen.h"
#include "JiveScreen.h"
#include "WaltzScreen.h"
#include "SalsaTwoScreen.h"
#include "JiveTwoScreen.h"
#include "WaltzTwoScreen.h"
#include "ChooseNextDanceScreen.h"
#include "KioskScreen.h"
#include "RestrictUserNumber.h"
#include "CodeScreen.h"
#include "FindPartnerScreen.h"

class videoWindow: public ofxFensterListener {
    public:
    
        ~videoWindow() {
            cout << "Image Listener destroyed" << endl;
        }
        void setup() {
            salsaVideo.loadMovie("videos/Salsa.mp4");
            jiveVideo.loadMovie("videos/Jive.mp4");
            waltzVideo.loadMovie("videos/Waltz.mp4");
        }
        
        void update() {
            salsaVideo.idleMovie();
            jiveVideo.idleMovie();
            waltzVideo.idleMovie();
        }
        
        void draw() {
            if(salsaVideo.isPlaying()) salsaVideo.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
            if(jiveVideo.isPlaying()) jiveVideo.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
            if(waltzVideo.isPlaying()) waltzVideo.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        }
        
        void keyReleased(int key, ofxFenster* window) {
            if(key==' ')
                ofxFensterManager::get()->deleteFenster(window);
            if(key == 'm'){ //this is to test set and get window position
                ofPoint winPos = window->getWindowPosition();
                window->setWindowPosition(winPos.x + 10, winPos.y);
            }
        }
    
        void playVideo(int videoId)
        {
            switch (videoId) {
                case salsaDanceId:
                    salsaVideo.setPosition(0);
                    salsaVideo.play();
                    break;
                    
                case jiveDanceId:
                    jiveVideo.setPosition(0);
                    jiveVideo.play();
                    break;
                    
                case waltzDanceId:
                    waltzVideo.setPosition(0);
                    waltzVideo.play();
                    break;
                    
                default:
                    break;
            }
        }
    
        void stopVideo(int videoId)
        {
            //cout << "stop video -> " << videoId << endl;
            switch (videoId) {
                case salsaDanceId:
                    salsaVideo.stop();
                    break;
                    
                case jiveDanceId:
                    jiveVideo.stop();
                    break;
                    
                case waltzDanceId:
                    waltzVideo.stop();
                    //cout << "stop video waltz -> " << waltzDanceId << endl;
                    break;
                    
                default:
                    break;
            }
        }
        
        ofVideoPlayer salsaVideo;
        ofVideoPlayer jiveVideo;
        ofVideoPlayer waltzVideo;
    
        // dances
        static const int        salsaDanceId = config::salsaDanceId;
        static const int        jiveDanceId  = config::jiveDanceId;
        static const int        waltzDanceId = config::waltzDanceId;
};

class backendWindow: public ofxFensterListener {
    public:
        ~backendWindow() {
            
        }
    
        void setup() {
            // Circles
            circleA.resize(3);
            circleA[config.waltzDanceId].x = config.circleWaltzA.x;     circleA[config.waltzDanceId].y = config.circleWaltzA.y;
            circleA[config.salsaDanceId].x = config.circleSalsaA.x;     circleA[config.salsaDanceId].y = config.circleSalsaA.y;
            circleA[config.jiveDanceId].x  = config.circleJiveA.x;      circleA[config.jiveDanceId].y  = config.circleJiveA.y;
            radiusA = config.circleRadiusA;
            
            circleB.resize(4);
            circleB[config.waltzDanceId].x = config.circleWaltzB.x;     circleB[config.waltzDanceId].y = config.circleWaltzB.y;
            circleB[config.salsaDanceId].x = config.circleSalsaB.x;     circleB[config.salsaDanceId].y = config.circleSalsaB.y;
            circleB[config.jiveDanceId].x  = config.circleJiveB.x;      circleB[config.jiveDanceId].y  = config.circleJiveB.y;
            circleB[config.cornerId].x     = config.circleCorner.x;     circleB[config.cornerId].y     = config.circleCorner.y;
            radiusB = config.circleRadiusB;
        }
        
        void update(ofxCvGrayscaleImage _grayImage, int _kinectWidth, int _kinectHeight, vector<ofxCvBlob> _people, int _blobSize) {
            // kinect
            kinectImage = _grayImage;
            kinectWidth = _kinectWidth;
            kinectHeight = _kinectHeight;
            kinectContour.findContours(kinectImage, 10, (kinectWidth*kinectHeight)/2, 20, false);
            
            // blobs
            people = _people;
            minSizeBlob = _blobSize;
        }
        
        void draw() {
            // display kinect data
            ofSetColor(255, 255, 255);
            kinectImage.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
            kinectContour.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
            
            // show user positions (blobs)
            ofFill();
            ofSetColor(0, 255, 0);
            
            numberOfUsers = 0;
            
            for(int n=0; n < people.size(); n++)
            {
                if(people[n].area > minSizeBlob)
                {
                    numberOfUsers++;
                    
                    float posX = people[n].centroid.x * ofGetWindowWidth() / kinectWidth;
                    float posY = people[n].centroid.y * ofGetWindowHeight() / kinectHeight;
                    
                    
                    ofCircle(posX, posY, 10);
                    ofDrawBitmapString(ofToString(n) , posX-5, posY+25);                    
                }
            }
            
            // display info
            ofSetColor(255, 255, 255);
            stringstream user__info;
            user__info << "We have " << ofToString(numberOfUsers) << " user." << endl;
            ofDrawBitmapString(user__info.str(), 10, 20);
            
            // danceType circles
            ofSetColor(255, 0, 0, 0);       if(config.bdisplayUserData) ofSetColor(255, 0, 0, 170);
            for(int i=0; i<circleA.size(); i++) {
                ofCircle(circleA[i].x, circleA[i].y, radiusA);
            }
            ofSetColor(0, 0, 255, 0);       if(config.bdisplayUserData) ofSetColor(0, 0, 255, 170);
            for(int i=0; i<circleB.size(); i++) {
                ofCircle(circleB[i].x, circleB[i].y, radiusB);
            }
            ofSetColor(255, 255, 255);
        }

        
        void mouseMoved(int x, int y) {
            
        }
        
        void dragEvent(ofDragInfo dragInfo) {
            cout << "GOT SOME FILES: "<<endl;
            std::vector<string>::iterator it = dragInfo.files.begin();
            while(it != dragInfo.files.end()) {
                cout << *it << endl;
                ++it;
            }
        }
        
        ofxCvGrayscaleImage     kinectImage;
        ofxCvContourFinder      kinectContour;
        int                     kinectWidth, kinectHeight;

        vector<ofxCvBlob>       people;
        int                     minSizeBlob;
        int                     numberOfUsers;
    
        vector<ofVec2f>         circleA, circleB;
        int                     radiusA, radiusB;
    
        config                  config;
};

class testApp : public ofBaseApp {
    
    //enum Scenes{ welcomeScreen, startScreen, danceScreen };
    enum Scenes{ SCENE_1, SCENE_2, SCENE_3, SCENE_4, SCENE_5, SCENE_6, SCENE_7, SCENE_8, SCENE_9, SCENE_10, SCENE_11, SCENE_12, SCENE_13, SCENE_14, SCENE_15, SCENE_16, SCENE_17, SCENE_18 };
    
	public:

		void setup();
		void update();
		void draw();
		void exit();
    
        void keyPressed(int key);
        void windowResized(int w, int h);
    
        float msToSecs(int number);
        int roundUp(float number);
    
        void updateChoreoPosition(int step, char gender, bool displayPrevious, vector< vector<int> > coreo);
    
    	
		ofxKinect               kinect;
        
        ofxBase3DVideo*         kinectSource;
    
        ofxCvGrayscaleImage     grayImage;
        ofxCvGrayscaleImage     grayThreshNear;
        ofxCvGrayscaleImage     grayThreshFar;
    
        ofxCvContourFinder      contourFinder;
        bool                    bThreshWithOpenCV;
        int                     nearThreshold;
        int                     farThreshold;
        
        int                     angle;
    
        vector<ofxCvBlob>       people;
        int                     minSizeBlob;
        int                     numberOfUsers;
        int                     storeNumberOfUsers;
    
        bool                    bdisplayKinectData;
        config                  config;
    
        // scenes    
        ofxSceneManager *       sceneManager;
        ChooseDanceScreen       chooseDanceScene;
        ChooseNextDanceScreen   chooseNextDanceScene;
        ofxScene *              instructionScreenB;
        ofxScene *              salsaScreen;
        ofxScene *              jiveScreen;
        ofxScene *              waltzTwoScreen;
        ofxScene *              salsaTwoScreen;
        ofxScene *              jiveTwoScreen;
        ofxScene *              waltzScreen;
        int                     danceId;
        int                     timeCapture;
        int                     currentTime;
    
        // windows
        int                     mainWindowWidth, mainWindowHeight;
        ofVec2f                 mousePos;
        videoWindow             videoWin;
        backendWindow           backendWin;
        ofxFenster*             win_backend;
        ofxFenster*             win_video;
        
        int                     iconCount;
    
        // dances
        static const int        salsaDanceId = config::salsaDanceId;
        static const int        jiveDanceId  = config::jiveDanceId;
        static const int        waltzDanceId = config::waltzDanceId;
        static const int        cornerId     = config::cornerId;
    
        int                     timer;
    
        // serial    
        ofSerial                serial, rearSerial, recSerial;
        unsigned char           byte, prevByte;
        unsigned char           serialSalsa, serialJive, serialWaltz, serialStopAll;
        bool                    bbyteWasWritten;
        int                     serialCurrTime, serialPrevTime, serialIntervall;
    
        // sound
        ofSoundPlayer           introSound, instructionSound;
        float                   introSoundVolume, instructionSoundVolume;
        bool                    binstructionWasPlayed;        
};
