#include "testApp.h"

void testApp::setup(){

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

void testApp::exit(){
    delete gui;
}


//--------------------------------------------------------------
void testApp::update(){
    gui->update();

	/*if(calling!=-1){
		if(rtp.getXMPP().getJingleState()==ofxXMPP::Disconnected){
			calling = -1;
		}
	}*/

}

//--------------------------------------------------------------
void testApp::draw(){
    gui->draw();
}

void testApp::keyPressed(int key) {
    
}

void testApp::keyReleased(int key) {
    
}

void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
