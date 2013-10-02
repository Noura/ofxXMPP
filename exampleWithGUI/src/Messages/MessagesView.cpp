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
: x(_x)
, y(_y)
, w(_w)
, h(_h)
, msg_h(30)
, canvas_h(_h * CONVERSATION_PERCENT_HEIGHT/100.0)
, appState(_appState)
, rtp(_rtp)
, messagesCanvas(NULL)
, composingCanvas(NULL)
, composingMsg(NULL)
, messagesHeight(0) {

}

MessagesView::~MessagesView() {
    if (model)
        ofRemoveListener(model->newMessage, this, &MessagesView::addMessage);
    if (composingMsg)
        ofRemoveListener(composingMsg->inputSubmitted, this, &MessagesView::onNewLocalMessage);
    delete messagesCanvas;
    delete composingCanvas;
    delete composingMsg;
}

void MessagesView::setModel(Messages * _model) {
    model = _model;
    ofAddListener(model->newMessage, this, &MessagesView::addMessage);
}

void MessagesView::setup() {
    messagesCanvas = new ofxUIScrollbarCanvas(x, y, w, canvas_h);
    messagesCanvas->setSnapping(false);
    messagesCanvas->setScrollbarImage("GUI/scrollbar.png");
    
    for (int i = 0; i < model->messages.size(); i++ ) {
        addMessage(model->messages[i]);
    }

    composingCanvas = new ofxUICanvas(x, y+canvas_h, w, h-canvas_h);
    
    composingMsg = new ofxUITextInput("composing", "", w, h-canvas_h, x, y+canvas_h);
    composingCanvas->addWidgetDown(composingMsg);
    ofAddListener(composingMsg->inputSubmitted, this, &MessagesView::onNewLocalMessage);
}

void MessagesView::onNewLocalMessage(string &msg) {
    ofNotifyEvent(newLocalMessage, msg, this);
}

void MessagesView::addMessage(ofxXMPPMessage &msg) {
    string text = formatMessage(msg);
    ofxUITextArea * messageView = new ofxUITextArea(text, text, w - OFX_UI_MIN_SCROLLBAR_W - 2.0);

    messagesCanvas->addWidgetDown(messageView);
    messagesHeight += messageView->getRect()->height + 6.0;
    messagesCanvas->setContentHeight(MAX(messagesHeight, messagesCanvas->getContentHeight()));
    messageView->setVisible(true);
    messagesCanvas->draw();
    messagesCanvas->scrollToBottom();
}

string MessagesView::formatMessage(ofxXMPPMessage msg) {
    return msg.from + ": " + msg.body;
}

void MessagesView::draw() {
    
    messagesCanvas->draw();
    //composingCanvas->draw();
    
    /* TODO add back in "composing" display
    if( calling >= 0 && calling<(int)friends.size()){
        if(friends[calling].chatState==ofxXMPPChatStateComposing){
            ofDrawBitmapString(friends[calling].userName + ": ...", ofGetWidth()-280, 20 + i*20 + j*30);
        }
    }*/
}

void MessagesView::update() {
    messagesCanvas->update();
    //composingCanvas->update();
}