/*
 *  Messages.cpp
 *
 *  Manages the friend-to-friend chat messages from RTP
 *  Messages is the model, MessagesView is the view
 *
 *  Created on: Sep 9, 2013
 *      Author: noura
 */

#include "Messages.h"
#include "MessagesView.h"

Messages::Messages(AppState * _appState, ofxGstXMPPRTP * _rtp)
: appState(_appState)
, rtp(_rtp) {
    ofAddListener(rtp->getXMPP().newMessage, this, &Messages::addMessage);
}

void Messages::setView(MessagesView * view) {
    //TODO ofRemoveListener in destructor or if changing views
    ofAddListener(view->newLocalMessage, this, &Messages::onNewLocalMessage);
}

void Messages::addMessage(ofxXMPPMessage & msg){
	messages.push_back(msg);
	if (messages.size() > MESSAGES_MAX_NUM) messages.pop_front();
    ofNotifyEvent(newMessage, msg, this);
}

void Messages::onNewLocalMessage(string & msg) {
    ofxXMPPMessage message;
    message.body = msg;
    message.from = "me";
    addMessage(message);

    rtp->getXMPP().sendMessage(appState->calling.userName, message.body);
}