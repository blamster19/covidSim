#include "city.hpp"

//message codes
enum msgCodes{MSG_crtPrsn, MSG_trnsltAll, MSG_trnsltPrsn, MSG_doneTrnslt};

//constructors
city::city()
: 	nIter( 100 )
, 	dt( 0.02 )
, 	boxSize( 0.25 )
, 	recoveryTime( 0.5 )
, 	verbose( 0 )
, 	extraVerbose( 0 )
{
}

city::city(double dtarg, double boxSizearg, double recoveryTimearg, bool verbosearg, bool everbosearg)
:	dt( dtarg )
,	boxSize( boxSizearg )
,	recoveryTime( recoveryTimearg )
, 	verbose( verbosearg )
, 	extraVerbose( everbosearg )
{
}

city::city(bool verbosearg)
: 	nIter( 100 )
, 	dt( 0.02 )
, 	boxSize( 0.25 )
, 	recoveryTime( 0.5 )
, 	verbose( verbosearg )
, 	extraVerbose( 0 )
{
}

city::city(bool verbosearg, bool everbosearg)
: 	nIter( 100 )
, 	dt( 0.02 )
, 	boxSize( 0.25 )
, 	recoveryTime( 0.5 )
, 	verbose( verbosearg )
, 	extraVerbose( everbosearg )
{
}

//verbosity function that prints what is being done
void city::verbIt(char code, void* arg){
	if(this -> verbose == 1){
		//this function writes addresses of what does what
		switch(code){
		case MSG_crtPrsn:
			printf("in city %p: created person %p\n", this, arg);
			break;
		case MSG_trnsltAll:
			printf("in city %p: start translating people\n", this);
			break;
		case MSG_trnsltPrsn:
			if(this -> extraVerbose == 1)//extra layer of scrutiny
				printf("in city %p: 	translated person %p\n", this, arg);
			break;
		case MSG_doneTrnslt:
			printf("in city %p: translated all people\n", this);
			break;
		default:
			printf("in city %p: unknown error code\n", this);
			break;
		}
	}
}

void city::createPerson(double x, double y, double vx, double vy, double radius, char status){
	person *newPerson = new person(x, y, vx, vy, radius, status);//allocate mem and init object
	this -> people.push_back(*newPerson);//add to list of objects
	verbIt(MSG_crtPrsn, newPerson);
}

void city::infectPeople(){
	//people.size() choose 2
	for(int i = 0; i < (this -> people.size()); i++){
		for(int j = i+1; j < (this -> people.size()); j++){
			//if one of them is infected
			if(people[i].getStatus() == 0 || people[j].getStatus() == 0){
				//compare squares of distances
				double x = people[i].getX() - people[j].getX();
				double y = people[i].getY() - people[j].getY();
				double r = people[i].getRadius() + people[j].getRadius();
				if(x*x + y*y < r*r){
					people[i].infect();
					people[j].infect();
				}
			}
		}
	}
}

void city::movePeople(){
	verbIt(MSG_trnsltAll);
	//iterate list of objects
	for(auto &i : people){
		i.translate(dt, boxSize, recoveryTime);
		verbIt(MSG_trnsltPrsn, &i);
	}
	verbIt(MSG_doneTrnslt);
	infectPeople();
}

double city::getTimeStep(){
	return this -> dt;
}

double city::getBoxSize(){
	return this -> boxSize;
}

void city::setAttr(city::attributes attr, double val){
	switch (attr){
		case attr_nIter:
			this -> nIter = (int) val;
			break;
		case attr_dt:
			this -> dt = val;
			break;
		case attr_boxSize:
			this -> boxSize = val;
			break;
		case attr_recoveryTime:
			this -> recoveryTime = val;
			break;
		case attr_verbose:
			this -> verbose = (val != 0.0);
			break;
		case attr_extraVerbose:
			this -> extraVerbose = (val != 0.0);
			break;
	}
}
