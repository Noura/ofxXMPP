/*
 *  FriendView.h
 *
 *  Displays one RTP gchat contact
 *
 *  Created on: Sep 16, 2013
 *      Author: noura
 */

#include "FriendView.h"
 
FriendView::FriendView(ofxXMPPUser _user, float _w, AppState * _appState, ofxGstXMPPRTP * _rtp)
: ofxUILabelButton(formatUserName(_user.userName), false, _w, FRIEND_HEIGHT, OFX_UI_FONT_SMALL_SIZE, true)
, user(_user)
, appState(_appState)
, rtp(_rtp) {
    ofAddListener(ofEvents().mouseReleased, this, &FriendView::onMousePressed);
    float xIndent = 4.0 + 4 + FRIEND_STATE_CIRCLE_RADIUS;
    label->getRect()->x = getRect()->x + xIndent;
    label->getRect()->y = getRect()->y + 0.25 * FRIEND_HEIGHT;
}

FriendView::~FriendView() {
    ofRemoveListener(ofEvents().mouseReleased, this, &FriendView::onMousePressed);
}


void FriendView::draw() {
    ofxUILabelButton::draw();
    
    float r = FRIEND_STATE_CIRCLE_RADIUS;
    float m = FRIEND_STATE_CIRCLE_MARGIN;
    float shape_x = getParent()->getRect()->x + rect->x + m;
    float shape_y = getParent()->getRect()->y + rect->y + rect->height/2;
    
    bool has_capability = false;
    for (int i = 0; i < user.capabilities.size(); i++) {
        if (user.capabilities[i] == appState->callCapability) {
            has_capability = true;
            break;
        }
    }
    
    if (has_capability && user.show == ofxXMPPShowAvailable) {
        drawCapabilityIcon(shape_x, shape_y - FRIEND_STATE_CIRCLE_RADIUS);
    } else if (user.show == ofxXMPPShowAvailable) {
        drawAvailableIcon(shape_x, shape_y - FRIEND_STATE_CIRCLE_RADIUS);
    } else if (user.show == ofxXMPPShowAway) {
        drawAwayIcon(shape_x, shape_y - FRIEND_STATE_CIRCLE_RADIUS);
    } else if (user.show == ofxXMPPShowDnd) {
        drawDndIcon(shape_x, shape_y - FRIEND_STATE_CIRCLE_RADIUS);
    } else if (user.show == ofxXMPPShowXA) {
        drawXAIcon(shape_x, shape_y - FRIEND_STATE_CIRCLE_RADIUS);
    }
}

void FriendView::onMousePressed(ofMouseEventArgs &e) {
    if (!rect->inside(e.x, e.y)) {
        return;
    }
    appState->setChatContact(user);
}

/* UTILITY FUNCTIONS ***********************************************************
 * FriendView knows the most about how to format email addresses and
 * represent availability status, but sometimes other classes want to
 * mimic the way that FriendView draws or formats things. So many of 
 * these functions are static.
 */

bool FriendView::isValidFriend(const ofxXMPPUser &_user) {
    // filter out friends that do not actually have a user name
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

void FriendView::drawLegend(float x, float y, AppState * _appState) {
    //TODO remove magic numbers
    float margin = 2.0;
    float lineH = 18.0;
    float lineY = y + 2.0;
    float labelYOffset = 10.0;
    float iconX = x + 2.0;
    float labelX = x + 4.0 + 4 * FRIEND_STATE_CIRCLE_RADIUS;
    if (_appState->callCapability.size() > 0) {
        drawCapabilityIcon(iconX, lineY);
        ofDrawBitmapString("Has calling capability", labelX, lineY + labelYOffset);
        lineY += lineH;
    }
    drawAvailableIcon(iconX, lineY);
    ofDrawBitmapString("Available", labelX, lineY + labelYOffset);
    lineY += lineH;
    drawAwayIcon(iconX, lineY);
    ofDrawBitmapString("Away", labelX, lineY + labelYOffset);
    lineY += lineH;
    drawDndIcon(iconX, lineY);
    ofDrawBitmapString("Do not disturb", labelX, lineY + labelYOffset);
    lineY += lineH;
    drawXAIcon(iconX, lineY);
    ofDrawBitmapString("XA", labelX, lineY + labelYOffset);
}

void FriendView::drawAvailableIcon(float x, float y) {
    ofPushStyle();
    ofSetColor(FRIEND_STATE_AVAILABLE_COLOR);
    ofCircle(x + FRIEND_STATE_CIRCLE_RADIUS, y + FRIEND_STATE_CIRCLE_RADIUS, FRIEND_STATE_CIRCLE_RADIUS);
    ofPopStyle();
}

void FriendView::drawAwayIcon(float x, float y) {
    ofPushStyle();
    ofSetColor(FRIEND_STATE_AWAY_COLOR);
    ofRect(x, y, 2*FRIEND_STATE_CIRCLE_RADIUS, 2*FRIEND_STATE_CIRCLE_RADIUS);
    ofPopStyle();
}

void FriendView::drawDndIcon(float x, float y) {
    ofPushStyle();
    ofSetColor(FRIEND_STATE_DND_COLOR);
    ofRect(x, y, 2*FRIEND_STATE_CIRCLE_RADIUS, 2*FRIEND_STATE_CIRCLE_RADIUS);
    ofPopStyle();
}

void FriendView::drawXAIcon(float x, float y) {
    ofPushStyle();
    ofSetColor(FRIEND_STATE_XA_COLOR);
    ofRect(x, y, 2*FRIEND_STATE_CIRCLE_RADIUS, 2*FRIEND_STATE_CIRCLE_RADIUS);
    ofPopStyle();
}

void FriendView::drawCapabilityIcon(float x, float y) {
    drawAvailableIcon(x, y);
    ofPushStyle();
    ofNoFill();
    ofSetColor(FRIEND_STATE_AVAILABLE_COLOR);
    ofCircle(x + FRIEND_STATE_CIRCLE_RADIUS, y + FRIEND_STATE_CIRCLE_RADIUS, 2 * FRIEND_STATE_CIRCLE_RADIUS);
    ofPopStyle();
}
