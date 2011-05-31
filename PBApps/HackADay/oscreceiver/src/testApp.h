#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "ofxOsc.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20

typedef struct Instrument {
	int id;
	ofSoundPlayer l;
	ofSoundPlayer r;
} Instrument;
typedef struct User {
	Instrument * instrument;
	int id;
	float left;
	float right;
	float center; 
} User;



//--------------------------------------------------------
class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		ofTrueTypeFont		font;
	
		ofSoundPlayer  kick0;
		ofSoundPlayer  snare0;
	
		ofSoundPlayer  kick1;
		ofSoundPlayer  snare1;


private:
		ofxOscReceiver	receiver;
	
		User	users[5];
		Instrument	instruments[2];
};

#endif
