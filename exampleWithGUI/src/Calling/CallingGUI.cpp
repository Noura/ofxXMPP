/** CallingGUI.h
 *
 *  Created on: Sep 9, 2013
 *      Author: noura
 */

#include "CallingGUI.h"

CallingGUI::CallingGUI(SharedStateBundle * _appState, ofxXMPP * _xmpp)
: appState(_appState)
, xmpp(_xmpp)
, addTempMsg(false)
, friendsView(NULL)
, messages(NULL)
, messagesView(NULL)
, callingDialog(NULL) {
}

CallingGUI::~CallingGUI() {
    ofRemoveListener(appState->chatContactChange, this, &CallingGUI::onChatContactChange);
    ofRemoveListener(xmpp->newMessage, this, &CallingGUI::onNewRemoteMessage);
    delete friendsView;
    delete messagesView;
    delete messages;
    if (callingDialog) ofRemoveListener(callingDialog->answer, this, &CallingGUI::onCallingDialogAnswer);
    delete callingDialog;
}

void CallingGUI::setup() {
    friendsView = new FriendsView(0, 0, CALLING_GUI_FRIENDS_WIDTH, ofGetHeight(), appState, xmpp);
    friendsView->setup();
    
    ofAddListener(appState->chatContactChange, this, &CallingGUI::onChatContactChange);
    ofAddListener(xmpp->newMessage, this, &CallingGUI::onNewRemoteMessage);
}

void CallingGUI::update() {
    friendsView->update();
    if (messagesView) {
        messagesView->update();
        if (addTempMsg) {
            onNewRemoteMessage(tempMsg);
            addTempMsg = false;
        }
    }
}

void CallingGUI::draw() {
    friendsView->draw();
    if (messagesView) messagesView->draw();
    if (callingDialog) callingDialog->draw();
}

void CallingGUI::onChatContactChange(ofxXMPPUser & _user) {
    delete messagesView;
    delete messages;

    messages = new Messages(appState, xmpp);
    messagesView = new MessagesView(CALLING_GUI_FRIENDS_WIDTH, 0, CALLING_GUI_MESSAGES_WIDTH, ofGetHeight(), appState, xmpp);
    messages->setView(messagesView);
    messagesView->setModel(messages);
    messagesView->setup();
}

void CallingGUI::onNewRemoteMessage(ofxXMPPMessage & _msg) {
    if (isSameXMPPUserName(_msg.from, appState->chatContact.userName)) {
        messages->addMessage(_msg);
    } else {
        tempMsg = _msg;
        if (callingDialog) {
            ofRemoveListener(callingDialog->answer, this, &CallingGUI::onCallingDialogAnswer);
            delete callingDialog;
            callingDialog = NULL;
        }
        string dialog = "";
        dialog += _msg.from.substr();
        dialog += " just messaged you. Do you want to switch to a conversation with them?";
        callingDialog = new YesNoDialog(700, 50, 300, 200, dialog);
        callingDialog->setup();
        ofAddListener(callingDialog->answer, this, &CallingGUI::onCallingDialogAnswer);
    }
}

bool CallingGUI::isSameXMPPUserName(string userName1, string userName2) {
    // sometimes email addresses have extra junk characters at the end
    // this checks to see if one email address is the prefix of the other
    if (userName1.size() == 0 || userName2.size() == 0) {
        return false;
    }
    string longNames[] = {userName1, userName2};
    string shortNames[2];
    for (int i = 0; i < 2; i++) {
        string s = longNames[i];
        int n = 0;
        while (s.size() > n && s.at(n) != '/') {
            n++;
        }
        shortNames[i] = s.substr(0, n);
    }
    return shortNames[0].compare(shortNames[1]) == 0;
}

void CallingGUI::onCallingDialogAnswer(bool & _answer) {
    // TODO what if user messages you and then suddenly signs out?
    if (_answer) { // user said yes
        ofxXMPPUser user;
        vector<ofxXMPPUser> friends = xmpp->getFriends();
        for (vector<ofxXMPPUser>::iterator it = friends.begin(); it != friends.end(); it++) {
            if (isSameXMPPUserName(tempMsg.from, it->userName)) {
                user = (*it);
                appState->setChatContact(user);
                addTempMsg = true;
                break;
            }
        }
    }
    ofRemoveListener(callingDialog->answer, this, &CallingGUI::onCallingDialogAnswer);
    delete callingDialog;
    callingDialog = NULL;
}