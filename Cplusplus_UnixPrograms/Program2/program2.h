/* Ryan Hosford
 * rph160030@utdallas.edu
 * CS3377
 */
#ifndef _PROGRAM2_H_
#define _PROGRAM2_H_ 

#include <string>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;
void parseCmdLine(int, char **);
void doWork();
string BoolToString(bool);

extern map<int,string> argument_map;
enum args {OUTPUT,INPUT,LOWERCASE,UPPERCASE};

#endif /* ifndef _PROGRAM2_H_ */
