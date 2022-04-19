#include "city.hpp"
#include "../deps/Plotter.h"
#include "generator.hpp"
#include <cstdlib>
#include <string>
#include <ctime>

enum msgCodes{MSG_invArg, MSG_noFile, MSG_dupliArg, MSG_help, MSG_conflict, MSG_noArg};
void verbIt(char code, char* arg, char* name);
bool parseParams(int argc, char **argv, bool &verbose, bool &extraverbose, char &flags, string (&parsedArgs)[7]);

int main(int argc, char **argv){
	bool verbose = 0;
	bool extraverbose = 0;
	char flags = 0b00000000;// C++14 introduces 0b
	/*
		flag bit layout (left to right):
		[nIter] [dt] [boxSize] [recoveryTime] [output] [doFrames] [input][input]
		-input bit layout:
			01 - default
			10 - random
			11 - from file
	*/
	string parsedArgs[7];
	if(parseParams(argc, argv, verbose, extraverbose, flags, parsedArgs)){
		return 1;
	}
	city argleton(verbose, extraverbose);
	if((flags|0b10000000) == flags){// nIter
		argleton.setAttr(city::attr_nIter, std::stod(parsedArgs[0]));
	}
	if((flags|0b01000000) == flags){// dt
		argleton.setAttr(city::attr_dt, std::stod(parsedArgs[1]));
	}
	if((flags|0b00100000) == flags){// boxSize
		argleton.setAttr(city::attr_boxSize, std::stod(parsedArgs[2]));
	}
	if((flags|0b00010000) == flags){// recoveryTime
		argleton.setAttr(city::attr_recoveryTime, std::stod(parsedArgs[3]));
	}
	if((flags|0b00000001) == flags){// default populate
		populateCity(argleton);
	}else
	if((flags|0b00000010) == flags){// random populate
		srand(time(NULL));
		int seed = std::rand();
		populateCity(argleton, seed);
	}else
	if((flags|0b00000011) == flags){// file populate
		populateCity(argleton, "input.config");
	}
	Plotter mapGen;
	for(int i = 0; i < argleton.getnIter(); i++)
	{
		if(verbose){
			printf("Iteration %i:\n", i);
		}
		mapGen.plot(argleton.people, i, argleton.getBoxSize());
		argleton.movePeople();
	}
	if((flags|0b00000100) == flags){
		printf("Merging frames into GIF...\n");
		system("python3 deps/mergeFrames.py");
		system("cd plots; rm -f frame*.png");
	}
	return 0;
}

void verbIt(char code, char* arg, char* name){
	switch(code){
		case MSG_invArg:
			printf("%s: Invalid option: '%s'\nTry '%s --help' for more information.\n", name, arg, name);
			break;
		case MSG_noFile:
			printf("%s: %s: No such file or directory\n", name, arg);
			break;
		case MSG_dupliArg:
			printf("%s: Supplied the same argument twice: %s\n", name, arg);
			break;
		case MSG_help:
			printf("###[ help text ]###]\n");
			break;
		case MSG_conflict:
			printf("%s: Conflicting arguments\nTry '%s --help' for more information.\n", name, name);
			break;
		case MSG_noArg:
			printf("%s: No value passed to an option that expects a value: '%s'\n", name, arg);
			break;
	}
}

