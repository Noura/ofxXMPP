/*
 *  Messages.h
 *
 *  Manages the friend-to-friend chat messages from RTP
 *  Messages is the model, MessagesView is the view
 *
 *  Created on: Sep 9, 2013
 *      Author: noura
 */

#ifndef example_all_Messages_h
#define example_all_Messages_h

#define MESSAGES_MAX_NUM 25

#include "ofMain.h"
#include "ofxGstXMPPRTP.h"

#include "AppState.h"

class MessagesView;

class Messages {
    
public:
    
    Messages(AppState * _appState, ofxGstXMPPRTP * _rtp);
    ~Messages();
    void setView(MessagesView * view);
    
    void onNewLocalMessage(string & msg);
    void addMessage(ofxXMPPMessage & msg);
    
    deque<ofxXMPPMessage> messages;
    ofEvent<ofxXMPPMessage> newMessage;
    
private:

    AppState * appState;
    ofxGstXMPPRTP * rtp;
    MessagesView * view;
    
};

#endif
