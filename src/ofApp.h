#pragma once

#include "ofMain.h"
//#include "ofxOpenCV.h"
#include "ofxKinect.h"

<<<<<<< HEAD
#include "particleChain.h"
=======
#include "keycode.h"
>>>>>>> e24ae659ce14923d96d772641cf777c7c68f2160

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

        std::vector<ParticleChain> particleSystem;
};
