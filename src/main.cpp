#include "city.hpp"
#include "../deps/Plotter.h"

int main(int argc, char **argv){
	city argleton;
	argleton.createPerson(0.1, 0.2, 0.1, 0.2, 0.02, 1);
	argleton.createPerson(0.1, 0.1, 0.5, 0.3, 0.05, 1);
	argleton.createPerson(0.2, 0.1, 0.3, 0.6, 0.03, 0);
	Plotter mapGen;
	for(int i = 0; i < 50; i++)
	{
		mapGen.plot(argleton.people, i, argleton.getBoxSize());
		argleton.movePeople();
	}
	return 0;
}
