//
//  FaceDetect.h
//  ofProject
//
//  Created by Audrey on 11/28/15.
//
//

#pragma once
#include "ofxOpenCv.h"


class FaceDetect{
    
public:
    void setup();
    void update();
    void draw();
    
   
    
    ofVideoGrabber vidGrabber;//using video from cam
    ofxCvHaarFinder finder;//face tracking
    int 				camWidth;
    int 				camHeight;
    
    float pos1;//keep track of the distance between two face rect points for bool
    float pos2;
    
     bool foundFace;
};
