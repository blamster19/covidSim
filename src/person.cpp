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

void person::translate(double dt, double bound, double recTime){
	//move
	x += dt*vx;
	y += dt*vy;
	//deflect upon collision
	if(x > bound && vx > 0)
		vx = -vx;
	if(x < 0 && vx < 0)
		vx = -vx;
	if(y > bound && vy > 0)
		vx = -vx;
	if(y < 0 && vy < 0)
		vx = -vx;
	//time flow
	timeR += dt;
	if(timeR > recTime && status == 1)
		status = 2;
}

double person::getX(){
	return this -> x;
}

double person::getY(){
	return this -> y;
}

double person::getRadius(){
	return this -> radius;
}

const char* person::getColor(){
	switch (this -> status){
		case 0:
			return "red";
		case 1:
			return "green";
		case 2:
			return "blue";
		default:
			return "black";
	}
}
