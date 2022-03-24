#ifndef CITY_HPP
#define CITY_HPP

#include <vector>
#include "person.hpp"

class city{
public:
	city();
	void setParams(double dt, double boxSize, double recoveryTime);
	void createPerson(double x, double y, double vx, double vy, double radius, char status);
	void movePeople();
	std::vector <person> getPeople();
	double getTimeStep();
	double getBoxSize();
private:
	std::vector<person> people;
	int nIter;
	double dt;
	double boxSize;
	double recoveryTime;
};

#endif
