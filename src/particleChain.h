
#include "ofMain.h"
#include "particle.h"

class ParticleChain{

public:
	ParticleChain();
	ParticleChain(ofVec3f color);

	void addParticle(ofVec2f pos);
	void update();
	void draw();

private:

	ofVec3f color;
	std::list<Particle> particles;

};