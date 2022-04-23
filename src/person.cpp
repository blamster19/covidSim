#include "person.hpp"

person::person()
: 	x( 0 )
,	y( 0 )
,	vx( 0 )
,	vy( 0 )
,	radius( 0.01 )
,	status( 0 )
,	timeR( 0 )
{
}

person::person(double xarg, double yarg, double vxarg, double vyarg, double radiusarg, char statusarg)
:	x( xarg )
,	y( yarg )
,	vx( vxarg )
,	vy( vyarg )
,	radius( radiusarg )
,	status( statusarg )
, 	timeR( 0 )
{
}

void person::translate(double dt, double bound, double recTime){
	x += dt*vx;
	y += dt*vy;
	if(x > bound && vx > 0){
		vx = -vx;
	}
	if(x < 0 && vx < 0){
		vx = -vx;
	}
	if(y > bound && vy > 0){
		vy = -vy;
	}
	if(y < 0 && vy < 0){
		vy = -vy;
	}
	if(status == 0){
		this -> timeR += dt;
	}
	if(this -> timeR >= recTime){
		this -> status = 2;
	}
}

double person::getX(){
	return this -> x;
}

double person::getY(){
	return this -> y;
}

double person::getVX(){
	return this -> vx;
}

double person::getVY(){
	return this -> vy;
}

double person::getRadius(){
	return this -> radius;
}

const char* person::getColor(){
	//return verbal color for Python library
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

char person::getStatus(){
	return this -> status;
}

void person::infect(){
	if(this -> status == 1){
		this -> status = 0;
	}
}
