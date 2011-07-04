#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(100);
	ofBackground(0,0,0);
	ofSetLogLevel(OF_LOG_WARNING);
	ofSetWindowShape(640, 604);
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
		
		XnPoint3D l_pos[2];
		l_pos[0].X = (*userIt)->left_lower_leg.end.x;
		l_pos[0].Y = (*userIt)->left_lower_leg.end.y;
		l_pos[0].Z = (*userIt)->left_lower_leg.end.z;
		
		l_pos[1].X = (*userIt)->left_lower_leg.end.x;
		l_pos[1].Y = (*userIt)->left_lower_leg.end.y;
		l_pos[1].Z = (*userIt)->left_lower_leg.end.z;
		
		depth.getXnDepthGenerator().ConvertProjectiveToRealWorld(2, l_pos, l_pos);
		
		XnPoint3D r_pos[2];
		r_pos[0].X = (*userIt)->right_lower_leg.end.x;
		r_pos[0].Y = (*userIt)->right_lower_leg.end.y;
		r_pos[0].Z = (*userIt)->right_lower_leg.end.z;
		
		r_pos[1].X = (*userIt)->right_lower_leg.end.x;
		r_pos[1].Y = (*userIt)->right_lower_leg.end.y;
		r_pos[1].Z = (*userIt)->right_lower_leg.end.z;
		
		depth.getXnDepthGenerator().ConvertProjectiveToRealWorld(2, r_pos, r_pos);
		
		(*userIt)->process(r_pos[1], l_pos[1]);
		
		stringstream reportStream;
		reportStream << "Hi Pass R " << (*userIt)->fastBuffer[0] << endl;
		reportStream << "Low Pass R " << (*userIt)->slowBuffer[0] << endl;
		reportStream << "Hi Pass " << (*userIt)->fastBuffer[1] << endl;
		reportStream << "Low Pass L " << (*userIt)->slowBuffer[1] << endl;
		
		if((*userIt)->jumpStarted[1]) reportStream << "LEFT! "  << endl;
		else reportStream <<  endl;
		if((*userIt)->jumpStarted[0]) reportStream << "RIGHT! "  << endl;
		else reportStream <<  endl;
		
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(reportStream.str(),20+ (((*userIt)->id-1)*200), 510);		
		
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