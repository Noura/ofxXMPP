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
    ofRemoveListener(rtp->getXMPP().userConnected, this, &FriendsView::addFriendView);
    ofRemoveListener(rtp->getXMPP().userDisconnected, this, &FriendsView::removeFriendView);
    delete canvas;
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
    rtp->getXMPP().lock();
    to_add.push_back(user);
    rtp->getXMPP().unlock();
}

void FriendsView::removeFriendView(ofxXMPPUser & user) {
    rtp->getXMPP().lock();
    to_remove.push_back(user);
    rtp->getXMPP().unlock();
}

void FriendsView::update() {
    canvas->update();
}

void FriendsView::draw() {

    rtp->getXMPP().lock();
    while (!to_add.empty()) {
        ofxXMPPUser & user = to_add.front();
        if (FriendView::isValidFriend(user)) {
            FriendView * f = new FriendView(user, w - scroll_w, friend_h, appState, rtp);
            canvas->addWidgetDown(f);
            friendViews.push_back(f);
        }
        to_add.pop_front();
    }

    while (!to_remove.empty()) {
        ofxXMPPUser & user = to_remove.front();
        for (vector<FriendView*>::iterator it = friendViews.begin(); it < friendViews.end(); it++) {
            FriendView * f = (*it);
            if (f->user.userName == user.userName) {
                canvas->removeWidget(f);
                friendViews.erase(it);
                break;
            }
        }
        to_remove.pop_front();
    }
    rtp->getXMPP().unlock();

    float padding_guess = 8.0;
    canvas->setContentHeight(2*padding_guess + (friend_h + padding_guess) * friendViews.size());
    canvas->draw();
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
