/*
 * GUI.h
 *
 *  Created on: Sep 9, 2013
 *      Author: noura
 */

#include "GUI.h"

GUI::GUI(AppState * _appState, ofxGstXMPPRTP * _rtp)
: appState(_appState)
, rtp(_rtp)
, friendsView(NULL)
, messages(NULL)
, messagesView(NULL) {
}

GUI::~GUI() {
    delete friendsView;
    delete messages;
    delete messagesView;
}

void GUI::setup() {
    float friends_w = 300;
    float messages_w = 300;
    
    friendsView = new FriendsView(0, 0, friends_w, ofGetHeight(), appState, rtp);
    friendsView->setup();
    
    messages = new Messages(appState, rtp);
    messagesView = new MessagesView(friends_w, 0, messages_w, ofGetHeight(), appState, rtp);
    messages->setView(messagesView);
    messagesView->setModel(messages);
    messagesView->setup();
}

void GUI::update() {
    friendsView->update();
}

void GUI::draw() {
    
    friendsView->draw();
    messagesView->draw();
}