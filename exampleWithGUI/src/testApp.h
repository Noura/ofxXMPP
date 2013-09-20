/*
 * testApp.h
 *
 *  Created on: Jul 19, 2013
 *      Author: arturo castro
 */

#pragma once

#include "ofMain.h"
#include "ofxGstXMPPRTP.h"
#include "ofxUI.h"

#include "GUI.h"
#include "CallRenderer.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void onConnectionStateChanged(ofxXMPPConnectionState & connectionState);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void onCallingChange(ofxXMPPUser &_user);
    
        AppState appState;

        ofxGstXMPPRTP rtp;
    
        CallRenderer * callRenderer;
    
		GUI *gui;
};
