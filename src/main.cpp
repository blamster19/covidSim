#include "city.hpp"
#include "../deps/Plotter.h"
#include "generator.hpp"
#include <cstdlib>
#include <string>

enum msgCodes{MSG_invArg, MSG_noFile, MSG_dupliArg, MSG_help, MSG_conflict};
void verbIt(char code, char* arg, char* name);
bool parseParams(int argc, char **argv, bool &verbose, bool &extraverbose, char &flags);

int main(int argc, char **argv){
	bool verbose = 0;
	bool extraverbose = 0;
	char flags = 0b00000000;// C++14
	/*
		flag bit layout (left to right):
		[nIter] [dt] [nPeople] [recoveryTime] [output] [doFrames] [input][input]
		-input bit layout:
			01 - default
			10 - random
			11 - from file
	*/
	if(parseParams(argc, argv, verbose, extraverbose, flags)){
		return 1;
	}
	city argleton(verbose, extraverbose);
	populateCity(argleton);
	Plotter mapGen;
	for(int i = 0; i < 50; i++)
	{
		mapGen.plot(argleton.people, i, argleton.getBoxSize());
		argleton.movePeople();
	}
	return 0;
}

void verbIt(char code, char* arg, char* name){
	switch(code){
		case MSG_invArg:
			printf("%s: Invalid option: '%s''\nTry '%s --help' for more information.\n", name, arg, name);
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
	}
}

bool parseParams(int argc, char **argv, bool &verbose, bool &extraverbose, char &flags){
	int token = 1;
	std::string argument;
	while(argv[token] != nullptr){
		if(argv[token][0] != '-'){
			verbIt(MSG_invArg, argv[token], argv[0]);
			return 1;
		}else{
			argument = std::string(argv[token]);
			if(argument == "-v" || argument == "--verbose"){
				if(verbose == 1){
					verbIt(MSG_dupliArg, argv[token], argv[0]);
					return  1;
				}
				verbose = 1;
			}
			if(argument == "-V" || argument == "--Verbose"){
				if(verbose == 1 || extraverbose == 1){
					verbIt(MSG_dupliArg, argv[token], argv[0]);
					return 1;
				}
				verbose = 1;
				extraverbose = 1;
			}
			if(argument == "-h" || argument == "--help"){
				if(argc > 2){
					verbIt(MSG_conflict, argv[0], argv[0]);
					return 1;
				}
				verbIt(MSG_help, argv[0], argv[0]);
				return 0;
			}
			if(argument == "--nIter"){
				if(flags|0b10000000 == flags){
					verbIt(MSG_dupliArg, argv[token], argv[0]);
					return 1;
				}
				flags += 0b10000000;
			}
			if(argument == "--dt"){
				if(flags|0b01000000 == flags){
					verbIt(MSG_dupliArg, argv[token], argv[0]);
					return 1;
				}
				flags += 0b01000000;
			}
			if(argument == "--nPeople"){
				if(flags|0b00100000 == flags){
					verbIt(MSG_dupliArg, argv[token], argv[0]);
					return 1;
				}
				flags += 0b00100000;
			}
			if(argument == "--recoveryTime"){
				if(flags|0b00010000 == flags){
					verbIt(MSG_dupliArg, argv[token], argv[0]);
					return 1;
				}
				flags += 0b00010000;
			}
			if(argument == "--output" || argument =="-o"){
				if(flags|0b00001000 == flags){
					verbIt(MSG_dupliArg, argv[token], argv[0]);
					return 1;
				}
				flags += 0b00001000;
			}
			if(argument == "--doFrames"){
				if(flags|0b00000100 == flags){
					verbIt(MSG_dupliArg, argv[token], argv[0]);
					return 1;
				}
				flags += 0b00000100;
			}
			if(argument == "--input" || argument == "-i"){
				if((flags|0b00000010 == flags)||(flags|0b00000001 == flags)){
					verbIt(MSG_dupliArg, argv[token], argv[0]);
					return 1;
				}
				if(flags|0b00000011 == flags){// from file
					flags += 0b00000011;
				}else if(flags|0b00000010 == flags){// random
					flags += 0b00000010;
				}else{// default
					flags += 0b00000001;
				}
			}
		}
		token++;
	}
	return 0;
}
