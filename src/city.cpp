#include "city.hpp"

city::city()
: 	nIter( 100 )
, 	dt( 0.02 )
, 	boxSize( 0.25 )
, 	recoveryTime( 0.5 )
{
}

city::city(double dtarg, double boxSizearg, double recoveryTimearg)
:	dt( dtarg )
,	boxSize( boxSizearg )
,	recoveryTime( recoveryTimearg )
{
}

void city::createPerson(double x, double y, double vx, double vy, double radius, char status){
	person *newPerson = new person(x, y, vx, vy, radius, status);
	this -> people.push_back(*newPerson);
}

void city::movePeople(){
	for(auto &i : people){
		i.translate(dt, boxSize, recoveryTime);
	}
}

std::vector<person> city::getPeople(){
	return this -> people;
}

double city::getTimeStep(){
	return this -> dt;
}

double city::getBoxSize(){
	return this -> boxSize;
}
