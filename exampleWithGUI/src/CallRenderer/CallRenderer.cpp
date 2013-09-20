/*
 *  CallRenderer.cpp
 *
 *  Handles data transmission and presentation of call video, audio, depth, etc
 *
 *  Created on: Sep 9, 2013
 *      Author: noura (just refactoring arturo's code)
 */

#include "CallRenderer.h"

//#define USE_16BIT_DEPTH

#ifdef USE_16BIT_DEPTH
bool depth16=true;
#else
bool depth16=false;
#endif

#define STRINGIFY(x) #x

const string CallRenderer::shaderRemoveZeroSource = STRINGIFY(
    uniform float removeFar;
    void main(){
      gl_TexCoord[0] = gl_MultiTexCoord0;
      if(gl_Vertex.z<0.1){
          gl_Position = vec4(0.,0.,0.,0.);
          gl_FrontColor =  vec4(0.,0.,0.,0.);
      }else if(removeFar>.5 && gl_Vertex.z>490.){
          gl_Position = vec4(0.,0.,0.,0.);
          gl_FrontColor =  vec4(0.,0.,0.,0.);
      }else{
          vec4 pos = gl_Vertex;
          pos.z *= -1.;
          gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * pos;
          gl_FrontColor =  gl_Color;
      }
    }
);

CallRenderer::CallRenderer(AppState * _appState, ofxGstXMPPRTP * _rtp)
: appState(_appState)
, rtp(_rtp) {
}

void CallRenderer::setup() {
    shaderRemoveZero.setupShaderFromSource(GL_VERTEX_SHADER,
                                           shaderRemoveZeroSource);
	shaderRemoveZero.linkProgram();
    
	kinect.init();
	kinect.setRegistration(true);
	kinect.open();
	kinect.setDepthClipping(500,1000);
    
    textureVideoRemote.allocate(640,480,GL_RGB8);
	textureVideoLocal.allocate(640,480,GL_RGB8);
    
	if(depth16){
		textureDepthRemote.allocate(640,480,GL_RGB8);
		textureDepthLocal.allocate(640,480,GL_LUMINANCE16);
	}else{
		textureDepthRemote.allocate(640,480,GL_LUMINANCE8);
		textureDepthLocal.allocate(640,480,GL_LUMINANCE8);
	}
    
	drawState = LocalRemote;
    
	pointCloud.setMode(OF_PRIMITIVE_POINTS);
	pointCloud.getVertices().resize(640*480);
	pointCloud.getTexCoords().resize(640*480);
	pointCloud.setUsage(GL_STREAM_DRAW);
	int i=0;
	for(int y=0;y<480;y++){
		for(int x=0;x<640;x++){
			pointCloud.getTexCoords()[i].set(x,y);
			pointCloud.getVertices()[i++].set(x,y);
		}
	}
    
	//ofSetBackgroundAuto(false);
    
	if(depth16){
		ofxGstRTPUtils::CreateColorGradientLUT(pow(2.f,14.f));
	}
    
	camera.setVFlip(true);
    
	gray.allocate(640,480);
}

