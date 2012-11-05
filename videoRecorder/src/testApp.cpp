#include "testApp.h"

void testApp::setup()
{
    ofSetDataPathRoot("../Resources/data/");
    
    //serial.setup("/dev/tty.usbmodemfd131", 9600);
    serial.setup("/dev/tty.usbserial-A4013FB1", 9600);
    serial.flush();
    byte = 0;
    
    ofBackground(0,0,0);
    ofSetFrameRate(24);
    
    recorder.setup();
    
    // setup external cam
    //cout << grabber.listDevices() << endl;
    //grabber.setDeviceID(1);
    grabber.setDeviceID("Logitech Camera");
    
    grabber.initGrabber(CAM_WIDTH,CAM_HEIGHT);
    fboSaver.allocate(CAM_WIDTH, CAM_HEIGHT, GL_RGB);
    fboPixels.allocate(CAM_WIDTH, CAM_HEIGHT, OF_IMAGE_COLOR);
    ofEnableAlphaBlending();
    fboSaver.begin();
    ofClear(255,255,255,0);
    fboSaver.end();
}



void testApp::update() {
    grabber.grabFrame();
    
    //the timing seems pretty good at 24fps
    if (grabber.isFrameNew()){
        if(recorder.getIsRecording()) {
            //Capture a texture to a Frame Buffer Object and write the pixels to our Recorder. 
            fboSaver.begin();
            ofClear(255, 255, 255);
            ofBackground(0, 0, 0);
            grabber.draw(0, 0, 640, 480);
            fboSaver.end();
            
            fboSaver.readToPixels(fboPixels);
            recorder.addFrame(fboPixels);
        }
	}
    
    recorder.update(); 
}

void testApp::draw() {
    grabber.draw(0,0);
    
    byte = serial.readByte();
    if ( byte == OF_SERIAL_NO_DATA )    cout << "no data was read" << endl;
    else if ( byte == OF_SERIAL_ERROR ) cout << "an error occurred" << endl;
    else                                cout << "myByte is " << byte << endl;
    
    if(byte == 10 || byte == 11 || byte == 12)
    {
        recorder.startNewRecording();
        ofDrawBitmapString("Recording", 20, 20);
    }
    if(byte == 255)
    {
        recorder.finishMovie();
        ofDrawBitmapString("Not rec", 20, 50);
        
        string code = generateCode();
        unsigned char buf[7] = { code[0], code[1], code[2], code[3], code[4], code[5], code[6] };
        
        // send to main computer
        serial.writeBytes(&buf[0], 7);
        //cout << code << " - " << code.size() << endl;
    }
}


void testApp::keyPressed(int key) {
    /*switch (key) {
        case 's':
            recorder.finishMovie(); 
            break;
        
        case 'r':
            recorder.startNewRecording(); 
            break; 

        default:
            break;
    }*/
}


void testApp::exit(){ 
    recorder.exit(); 
}

string testApp::generateCode(){
    char $code[7];
    time_t now = time(NULL);
	struct tm *ts2 = localtime(&now);
	strftime($code, sizeof($code), "%H%M-%d", ts2);
    cout << $code << endl;
    string genCode = string($code);
    
    return genCode;
}


