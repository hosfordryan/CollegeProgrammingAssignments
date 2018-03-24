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

map <int,string> argument_map;


int main (int argc, char *argv[]){
	parseCmdLine(argc,argv);
	doWork();	

}
