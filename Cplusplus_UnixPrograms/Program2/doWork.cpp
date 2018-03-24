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

using namespace std;

string BoolToString(bool b){
	return b ? "true" : "false";
}

void toUpperCase(string &s){
	for (int i = 0; i < s.length(); ++i) {
		s[i] = toupper(s[i]);	
	}
}
void toLowerCase(string &s){
	for (int i = 0; i < s.length(); ++i) {
		s[i] = tolower(s[i]);	
	}
}

void doWork (){
	

		ifstream inFile;
		ofstream outFile;

		outFile.open(argument_map[OUTPUT].c_str());
		inFile.open(argument_map[INPUT].c_str());
		if(!inFile){

			cout << "Unable to open file: " << argument_map[INPUT] << endl;
			exit(1);
		}




		if(argument_map[UPPERCASE] == "true"){
			while(!inFile.eof())
			{
				string s;
				getline(inFile, s);
				toUpperCase(s);
				outFile << s << endl;
			}			
		}
		else if(argument_map[LOWERCASE] == "true"){
			while(!inFile.eof())
			{
				string s;
				getline(inFile, s);
				toLowerCase(s);
				outFile << s << endl;
			}			
		}
		else{
			while(!inFile.eof())
			{
				string s;
				getline(inFile,s);
				outFile << s << endl;
			}	
		}
		outFile.close();
		inFile.close();
}
