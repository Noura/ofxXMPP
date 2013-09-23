/*
 *  FriendsView.h
 *
 *  Manages the list of contacts from RTP
 *  ofxGstXMPPRTP is the model (accessible through appState),
 *  FriendsView is the view
 *
 *  Created on: Sep 9, 2013
 *      Author: noura
 */

#ifndef example_all_FriendsView_h
#define example_all_FriendsView_h

class GUI;

#include "ofMain.h"
#include "ofxUI.h"

#include "ofxGstXMPPRTP.h"
#include "AppState.h"
#include "FriendView.h"

class FriendsView {
    
public:
    
    FriendsView(float _x, float _y, float _w, float _h, AppState * _appState,
                ofxGstXMPPRTP * _rtp);
    ~FriendsView();

    void addFriendView(ofxXMPPUser & user);
    void removeFriendView(ofxXMPPUser & user);
    void mousePressed(int x, int y, int button);
    void setup();
    void update();
    void draw();

private:
    
    AppState * appState;
    ofxGstXMPPRTP * rtp;
    
    float x, y, w, h, friend_h;
    float scroll_w = 30;
    ofxUIScrollbarCanvas * canvas;
    vector<FriendView*> friendViews;
    deque<ofxXMPPUser> to_remove;
    deque<ofxXMPPUser> to_add;
};

#endif