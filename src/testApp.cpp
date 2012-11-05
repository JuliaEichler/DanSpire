#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup()
{
    // SETTINGS ------------------------------------------------
    // blob
    minSizeBlob = 5000;
    
    // info
    bdisplayKinectData      = true;

    
    // PREFERENCES ---------------------------------------------
    ofSetFrameRate(config.fps);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofBackground(0, 0, 0);
    
    // store main window data before loading any other one
    // fixing framebug caused by combi of ofxFenster with ofxSceneManager
    mainWindowWidth = config.mainWindowWidth;
    mainWindowHeight = config.mainWindowHeight;
    
    // other prefs
    danceId = 404;
    //prevPlayerPos = 0;
    

    // KINECT --------------------------------------------------
    kinect.init();
    // kinect.setVerbose(true);
    kinect.open();
    
    kinectSource = &kinect;
    
    grayImage.allocate(kinect.width, kinect.height);
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);
    
    // value calculation: 380 cm - x cm = real distance cm (approx.)
    nearThreshold   = 230;
    farThreshold    = 100;
    bThreshWithOpenCV = true;
    
    // camera tilting
    angle = 0;
    kinect.setCameraTiltAngle(0);
    
    if(config.bmultiWindow)
    {
        // WINDOWS -------------------------------------------------
        int windowWidth  = 1024;
        int windowHeight = 768;
        
        // BACKEND WINDOW ---
        backendWin.setup();
        win_backend = ofxFensterManager::get()->createFenster(mainWindowWidth, 0, windowWidth, windowHeight, OF_WINDOW);
        win_backend->addListener(&backendWin);
        
        win_backend->setWindowTitle("Backend");
        
        // VIDEO WINDOW ---
        //setup of fensterListener does not get called automatically yet
        videoWin.setup();
        win_video = ofxFensterManager::get()->createFenster(mainWindowWidth, windowHeight, windowWidth, windowHeight, OF_WINDOW);
        win_video->addListener(&videoWin);
        win_video->setWindowTitle("Video Projection");
        
        // ---
        // set app icon
        ofImage icon;
        icon.loadImage("icon.png");
        ofxFensterManager::get()->setIcon(icon.getPixelsRef());    
    }
    
    // SCENES --------------------------------------------------
    sceneManager = new ofxSceneManager();
    sceneManager->addScene( new WelcomeScreenA(), SCENE_1);
	sceneManager->addScene( new WelcomeScreenB(), SCENE_2); 
    sceneManager->addScene( new ChooseDanceScreen(), SCENE_3);
    sceneManager->addScene( new LoadingScreen(), SCENE_4);
    sceneManager->addScene( new InstructionScreenA(), SCENE_5);
    instructionScreenB = new InstructionScreenB();
    sceneManager->addScene( instructionScreenB, SCENE_6);
    sceneManager->addScene( new InstructionScreenC(), SCENE_7);
    salsaScreen = new SalsaScreen();
    sceneManager->addScene( salsaScreen, SCENE_8);
    jiveScreen  = new JiveScreen();
    sceneManager->addScene( jiveScreen, SCENE_9);
    waltzScreen = new WaltzScreen();
    sceneManager->addScene( waltzScreen, SCENE_10);
    sceneManager->addScene( new ChooseNextDanceScreen(), SCENE_11);
    sceneManager->addScene( new KioskScreen(), SCENE_12);
    sceneManager->addScene( new RestrictUserNumber(), SCENE_13);
    sceneManager->addScene( new CodeScreen(), SCENE_14);
    salsaTwoScreen = new SalsaTwoScreen();
    sceneManager->addScene( salsaTwoScreen, SCENE_15);
    jiveTwoScreen  = new JiveTwoScreen();
    sceneManager->addScene( jiveTwoScreen, SCENE_16);
    waltzTwoScreen = new WaltzTwoScreen();
    sceneManager->addScene( waltzTwoScreen, SCENE_17);
    sceneManager->addScene( new FindPartnerScreen(), SCENE_18);
    
    sceneManager->windowResized(mainWindowWidth, mainWindowHeight); // remove black border
	sceneManager->setDrawDebug(true);
	sceneManager->setCurtainDropTime(0.5);
	sceneManager->setCurtainStayTime(0.0);
	sceneManager->setCurtainRiseTime(0.5);
	sceneManager->setOverlapUpdate(true);
    
    // initialise classes with globally required functions
    chooseDanceScene.setup();
    chooseNextDanceScene.setup();
    
    // SERIAL --------------------------------------------------
    serial.setup("/dev/tty.usbserial-A100RZK8", 9600);
    serial.flush();
    bbyteWasWritten = false;
    serialSalsa     = 10; // bytes to be sent
    serialJive      = 11;
    serialWaltz     = 12;
    serialStopAll   = 255;
    byte            = serialStopAll;
    serialPrevTime  = 0;
    serialIntervall = 500; // ms
    
    // SOUND ---------------------------------------------------
    introSound.loadSound("sounds/introduction_sand-dance.mp3");
    introSound.setLoop(false);
    introSound.setMultiPlay(false);
    introSoundVolume = 0.75f;
    introSound.setVolume(introSoundVolume);
    
    instructionSound.loadSound("sounds/Circle_instruction.mp3");
    instructionSound.setLoop(false);
    instructionSound.setMultiPlay(false);
    instructionSoundVolume = 0.75f;
    instructionSound.setVolume(instructionSoundVolume);
    binstructionWasPlayed = false;
    
    //numberOfUsers = 0;
    timer = 0;
}

