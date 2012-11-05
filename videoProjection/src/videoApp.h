#pragma mark once
#include "ofMain.h"

class videoApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
        
    ofVideoPlayer   salsa, jive, waltz;
    float           screenHeight;
    
    ofSerial        serial;
    int             byte;
    
    int             movieWidth, movieHeight;
    
    ofImage         logo;
    int             logoWidth, logoHeight;
};