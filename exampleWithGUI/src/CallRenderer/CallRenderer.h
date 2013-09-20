/*
 *  CallRenderer.h
 *
 *  Handles data transmission and presentation of call video, audio, depth, etc
 *
 *  Created on: Sep 9, 2013
 *      Author: noura (just refactoring arturo's code)
 */

#ifndef example_all_CallRenderer_h
#define example_all_CallRenderer_h

#include <string>
#include "ofMain.h"
#include "ofxFPS.h"
#include "ofxGstRTPUtils.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxGstXMPPRTP.h"
#include "AppState.h"

class CallRenderer {

public:

    CallRenderer(AppState * _appState, ofxGstXMPPRTP * _rtp);
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    enum DrawState {
        LocalRemote,
        LocalPointCloud,
        RemotePointCloud,
        NumStates
    } drawState;
    
    ofxKinect kinect;
    ofxFPS fpsRGB;
    ofxFPS fpsDepth;
    ofxFPS fpsClientVideo;
    ofxFPS fpsClientDepth;
    ofTexture textureVideoRemote, textureDepthRemote;
    ofTexture textureVideoLocal, textureDepthLocal;
    
    ofVboMesh pointCloud;
    ofEasyCam camera;

    ofShader shaderRemoveZero;
    static const string shaderRemoveZeroSource;
    
    ofxCvGrayscaleImage gray;
    ofxCvContourFinder contourFinder;
    ofPolyline remoteContour;
    
    AppState * appState;
    ofxGstXMPPRTP * rtp;
};

#endif