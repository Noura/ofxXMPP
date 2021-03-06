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

MessagesView::MessagesView(float _x, float _y, float _w, float _h, SharedStateBundle * _appState, ofxXMPP * _xmpp)
: x(_x)
, y(_y)
, w(_w)
, h(_h)
, title_h(30.0)
, appState(_appState)
, xmpp(_xmpp)
, call_button_label("Call")
, messagesCanvas(NULL)
, composingCanvas(NULL)
, composingMsg(NULL)
, callButton(NULL)
, callButtonCanvas(NULL) {
    canvas_h = h * CONVERSATION_PERCENT_HEIGHT/100.0 - title_h;
}

MessagesView::~MessagesView() {
    if (model)
        ofRemoveListener(model->newMessage, this, &MessagesView::addMessage);
    if (composingMsg)
        ofRemoveListener(composingMsg->inputSubmitted, this, &MessagesView::onNewLocalMessage);
    delete messagesCanvas;
    delete composingCanvas;
    delete callButtonCanvas;
}

void MessagesView::setModel(Messages * _model) {
    model = _model;
    ofAddListener(model->newMessage, this, &MessagesView::addMessage);
}

void MessagesView::setup() {
    ofxXMPPUser user = appState->chatContact;

    title = FriendView::formatUserName(user.userName);
    
    if (appState->callCapability.size() > 0) {
        for (int i = 0; i < user.capabilities.size(); i++) {
            if (user.capabilities[i] == appState->callCapability && !callButton) {
                float bX = x + w - 50.0;
                float bY = y + 3.0;
                float bW = 50.0;
                float bH = title_h - 6.0;
                callButtonCanvas = new ofxUICanvas(bX, bY, bW, bH);
                callButton = new ofxUILabelButton(call_button_label, false, bW, bH, bX, bY, OFX_UI_FONT_SMALL_SIZE);
                callButtonCanvas->addWidgetDown(callButton);
            }
        }
    }
    
    messagesCanvas = new ofxUIScrollbarCanvas(x, y + title_h, w, canvas_h);
    messagesCanvas->setSnapping(false);
    messagesCanvas->setScrollbarImage("GUI/scrollbar.png");
    for (int i = 0; i < model->messages.size(); i++ ) {
        addMessage(model->messages[i]);
    }

    composingCanvas = new ofxUICanvas(x, y + title_h + canvas_h, w, h - title_h - canvas_h);
    composingMsg = new ofxUITextInput("composing", "", w, h - title_h - canvas_h, x, y + title_h + canvas_h);
    composingCanvas->addWidgetDown(composingMsg);
    composingMsg->focus();
    ofAddListener(composingMsg->inputSubmitted, this, &MessagesView::onNewLocalMessage);
}

void MessagesView::onNewLocalMessage(string &msg) {
    ofNotifyEvent(newLocalMessage, msg, this);
}

void MessagesView::addMessage(ofxXMPPMessage &msg) {
    string text = formatMessage(msg);
    ofxUITextArea * messageView = new ofxUITextArea(text, text, w - OFX_UI_MIN_SCROLLBAR_W - 2.0);

    messagesCanvas->addWidgetToList(messageView);
    messagesCanvas->scrollToBottom();
}

string MessagesView::formatMessage(ofxXMPPMessage msg) {
    string from = msg.from.substr();
    int i = from.find('@');
    if (i < from.size()) {
        from = from.substr(0, i);
    }
    return from + ": " + msg.body;
}

void MessagesView::draw() {
    ofPushStyle();
    ofSetColor(0);
    ofDrawBitmapString("Chat with " + title, x + 3.0, y + title_h - 3.0);
    ofPopStyle();
    
    messagesCanvas->draw();
    if (callButton)
        callButtonCanvas->draw();

    composingCanvas->draw();
    
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