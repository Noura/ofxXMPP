/** Lets the user see their XMPP contacts and select one to chat with.
 *
 * This is intentionally NOT a full featured chat client. It is intended to pair
 * with ofStreamer to help two people on separate computers find each other,
 * text chat a little bit, and call each other to form the peer-to-peer network
 * connection needed for ofStreamer.
 *
 * Text chatting is only provided as a convenience to help people communicate
 * before connecting. For example, Bob and Sue want to connect.
 *
 * Sue: "Hey Bob, ready for our call?"
 * Bob: "Hang on a sec, plugging in my Kinect..."
 * Sue: "OK."
 * Bob: "OK, ready."
 *
 * Perhaps the two connected users could continue to chat while connected and
 * using the application built with ofStreamer.
 *
 * ofxXMPPCaller.h
 *
 *  Created on: Oct 9, 2013
 *      Author: noura
 */

#ifndef OFX_XMPP_CALLER_H_
#define OFX_XMPP_CALLER_H_

#include <iostream>

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxXMPP.h"

#include "CallingGUI.h"
#include "SharedStateBundle.h"

class ofxXMPPCaller {
public:
    
    ofxXMPPCaller(string _capability);
    ~ofxXMPPCaller();
    
    void setup();
    void update();
    void draw();
    
    //TODO do something here
    void onConnectionStateChanged(ofxXMPPConnectionState & connectionState);
    
    SharedStateBundle appState;
    
    ofxXMPP xmpp;
    
    CallingGUI * gui;
    
};

#endif /* defined(OFX_XMPP_CALLER_H_) */
