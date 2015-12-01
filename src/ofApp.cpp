#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //facial setup
    foundFace = false;
    camWidth 		= 320;	// grab at this size
    camHeight 		= 240;
    
    //initiate the video grabber and load the face tracking model file
    vidGrabber.initGrabber(camWidth,camHeight);
    finder.setup("haarcascade_frontalface_default.xml");

    //timer biz
    bTimerReached = false;
    startTime = ofGetElapsedTimeMillis();  // get the start time
    endTime = (3000); //initial time, keep short for tests
    
    //type setup
    ofTrueTypeFont::setGlobalDpi(72);
    
    courierBold14.loadFont("Courier_New_Bold.ttf", 14, true, true);
    courierBold14.setLineHeight(18.0f);
    courierBold14.setLetterSpacing(1.037);
    
    courierBold30.loadFont("Courier_New_Bold.ttf", 30, true, true);
    courierBold30.setLineHeight(34.0f);
    courierBold30.setLetterSpacing(1.035);
    
    // change below for your usb port
    ard.connect("/dev/tty.usbmodem621", 57600);
    
    // listen for EInitialized notification. this indicates that
    // the arduino is ready to receive commands and it is safe to
    // call setupArduino()
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
}

//--------------------------------------------------------------
void ofApp::ifFaceFound(){
    
}
//--------------------------------------------------------------
void ofApp::ifFaceLost(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //call an update to get a new frame from the camera
    vidGrabber.update();
    updateArduino();
    
    //if there is a new frame, look for faces in it.
    if (vidGrabber.isFrameNew()){
        finder.findHaarObjects(vidGrabber.getPixelsRef());
    }
}
void ofApp::setupArduino(const int & version) {
    
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();

    // attach a servo to a flux pin ~
    ard.sendServoAttach(9);
    
}


void ofApp::updateArduino(){
    
    // update the arduino
    ard.update();
    
    // only send if the arduino is ready
    if (bSetupArduino) {
        // do some biz
       
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (!bSetupArduino){
        cout << "arduino not ready\n" << endl;
    } else {
    for(unsigned int i = 0; i < finder.blobs.size(); i++) {
        ofRectangle face = finder.blobs[i].boundingRect;
        
        if (face.width*2>100) {//is there a significant face area?
            foundFace = true;
            cout <<"Face Detected" << endl;

        }else{
            foundFace = false;
            cout <<"Face Lost" << endl;
        }
        
    }

    float barWidth = 500;
    
    // update the timer
    float timer = ofGetElapsedTimeMillis() - startTime;
    
    if(timer >= endTime && !bTimerReached) {
        bTimerReached = true;
        ofMessage msg("Time is up");
        ofSendMessage(msg);
    }
    
    // background of the progress bar
    ofSetColor(100);
    ofRect((ofGetWidth()-barWidth)/2, (ofGetHeight()/2)+300, barWidth, 30);
    
    // get the percantage of the timer
    float pct = ofMap(timer, 0.0, endTime, 0.0, 1.0, true);
    ofSetColor(ofColor::orangeRed);
    ofRect((ofGetWidth()-barWidth)/2, (ofGetHeight()/2)+300, barWidth*pct, 30);
    
    // draw the percantage
    ofSetColor(20);
    ofDrawBitmapString(ofToString(pct*100, 0)+"%", ((ofGetWidth()-barWidth)/2)+barWidth+10, (ofGetHeight()/2)+320);
    
    // time's up!
    if(bTimerReached) {
        ofBackground(ofColor::paleTurquoise);
        ofSetColor(ofColor::orangeRed);
        ofSetFullscreen(true);
        courierBold30.drawString("Stand up!\n\nBreathe in!\n\nGo outside!", (ofGetWidth()-100)/2, (ofGetHeight()/2));
        ard.sendServo(9, 180, false);
        
    }
    
    // timer info
    string
    info = "Timer:   "+ofToString(endTime/60000.0, 1)+" minutes\n";
    info += "Time Elapsed:      "+ofToString(timer/60000.0, 1)+" minutes\n";
    info += "Percentage: "+ofToString(pct*100, 1)+"%\n";
    info += "\nPress 't' to start a new timer\n";
    ofSetColor(0);
    courierBold14.drawString(info, 20, 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
     //reset the timer
    if(key == 't') {
        bTimerReached = false;
        startTime = ofGetElapsedTimeMillis();
        endTime = (300000);// 5 minutes on the clock!
        ofBackgroundHex(0xc5c9b2);
        ofSetFullscreen(false);
        ard.sendServo(9, 0, false);
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    cout << msg.message << endl;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
