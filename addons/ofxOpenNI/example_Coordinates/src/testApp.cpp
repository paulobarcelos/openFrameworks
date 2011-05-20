#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);
	context.setupUsingXMLFile(ofToDataPath("openni/config/ofxopenni_config.xml", true));
	depth.setup(&context);
	user.setup(&context, &depth);
}

//--------------------------------------------------------------
void testApp::update(){
	context.update();
	user.update();

}

//--------------------------------------------------------------
void testApp::draw(){
	depth.draw(0,0,640,480);
	user.draw();
	ofxTrackedUser* tracked = user.getTrackedUser(0);
	
	stringstream reportStream;
	
	if(tracked != NULL) {
		tracked->debugDraw();
		
		XnPoint3D pos[2];
		pos[0].X = tracked->left_lower_arm.begin.x;
		pos[0].Y = tracked->left_lower_arm.begin.y;
		pos[0].Z = tracked->left_lower_arm.begin.z;
		
		pos[1].X = tracked->left_lower_arm.begin.x;
		pos[1].Y = tracked->left_lower_arm.begin.y;
		pos[1].Z = tracked->left_lower_arm.begin.z;
		
		depth.getXnDepthGenerator().ConvertProjectiveToRealWorld(2, pos, pos);

		reportStream << "Left Hand X: " << ofToString(pos[1].X, 2) << endl;
		reportStream << "Left Hand Y: " << ofToString(pos[1].Y, 2) << endl;
		reportStream << "Left Hand Z: " << ofToString(pos[1].Z, 2) << endl;
	}

	 // draw instructions
	 ofSetColor(255, 255, 255);	
	 ofDrawBitmapString(reportStream.str(),650,20);
	 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}