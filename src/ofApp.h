#pragma once

// OpenFrameworks includes
#include "ofMain.h"
#include "ofxOpenCV.h"
#include "ofxKinect.h"

// OpenNI includes
//#include <OpenNI.h>

// local includes
#include "keycode.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();

    private:
        ofxKinect kinect;
        int angle;
};
