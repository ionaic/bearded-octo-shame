
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
		//FOR TESTING
		std::cout << "Updating Particle: " << std::endl;


		to_delete = p->update();
//		if(to_delete == true) std::cout << "    delete" << endl; 
		
		if(to_delete){
			p = particles.erase(p);
			//if(p == particles.end()) break;
		}
		else { //increment if not erasing
			if(p != particles.end()){
				p++;	
			}
			
		}
//		std::cout << "    Done updating single particle" << std::endl;
	}
}

void ParticleChain::draw(){
	std::cout << "Num particles: " << particles.size() << endl;

	for(list<Particle>::iterator p = particles.begin(); p != particles.end(); p++){
		std::cout << "    draw a particle:" << std::endl;
		p->draw(color);
	}
}