void CallRenderer::update() {/*
    {
		kinect.update();
        
		if(kinect.isFrameNewVideo()){
			fpsRGB.newFrame();
			textureVideoLocal.loadData(kinect.getPixelsRef());
			{
				//kinectUpdater.signalNewKinectFrame();
				rtp->getServer().newFrame(kinect.getPixelsRef());
			}
            
		}
        
		if(kinect.isFrameNewDepth()){
			fpsDepth.newFrame();
            
			if(depth16){
				textureDepthLocal.loadData(kinect.getRawDepthPixelsRef());
			}else{
				textureDepthLocal.loadData(kinect.getDepthPixelsRef());
			}
            
			{
				//kinectUpdater.signalNewKinectFrame();
				if(depth16){
					rtp->getServer().newFrameDepth(kinect.getRawDepthPixelsRef());
				}else{
					rtp->getServer().newFrameDepth(kinect.getDepthPixelsRef());
				}
			}
            
			{
				gray.setFromPixels(kinect.getDepthPixelsRef());
				gray.adaptiveThreshold(5,0,false,true);
				contourFinder.findContours(gray,10,640*480/3,1,false,true);
				ofxOscMessage msg;
				msg.setAddress("//telekinect/contour");
                
				if(contourFinder.blobs.size()){
					ofPolyline blob;
					blob.addVertices(contourFinder.blobs[0].pts);
					blob.simplify(2);
					for(int i=0;i<(int)blob.size();i++){
						msg.addFloatArg(blob[i].x);
						msg.addFloatArg(blob[i].y);
					}
				}
				rtp->getServer().newOscMsg(msg);
			}
            
			if(drawState==LocalPointCloud){
				int i=0;
				for(int y=0;y<480;y++){
					for(int x=0;x<640;x++){
						pointCloud.getVertices()[i].set(kinect.getWorldCoordinateAt(x,y,kinect.getRawDepthPixelsRef()[i]));
						i++;
					}
				}
			}
		}
	}
    
	// update the client ànd load the pixels into a texture if there's a new frame
	{
		rtp->getClient().update();
		if(rtp->getClient().isFrameNewVideo()){
			fpsClientVideo.newFrame();
			textureVideoRemote.loadData(rtp->getClient().getPixelsVideo());
		}
		if(rtp->getClient().isFrameNewDepth()){
			fpsClientDepth.newFrame();
			textureDepthRemote.loadData(rtp->getClient().getPixelsDepth());
            
			if(depth16){
				if(drawState==RemotePointCloud){
					int i=0;
					for(int y=0;y<480;y++){
						for(int x=0;x<640;x++){
							pointCloud.getVertices()[i].set(kinect.getWorldCoordinateAt(x, y,
                                    rtp->getClient().getPixelsDepth16()[i]));
							i++;
						}
					}
				}
			}else{
				if(drawState==RemotePointCloud){
					int i=0;
					for(int y=0;y<480;y++){
						for(int x=0;x<640;x++){
							pointCloud.getVertices()[i].set(x-320, y-240,
                                    1000-ofMap(rtp->getClient().getPixelsDepth()[i],
                                    0,255,500,1000));
							i++;
						}
					}
				}
                
			}
		}
        
		if(rtp->getClient().isFrameNewOsc()){
			ofxOscMessage msg = rtp->getClient().getOscMessage();
			remoteContour.clear();
			for(int i=0;i<msg.getNumArgs();i+=2){
				remoteContour.addVertex(msg.getArgAsFloat(i),msg.getArgAsFloat(i+1));
			}
		}
	}
*/}

void CallRenderer::draw() {/*
    switch(drawState){
        case LocalRemote:
            ofSetColor(255);
		{
			textureVideoRemote.draw(0,0);
			ofSetColor(255,255,0);
			remoteContour.draw();
			ofSetColor(255);
			ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
			ofDrawBitmapString(ofToString(fpsClientVideo.getFPS(),2),20,40);
		}
            
		{
			textureDepthRemote.draw(640,0);
			ofDrawBitmapString(ofToString(fpsClientDepth.getFPS(),2),660,20);
		}
            
            ofSetColor(255);
		{
			textureVideoLocal.draw(400,300,240,180);
			ofDrawBitmapString(ofToString(fpsRGB.getFPS(),2),410,315);
		}
		{
			textureDepthLocal.draw(1040,300,240,180);
			ofDrawBitmapString(ofToString(fpsDepth.getFPS(),2),1050,315);
		}
            break;
        case RemotePointCloud:
            if(rtp->getClient().isFrameNewDepth()){
                ofBackground(255);
                ofSetColor(255);
                ofEnableDepthTest();
                shaderRemoveZero.begin();
                shaderRemoveZero.setUniform1f("removeFar",1);
                camera.begin();
                textureVideoRemote.bind();
                pointCloud.draw();
                textureVideoRemote.unbind();
                camera.end();
                shaderRemoveZero.end();
                ofDisableDepthTest();
            }
            break;
        case LocalPointCloud:
            if(kinect.isFrameNewDepth()){
                ofBackground(255);
                ofSetColor(255);
                ofEnableDepthTest();
                shaderRemoveZero.begin();
                shaderRemoveZero.setUniform1f("removeFar",0);
                camera.begin();
                textureVideoLocal.bind();
                pointCloud.draw();
                textureVideoLocal.unbind();
                camera.end();
                shaderRemoveZero.end();
                ofDisableDepthTest();
            }
            break;
	}
*/}

void CallRenderer::keyPressed(int key){
    if(key == OF_KEY_RIGHT){
		drawState =(DrawState)(drawState+1);
		drawState = (DrawState)(drawState%NumStates);
	}else if (key == OF_KEY_LEFT){
		drawState = (DrawState)(drawState-1);
		drawState = (DrawState)(drawState%NumStates);
	}
}