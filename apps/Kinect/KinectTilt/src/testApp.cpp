#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {	
	ofSetFrameRate(60);
	ofSetWindowShape(810, 320);
	ofBackground(0,0,0);
	
	kinect.init();
	kinect.setVerbose(true);
	kinect.open();	
	
	angle = 0;
	kinect.setCameraTiltAngle(angle);
}
//--------------------------------------------------------------
void testApp::update() {	
	kinect.update();
}
//--------------------------------------------------------------
void testApp::draw() {	
	ofSetColor(255, 255, 255);
	kinect.drawDepth(0, 0, 400, 300);
	kinect.draw(410, 0, 400, 300);

	stringstream reportStream;
	reportStream <<  "press UP and DOWN to change the tilt angle: " << angle << " degrees";
	ofDrawBitmapString(reportStream.str(),23,310);
}
//--------------------------------------------------------------
void testApp::exit() {
	kinect.close();
}
//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch (key) {
		case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
			
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
	}
}