bool parseParams(int argc, char **argv, bool &verbose, bool &extraverbose, char &flags, string (&parsedArgs)[7]){
	int token = 1;
	std::string argument;
	while(argv[token] != nullptr){
		if(argv[token][0] != '-'){
			verbIt(MSG_invArg, argv[token-1], argv[0]);
			return 1;
		}else{
			argument = std::string(argv[token]);
			if(argument == "-v" || argument == "--verbose"){
				if(verbose == 1){
					goto dupliErr;
				}
				verbose = 1;
			}else
			if(argument == "-V" || argument == "--Verbose"){
				if(verbose == 1 || extraverbose == 1){
					goto dupliErr;
				}
				verbose = 1;
				extraverbose = 1;
			}else
			if(argument == "-h" || argument == "--help"){
				if(argc > 2){
					verbIt(MSG_conflict, argv[0], argv[0]);
					return 1;
				}
				verbIt(MSG_help, argv[0], argv[0]);
				return 1;
			}else
			if(argument == "--nIter"){
				if((flags|0b10000000) == flags){
					goto dupliErr;
				}
				token++;
				if(argv[token] == nullptr){
					goto notAnOpt;
				}
				if(argv[token][0] == '-'){
					goto notAnOpt;
				}
				flags += 0b10000000;
				parsedArgs[0] = argv[token];
			}else
			if(argument == "--dt"){
				if((flags|0b01000000) == flags){
					goto dupliErr;
				}
				token++;
				if(argv[token] == nullptr){
					goto notAnOpt;
				}
				if(argv[token][0] == '-'){
					goto notAnOpt;
				}
				flags += 0b01000000;
				parsedArgs[1] = argv[token];
			}else
			if(argument == "--boxSize"){
				if((flags|0b00100000) == flags){
					goto dupliErr;
				}
				token++;
				if(argv[token] == nullptr){
					goto notAnOpt;
				}
				if(argv[token][0] == '-'){
					goto notAnOpt;
				}
				flags += 0b00100000;
				parsedArgs[2] = argv[token];
			}else
			if(argument == "--recoveryTime"){
				if((flags|0b00010000) == flags){
					goto dupliErr;
				}
				token++;
				if(argv[token] == nullptr){
					goto notAnOpt;
				}
				if(argv[token][0] == '-'){
					goto notAnOpt;
				}
				flags += 0b00010000;
				parsedArgs[3] = argv[token];
			}else
			if(argument == "--output" || argument =="-o"){
				if((flags|0b00001000) == flags){
					goto dupliErr;
				}
				token++;
				if(argv[token] == nullptr){
					goto notAnOpt;
				}
				if(argv[token][0] == '-'){
					goto notAnOpt;
				}
				argument = argv[token];
				if(argument == "true" || argument == "TRUE" || argument == "1"){
					flags += 0b00001000;
				}else
				if(argument == "false" || argument == "FALSE" || argument == "0"){
					// do nothing
				}else{
					goto invalidArg;
				}
			}else
			if(argument == "--doFrames"){
				if((flags|0b00000100) == flags){
					goto dupliErr;
				}
				token++;
				if(argv[token] == nullptr){
					goto notAnOpt;
				}
				if(argv[token][0] == '-'){
					goto notAnOpt;
				}
				argument = argv[token];
				if(argument == "true" || argument == "TRUE" || argument == "1"){
					flags += 0b00000100;
				}else
				if(argument == "false" || argument == "FALSE" || argument == "0"){
					//do nothing
				}else{
					goto invalidArg;
				}
			}else
			if(argument == "--input" || argument == "-i"){
				if(((flags|0b00000010) == flags)||((flags|0b00000001) == flags)){
					goto dupliErr;
				}
				token++;
				if(argv[token] == nullptr){
					goto notAnOpt;
				}
				if(argv[token][0] == '-'){
					goto notAnOpt;
				}
				argument = argv[token];
				if(argument == "file"){// from file
					flags += 0b00000011;
				}else if(argument == "random"){// random
					flags += 0b00000010;
				}else if(argument == "test"){// default
					flags += 0b00000001;
				}else{
					goto invalidArg;
				}
				parsedArgs[6] = argv[token];
			}else{
				verbIt(MSG_invArg, argv[token], argv[0]);
				return 1;
			}
		}
		token++;
	}
	return 0;
	dupliErr:// duplicate argument
		verbIt(MSG_dupliArg, argv[token], argv[0]);
		return 1;
	notAnOpt:// no option value provided
		verbIt(MSG_noArg, argv[token-1], argv[0]);
		return 1;
	invalidArg:// wrong argument value
		verbIt(MSG_invArg, argv[token], argv[0]);
		return 1;
}
