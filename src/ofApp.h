#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofEvents.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
//        void ofAddListener(FaceDetect);

        void ifFaceFound();
        void ifFaceLost();
    
        float startTime; // store when we start time timer
        float endTime; // when do want to stop the timer
    
        bool  bTimerReached; // used as a trigger when we hit the timer
    
        ofVideoGrabber vidGrabber;//using video from cam
        ofxCvHaarFinder finder;//face tracking
        int camWidth;
        int camHeight;
        bool foundFace;

    
        ofTrueTypeFont  courierBold14;
        ofTrueTypeFont  courierBold30;
    
        //arduino setup
        ofArduino	ard;
        bool		bSetupArduino;			// flag variable for setting up arduino once
    
private:
    
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
    void updateArduino();
    
    
		
};
