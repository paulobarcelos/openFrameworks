#include "ofxTrackedUser.h"
#include "ofxDepthGenerator.h"
#include "ofxUserGenerator.h"



////////////////////////////////////////////////////////////
// process ------------------------------------------------
////////////////////////////////////////////////////////////
void ofxTrackedUser::process(XnPoint3D r_pos, XnPoint3D l_pos){
	

	pos[0] = r_pos;
	pos[1] = l_pos;
	
	if(pos[0].Y < -1300) pos[0].Y = -1300;
	else if (pos[0].Y > 0) pos[0].Y = 0;
	
	if(pos[1].Y < -1300) pos[0].Y = -1300;
	else if (pos[1].Y > 0) pos[1].Y = 0;
	
	float center = ((hip.begin.x + hip.end.x)/2);
	
	hand[0] = center - right_lower_arm.end.x;
	hand[1] = center - left_lower_arm.end.x;
	
	ofxOscMessage m;
	m.setAddress("/hands");
	m.addFloatArg(id);
	m.addFloatArg(center);
	m.addFloatArg(hand[0]);
	m.addFloatArg(hand[1]);
	oscSender.sendMessage(m);
	
	if(hand[0] < - 120){
		ofxOscMessage m;
		m.setAddress("/instrument");
		m.addIntArg(id);
		m.addIntArg(0);
		oscSender.sendMessage(m);
	}
	
	if(hand[1] > 120){
		ofxOscMessage m;
		m.setAddress("/instrument");
		m.addIntArg(id);
		m.addIntArg(1);
		oscSender.sendMessage(m);
	}
	
	for (int i = 0; i < 2; i++) {
		fastBuffer[i] = (fastBuffer[i] *0.2) + (pos[i].Y*0.8);
		if(!jumpStarted[i]) slowBuffer[i] = (slowBuffer[i] *0.9) + (pos[i].Y*0.1);
		
		if(fastBuffer[i] > (slowBuffer[i] + TOL_JUMP) && !jumpStarted[i]){
			jumpStarted[i] = true;
			jumpDuration[i] = 0;
			jumpFloor[i] = slowBuffer[i];
			jumpStartTimestamp[i] = ofGetElapsedTimeMillis();
		}
		if(fastBuffer[i] < (jumpFloor[i] + TOL_JUMP) && jumpStarted[i]){
			ofxOscMessage m;
			m.setAddress("/stomp");
			m.addIntArg(id);
			m.addIntArg(i);
			oscSender.sendMessage(m);
			
			ofxOscMessage m2;
			m2.setAddress("/Kinect");
			m2.addIntArg(id);
			m2.addIntArg(i);
			oscSender.sendMessage(m2);
			
			jumpStarted[i] = false;
		}
		
		if(jumpStarted[i]) {
			jumpDuration[i] = ofGetElapsedTimeMillis() - jumpStartTimestamp[i];
			if(jumpDuration[i] > 2000)
			{
				jumpStarted[i] = false;
				jumpDuration[i] = 0;
				fastBuffer[i] = pos[i].Y;
				slowBuffer[i] = pos[i].Y;
			}
			
		}
	}
	
	
	
	/*
	
	r_fastBuffer = (r_fastBuffer*0.1) + (r_pos.Y*0.9);
	r_slowBuffer = (r_slowBuffer *0.98) + (r_pos.Y*0.02);
	
	// check if fast buffer is smaller than slow buffer
	if(r_fastBuffer > (r_slowBuffer + TOL_JUMP)){
		r_jumpFloor = r_slowBuffer;
		r_jumpStarted = true;
		r_jumpComplete = false;
	}
	if(r_jumpStarted) {
		if(r_fastBuffer < (r_fastBuffer - TOL_DOWN) && !r_downStarted) {
			r_downStarted = true;
			r_downStartTimestamp = ofGetElapsedTimef();
			r_downStartHeight = r_fastBuffer;
		}
		else if(r_fastBuffer > (r_fastBuffer) && r_downStarted){
			r_downStarted = false;
			r_downStartTimestamp = 0;
		}
	}
	
	if(r_fastBuffer < (r_jumpFloor + TOL_JUMP) && !r_jumpComplete){
		
		r_downEndTimestamp = ofGetElapsedTimef();
		r_downEndHeight = r_fastBuffer;
		
		float diff = r_downEndTimestamp - r_downStartTimestamp;
		ofClamp(diff, 60.f, 130.f);
		
		diff = (diff - 60.f) / 70.f;
		
		float speed = diff;
		
		ofxOscMessage m;
		m.setAddress( "/stomp" );
		m.addIntArg( id );
		m.addIntArg( 1);
		m.addFloatArg(speed) ;
		m.addFloatArg((r_downStartHeight - r_downEndHeight)) ;
		m.addFloatArg((r_downEndTimestamp - r_downStartTimestamp)) ;
		oscSender.sendMessage(m);
		
		r_jumpStarted = false;
		r_jumpComplete = true;
		r_downStarted = false;
	}
	*/

}









































