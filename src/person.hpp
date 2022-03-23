#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

class person{
public:
	person();
	void setParams(double x, double y, double vx, double vy, double radius, char status);
	void translate(double dt, double bound, double recTime);
	double getX();
	double getY();
	double getRadius();
	const char* getColor();
private:
	double x;
	double y;
	double vx;
	double vy;
	double radius;
	char status;
	double timeR;
};

#endif
