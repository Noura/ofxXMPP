/*
 *  FriendView.h
 *
 *  Displays one RTP gchat contact
 *
 *  Created on: Sep 16, 2013
 *      Author: noura
 */

#include "FriendView.h"
 
FriendView::FriendView(ofxXMPPUser _user, float _w, float _h, AppState * _appState, ofxGstXMPPRTP * _rtp)
: ofxUILabelButton(formatUserName(_user.userName), false, _w, _h, OFX_UI_FONT_SMALL_SIZE, true)
, user(_user)
, appState(_appState)
, rtp(_rtp) {
    ofAddListener(ofEvents().mouseReleased, this, &FriendView::onMouseReleased);
}

FriendView::~FriendView() {
    ofRemoveListener(ofEvents().mouseReleased, this, &FriendView::onMouseReleased);
}

bool FriendView::isValidFriend(const ofxXMPPUser &_user) {
    string name = FriendView::formatUserName(_user.userName);
    return (name != "");
}

string FriendView::formatUserName(string _name) {
    //string spam = "public.talk.google.com"; //TODO filter out gchat contacts from this domain
    
    //TODO include extended ascii so we can use a real ellipsis
    int max_name_length = 20;
    string ellipsis = "...";
    if (_name.length() < max_name_length) {
        return _name;
    }
    string name = _name.substr(0, max_name_length-ellipsis.length())
    + ellipsis;
    return name;
}

void FriendView::draw() {
    ofxUILabelButton::draw();
    ofPushStyle();

    if (user.show == ofxXMPPShowAvailable) {
        ofSetColor(FRIEND_STATE_AVAILABLE_COLOR);
    } else if (user.show == ofxXMPPShowAway) {
        ofSetColor(FRIEND_STATE_AWAY_COLOR);
    } else if (user.show == ofxXMPPShowDnd) {
        ofSetColor(FRIEND_STATE_DND_COLOR);
    } else if (user.show == ofxXMPPShowXA) {
        ofSetColor(FRIEND_STATE_XA_COLOR);
    }
    
    float r = FRIEND_STATE_CIRCLE_RADIUS;
    float m = FRIEND_STATE_CIRCLE_MARGIN;
    float shape_x = getParent()->getRect()->x + rect->x + r + m;
    float shape_y = getParent()->getRect()->y + rect->y + rect->height/2;
    if (user.show == ofxXMPPShowAvailable) {
        ofCircle(shape_x, shape_y, r);
        for (int i = 0; i < user.capabilities.size(); i++) {
            if (user.capabilities[i] == "telekinect" || i == 0) {
                ofNoFill();
                ofCircle(shape_x, shape_y, 2*r);
                ofFill();
            }
        }
    } else {
        ofRect(shape_x - r, shape_y - r, r*2, r*2);
    }

    ofPopStyle();
}

void FriendView::onMouseReleased(ofMouseEventArgs &e) {
    if (!rect->inside(e.x, e.y)) {
        return;
    }
    appState->setCalling(user);
}