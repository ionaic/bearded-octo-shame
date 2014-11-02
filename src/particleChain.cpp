
#include "particleChain.h"

ParticleChain::ParticleChain(){

}

ParticleChain::ParticleChain(ofVec3f color){
	this->color = color;
}

void ParticleChain::addParticle(ofVec2f pos){
	particles.push_back(Particle(pos));
}

void ParticleChain::update(){

	bool to_delete = false;
	for(list<Particle>::iterator p = particles.begin(); p != particles.end(); ){
		to_delete = p->update();
		if(to_delete){
			particles.erase(p);
		}
		else { //increment if not erasing
			p++;
		}
	}
}

void ParticleChain::draw(){

	for(list<Particle>::iterator p = particles.begin(); p != particles.end(); ){
		p->draw(color);
	}
}