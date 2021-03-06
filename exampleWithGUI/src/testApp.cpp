#include "testApp.h"

void testApp::setup(){
    xmppCaller = new ofxXMPPCaller("telekinect");
    xmppCaller->setup();
}

void testApp::exit(){
    delete xmppCaller;
}

void testApp::update(){
    xmppCaller->update();
}

void testApp::draw(){
    xmppCaller->draw();
}

/* Required method stubs for ofBaseApp ****************************************/

void testApp::keyPressed(int key) {}

void testApp::keyReleased(int key) {}

void testApp::mouseMoved(int x, int y ) {}

void testApp::mouseDragged(int x, int y, int button) {}

void testApp::mouseReleased(int x, int y, int button) {}

void testApp::mousePressed(int x, int y, int button) {}

void testApp::windowResized(int w, int h) {}

void testApp::dragEvent(ofDragInfo dragInfo) {}

void testApp::gotMessage(ofMessage msg) {}
