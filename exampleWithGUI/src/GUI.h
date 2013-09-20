/*
 * GUI.h
 *
 *  Created on: Sep 9, 2013
 *      Author: noura
 */

#ifndef example_all_GUI_h
#define example_all_GUI_h

#include "AppState.h"
#include "ofxUI.h"
#include "Messages/Messages.h"
#include "Messages/MessagesView.h"
#include "Friends/FriendsView.h"

class GUI {

public:

    GUI(AppState * _appState, ofxGstXMPPRTP * _rtp);
    ~GUI();
    
    void setup();
    void update();
    void draw();
    
private:
    
    AppState * appState;
    ofxGstXMPPRTP * rtp;

    FriendsView * friendsView;
    
    Messages * messages;
    MessagesView * messagesView;
    
};


#endif
