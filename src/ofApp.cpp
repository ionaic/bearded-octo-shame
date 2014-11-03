#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);

    // enable depth->video image calibration
    kinect.setRegistration(true);

    kinect.init(); // init(true) shows infrared instead of RGB, init(false,false) disables video image (faster fps)

    kinect.open(); // opens first available kinect

    // print the intrinsic IR sensor values
	if(kinect.isConnected()) {
		ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
		ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
		ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
		ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
	}

	// zero the tilt on startup
	angle = 0;
	kinect.setCameraTiltAngle(angle);
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();

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
    std::cout << "Drawing all particles" << std::endl;
    for(unsigned int p = 0; p < particleSystem.size(); p++){
    	particleSystem[p].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // quit on esc, Q or q
    if (key == 0x1B || key == 0x51 || key == 0x71) {
        exit();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

	//FOR TESTING
	if(particleSystem.size() != 0){
		particleSystem[0].addParticle(ofVec2f(x,y));
		std::cout << "Adding particle" << std::endl;
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	//FOR TESTING
	particleSystem.push_back(ParticleChain
    									(ofVec3f(
    										ofRandom(0,255),
    										ofRandom(0,255),
    										ofRandom(0,255))
    									)
    							);
	std::cout << "Adding partcle chain" << std::endl;
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
}
