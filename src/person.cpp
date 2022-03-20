#include "person.hpp"

person::person()
: 	x( 0 ),
	y( 0 ),
	vx( 0 ),
	vy( 0 ),
	radius( 0.01 ),
	status( 0 ),
	timeR( 0 )
{
}

void person::setParams(double x, double y, double vx, double vy, double radius, char status){
	this -> x = x;
	this -> y = y;
	this -> vx = vx;
	this -> vy = vy;
	this -> radius = radius;
	this -> status = status;
}
