/* Ryan Hosford
 * rph160030@utdallas.edu
 * CS3377
 */
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string gawkLocation = "/home/013/r/rp/rph160030/Programs/Program3/bin/gawk";
char *shellCmd1 = "/home/013/r/rp/rph160030/Programs/Program3/bin/gawk --version";
char *shellCmd2 = "/home/013/r/rp/rph160030/Programs/Program3/bin/gawk -f gawk.code numbers.txt";

int num1;
int num2;

FILE *popen(const char *command, const char *mode);
int pclose(FILE *stream);

string  getString(const char *command){
	FILE * file = popen(command, "r");

	if(file){
		ostringstream stream;
		char line[1024];

		while( fgets(line, 1024, file) ) stream << line;

		pclose(file);
		return stream.str();
	}
}

void getVersion(){
	string version = getString(shellCmd1);
	cout << "The first call to gawk returned:\n"<< version << endl;
}

void getNums(){
	string numString = getString(shellCmd2);
	cout << "The Second call to gawk returned: " << numString << endl;

	int num1, num2;
	stringstream ss;
	ss<<numString;
	ss>>num1>>num2;
	ss.str("");
	ss.clear();

	int sum = num1 + num2;
	cout << "The sum of column 1 is: " << num1 << endl;
	cout << "The sum of column 4 is: " << num2 << endl;
	cout << "The sum of the two numbers is: " << sum << endl;
}

int main(int argc, char *argv[]){
	cout << "gawk at: " << gawkLocation << endl << "shellCmd1: " << shellCmd1 << endl << "shellCmd2L " << shellCmd2 << "\n\n";
	getVersion();
	getNums();
}
