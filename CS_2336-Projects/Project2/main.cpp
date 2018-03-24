//Author Ryan Hosford (rph160030)


#include "ComplexNumber.h"
#include "ComplexNumber.cpp"
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;


void operation(ComplexNumber a, ComplexNumber b, string op,ofstream &out)       //Checks what operation to do, and does it.
{

    ComplexNumber res;

    if(op == "+"){  //Checks for +
        ComplexNumber res = a + b;
        ostringstream firstStream, secondStream;
        firstStream << a << " " << op << " " << b;      //Building output for file
        secondStream << res << endl;
        string first = firstStream.str();
        string second = secondStream.str();
        out << left << setw(30) << first;       //Outputs to file
        out <<"|" << right << setw(30) << second;   //Outputs to file


        //cout << res << endl;
    }
    else if(op == "-"){     //Checks if -
        ComplexNumber res = a - b;
        ostringstream firstStream, secondStream;
        firstStream << a << " " << op << " " << b;      //Building output for file
        secondStream << res << endl;
        string first = firstStream.str();
        string second = secondStream.str();
        out << left << setw(30) << first;       //Outputs to file
        out <<"|" << right << setw(30) << second;       //Outputs to file
    }
    else if(op == "*"){     //Checks if *
        ComplexNumber res = a * b;
        ostringstream firstStream, secondStream;
        firstStream << a << " " << op << " " << b;      //Building output for file
        secondStream << res << endl;
        string first = firstStream.str();
        string second = secondStream.str();
        out << left << setw(30) << first;       //Outputs to file
        out <<"|" << right << setw(30) << second;       //Outputs to file
    }
    else if(op == "/"){     //Checks if /
        ComplexNumber res = a / b;
        ostringstream firstStream, secondStream;
        firstStream << a << " " << op << " " << b;      //Building output for file
        secondStream << res << endl;
        string first = firstStream.str();
        string second = secondStream.str();
        out << left << setw(30) << first;   //Outputs to file
        out <<"|" << right << setw(30) << second;   //Outputs to file
    }

    else if(op == "<"){
        ostringstream firstStream;
        firstStream << a << " " << op << " " << b;      //Building output for file
        string first = firstStream.str();
        out << left << setw(30) << first;
        if(a<b) out <<"|" <<right << setw(29) << "True" << endl;        //Outputs to file
        else out <<"|"<<right << setw(29)<< "False" << endl;        //Outputs to file
    }

    else if(op == ">"){
        ostringstream firstStream;
        firstStream << a << " " << op << " " << b;      //Building output for file
        string first = firstStream.str();
        out << left << setw(30) << first;
        if(a>b) out <<"|" <<right << setw(29) << "True" << endl;        //Outputs to file
        else out <<"|"<<right << setw(29)<< "False" << endl;        //Outputs to file
    }

    else if(op == "="){
        ostringstream firstStream;
        firstStream << a << " " << op << " " << b;      //Building output for file
        string first = firstStream.str();
        out << left << setw(30) << first;
        if(a==b) out <<"|" <<right << setw(29) << "True" << endl;       //Outputs to file
        else out <<"|"<<right << setw(29)<< "False" << endl;        //Outputs to file
    }

    else if(op == "/="){
        ostringstream firstStream;
        firstStream << a << " " << op << " " << b;      //Building output for file
        string first = firstStream.str();
        out << left << setw(30) << first;
        if(a!=b) out <<"|" <<right << setw(29) << "True" << endl;       //Outputs to file
        else out <<"|"<<right << setw(29)<< "False" << endl;        //Outputs to file
    }

}

void input(ifstream &in, int cnt, ofstream &out)
{
    ComplexNumber a,b;
    string temp;
    getline(in,temp,' ');   //Gets first complex number
    string op;
    getline(in,op,' ');     //Gets operator
    if(op != "+" && op != "-" && op != "*" && op != "/" && op != "<" && op != ">" && op != "=" && op != "/=" ){     //Check if operator is not valid
        string remaining;
        getline(in,remaining);      // thowaway rest of line
        return;     //End input for this set
    }

    stringstream input(temp);

    if(input >> a){     //Build first complex number
        string remaining;
    }
    else{
        string remaining;
        getline(in,remaining);      //If that failed, throw away rest of line
        return;     //End input for this set
    }

    getline(in,temp);

    stringstream input2(temp);
    if(input2 >> b){        //Build second complex number
        string remaining;
    }
    else{
        string remaining;
        getline(in,remaining);     //If building second number failed, throw away rest of line
        return;     //End input for this set
    }
    operation(a,b,op,out);      //Run the operation function
}

int main()
{
    ifstream in("complex.txt");     //Input file
    ofstream out("results.txt");    //Output file
    if(!in) cout << "failed to open file." << endl;
    int cnt = 0;
    while(!in.eof()){
        input(in,cnt,out);      //Run input for file
    }
    out.close();        //Close output file
    in.close();
    return 0;
}
