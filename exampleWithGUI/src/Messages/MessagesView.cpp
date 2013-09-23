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
, canvas_h(_h * CONVERSATION_PERCENT_HEIGHT/100.0)
, appState(_appState)
, rtp(_rtp)
, canvas(NULL)
, composingCanvas(NULL)
, composingMsg(NULL) {
    ofAddListener(ofEvents().keyPressed, this, &MessagesView::onKeyPressed);
}

MessagesView::~MessagesView() {
    ofRemoveListener(ofEvents().keyPressed, this, &MessagesView::onKeyPressed);
    delete canvas;
    delete composingCanvas;
    delete composingMsg;
}

void MessagesView::setModel(Messages * _model) {
    model = _model;
    ofAddListener(model->newMessage, this, &MessagesView::addMessage);
}

void MessagesView::setup() {
    canvas = new ofxUIScrollbarCanvas(x, y, w, canvas_h);
    canvas->setSnapping(false);
    canvas->setScrollbarImage("GUI/scrollbar.png");
    
    for (int i = 0; i < model->messages.size(); i++ ) {
        addMessage(model->messages[i]);
    }
    
    composingCanvas = new ofxUIScrollbarCanvas(x, y+canvas_h, w, h-canvas_h);
    composingMsg = new ofxUITextArea("composing", currentMessage, w - 50, h-canvas_h - 10, x + 5, y+canvas_h + 5);
    composingCanvas->addWidgetDown(composingMsg);
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
    } else if (key.key == OF_KEY_BACKSPACE) {
        if (currentMessage.size() > 0) {
            currentMessage = currentMessage.substr(0, currentMessage.size()-1);
        }
    } else {
        currentMessage += (char)key.key;
    }
    composingMsg->setTextString(currentMessage);
}

void MessagesView::draw() {
    
    canvas->draw();
    composingCanvas->draw();
    
    /* TODO add back in "composing" display
    if( calling >= 0 && calling<(int)friends.size()){
        if(friends[calling].chatState==ofxXMPPChatStateComposing){
            ofDrawBitmapString(friends[calling].userName + ": ...", ofGetWidth()-280, 20 + i*20 + j*30);
        }
    }*/
}

void MessagesView::update() {
    
    canvas->update();
    composingCanvas->update();
}