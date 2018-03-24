//Ryan Hosford - rph160030

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;



void solve(ifstream);
vector<string> split(string,char);

//Function to build the vectors that will store the coordinates
void buildVectors(ifstream& inFile,vector<double>& xArr, vector<double>& yArr){
    while(inFile.peek() != '\n' ){    //Reads until it reaches the end of the line
        double doub;
        inFile >> doub;
        xArr.push_back(doub);   //Pushes the next double into the x Coordinate vector
        inFile.get();           //Skips the comma
        inFile >> doub;
        yArr.push_back(doub);   //Pushes the next double into the y Coordinate vector
    }
}

double solve(string name, vector<double>& xArr, vector<double>& yArr ){     //Calculate the area
    double sum = 0;
    for(int i = 0; i < xArr.size()-1; i++){                             //Loop through the coordinates
        sum += ((xArr[i+1] + xArr[i]) * (yArr[i+1] - yArr[i]) );        //Calculate the inner number
    }
    sum = abs(sum);                                                     //Take Absolute value
    sum = sum/2;                                                        //Divide sum by 2
    xArr.clear();                                                       //Clear vector
    yArr.clear();
    return sum;
}

void output(string name, double ans, ofstream& output){                                   //Output the name and sum with proper formatting into a file

    output << name << "\t" << fixed << setprecision(2) << ans << endl;    //output to file with proper precision on decimal.

}

int main(){
    string filename = "pilot_routes.txt";
    ifstream inFile(filename.c_str());                                  //Read in file
    ofstream out("pilot_areas.txt");

    if(!inFile){
        cout << endl << "File not found.";                              //Make sure file is found
    }
    while(!inFile.eof()){                       //Loop until end of file
        vector<double> xArr;                //Define x Coordinate vector
        vector<double> yArr;                //Define y Coordinate vector
        string name;

        inFile >> name;     //Save name to variable
        inFile.get();       //Get rid of extra space

        string wholeLine;

        if(name.length() > 0){      //Make sure the line has data on it
            buildVectors(inFile,xArr,yArr);     //Build vectors
            double answer = solve(name,xArr,yArr);      //Get answer and save as double
            output(name,answer,out);        //output answer
        }


    }
    out.close();                //Close output file
    return 0;
}




