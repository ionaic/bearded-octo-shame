#include "ofMain.h"

// SkelTrack includes
#include <gfreenect.h>
#include <skeltrack.h>

class ofxSkeleton;

// any arguments that need to be passed to the callback function
struct ofxSkeleton_CBArgs { 
    ofxSkeleton *skeleton;
    SkeltrackSkeleton *st_skel;
};

class ofxSkeleton {
    public:
        // get the screen space coordinates of the skeleton joint
        static ofVec2f getSkelJointScreenPosition(const SkeltrackJoint *joint) {
            return ofVec2f(joint->screen_x, joint->screen_y);
        }
        // get the world space coordinates of the skeleton joint
        static ofVec3f getSkelJointPosition(const SkeltrackJoint *joint) {
            return ofVec3f(joint->x, joint->y, joint->z);
        }

        // set skeleton joint positions from joint list
        void skeletonFromJointList(const SkeltrackJointList joints);

        // nodes of the skeleton
        ofNode head,
               leftShoulder,
               rightShoulder,
               leftElbow,
               rightElbow,
               leftHand,
               rightHand;
};
