#include "city.hpp"
#include "../deps/Plotter.h"
#include "generator.hpp"
#include <cstdlib>
#include <string>

enum msgCodes{MSG_invArg, MSG_noFile};
void verbIt(char code, char* arg, char* name);

int main(int argc, char **argv){
	bool verbose = 0;
	bool extraverbose = 0;
	//parse args
	int token = 1;
	std::string argument;
	while(argv[token] != nullptr){
		if(argv[token][0] != '-'){
			verbIt(MSG_invArg, argv[token], argv[0]);
		}else{
			argument = std::string(argv[token]);
			if(argument == "-v" || argument == "--verbose"){
				verbose = 1;
			}
			if(argument == "-V" || argument == "--Verbose"){
				verbose = 1;
				extraverbose = 1;
			}
		}
		token++;
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
			printf("%s: Invalid option: '%s''\nTry '%s --help' for more information.", name, arg, name);
	}
}
