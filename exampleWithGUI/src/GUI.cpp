/*
 * GUI.h
 *
 *  Created on: Sep 9, 2013
 *      Author: noura
 */

#include "GUI.h"

GUI::GUI(AppState * _appState, ofxGstXMPPRTP * _rtp, string _call_capability)
: appState(_appState)
, rtp(_rtp)
, call_capability(_call_capability)
, friendsView(NULL)
, messages(NULL)
, messagesView(NULL) {
}

GUI::~GUI() {
    ofRemoveListener(appState->chatContactChange, this, &GUI::onChatContactChange);
    delete friendsView;
    delete messagesView;
    delete messages;
}

void GUI::setup() {    
    friendsView = new FriendsView(0, 0, GUI_FRIENDS_WIDTH, ofGetHeight(), appState, rtp);
    friendsView->setup();
    
    ofAddListener(appState->chatContactChange, this, &GUI::onChatContactChange);
}

void GUI::update() {
    friendsView->update();
    if (messagesView) messagesView->update();
}

void GUI::draw() {
    friendsView->draw();
    if (messagesView) messagesView->draw();
}

void GUI::onChatContactChange(ofxXMPPUser & _user) {
    delete messagesView;
    delete messages;
    rtp->call(_user);
    messages = new Messages(appState, rtp);
    messagesView = new MessagesView(GUI_FRIENDS_WIDTH, 0, GUI_MESSAGES_WIDTH, ofGetHeight(), appState, rtp, call_capability);
    messages->setView(messagesView);
    messagesView->setModel(messages);
    messagesView->setup();
}