#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    faceDetect.setup();
    
    bTimerReached = false;
    startTime = ofGetElapsedTimeMillis();  // get the start time
    endTime = (3000); // 5 minutes on the clock!
}

//--------------------------------------------------------------
void ofApp::update(){
    faceDetect.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    faceDetect.draw();

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
        ofDrawBitmapString("Stand up!\n\nBreathe in!\n\nGo outside!", (ofGetWidth()-100)/2, (ofGetHeight()/2));
        
    }
    
    // timer info
    string
    info = "Timer:   "+ofToString(endTime/60000.0, 1)+" minutes\n";
    info += "Time Elapsed:      "+ofToString(timer/60000.0, 1)+" minutes\n";
    info += "Percentage: "+ofToString(pct*100, 1)+"%\n";
    info += "\nPress 't' to start a new timer\n";
    ofSetColor(0);
    ofDrawBitmapString(info, 20, 20);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
     //reset the timer
    if(key == 't') {
        bTimerReached = false;
        startTime = ofGetElapsedTimeMillis();
        endTime = (300000);
        ofBackgroundHex(0xc5c9b2);
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
