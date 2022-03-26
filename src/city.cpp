#include "city.hpp"

city::city()
: 	nIter( 100 )
, 	dt( 0.02 )
, 	boxSize( 0.25 )
, 	recoveryTime( 0.5 )
, 	verbose( 0 )
{
}

city::city(double dtarg, double boxSizearg, double recoveryTimearg, bool verbosearg)
:	dt( dtarg )
,	boxSize( boxSizearg )
,	recoveryTime( recoveryTimearg )
, 	verbose( verbosearg )
{
}

city::city(bool verbosearg)
: 	nIter( 100 )
, 	dt( 0.02 )
, 	boxSize( 0.25 )
, 	recoveryTime( 0.5 )
, 	verbose( verbosearg )
{
}

void city::verbIt(char code, void* arg){
	if(this -> verbose == 1){
		intptr_t addr = reinterpret_cast<intptr_t>(arg);
		switch(code){
		case 1:
			printf("in city %x: created person %x\n", this, addr);
			break;
		case 2:
			printf("in city %x: start translating people\n", this);
			break;
		case 3:
			printf("in city %x: translated person %x\n", this, addr);
			break;
		case 4:
			printf("in city %x: translated all people\n", this);
			break;
		default:
			printf("in city %x: unknown error code\n", this);
			break;
		}
	}
}

void city::createPerson(double x, double y, double vx, double vy, double radius, char status){
	person *newPerson = new person(x, y, vx, vy, radius, status);
	this -> people.push_back(*newPerson);
	verbIt(1, newPerson);
}

void city::movePeople(){
	verbIt(2);
	for(auto &i : people){
		i.translate(dt, boxSize, recoveryTime);
		//verbosity
		verbIt(3, &i);
	}
	//verbosity
	verbIt(4);
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
