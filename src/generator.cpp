#include "generator.hpp"
#include <random>
#include <fstream>
#include <string>

void populateCity(city &cityPop){
	cityPop.createPerson(0.1, 0.2, 0.1, 0.2, 0.002, 1);
	cityPop.createPerson(0.1, 0.1, 0.5, 0.3, 0.005, 1);
	cityPop.createPerson(0.2, 0.1, 0.3, 0.6, 0.003, 0);
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

int populateCity(city &cityPop, const char* path){
	std::fstream file;
	file.open(path, std::ios::in);
	if(!file.good()){
		return 1;
	}
	double x;
	double y;
	double vx;
	double vy;
	double r;
	char status;
	std::string statusStr;
	while(file){
		file >> x >> y >> vx >> vy >> r >> statusStr;
		if(file.fail()){
			return 1;
		}
		if(statusStr == "red"){
			status = 0;
		}else
		if(statusStr == "green"){
			status = 1;
		}else
		if(statusStr == "blue"){
			status = 2;
		}else{
			return 2;
		}
		cityPop.createPerson(x, y, vx, vy, r, status);
		file.clear();
	}
	file.close();
	return 0;
}

int saveFile(city &cityPop, const char* path){
	std::ofstream file;
	file.open(path, std::ios::trunc);
	if(!file.good()){
		return 1;
	}
	for(auto &i : cityPop.people){
		file<<i.getX()<<" "<<i.getY()<<" "<<i.getVX()<<" "<<i.getVY()<<" "<<i.getRadius()<<" ";
		switch(i.getStatus()){
			case 0:
				file<<"red";
				break;
			case 1:
				file<<"green";
				break;
			case 2:
				file<<"blue";
				break;
			default:
				return 2;
				break;

		}
		file<<std::endl;
	}
	file.close();
	return 0;
}
