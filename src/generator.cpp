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
		file.close();
		return 1;
	}
	double x;
	double y;
	double vx;
	double vy;
	double r;
	char status;
	std::string input;
	char counter = 0;
	while(1){
		file >> input;
		if(file.eof()){
			break;
		}
		if(file.fail()){
			file.close();
			return 2;
		}
		switch(counter%6){
			case 0:
				if((counter != 0)){
					cityPop.createPerson(x, y, vx, vy, r, status);
				}
				x = std::stod(input);
				break;
			case 1:
				y = std::stod(input);
				break;
			case 2:
				vx = std::stod(input);
				break;
			case 3:
				vy = std::stod(input);
				break;
			case 4:
				r = std::stod(input);
				break;
			case 5:
				if(input == "red"){
					status = 0;
				}else
				if(input == "green"){
					status = 1;
				}else
				if(input == "blue"){
					status = 2;
				}else{
					return 2;
				}
				break;
			default:
				break;
		}
		file.clear();
		counter++;
	}
			cityPop.createPerson(x, y, vx, vy, r, status);
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
