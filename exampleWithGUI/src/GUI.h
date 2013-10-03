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

#define GUI_FRIENDS_WIDTH 300
#define GUI_MESSAGES_WIDTH 300

class GUI {

public:

    GUI(AppState * _appState, ofxGstXMPPRTP * _rtp);
    ~GUI();
    
    void setup();
    void update();
    void draw();
    
    void onChatContactChange(ofxXMPPUser & _user);
    
private:
    
    AppState * appState;
    ofxGstXMPPRTP * rtp;

    FriendsView * friendsView;
    
    Messages * messages;
    MessagesView * messagesView;
    
};


#endif
