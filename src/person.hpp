#ifndef PERSON_HPP
#define PERSON_HPP

class person{
public:
	person();
	person(double xarg, double yarg, double vxarg, double vyarg, double radiusarg, char statusarg);
	void translate(double dt, double bound, double recTime);
	double getX();
	double getY();
	double getRadius();
	const char* getColor();
	char getStatus();
	double getVX();
	double getVY();
	void infect();
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
