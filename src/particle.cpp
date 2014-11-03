
#include "particle.h"

#define STARTING_RADIUS_SIZE 40
#define ALPHA_STEP_SIZE .6
#define RADIUS_REDUCTION .93


Particle::Particle(){

}

Particle::Particle(ofVec2f loc){
	location = loc;
	frameNumber = 0;
	currentSize = STARTING_RADIUS_SIZE;
	currentAlpha = 1.0;
}

void Particle::draw(ofVec3f color){

//	std:: cout << "Drawing a particle at " << location.x << " " << location.y << std::endl;
//	std::cout << "currentAlpha is " << currentAlpha << std::endl;
	ofSetColor(color.x, color.y, color.z, 10);

	ofCircle(location, currentSize);
}

bool Particle::update(){

	//FOR TESTING
//	std::cout << "    updating a Single Particle" << std::endl;
	frameNumber++;
//	std::cout << "    Radius start: " << currentSize << std::endl;
	currentSize *= RADIUS_REDUCTION;
	currentAlpha *= ALPHA_STEP_SIZE;
//	std::cout << "    Radius end: " << currentSize << std::endl;

	//Delete the particle if its size <= 0
	if(currentSize <= 1){
//		std::cout << "    returning delete" << std::endl;
		return true;
	}
	return false;
}