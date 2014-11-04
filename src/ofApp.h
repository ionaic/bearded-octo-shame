#pragma once

// OpenFrameworks includes
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

// SkelTrack includes
#include <gfreenect.h>
#include <skeltrack.h>

// local includes
#include "particleChain.h"
#include "ofxkeycode.h"
#include "ofxSkeleton.h"

void on_track_joints(GObject *obj, GAsyncResult *res, gpointer user_data);

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

        // intermediary image for reading out depth data
        ofxCvShortImage conv_image;

        SkeltrackSkeleton *st_skel;
        ofxSkeleton skeleton;

        ofxSkeleton_CBArgs cb_args;
};
