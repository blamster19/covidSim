#include "generator.hpp"
#include <random>

void populateCity(city &cityPop){
	cityPop.createPerson(0.1, 0.2, 0.1, 0.2, 0.02, 1);
	cityPop.createPerson(0.1, 0.1, 0.5, 0.3, 0.05, 1);
	cityPop.createPerson(0.2, 0.1, 0.3, 0.6, 0.03, 0);
}

void populateCity(city &cityPop, int seed){
	std::minstd_rand0 generator(seed);
	double x;
	double y;
	double vx;
	double vy;
	double r;
	char status;
	double boxSize = cityPop.getBoxSize();
	for(int i = 0; i < 50; i++){
		x = (float)generator()/(float)generator.max()*boxSize;// [0, L]
		y = (float)generator()/(float)generator.max()*boxSize;// [0, L]
		vx = (float)generator()/(float)generator.max()-0.5;// [-0.5, 0.5]
		vy = (float)generator()/(float)generator.max()-0.5;// [-0.5, 0.5]
		r = (float)generator()/(float)generator.max()*0.004+0.001;// [0.001, 0.005]
		if((float)generator() > (float)generator.max()*0.9){// 90% healthy
			status = 0;
		}else{
			status = 1;
		}
		cityPop.createPerson(x, y, vx, vy, r, status);
	}
}
