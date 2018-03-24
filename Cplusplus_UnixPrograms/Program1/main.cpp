/* Ryan Hosford
 * rph160030@utdallas.edu
 * CS3377
 */
#include <iostream>
using namespace std;

void otherFunct();

int main(int argc, char** argv){
	cout << "You entered " << argc << " arguments.\n";
	for (int i = 0; i < argc; ++i) {
		cout << argv[i] << "\n";	
	}
	
	otherFunct();
	return 0;
}
