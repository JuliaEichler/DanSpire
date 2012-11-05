### About the project

DanSpire is an interactive dancefloor which encourages people to learn how to dance. The mainApp is connected to the Kinect to track the users and to two projectors which simultaneously display the interface on the floor (two projectors to reduce interferences caused by shadows). Another computer runs an app for projecting introductory videos displaying professionals showing the dance. A third computer records the user during the experience and makes the video available to watch immediately after finishing the dance. The 3 computers thereby communicate wirelessly via XBees.
Further information about the concept on http://juliaeichler.de/2012/10/danspire-interactive-dancefloor/


### About the code

The code remains in the state as of the final version that run during the final show in September 2012. I am aware, that there are quite a few repetitions which could have been reduced to some classes to make the code run more efficiently. I also kept some lines commented out which I used for debugging when working with only one computer.

*openFrameworks version* 0071


#### Addons required for this application
**For the mainApp:**
- [ofxKinect](https://github.com/ofTheo/ofxKinect)
- [ofxOpenCv](https://github.com/openframeworks/ofxOpenCv)
- [ofxSceneManager](https://github.com/armadillu/ofxSceneManager) incl. [ofxAnimatable](https://github.com/armadillu/ofxAnimatable) and [ofxScreenCurtain](https://github.com/armadillu/ofxScreenCurtain)
- [ofxCenteredTrueTypeFont](https://github.com/armadillu/ofxCenteredTrueTypeFont)
- [ofxFenster](https://github.com/underdoeg/ofxFenster) (for debugging)

**For the video recorder:**
- [ofxQTKitAVScreenRecorder](https://github.com/sethismyfriend/ofxQTKitAVScreenRecorder) by Seth Hunter (for video recording)