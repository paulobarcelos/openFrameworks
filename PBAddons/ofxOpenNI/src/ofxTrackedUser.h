#pragma once

#include <XnOpenNI.h>
#include <XnCppWrapper.h>
#include "ofMain.h"

struct ofxLimb {
	ofxLimb(XnSkeletonJoint nStartJoint, XnSkeletonJoint nEndJoint) 
		:start_joint(nStartJoint)
		,end_joint(nEndJoint)
		,found(false)
	{
		/*
		position[0].X = position[1].X = 0;
		position[0].Y = position[1].Y = 0;
		position[0].Z = position[1].Z = 0;
		 */
	}
	XnSkeletonJoint start_joint;
	XnSkeletonJoint end_joint;
	//XnPoint3D position[2];
	ofVec3f begin;
	ofVec3f end;
	bool found;
	
	void debugDraw() {
		if(!found)
			return;
		glPushMatrix();
		glLineWidth(5);
		glColor3f(1,0,0);
		glBegin(GL_LINES);
			//std::cout << position[0].X << ", " << position[0].Y << std::endl;
			glVertex2f(begin.x, begin.y);
			glVertex2f(end.x, end.y);
			//glVertex2i(position[0].X, position[0].Y);
			//glVertex2i(position[1].X, position[1].Y);
		glEnd();
		glPopMatrix();
	}
	
};

class ofxUserGenerator;
class ofxDepthGenerator;
class ofxTrackedUser {
public: 
	void debugDraw();
		

	ofxLimb neck;
	
	// left arm + shoulder
	ofxLimb left_shoulder;
	ofxLimb left_upper_arm;
	ofxLimb left_lower_arm;
	
	// right arm + shoulder
	ofxLimb right_shoulder;
	ofxLimb right_upper_arm;
	ofxLimb right_lower_arm;
	
	// torso
	ofxLimb left_upper_torso;
	ofxLimb right_upper_torso;
	
	// left lower torso + leg
	ofxLimb left_lower_torso;
	ofxLimb left_upper_leg;
	ofxLimb left_lower_leg;
	
	// right lower torso + leg
	ofxLimb right_lower_torso;
	ofxLimb right_upper_leg;
	ofxLimb right_lower_leg;

	ofxLimb hip;
	XnUserID id;


private:
	ofxTrackedUser(ofxUserGenerator* pGenerator, ofxDepthGenerator* pDepthGenerator);
	
	void updateBonePositions();
	
	void updateLimb(ofxLimb& rLimb);
	
	ofxUserGenerator* user_generator;
	
	xn::UserGenerator* xn_user_generator;
	
	ofxDepthGenerator* depth_generator;

	friend class ofxUserGenerator;
	
	bool is_tracked;
};
