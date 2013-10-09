/** ofxXMPPCaller.cpp
 *
 *  Created on: Oct 9, 2013
 *      Author: noura
 */

#include "ofxXMPPCaller.h"

void ofxXMPPCaller::setup() {
    ofXml settings;
	settings.load("settings.xml");
	string server = settings.getValue("server");
	string user = settings.getValue("user");
	string pwd = settings.getValue("pwd");
    
    xmpp.setShow(ofxXMPPShowAvailable);
    xmpp.connect(server, user, pwd);
    xmpp.setCapabilities(CALL_CAPABILITY);
    
    appState.setCallCapability(CALL_CAPABILITY);
    
    gui = new CallingGUI(&appState, &xmpp);
    gui->setup();
}

ofxXMPPCaller::~ofxXMPPCaller() {
    delete gui;
}

void ofxXMPPCaller::update() {
    gui->update();
}

void ofxXMPPCaller::draw() {
     gui->draw();
}