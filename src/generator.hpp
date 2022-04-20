#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "city.hpp"

void populateCity(city &cityPop);
void populateCity(city &cityPop, int seed);
int populateCity(city &cityPop, const char* path);
int saveFile(city &cityPop, const char* path);

#endif
