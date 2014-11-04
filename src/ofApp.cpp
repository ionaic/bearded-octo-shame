#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetLogLevel(OF_LOG_VERBOSE);

    // Skeltrack Skeleton
    st_skel = skeltrack_skeleton_new();

    // enable depth->video image calibration
    kinect.setRegistration(true);

    // init(true) shows infrared instead of RGB, init(false,false) disables
    // video image (faster fps)
    kinect.init(); 

    kinect.open(); // opens first available kinect

    // print the intrinsic IR sensor values
	if(kinect.isConnected()) {
		ofLogNotice() << "sensor-emitter dist: " 
            << kinect.getSensorEmitterDistance() << "cm";
		ofLogNotice() << "sensor-camera dist:  " 
            << kinect.getSensorCameraDistance() << "cm";
		ofLogNotice() << "zero plane pixel size: " 
            << kinect.getZeroPlanePixelSize() << "mm";
		ofLogNotice() << "zero plane dist: " 
            << kinect.getZeroPlaneDistance() << "mm";
	}

    conv_image.allocate(kinect.width, kinect.height);

	// zero the tilt on startup
	angle = 0;
	kinect.setCameraTiltAngle(angle);

    cb_args.skeleton = &skeleton;
    cb_args.st_skel = st_skel;
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();

    if (kinect.isFrameNew()) {
        conv_image.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);

        skeltrack_skeleton_track_joints(st_skel,
                conv_image.getShortPixelsRef().getPixels(),
                conv_image.getWidth(), conv_image.getHeight(), NULL,
                on_track_joints, &cb_args);

        // TODO: use the ofNodes in this->skeleton to put particle trackers at positions
    }

    // Draw all of the particles
    for(unsigned int p = 0; p < particleSystem.size(); p++){
    	particleSystem[p].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    kinect.drawDepth(0, 0, kinect.width, kinect.height);
    kinect.draw(kinect.width+10, 0, kinect.width, kinect.height);

    // Update each particle (within each chain)
    //std::cout << "Drawing all particles" << std::endl;
    for(unsigned int p = 0; p < particleSystem.size(); p++){
    	particleSystem[p].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == keycode_Esc || key == keycode_Q || key == keycode_q) {
        exit();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

	//FOR TESTING
    for(int i = 0; i < 10; i++){
        if(particleSystem.size() >= i+1){
            particleSystem[i].addParticle(ofVec2f(x+(i*40),y+(i*40)));
        }
        
    }
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	//FOR TESTING

    for(int i = 0; i < 10; i++){
        ofVec3f color =
            ofVec3f(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
        //std::cout << "color for chain: " << color.x << " " << color.y << " " << color.z << std::endl;
        particleSystem.push_back(ParticleChain(color));
    }
	
	//std::cout << "Adding partcle chain" << std::endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();

    g_object_unref(st_skel);
}
