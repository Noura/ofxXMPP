/*
 *  MessagesView.cpp
 *
 *  Manages the friend-to-friend chat messages from RTP
 *  Messages is the model, MessagesView is the view
 *
 *  Created on: Sep 9, 2013
 *      Author: noura
 */

#include "MessagesView.h"
#include "Messages.h"

MessagesView::MessagesView(float _x, float _y, float _w, float _h, AppState * _appState, ofxGstXMPPRTP * _rtp)
: currentMessage("")
, x(_x)
, y(_y)
, w(_w)
, h(_h)
, msg_h(30)
, appState(_appState)
, rtp(_rtp)
, canvas(NULL) {
    ofAddListener(ofEvents().keyPressed, this, &MessagesView::onKeyPressed);
}

MessagesView::~MessagesView() {
    if (canvas) delete canvas;
}

void MessagesView::setModel(Messages * _model) {
    model = _model;
    ofAddListener(model->newMessage, this, &MessagesView::addMessage);
}

void MessagesView::setup() {
    canvas = new ofxUIScrollbarCanvas(x, y, w, h);
    canvas->setSnapping(false);
    canvas->setScrollbarImage("GUI/scrollbar.png");
    
    for (int i = 0; i < model->messages.size(); i++ ) {
        addMessage(model->messages[i]);
    }
}

void MessagesView::addMessage(ofxXMPPMessage &msg) {
    string text = formatMessage(msg);
    ofxUITextArea * messageView = new ofxUITextArea(text, text, w - OFX_UI_MIN_SCROLLBAR_W - 2.0);
    canvas->addWidgetDown(messageView);
    messageView->setVisible(true);
    cout << "MESSAGE: " << text << "[EOM]" << endl;
    canvas->draw();
}

string MessagesView::formatMessage(ofxXMPPMessage msg) {
    return msg.from + " " + msg.body;
}

void MessagesView::onKeyPressed(ofKeyEventArgs &key) {
    if (key.key == OF_KEY_LEFT || key.key == OF_KEY_RIGHT) {
        return;
    }
    if (key.key == OF_KEY_RETURN) {
        ofxXMPPMessage msg;
        msg.from = "me:"; // TODO use actual user name
        msg.body = currentMessage.substr();
        ofNotifyEvent(userLocalFinishedTypingMessage, msg, this);
        currentMessage = "";
    } else {
        currentMessage += (char)key.key;
    }
}

void MessagesView::draw() {
    
    canvas->draw();
    
    /* TODO add back in "composing" display
    if( calling >= 0 && calling<(int)friends.size()){
        if(friends[calling].chatState==ofxXMPPChatStateComposing){
            ofDrawBitmapString(friends[calling].userName + ": ...", ofGetWidth()-280, 20 + i*20 + j*30);
        }
    }*/
}