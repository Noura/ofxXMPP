/*
 *  MessagesView.h
 *
 *  Manages the friend-to-friend chat messages from RTP
 *  Messages is the model, MessagesView is the view
 *
 *  Created on: Sep 9, 2013
 *      Author: noura
 */

#ifndef example_all_MessagesView_h
#define example_all_MessagesView_h

#include "ofMain.h"
#include "ofxUI.h"

#include "AppState.h"
#include "Messages.h"

class Messages;

class MessagesView {
  
public:
    
    MessagesView(float _x, float _y, float _w, float _h, AppState * _appState, ofxGstXMPPRTP * _rtp);
    ~MessagesView();
    void setModel(Messages * _model);

    void onKeyPressed(ofKeyEventArgs &key);
    void setup();
    void draw();
    
    static string formatMessage(ofxXMPPMessage msg);
    void addMessage(ofxXMPPMessage &msg);
    
    ofEvent<ofxXMPPMessage> userLocalFinishedTypingMessage;
    std::string currentMessage;
    
private:
    
    AppState * appState;
    ofxGstXMPPRTP * rtp;
    Messages * model;
    
    float x, y, w, h, msg_h;
    ofxUIScrollbarCanvas * canvas;

};

#endif
