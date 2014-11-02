
#include "particle.h"

#define STARTING_RADIUS_SIZE 10
#define RADIUS_REDUCTION .8
#define ALPHA_STEP_SIZE .1

Particle::Particle(){

}

Particle::Particle(ofVec2f loc){
	location = loc;
	frameNumber = 0;
	currentSize = STARTING_RADIUS_SIZE;
	currentAlpha = 1.0;
}

void Particle::draw(ofVec3f color){

	ofSetColor(color.x, color.y, color.z, currentAlpha);

	ofCircle(location, currentSize);
}

bool Particle::update(){

	frameNumber++;
	currentSize *= RADIUS_REDUCTION;
	currentAlpha -= ALPHA_STEP_SIZE;

	//Delete the particle if its size <= 0
	if(currentSize <= 0){
		return false;
	}
	return true;
}