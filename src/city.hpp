#ifndef CITY_HPP
#define CITY_HPP

#include <vector>
#include "person.hpp"

class city{
public:
	city();
	void createPerson(double x, double y, double vx, double vy, double radius, char status);
	void movePeople();
private:
	std::vector<person> people;
	int nIter;
	double dt;
	double boxSize;
	double recoveryTime;

};

#endif
