/*
 * AppState.cpp
 *
 * Application state that is shared across multiple classes should be stored
 * here. Member variables are public for convenient reading, but for writing
 * the setter methods should always be used because they trigger events. Many
 * parts of the application can listen for changes to the shared appState
 * object.
 *
 *  Created on: Sep 9, 2013
 *      Author: noura
 */

#include "AppState.h"

AppState::AppState() {
}

void AppState::setChatContact(ofxXMPPUser _user) {
    chatContact = _user;
    //int callingChangeEventArgs = 0; // just a placeholder
    ofNotifyEvent(chatContactChange, chatContact, this);
}
