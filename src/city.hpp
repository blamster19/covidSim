#ifndef CITY_HPP
#define CITY_HPP

#include <vector>
#include "person.hpp"

class city{
public:
	city();
	city(double dtarg, double boxSizearg, double recoveryTimearg, bool verbosearg, bool everbosearg);
	city(bool verbosearg);
	city(bool verbosearg, bool everbosearg);
	void createPerson(double x, double y, double vx, double vy, double radius, char status);
	void movePeople();
	std::vector <person> getPeople();
	double getTimeStep();
	double getBoxSize();
	std::vector<person> people;
private:
	void verbIt(char code, void* arg = NULL);
	int nIter;
	double dt;
	double boxSize;
	double recoveryTime;
	bool verbose;
	bool extraVerbose;
};

#endif
