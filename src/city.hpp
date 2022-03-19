#ifndef CITY_HPP
#define CITY_HPP

#include <vector>
#include "person.hpp"

class city{
public:
	city();
private:
	std::vector<person> people;
	int nIter;
	double dt;
	double boxSize;
	double recoveryTime;
};

#endif
