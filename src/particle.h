
#include "ofMain.h"

class Particle{

public:
	Particle();
	Particle(ofVec2f loc);

	void draw(ofVec3f color);
	bool update();

private:
	
	ofVec2f location;
	int frameNumber; //how many frames this particle has been around for
	double currentSize;
	double currentAlpha;
};