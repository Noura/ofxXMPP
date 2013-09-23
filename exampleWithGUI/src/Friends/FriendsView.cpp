/*
 *  FriendsView.cpp
 *
 *  Manages the list of contacts from RTP
 *  ofxGstXMPPRTP is the model, FriendsView is the view
 *
 *  Created on: Sep 9, 2013
 *      Author: noura
 */

#include "FriendsView.h"

FriendsView::FriendsView(float _x, float _y, float _w, float _h,
                         AppState * _appState, ofxGstXMPPRTP * _rtp)
: x(_x)
, y(_y)
, w(_w)
, h(_h)
, friend_h(20)
, appState(_appState)
, rtp(_rtp)
, canvas(NULL)
, num_friends(0)
, need_to_update(true) {
}

FriendsView::~FriendsView() {
    ofRemoveListener(rtp->getXMPP().userConnected, this, &FriendsView::onXMPPFriendEvent);
    ofRemoveListener(rtp->getXMPP().userDisconnected, this, &FriendsView::onXMPPFriendEvent);
    delete canvas;
}

void FriendsView::setup() {
    ofAddListener(rtp->getXMPP().userConnected, this, &FriendsView::onXMPPFriendEvent);
    ofAddListener(rtp->getXMPP().userDisconnected, this, &FriendsView::onXMPPFriendEvent);
}

void FriendsView::onXMPPFriendEvent(ofxXMPPUser & user) {
    need_to_update = true;
}

void FriendsView::update() {
    if (!need_to_update) {
        return;
    }

    // I used to add and remove FriendView widgets from the canvas individually
    // on XMPP.userConnected and XMPP.userDisconnected events, but ofxUICanvas
    // does not "reflow" its widgets and so there would be holes left by
    // disconnected users. The simplest workaround is just redrawing it all.
    delete canvas;
    canvas = new ofxUIScrollbarCanvas(x, y, w, h);
    canvas->setSnapping(false);
    canvas->setScrollbarImage("GUI/scrollbar.png");
    
    const vector<ofxXMPPUser> & friends = rtp->getXMPP().getFriends();
    int num_friends = friends.size();
    for (int i = 0; i < num_friends; i++) {
        ofxXMPPUser user = friends[i];
        if (FriendView::isValidFriend(user)) {
            FriendView * f = new FriendView(user, w - scroll_w, friend_h, appState, rtp);
            canvas->addWidgetDown(f);
        }
    }
    
    //ofxUIScrollbarCanvas needs to be told its height so it can scroll properly
    float padding_guess = 8.0;
    canvas->setContentHeight(2*padding_guess + (friend_h + padding_guess) * num_friends);
    canvas->update();

    need_to_update = false;
}

void FriendsView::draw() {

    canvas->draw();

    /*
    ofSetColor(255);
    ofRect(x, y, w, h);
    const vector<ofxXMPPUser> & friends = rtp->getXMPP().getFriends();
    
    size_t i=0;
    
    for ( ; i < friends.size(); i++ ) {
        
        ofSetColor(0);
        
        if (appState->calling == i) {
            if (rtp->getXMPP().getJingleState()==ofxXMPP::SessionAccepted) {
                ofSetColor(127); //TODO name the colors
            } else {
                //TODO what does this color function do?
                ofSetColor(ofMap(sin(ofGetElapsedTimef()*2),-1,1,50,127));
            }
            ofRect(x, appState->calling*friend_h + 5, w, friend_h);
            ofSetColor(255);
        }
        
        ofDrawBitmapString(friends[i].userName, x + 50, (i+1) * friend_h);
        
        if (friends[i].show == ofxXMPPShowAvailable) {
            ofSetColor(ofColor::green);
        } else {
            ofSetColor(ofColor::orange);
        }
        
        ofCircle(x+30, (i+1) * friend_h - 5, 3); //TODO name the margin and circle sizes, etc

        for (size_t j = 0; j < friends[i].capabilities.size(); j++) {
            if (friends[i].capabilities[j] == "telekinect") {
                ofNoFill();
                ofCircle(x + 30, (i+1) * friend_h - 5, 5);
                ofFill();
                break;
            }
        }
    }*/
}

void FriendsView::mousePressed(int x, int y, int button) {
    /*
    if (appState->calling == -1) {
        ofVec2f mouse(x,y);
        ofRectangle friendsRect(x, y, w, rtp->getXMPP().getFriends().size() * friend_h);
        if (friendsRect.inside(mouse)) {
            int calling = mouse.y / 20;
            appState->setCalling(calling);
        }
    }*/
}
