#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetLogLevel(OF_LOG_VERBOSE);

    // start the kinect library
    kinect.start();
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();

    if (kinect.isNewSkeleton()) {
        for (int i = 0; i < kinect.getSkeletons().size(); ++i) {
            // do things with the skeletons
        }
    }

    // Draw all of the particles
    for(unsigned int p = 0; p < particleSystem.size(); p++){
    	particleSystem[p].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    kinect.draw(0, 0);
    kinect.drawDepth(0, 480);

    // Update each particle (within each chain)
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
    //for(int i = 0; i < 10; i++){
    //    if(particleSystem.size() >= i+1){
    //        particleSystem[i].addParticle(ofVec2f(x+(i*40),y+(i*40)));
    //    }
    //
    //}

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	//FOR TESTING

    //for(int i = 0; i < 10; i++){
    //    ofVec3f color =
    //        ofVec3f(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
    //    //std::cout << "color for chain: " << color.x << " " << color.y << " " << color.z << std::endl;
    //    particleSystem.push_back(ParticleChain(color));
    //}

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

}
