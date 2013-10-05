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
, legend_h(100.0)
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
    canvas = new ofxUIScrollbarCanvas(x, y, w, h - legend_h);
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
    // this callback runs on the XMPP thread
    rtp->getXMPP().lock();
    to_add.push_back(user);
    rtp->getXMPP().unlock();
}

void FriendsView::removeFriendView(ofxXMPPUser & user) {
    // this callback runs on the XMPP thread
    rtp->getXMPP().lock();
    to_remove.push_back(user);
    rtp->getXMPP().unlock();
}

void FriendsView::update() {
    vector<ofxXMPPUser> to_add_copy;
    vector<ofxXMPPUser> to_remove_copy;
    rtp->getXMPP().lock();
    while (!to_add.empty()) {
        to_add_copy.push_back(to_add.front());
        to_add.pop_front();
    }
    while (!to_remove.empty()) {
        to_remove_copy.push_back(to_remove.front());
        to_remove.pop_front();
    }
    rtp->getXMPP().unlock();
    
    for (vector<ofxXMPPUser>::iterator it = to_add_copy.begin(); it < to_add_copy.end(); it++) {
        ofxXMPPUser user = (*it);
        if (FriendView::isValidFriend(user)) {
            FriendView * f = new FriendView(user, w - scroll_w, appState, rtp);
            canvas->addWidgetToList(f);
        }
    }
    
    list<ofxUIWidget*> friends = canvas->getWidgetList();
    for (vector<ofxXMPPUser>::iterator uit = to_remove_copy.begin(); uit < to_remove_copy.end(); uit++) {
        ofxXMPPUser user = (*uit);
        for (list<ofxUIWidget*>::iterator it = friends.begin(); it != friends.end(); it++) {
            FriendView * f = (FriendView*)(*it);
            if (f->user.userName == user.userName) {
                canvas->removeWidgetFromList(it);
            }
        }
    }
    
    if (to_add_copy.size() > 0 || to_remove_copy.size() > 0) {
        // FriendViewComparator c;
        canvas->sortWidgets(&FriendView::comparator);
    }
    
    canvas->update();
}

void FriendsView::draw() {
    
    canvas->draw();
    
    FriendView::drawLegend(x + 5.0, y + h - legend_h + 5.0, appState);
}