//--------------------------------------------------------------
void testApp::update()
{
    //ofBackground(100, 100, 100);
    
    // SCENES --------------------------------------------------
    float dt = 0.016666666;
	sceneManager->update( dt );
    
    // SOUND ---------------------------------------------------
    ofSoundUpdate();
    
    
    // KINECT --------------------------------------------------
    kinectSource->update();
    
    if(kinectSource->isFrameNew()) {
        grayImage.setFromPixels(kinectSource->getDepthPixels(), kinect.width, kinect.height);
        
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(nearThreshold, true);
            grayThreshFar.threshold(farThreshold);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        }
        grayImage.flagImageChanged();
        
        // find contours which are between the size of 20 px and 1/2 the w*h px
        contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
        people.resize(contourFinder.nBlobs);
        for (int i = 0; i < contourFinder.nBlobs; i++) {
            people[i] = contourFinder.blobs[i];
        }
        
        if(config.bmultiWindow) backendWin.update(grayImage, kinect.width, kinect.height, people, minSizeBlob);
    }
}

//--------------------------------------------------------------
void testApp::draw()
{
    // SERIAL --------------------------------------------------
    serialCurrTime = ofGetElapsedTimeMillis();
    
    if (serialCurrTime > serialPrevTime+serialIntervall) {
        serialPrevTime = serialCurrTime;
        
        //cout << "Byte: " << byte << " - S " << serialSalsa << " - J " << serialJive << " - W " << serialWaltz << endl;
        bbyteWasWritten = serial.writeByte(byte);
        if(bbyteWasWritten) cout << "serial sent: " << byte << endl;
    }

    // SCENES --------------------------------------------------
    sceneManager->draw();
    
    // SETTINGS ------------------------------------------------
    // reset color to prevent from tinting images
    ofSetColor(255,255,255);
    
    // CHECK USERS ---------------------------------------------
    // user blobs
    numberOfUsers = 0;
    
    for(int n=0; n < people.size(); n++)
    {
        if(people[n].area > minSizeBlob)
        {
            numberOfUsers++;
            
            //welcome.update(numberOfUsers);
            
            float posX = people[n].centroid.x * ofGetWindowWidth() / kinect.width;
            float posY = people[n].centroid.y * ofGetWindowHeight() / kinect.height;
            
            if(config.bdisplayUserData)
            {
                ofSetColor(0, 255, 0);
                ofCircle(posX, posY, 10);
                ofDrawBitmapString(ofToString(n) , posX-5, posY+25);
                ofSetColor(255, 255, 255);
            }
            
            // check
            if(sceneManager->getcurrentSceneID()==SCENE_3) chooseDanceScene.checkUserPosition(n, posX, posY, numberOfUsers);
            if(sceneManager->getcurrentSceneID()==SCENE_11) chooseNextDanceScene.checkUserPosition(n, posX, posY, numberOfUsers);
        }
    }
    
    
    // DIRECT SCENES -------------------------------------------
    if(numberOfUsers < 1 && sceneManager->getcurrentSceneID()!=SCENE_1)
    {
        timer++;
        if(timer > 60*config.decisionTime)
        {
            danceId = 404;
            ofSoundStopAll();
            sceneManager->goToScene(SCENE_1);
            timer = 0;
        }
    }else{
        timer = 0;
    }
    // debugging start ----
    /*if(sceneManager->getcurrentSceneID()==SCENE_1)
    {
        serial.flush();
        byte = serialSalsa;
        if(config.bmultiWindow) videoWin.playVideo(salsaDanceId);
        sceneManager->goToScene(SCENE_8);
    }*/
    // debugging end ------
    if(sceneManager->getcurrentSceneID()==SCENE_1)
    {
        if(!introSound.getIsPlaying()) introSound.play();
    }
    if(sceneManager->getcurrentSceneID()==SCENE_1 && numberOfUsers>0)
    {
        sceneManager->goToScene(SCENE_2);
        timeCapture = roundUp(msToSecs(ofGetElapsedTimeMillis()));
    }
    if(sceneManager->getcurrentSceneID()== SCENE_2 && (numberOfUsers==1 || numberOfUsers==3) )
    {
        currentTime = roundUp(msToSecs(ofGetElapsedTimeMillis()));
        
        if(currentTime == timeCapture + config.slideShowDuration)
        {
            sceneManager->goToScene(SCENE_18);
            timeCapture = roundUp(msToSecs(ofGetElapsedTimeMillis()));
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_18 && (numberOfUsers==2 || numberOfUsers==4) )
    {
        storeNumberOfUsers = numberOfUsers;
        sceneManager->goToScene(SCENE_3);
        timer = 0;
    }
    if(sceneManager->getcurrentSceneID()==SCENE_2 && (numberOfUsers==2 || numberOfUsers==4) )
    {
        storeNumberOfUsers = numberOfUsers;
        sceneManager->goToScene(SCENE_3);
    }
    if(sceneManager->getcurrentSceneID()==SCENE_2 && numberOfUsers>4)
    {
        sceneManager->goToScene(SCENE_13);
        timer = 0;
    }
    if(sceneManager->getcurrentSceneID()==SCENE_3)
    {
        // fade out sound
        introSoundVolume -= 0.0075f;
        introSound.setVolume(introSoundVolume);
        if(introSoundVolume < 0.5)
        {
            if(!instructionSound.getIsPlaying() && !binstructionWasPlayed)
            {
                instructionSound.play();
                binstructionWasPlayed = true;
            }
        }
        if(introSoundVolume < 0.0)
        {
            introSound.stop();
        }
        
        danceId = chooseDanceScene.makeDanceSelection(numberOfUsers);
        if(danceId != 404)
        {
            cout << "Dance ID: " << danceId << endl;
            sceneManager->goToScene(SCENE_4);
            timeCapture = roundUp(msToSecs(ofGetElapsedTimeMillis()));
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_4)
    {
        currentTime = roundUp(msToSecs(ofGetElapsedTimeMillis()));
        
        // go to next slide if slideShowDuration secs have passed
        if(currentTime == timeCapture + config.slideShowDuration)
        {
            sceneManager->goToScene(SCENE_5);
            timeCapture = roundUp(msToSecs(ofGetElapsedTimeMillis()));
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_5)
    {
        currentTime = roundUp(msToSecs(ofGetElapsedTimeMillis()));
        
        // go to next slide if slideShowDuration secs have passed
        if(currentTime == timeCapture + config.slideShowDuration)
        {
            sceneManager->goToScene(SCENE_6);
            timeCapture = roundUp(msToSecs(ofGetElapsedTimeMillis()));
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_6)
    {
        if(danceId == waltzDanceId) instructionScreenB->isWaltz();
        
        currentTime = roundUp(msToSecs(ofGetElapsedTimeMillis()));
        
        // go to next slide if slideShowDuration secs have passed
        if(currentTime == timeCapture + config.slideShowDuration)
        {
            /*if(storeNumberOfUsers < 3 && numberOfUsers < 3)
            {
                switch (danceId) {
                    case waltzDanceId:
                        serial.flush();
                        byte = serialWaltz;
                        if(config.bmultiWindow) videoWin.playVideo(waltzDanceId);
                        sceneManager->goToScene(SCENE_17);
                        break;
                        
                    default:
                        sceneManager->goToScene(SCENE_7);
                        timeCapture = roundUp(msToSecs(ofGetElapsedTimeMillis()));
                        break;
                }
            }else{*/
                switch (danceId) {
                    case waltzDanceId:
                        serial.flush();
                        byte = serialWaltz;
                        if(config.bmultiWindow) videoWin.playVideo(waltzDanceId);
                        sceneManager->goToScene(SCENE_10);
                        break;
                        
                    default:
                        sceneManager->goToScene(SCENE_7);
                        timeCapture = roundUp(msToSecs(ofGetElapsedTimeMillis()));
                        break;
                }
            //}
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_7)
    {
        currentTime = roundUp(msToSecs(ofGetElapsedTimeMillis()));
        // go to next slide if slideShowDuration secs have passed
        if(currentTime == timeCapture + config.slideShowDuration)
        {/*
            if(storeNumberOfUsers < 3 && numberOfUsers < 3)
            {
                switch (danceId) {
                    case salsaDanceId:
                        serial.flush();
                        byte = serialSalsa;
                        if(config.bmultiWindow) videoWin.playVideo(salsaDanceId);
                        sceneManager->goToScene(SCENE_15);
                        break;
                        
                    case jiveDanceId:
                        serial.flush();
                        byte = serialJive;
                        if(config.bmultiWindow) videoWin.playVideo(jiveDanceId);
                        sceneManager->goToScene(SCENE_16);
                        break;
                        
                    case waltzDanceId:
                        serial.flush();
                        byte = serialWaltz;
                        if(config.bmultiWindow) videoWin.playVideo(waltzDanceId);
                        cout << "Start " << waltzScreen->getPlayerPositionMS() << endl;
                        sceneManager->goToScene(SCENE_17);
                        break;
                }
            }
            else
            {*/
                switch (danceId) {
                    case salsaDanceId:
                        serial.flush();
                        byte = serialSalsa;
                        if(config.bmultiWindow) videoWin.playVideo(salsaDanceId);
                        sceneManager->goToScene(SCENE_8);
                        break;
                        
                    case jiveDanceId:
                        serial.flush();
                        byte = serialJive;
                        if(config.bmultiWindow) videoWin.playVideo(jiveDanceId);
                        sceneManager->goToScene(SCENE_9);
                        break;
                        
                    case waltzDanceId:
                        serial.flush();
                        byte = serialWaltz;
                        if(config.bmultiWindow) videoWin.playVideo(waltzDanceId);
                        cout << "Start " << waltzScreen->getPlayerPositionMS() << endl;
                        sceneManager->goToScene(SCENE_10);
                        break;
                }
            //}
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_8)
    {
        if(roundUp(salsaScreen->getPlayerPositionMS()/100) == 1450)
        {
            serial.flush();
            byte = serialStopAll;
            if(config.bmultiWindow) videoWin.stopVideo(salsaDanceId);
            
            sceneManager->goToScene(SCENE_14);
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_9)
    {
        if(roundUp(jiveScreen->getPlayerPositionMS()/100) == 1490)
        {
            serial.flush();
            byte = serialStopAll;
            if(config.bmultiWindow) videoWin.stopVideo(jiveDanceId);
            
            sceneManager->goToScene(SCENE_14);
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_10)
    {
        if(roundUp(waltzScreen->getPlayerPositionMS()/100) == 1650)
        {
            serial.flush();
            byte = serialStopAll;
            if(config.bmultiWindow) videoWin.stopVideo(waltzDanceId);
            
            sceneManager->goToScene(SCENE_14);
            timer = 0;
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_15)
    {
        if(roundUp(salsaTwoScreen->getPlayerPositionMS()/100) == 1450)
        {
            serial.flush();
            byte = serialStopAll;
            if(config.bmultiWindow) videoWin.stopVideo(salsaDanceId);
            
            sceneManager->goToScene(SCENE_14);
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_16)
    {
        if(roundUp(jiveTwoScreen->getPlayerPositionMS()/100) == 1490)
        {
            serial.flush();
            byte = serialStopAll;
            if(config.bmultiWindow) videoWin.stopVideo(jiveDanceId);
            
            sceneManager->goToScene(SCENE_14);
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_17)
    {
        if(roundUp(waltzTwoScreen->getPlayerPositionMS()/100) == 1650)
        {
            serial.flush();
            byte = serialStopAll;
            if(config.bmultiWindow) videoWin.stopVideo(waltzDanceId);
            
            sceneManager->goToScene(SCENE_14);
            timer = 0;
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_14)
    {
        timer++;
        if(timer > 60*config.decisionTime*2)
        {
            sceneManager->goToScene(SCENE_11);
            timer = 0;
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_11)
    {
        if(numberOfUsers < 1)
        {
            timer++;
            if(timer > 60*config.decisionTime*1.5)
            {
                sceneManager->goToScene(SCENE_1);
                timer = 0;
            }
        }
        
        danceId = chooseNextDanceScene.makeDanceSelection(numberOfUsers);
        if(danceId != 404)
        {
            /*if(numberOfUsers < 3)
            {
                switch (danceId) {
                    case salsaDanceId:
                        serial.flush();
                        byte = serialSalsa;
                        if(config.bmultiWindow) videoWin.playVideo(salsaDanceId);
                        sceneManager->goToScene(SCENE_15);
                        break;
                        
                    case jiveDanceId:
                        serial.flush();
                        byte = serialJive;
                        if(config.bmultiWindow) videoWin.playVideo(jiveDanceId);
                        sceneManager->goToScene(SCENE_16);
                        break;
                        
                    case waltzDanceId:
                        serial.flush();
                        byte = serialWaltz;
                        if(config.bmultiWindow) videoWin.playVideo(waltzDanceId);
                        sceneManager->goToScene(SCENE_17);
                        break;
                        
                    case cornerId:
                        timer = 0;
                        sceneManager->goToScene(SCENE_12);
                        break;
                }
            }
            else
            {*/
                switch (danceId) {
                    case salsaDanceId:
                        serial.flush();
                        byte = serialSalsa;
                        if(config.bmultiWindow) videoWin.playVideo(salsaDanceId);
                        sceneManager->goToScene(SCENE_8);
                        break;
                        
                    case jiveDanceId:
                        serial.flush();
                        byte = serialJive;
                        if(config.bmultiWindow) videoWin.playVideo(jiveDanceId);
                        sceneManager->goToScene(SCENE_9);
                        break;
                        
                    case waltzDanceId:
                        serial.flush();
                        byte = serialWaltz;
                        if(config.bmultiWindow) videoWin.playVideo(waltzDanceId);
                        sceneManager->goToScene(SCENE_10);
                        break;
                        
                    case cornerId:
                        timer = 0;
                        sceneManager->goToScene(SCENE_12);
                        break;
                }
            //}
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_12)
    {
        timer++;
        if(timer > 60*config.decisionTime*2)
        {
            sceneManager->goToScene(SCENE_1);
            timer = 0;
        }
    }
    if(sceneManager->getcurrentSceneID()==SCENE_13)
    {
        timer++; cout << timer << endl;
        if(timer > 60*config.decisionTime*2)
        {
            if(numberOfUsers==4 || numberOfUsers==2) sceneManager->goToScene(SCENE_3);
            else if(numberOfUsers<4) sceneManager->goToScene(SCENE_2);
            
            timer = 0;
        }
    }
}

//--------------------------------------------------------------
void testApp::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    if (key == 'F' || key == 'f')
    {
        ofToggleFullscreen();
        //windowResized(ofGetScreenWidth(),ofGetScreenHeight());
    }
    //if(key == 'm') numberOfUsers++;
    //if(key == 'l') numberOfUsers--;
        
    switch (key) {
        case OF_KEY_UP:
            angle++;
            if(angle > 30) angle = 30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case 269:
            angle++;
            if(angle > 30) angle = 30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle < -30) angle = -30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case 270:
            angle--;
            if(angle < -30) angle = -30;
            kinect.setCameraTiltAngle(angle);
            break;
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
    sceneManager->windowResized(w,h);
}

//--------------------------------------------------------------
float testApp::msToSecs(int number)
{
    return number/1000;
}

//--------------------------------------------------------------
int testApp::roundUp(float number)
{
    number += 0.5;  // to round up correctly
    return (int)number;
}