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
	
	trackedUsers = user.getTrackedUsers();
	
	std::vector<ofxTrackedUser*>::iterator userIt = trackedUsers.begin();
	while(userIt != trackedUsers.end()) {
		(*userIt)->debugDraw();
		
		XnPoint3D pos[2];
		pos[0].X = (*userIt)->left_lower_arm.end.x;
		pos[0].Y = (*userIt)->left_lower_arm.end.y;
		pos[0].Z = (*userIt)->left_lower_arm.end.z;
		
		pos[1].X = (*userIt)->left_lower_arm.end.x;
		pos[1].Y = (*userIt)->left_lower_arm.end.y;
		pos[1].Z = (*userIt)->left_lower_arm.end.z;
		
		depth.getXnDepthGenerator().ConvertProjectiveToRealWorld(2, pos, pos);
		
		stringstream reportStream;
		reportStream << "User " << ofToString((*userIt)->id, 1) << endl << "Left Hand (";
		reportStream << ofToString(pos[1].X, 2) << ", ";
		reportStream << ofToString(pos[1].Y, 2) << ", ";
		reportStream << ofToString(pos[1].Z, 2) << ")";
		
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(reportStream.str(),(*userIt)->left_lower_arm.end.x,(*userIt)->left_lower_arm.end.y);		
		
		++userIt;
	}
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