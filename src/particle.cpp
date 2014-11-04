
#include "particle.h"

#define STARTING_RADIUS_SIZE 40
#define ALPHA_STEP_SIZE .93
#define RADIUS_REDUCTION .93


Particle::Particle(){

}

Particle::Particle(ofVec2f loc){
	location = loc;
	frameNumber = 0;
	currentSize = STARTING_RADIUS_SIZE;
	currentAlpha = 255;
}

void Particle::draw(ofVec3f color){

//	std:: cout << "Drawing a particle at " << location.x << " " << location.y << std::endl;
	//std::cout << "color: " << color.x << " " << color.y << " " << color.z << std::endl;
//	std::cout << "currentAlpha is " << currentAlpha << std::endl;


	//Store current color to restore it afterwards
	float currentColor[4];
	//std::cout << "Current color: " << currentColor[0] << " " << currentColor[1] << " " << currentColor[2] << " " << currentColor[3] << std::endl;
	glGetFloatv(GL_CURRENT_COLOR,currentColor);

	//Draw circle
	//std::cout << "particle color: " << color.x << " " << color.y << " " << color.z << std::endl;
	ofSetColor(color.x, color.y, color.z, currentAlpha);
	ofCircle(location, currentSize);

	//Restore Previous Color
	ofSetColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
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