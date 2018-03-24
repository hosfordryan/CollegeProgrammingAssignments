/* Ryan Hosford
 * rph160030@utdallas.edu
 * CS3377
 */
#include <string>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <tclap/CmdLine.h>
#include "program2.h"

/* ToDo: Make sure l and u are mutually exclusive. Can do this by checking if both have been used and then returning an error.
 *
 */
using namespace std;

void parseCmdLine (int argc, char *argv[]){
	

	try {
		TCLAP::CmdLine cmd("Opens an input file, processes the data, and writes to an output file",' ',"1.0");
		TCLAP::ValueArg<string> outputArg("o","output","File to output to. Defaults to output.txt",false,"output.txt","string");
		cmd.add(outputArg);
		TCLAP::SwitchArg lowerCase("l","lower","change text to lower case",cmd,false);	
		TCLAP::SwitchArg upperCase("u","upper","change text to upper case",cmd,false);	
		TCLAP::UnlabeledValueArg<string> inputArg("input","Input File. Required",true,"input.txt","string",cmd);	//add cmd to the end so you don't have to manually add it afterwards.

		cmd.parse(argc, argv);

		string outputName = outputArg.getValue();
		bool lower = lowerCase.getValue();
		bool upper = upperCase.getValue();


		//Populate map:
		argument_map[OUTPUT] = outputArg.getValue();
		argument_map[INPUT] = inputArg.getValue();
		argument_map[LOWERCASE] = BoolToString(lowerCase.getValue());
		argument_map[UPPERCASE] = BoolToString(upperCase.getValue());


		if(argument_map[LOWERCASE] == "true" && argument_map[UPPERCASE] == "true"){
			//These are mutually exclusive. If they are both true, that's an error.
			cerr << "error: Can't use -l and -u at the same time. Please only use one." << endl;
			exit(1);
		}


	}catch(TCLAP::ArgException &e) {
		cerr << "error: " << e.error() << " for arg " << e.argId() << endl;	
	}
	
	
	
}
