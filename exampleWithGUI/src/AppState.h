/*
 * AppState.h
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

#ifndef example_all_AppState_h
#define example_all_AppState_h

#include "ofxGstXMPPRTP.h"

class AppState {
    
public:
    
    AppState();
    
    // the friend index in rtp->getXMPP().getFriends() being called
    // -1 means no one is being called
    ofxXMPPUser calling;
    ofEvent<ofxXMPPUser> callingChange;
    void setCalling(ofxXMPPUser _user);

};

#endif
