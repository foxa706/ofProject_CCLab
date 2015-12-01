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
    endTime = (10000); //initial time, keep short for tests
    
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

    // attach servo to a flux pin ~
    ard.sendServoAttach(9);
    
}


void ofApp::updateArduino(){
    
    // update the arduino
    ard.update();
    
    // only send if the arduino is ready
    if (bSetupArduino) {

       
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor:: black);
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
                ofSetColor(ofColor::green);
                courierBold30.drawString("Where'd ya go?", 155, ofGetHeight()/2+200);
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
    if (!bTimerReached){
    courierBold30.drawString("+-+-+-+-+ +-+-+-+\n|t|i|c|k| |t|o|c|\n+-+-+-+-+ +-+-+-+", 135, ofGetHeight()/2-100);
    // background of the progress bar
    ofSetColor(ofColor::yellowGreen);
    ofRect((ofGetWidth()-barWidth)/2, (ofGetHeight()/2)+50, barWidth, 30);
    
    // get the percantage of the timer
    float pct = ofMap(timer, 0.0, endTime, 0.0, 1.0, true);
    ofSetColor(ofColor::green);
    ofRect((ofGetWidth()-barWidth)/2, (ofGetHeight()/2)+50, barWidth*pct, 30);
    
    // draw the percantage
    ofSetColor(ofColor::green);
    ofDrawBitmapString(ofToString(pct*100, 0)+"%", ((ofGetWidth()-barWidth)/2)+barWidth+10, (ofGetHeight()/2)+320);

    //    // timer info
    //    string
    //    info = "Timer:   "+ofToString(endTime/60000.0, 1)+" minutes\n";
    //    info += "Time Elapsed:      "+ofToString(timer/60000.0, 1)+" minutes\n";
    //    info += "Percentage: "+ofToString(pct*100, 1)+"%\n";
    //    info += "\nPress 't' to start a new timer\n";
    //    ofSetColor(ofColor::green);
    //    courierBold14.drawString(info, 20, 20);
    }
    // time's up!
    if(bTimerReached) {
        ofBackground(ofColor:: green);
        ofSetFullscreen(true);
        ofSetColor(ofColor::black);
        courierBold30.drawString(" **********     **     **   ** ********       **    \n/////**///     ****   /**  ** /**/////       ****   \n    /**       **//**  /** **  /**           **//**  \n    /**      **  //** /****   /*******     **  //** \n    /**     **********/**/**  /**////     **********\n    /**    /**//////**/**//** /**        /**//////**\n   /**    /**     /**/** //**/********  /**     /**\n     //     //      // //   // ////////   //      // \n ******   *******   ********     **     **   **\n/*////** /**////** /**/////     ****   /**  ** \n/*   /** /**   /** /**         **//**  /** **  \n/******  /*******  /*******   **  //** /****   \n/*//// **/**///**  /**////   **********/**/**  \n/*    /**/**  //** /**      /**//////**/**//** \n/******* /**   //**/********/**     /**/** //**\n///////  //     // //////// //      // //   // ", 30, 30);//take a break in ascii art
        
        courierBold30.drawString("Press 't' for a new timer", 30, 700);
        
        ard.sendServo(9, 180, false);
        
        
    }
    

    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
     //reset the timer
    if(key == 't') {
        bTimerReached = false;
        startTime = ofGetElapsedTimeMillis();
        endTime = (300000);// 5 minutes on the clock!
        ofBackground(ofColor::black);
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
