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
, canvas(NULL) {
}

FriendsView::~FriendsView() {
    if(canvas) delete canvas;
}

void FriendsView::setup() {
    canvas = new ofxUIScrollbarCanvas(x, y, w, h);
    canvas->setSnapping(false);
    canvas->setScrollbarImage("GUI/scrollbar.png");
    
    const vector<ofxXMPPUser> & friends = rtp->getXMPP().getFriends();
    for (int i = 0; i < friends.size(); i++) {
        ofxXMPPUser user = friends[i];
        addFriendView(user);
    }

    ofAddListener(rtp->getXMPP().userConnected, this, &FriendsView::addFriendView);
    ofAddListener(rtp->getXMPP().userDisconnected, this, &FriendsView::removeFriendView);
}

void FriendsView::addFriendView(ofxXMPPUser & user) {
    if (FriendView::isValidFriend(user)) {
        FriendView * f = new FriendView(user, w - scroll_w, friend_h, appState, rtp);
        canvas->addWidgetDown(f);
        friendViews.push_back(f);
        estimateCanvasHeight();
    }
}

void FriendsView::removeFriendView(ofxXMPPUser & user) {
    
    for (vector<FriendView*>::iterator it = friendViews.begin(); it < friendViews.end(); it++) {
        FriendView * f = (*it);
        if (f->user.userName == user.userName) {
            canvas->removeWidget(f);
            friendViews.erase(it);
            estimateCanvasHeight();
            break;
        }
    }
}

void FriendsView::estimateCanvasHeight() {
    float padding_guess = 8.0;
    canvas->setContentHeight(2*padding_guess + (friend_h + padding_guess) * friendViews.size());
}

void FriendsView::update() {
    canvas->update();
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
