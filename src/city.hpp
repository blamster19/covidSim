#ifndef CITY_HPP
#define CITY_HPP

#include <vector>
#include <cstdio>
#include <cstdint>
#include "person.hpp"


class city{
public:
	enum attributes{attr_nIter, attr_dt, attr_boxSize, attr_recoveryTime, attr_verbose, attr_extraVerbose};
	city();
	city(double dtarg, double boxSizearg, double recoveryTimearg, bool verbosearg, bool everbosearg);
	city(bool verbosearg);
	city(bool verbosearg, bool everbosearg);
	void createPerson(double x, double y, double vx, double vy, double radius, char status);
	void movePeople();
	double getTimeStep();
	double getBoxSize();
	int getnIter();
	void setAttr(attributes attr, double val);
	void reverbAttributes();
	std::vector<person> people;
private:
	void verbIt(char code, void* arg = NULL);
	void infectPeople();
	int nIter;
	double dt;
	double boxSize;
	double recoveryTime;
	bool verbose;
	bool extraVerbose;
};

#endif
