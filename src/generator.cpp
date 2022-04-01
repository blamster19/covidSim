#include "generator.hpp"
#include <random>

void populateCity(city &cityPop){
	cityPop.createPerson(0.1, 0.2, 0.1, 0.2, 0.02, 1);
	cityPop.createPerson(0.1, 0.1, 0.5, 0.3, 0.05, 1);
	cityPop.createPerson(0.2, 0.1, 0.3, 0.6, 0.03, 0);
}
