#include "ofxSkeleton.h"

ofxSkeleton::ofxSkeleton(){

    ofVec3f color = ofVec3f(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
    head_pc = ParticleChain(color);

    color = ofVec3f(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
    leftShoulder_pc = ParticleChain(color);

    color = ofVec3f(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
    rightShoulder_pc = ParticleChain(color);
    
    color = ofVec3f(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
    leftElbow_pc = ParticleChain(color);

    color = ofVec3f(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
    rightElbow_pc = ParticleChain(color);
    
    color = ofVec3f(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
    leftHand_pc = ParticleChain(color);

    color = ofVec3f(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
    rightHand_pc = ParticleChain(color);
}

void on_track_joints(GObject *obj, GAsyncResult *res, gpointer user_data) {
    std::cout << "on_track_joints" << std::endl;
    // retrieve the tracked joints
    GError *err;
    SkeltrackJointList joints =
        skeltrack_skeleton_track_joints_finish(((ofxSkeleton_CBArgs*)user_data)->st_skel, res, &err);

    // process the joints into ofNodes
    ((ofxSkeleton_CBArgs*)user_data)->skeleton->skeletonFromJointList(joints);

    ofxSkeleton* skel = ((ofxSkeleton_CBArgs*)user_data)->skeleton;


    ofVec3f loc;

    loc = ((ofxSkeleton_CBArgs*)user_data)->skeleton->head.getPosition();
    skel->head_pc.addParticle(ofVec2f(loc.x, loc.y));

    loc = ((ofxSkeleton_CBArgs*)user_data)->skeleton->leftShoulder.getPosition();
    skel->leftShoulder_pc.addParticle(ofVec2f(loc.x, loc.y));

    loc = ((ofxSkeleton_CBArgs*)user_data)->skeleton->rightShoulder.getPosition();
    skel->rightShoulder_pc.addParticle(ofVec2f(loc.x, loc.y));

    loc = ((ofxSkeleton_CBArgs*)user_data)->skeleton->leftElbow.getPosition();
    skel->leftElbow_pc.addParticle(ofVec2f(loc.x, loc.y));
    
    loc = ((ofxSkeleton_CBArgs*)user_data)->skeleton->rightElbow.getPosition();
    skel->rightElbow_pc.addParticle(ofVec2f(loc.x, loc.y));
    
    loc = ((ofxSkeleton_CBArgs*)user_data)->skeleton->leftHand.getPosition();
    skel->leftHand_pc.addParticle(ofVec2f(loc.x, loc.y));
    
    loc = ((ofxSkeleton_CBArgs*)user_data)->skeleton->rightHand.getPosition();
    skel->rightHand_pc.addParticle(ofVec2f(loc.x, loc.y));

    std::cout << skel->head.getPosition() << std::endl;


    // free the joint list
    skeltrack_joint_list_free(joints);
}

void ofxSkeleton::skeletonFromJointList(const SkeltrackJointList joints) {
    head.setGlobalPosition(
            ofxSkeleton::getSkelJointPosition(
                skeltrack_joint_list_get_joint(joints, SKELTRACK_JOINT_ID_HEAD)
                ));
    leftShoulder.setGlobalPosition(
            ofxSkeleton::getSkelJointPosition(
                skeltrack_joint_list_get_joint(joints, SKELTRACK_JOINT_ID_LEFT_SHOULDER)
                ));
    rightShoulder.setGlobalPosition(
            ofxSkeleton::getSkelJointPosition(
                skeltrack_joint_list_get_joint(joints, SKELTRACK_JOINT_ID_RIGHT_SHOULDER)
                ));
    leftElbow.setGlobalPosition(
            ofxSkeleton::getSkelJointPosition(
                skeltrack_joint_list_get_joint(joints, SKELTRACK_JOINT_ID_LEFT_ELBOW)
                ));
    rightElbow.setGlobalPosition(
            ofxSkeleton::getSkelJointPosition(
                skeltrack_joint_list_get_joint(joints, SKELTRACK_JOINT_ID_RIGHT_ELBOW)
                ));
    leftHand.setGlobalPosition(
            ofxSkeleton::getSkelJointPosition(
                skeltrack_joint_list_get_joint(joints, SKELTRACK_JOINT_ID_LEFT_HAND)
                ));
    rightHand.setGlobalPosition(
            ofxSkeleton::getSkelJointPosition(
                skeltrack_joint_list_get_joint(joints, SKELTRACK_JOINT_ID_RIGHT_HAND)
                ));
}


void ofxSkeleton::update(){
    head_pc.update();
    leftShoulder_pc.update();
    rightShoulder_pc.update();
    leftElbow_pc.update();
    rightElbow_pc.update();
    leftHand_pc.update();
    rightHand_pc.update();
}

void ofxSkeleton::draw(){
    head_pc.draw();
    leftShoulder_pc.draw();
    rightShoulder_pc.draw();
    leftElbow_pc.draw();
    rightElbow_pc.draw();
    leftHand_pc.draw();
    rightHand_pc.draw();
}
