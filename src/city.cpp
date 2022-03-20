#include "city.hpp"

city::city()
: 	nIter( 100 )
, 	dt( 0.02 )
, 	boxSize( 0.25 )
, 	recoveryTime( 0.5 )
{
}

void city::createPerson(double x, double y, double vx, double vy, double radius, char status){
	person *newPerson = new person;
	newPerson -> setParams(x, y, vx, vy, radius, status);
	this -> people.push_back(*newPerson);
}
