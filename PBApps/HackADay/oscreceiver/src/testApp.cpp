#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup( PORT );
	
	ofSetFrameRate(100);

	ofBackground( 30, 30, 130 );
	ofSetWindowShape(180, 75);
	
	users[0].id = 0;
	users[1].id = 1;
	users[2].id = 2;
	users[3].id = 3;
	users[4].id = 4;
	
	users[0].instrument = &instruments[0];
	users[1].instrument = &instruments[0];
	users[2].instrument = &instruments[0];
	users[3].instrument = &instruments[0];
	users[4].instrument = &instruments[0];
	
	instruments[0].id = 0;
	instruments[0].l.loadSound("r0.wav");
	instruments[0].l.setMultiPlay(true);
	instruments[0].r.loadSound("l0.wav");
	instruments[0].r.setMultiPlay(true);
	
	instruments[1].id = 1;
	instruments[1].l.loadSound("r1.wav");
	instruments[1].l.setMultiPlay(true);
	instruments[1].r.loadSound("l1.wav");
	instruments[1].r.setMultiPlay(true);

}

//--------------------------------------------------------------
void testApp::update(){

	// check for waiting messages
	while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		
		if ( m.getAddress() == "/hands" )
		{
			int id = m.getArgAsInt32( 0 );
			float center = m.getArgAsInt32(1);
			float right = m.getArgAsInt32(2);
			float left = m.getArgAsInt32(3);
			users[id].center = center;
			users[id].right = right;
			users[id].left = left;
		}
		
		if ( m.getAddress() == "/instrument" )
		{
			int id = m.getArgAsInt32( 0 );
			int instrument = m.getArgAsInt32(1);
			users[id].instrument = &instruments[instrument];
		}

		// check for mouse moved message
		if ( m.getAddress() == "/stomp" )
		{
			// both the arguments are int32's
			int id = m.getArgAsInt32( 0 );
			int foot = m.getArgAsInt32( 1 );			
						
			if (foot == 1) users[id].instrument->r.play();
			else if (foot == 0) users[id].instrument->l.play();
		}
	}

}


//--------------------------------------------------------------
void testApp::draw(){

	stringstream msg;
	for(int i = 0; i< 5; i++){
		msg << "user " << users[i].id << " instrument " << users[i].instrument->id << endl; // << " c "<< users[i].center << " r "<< users[i].right << " l "<< users[i].left << endl;
	}
	
	ofDrawBitmapString(msg.str(), 10,10);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

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

