//
//  FaceDetect.cpp
//  ofProject
//
//  Created by Audrey on 11/28/15.
//
//

#include "FaceDetect.h"\


//ofEvent<bool> FaceDetect::faceEvent = ofEvent<bool>();


//--------------------------------------------------------------
void FaceDetect::setup(bool _foundFace){
    
//    foundFace = false;
    foundFace = _foundFace;
    
    camWidth 		= 320;	// grab at this size
    camHeight 		= 240;
    
    //initiate the video grabber and load the face tracking model file
    vidGrabber.initGrabber(camWidth,camHeight);
    finder.setup("haarcascade_frontalface_default.xml");
    
}

//--------------------------------------------------------------
void FaceDetect::update(){
    
    //call an update to get a new frame from the camera
    vidGrabber.update();
    
    //if there is a new frame, look for faces in it.
    if (vidGrabber.isFrameNew()){
        finder.findHaarObjects(vidGrabber.getPixelsRef());
    }
}

//--------------------------------------------------------------
void FaceDetect::draw(){

    
//white rectangle for debugging
//    ofNoFill();
//    ofSetLineWidth(2.0);
    for(unsigned int i = 0; i < finder.blobs.size(); i++) {
        ofRectangle face = finder.blobs[i].boundingRect;
//        ofRect(face.x*2, face.y*2, face.width*2, face.height*2);

        if (face.width*2>100) {//is there a significant face area?
            foundFace = true;
            cout <<"Face Detected" << endl;
//            ofNotifyEvent(faceEvent, true);
        }else{
            foundFace = false;
            cout <<"Face Lost" << endl;
//            ofNotifyEvent(faceEvent, false);
//        
        }
        
    }
    
}