#include "ofxSkeleton.h"
#include <skeltrack.h>

void on_track_joints(GObject *obj, GAsyncResult *res, gpointer user_data) {
    // retrieve the tracked joints
    GError *err;
    SkeltrackJointList joints =
        skeltrack_skeleton_track_joints_finish(((ofxSkeleton_CBArgs*)user_data)->st_skel, res, &err);

    // process the joints into ofNodes
    ((ofxSkeleton_CBArgs*)user_data)->skeleton->skeletonFromJointList(joints);

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
