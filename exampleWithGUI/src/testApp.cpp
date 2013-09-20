#include "testApp.h"
#include "ofxGstRTPUtils.h"

void testApp::setup(){
	ofSetLogLevel(ofxGstRTPClient::LOG_NAME,OF_LOG_VERBOSE);

	ofXml settings;
	settings.load("settings.xml");
	string server = settings.getValue("server");
	string user = settings.getValue("user");
	string pwd = settings.getValue("pwd");
    
	rtp.setup(0);
	rtp.getXMPP().setCapabilities("telekinect");
	rtp.connectXMPP(server,user,pwd);
	rtp.addSendVideoChannel(640,480,30,300);
	rtp.addSendDepthChannel(640,480,30,300);
	rtp.addSendOscChannel();
	rtp.addSendAudioChannel();
    
    callRenderer = new CallRenderer(&appState, &rtp);
    callRenderer->setup();

    gui = new GUI(&appState, &rtp);
    gui->setup();
    
    ofAddListener(appState.callingChange, this, &testApp::onCallingChange);
}

void testApp::exit(){
    delete callRenderer;
    delete gui;
}


//--------------------------------------------------------------
void testApp::update(){
    callRenderer->update();
    gui->update();

	/*if(calling!=-1){
		if(rtp.getXMPP().getJingleState()==ofxXMPP::Disconnected){
			calling = -1;
		}
	}*/

}

//--------------------------------------------------------------
void testApp::draw(){
    callRenderer->draw();
    gui->draw();
}

void testApp::onCallingChange(ofxXMPPUser &_user) {
    rtp.call(_user);
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
