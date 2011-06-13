#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxUeye.h"
#include "ofxUeyeSettings.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed  (int key);
		void exit();
		void ueyeReady(ofxUeyeEventArgs &args); // Called after any bandwith change, immediately before the first frame is ready (allocate data and adjust pixel clock / fps / exposure here!)
		
		ofxUeye	ueye; // Only one instance of ofxUeye is allowed! ofxUeye is singleton.

		ofxUeyeSettings settings;
		
		ofTexture tex;
};

#endif
