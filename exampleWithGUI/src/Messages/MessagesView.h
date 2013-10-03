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

#define CONVERSATION_PERCENT_HEIGHT 70.0

class Messages;

class MessagesView {
  
public:
    
    MessagesView(float _x, float _y, float _w, float _h, AppState * _appState, ofxGstXMPPRTP * _rtp);
    ~MessagesView();
    void setModel(Messages * _model);

    void setup();
    void update();
    void draw();
    
    static string formatMessage(ofxXMPPMessage msg);
    void addMessage(ofxXMPPMessage &msg);
    void onNewLocalMessage(string &msg);
    ofEvent<string> newLocalMessage;
    
private:
    
    AppState * appState;
    ofxGstXMPPRTP * rtp;
    Messages * model;
    
    float x, y, w, h, canvas_h;
    ofxUIScrollbarCanvas * messagesCanvas;
    float messagesHeight; // must tell messagesCanvas the height of its content
    ofxUICanvas * composingCanvas;
    ofxUITextInput * composingMsg;

};

#endif
