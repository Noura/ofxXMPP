/*
 *  FriendView.h
 *
 *  Displays one RTP gchat contact
 *
 *  Created on: Sep 16, 2013
 *      Author: noura
 */

#ifndef example_all_FriendView_h
#define example_all_FriendView_h

#define FRIEND_STATE_AVAILABLE_COLOR 27, 224, 126
#define FRIEND_STATE_AWAY_COLOR 246, 246, 0
#define FRIEND_STATE_DND_COLOR 255, 150, 25
#define FRIEND_STATE_XA_COLOR 255, 50, 50

#define FRIEND_STATE_CIRCLE_RADIUS 5
#define FRIEND_STATE_CIRCLE_MARGIN 2

#define FRIEND_HEIGHT 30

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxGstXMPPRTP.h"
#include "AppState.h"

class FriendView : public ofxUILabelButton {

public:
    
    FriendView(ofxXMPPUser _user, float _w, AppState * _appState, ofxGstXMPPRTP * _rtp);
    ~FriendView();

    static bool isValidFriend(const ofxXMPPUser &_user);
    static string formatUserName(string _name);
    void onMousePressed(ofMouseEventArgs &e);
    void draw();
    
    static void drawLegend(float x, float y, AppState * _appState);
    static void drawAvailableIcon(float x, float y);
    static void drawAwayIcon(float x, float y);
    static void drawDndIcon(float x, float y);
    static void drawXAIcon(float x, float y);
    static void drawCapabilityIcon(float x, float y);
    
    ofxXMPPUser user;
    
protected:

    AppState * appState;
    ofxGstXMPPRTP * rtp;
    
};


#endif
