#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetLogLevel(OF_LOG_VERBOSE);

    threshMin = 70;
    threshMax = 230;

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

    conv_image.allocate(kinect.width / 2, kinect.height / 2);
    min_image.allocate(kinect.width / 2, kinect.height / 2);
    max_image.allocate(kinect.width / 2, kinect.height / 2);
    simg.allocate(kinect.width / 2, kinect.height / 2);

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
        ofxCvGrayscaleImage tmp;
        tmp.allocate(kinect.width, kinect.height);
        tmp.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        std::cout << "width: " << kinect.width << "; height: " << kinect.height << std::endl;
        tmp.resize(kinect.width / 2, kinect.height / 2);
        min_image = tmp;
        max_image = tmp;
        min_image.threshold(threshMin);
        max_image.threshold(threshMax, true);
        cvAnd(min_image.getCvImage(), max_image.getCvImage(), conv_image.getCvImage(), NULL);

        simg.setFromPixels(conv_image.getPixels(), conv_image.getWidth(), conv_image.getHeight());
        std::cout << "width: " << conv_image.getWidth() << "; height: " << conv_image.getHeight() << std::endl;


        std::cout << "sending out asynch track call" << std::endl;
        skeltrack_skeleton_track_joints(st_skel,
                simg.getShortPixelsRef().getPixels(),
                simg.getWidth(), simg.getHeight(), NULL,
                on_track_joints, &cb_args);
    }

    skeleton.update();

    // Draw all of the particles
    for(unsigned int p = 0; p < particleSystem.size(); p++){
    	particleSystem[p].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //kinect.drawDepth(0, 0, kinect.width, kinect.height);
    //kinect.draw(kinect.width+10, 0, kinect.width, kinect.height);
    conv_image.draw(0, 0);
    simg.draw(conv_image.getWidth() + 10, 0);
    min_image.draw(0, conv_image.getHeight() + 10);
    max_image.draw(min_image.getWidth() + 10, simg.getHeight() + 10);
    skeleton.draw();

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
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();

    g_object_unref(st_skel);
}
