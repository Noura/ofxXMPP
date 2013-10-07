/*
 * GUI.h
 *
 *  Created on: Sep 9, 2013
 *      Author: noura
 */

#include "GUI.h"

GUI::GUI(AppState * _appState, ofxXMPP * _xmpp)
: appState(_appState)
, xmpp(_xmpp)
, friendsView(NULL)
, messages(NULL)
, messagesView(NULL) {
}

GUI::~GUI() {
    ofRemoveListener(appState->chatContactChange, this, &GUI::onChatContactChange);
    ofRemoveListener(xmpp->newMessage, this, &GUI::onNewRemoteMessage);
    delete friendsView;
    delete messagesView;
    delete messages;
}

void GUI::setup() {    
    friendsView = new FriendsView(0, 0, GUI_FRIENDS_WIDTH, ofGetHeight(), appState, xmpp);
    friendsView->setup();
    
    ofAddListener(appState->chatContactChange, this, &GUI::onChatContactChange);
    ofAddListener(xmpp->newMessage, this, &GUI::onNewRemoteMessage);
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

    messages = new Messages(appState, xmpp);
    messagesView = new MessagesView(GUI_FRIENDS_WIDTH, 0, GUI_MESSAGES_WIDTH, ofGetHeight(), appState, xmpp);
    messages->setView(messagesView);
    messagesView->setModel(messages);
    messagesView->setup();
}

void GUI::onNewRemoteMessage(ofxXMPPMessage & _msg) {
    // check if this message is from our current chat contact
    // (the two email addresses will be the same, but _msg.from might have extra junk at the end)
    int n = MIN(_msg.from.length(), appState->chatContact.userName.length());
    if ( n > 0 && _msg.from.compare(0, n, appState->chatContact.userName) == 0 ) {
        messages->addMessage(_msg);
    } else {
        // TODO make a popup to suggest changing convos
    }
}