ofxTrackedUser::ofxTrackedUser(
	 ofxUserGenerator* pUserGenerator
	,ofxDepthGenerator* pDepthGenerator
) 
:neck(XN_SKEL_HEAD, XN_SKEL_NECK)

// left arm + shoulder
,left_shoulder(XN_SKEL_NECK, XN_SKEL_LEFT_SHOULDER)
,left_upper_arm(XN_SKEL_LEFT_SHOULDER, XN_SKEL_LEFT_ELBOW)
,left_lower_arm(XN_SKEL_LEFT_ELBOW, XN_SKEL_LEFT_HAND)

// right arm + shoulder
,right_shoulder(XN_SKEL_NECK, XN_SKEL_RIGHT_SHOULDER)
,right_upper_arm(XN_SKEL_RIGHT_SHOULDER, XN_SKEL_RIGHT_ELBOW)
,right_lower_arm(XN_SKEL_RIGHT_ELBOW, XN_SKEL_RIGHT_HAND)

// upper torso
,left_upper_torso(XN_SKEL_LEFT_SHOULDER, XN_SKEL_TORSO)
,right_upper_torso(XN_SKEL_RIGHT_SHOULDER, XN_SKEL_TORSO)

// left lower torso + leg
,left_lower_torso(XN_SKEL_TORSO, XN_SKEL_LEFT_HIP)
,left_upper_leg(XN_SKEL_LEFT_HIP, XN_SKEL_LEFT_KNEE)
,left_lower_leg(XN_SKEL_LEFT_KNEE, XN_SKEL_LEFT_FOOT)

// right lower torso + leg
,right_lower_torso(XN_SKEL_TORSO, XN_SKEL_RIGHT_HIP)
,right_upper_leg(XN_SKEL_RIGHT_HIP, XN_SKEL_RIGHT_KNEE)
,right_lower_leg(XN_SKEL_RIGHT_KNEE, XN_SKEL_RIGHT_FOOT)

,hip(XN_SKEL_LEFT_HIP, XN_SKEL_RIGHT_HIP)
,user_generator(pUserGenerator)
,depth_generator(pDepthGenerator) 
,xn_user_generator(&user_generator->getXnUserGenerator())
,is_tracked(false)
{
	oscSender.setup( HOST, PORT );
	
	for (int i = 0; i < 2; i++) {
		fastBuffer[i] = 0;
		slowBuffer[i] = 0;
	}
	
}

void ofxTrackedUser::updateBonePositions() {
	updateLimb(neck);
	
	// left arm + shoulder
	updateLimb(left_shoulder);
	updateLimb(left_upper_arm);
	updateLimb(left_lower_arm);
	
	// right arm + shoulder
	updateLimb(right_shoulder);
	updateLimb(right_upper_arm);
	updateLimb(right_lower_arm);
	
	// upper torso
	updateLimb(left_upper_torso);
	updateLimb(right_upper_torso);
	
	// left lower torso + leg
	updateLimb(left_lower_torso);
	updateLimb(left_upper_leg);
	updateLimb(left_lower_leg);
	
	// right lower torso + leg
	updateLimb(right_lower_torso);
	updateLimb(right_upper_leg);
	updateLimb(right_lower_leg);

	updateLimb(hip);	
}

void ofxTrackedUser::updateLimb(ofxLimb& rLimb) {
	if(!xn_user_generator->GetSkeletonCap().IsTracking(id)) {
		//printf("Not tracking this user: %d\n", id);
		return;
	}
	
	XnSkeletonJointPosition a,b;
	xn_user_generator->GetSkeletonCap().GetSkeletonJointPosition(id, rLimb.start_joint, a);
	xn_user_generator->GetSkeletonCap().GetSkeletonJointPosition(id, rLimb.end_joint, b);
	if(a.fConfidence < 0.3f || b.fConfidence < 0.3f) {
		rLimb.found = false; 
		return;
	}
	
	XnPoint3D pos[2];
	pos[0] = a.position;
	pos[1] = b.position;
	depth_generator->getXnDepthGenerator()
		.ConvertRealWorldToProjective(2, pos, pos);

	rLimb.found = true;
	rLimb.begin.set(pos[0].X, pos[0].Y, pos[0].Z);
	rLimb.end.set(pos[1].X, pos[1].Y, pos[1].Z);	
}

void ofxTrackedUser::debugDraw() {
	neck.debugDraw();
	
	// left arm + shoulder
	left_shoulder.debugDraw();
	left_upper_arm.debugDraw();
	left_lower_arm.debugDraw();
	
	// right arm + shoulder
	right_shoulder.debugDraw();
	right_upper_arm.debugDraw();
	right_lower_arm.debugDraw();
	
	// upper torso
	left_upper_torso.debugDraw();
	right_upper_torso.debugDraw();
	
	// left lower torso + leg
	left_lower_torso.debugDraw();
	left_upper_leg.debugDraw();
	left_lower_leg.debugDraw();

	// right lower torso + leg
	right_lower_torso.debugDraw();
	right_upper_leg.debugDraw();
	right_lower_leg.debugDraw();
	
	hip.debugDraw();
	ofDrawBitmapString(ofToString((int)id),neck.begin.x+ 10, neck.begin.y);
}
