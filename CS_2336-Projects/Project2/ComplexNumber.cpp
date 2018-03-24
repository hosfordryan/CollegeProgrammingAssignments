//Author Ryan Hosford (rph160030)

#include "ComplexNumber.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <iterator>

using namespace std;


ComplexNumber::ComplexNumber()  //Default constructor
{
    realNum = 0;
    imaginaryNum = 0;
}

ComplexNumber::ComplexNumber(double in, string r_i)    //Overloaded constructor
{
    if(r_i == "r"){realNum = in; imaginaryNum = 0;} //Checks if input is only a real
    else{imaginaryNum = in; realNum = 0;}
}

ComplexNumber::ComplexNumber(double r,double i) //Constructor that takes input and sets apropriate variables
{
    realNum = r;
    imaginaryNum = i;
}


ComplexNumber::ComplexNumber(const ComplexNumber& other)    //Copy Constructor
{
    realNum = other.realNum;
    imaginaryNum = other.imaginaryNum;

}

double ComplexNumber::getR()   //Real accessor method
{
    return realNum;
}

double ComplexNumber::getI()   //Imaginary accessor method
{
    return imaginaryNum;
}

void ComplexNumber::setR(double newR)   //Mutator for real
{
    realNum = newR;
}

void ComplexNumber::setI(double newI)   //Mutator for Imaginary
{
    imaginaryNum = newI;
}


//////////////////////////////////////////Arithmetic////////////////////////////////////////

ComplexNumber ComplexNumber::operator+(ComplexNumber &other)    //Overloaded + operator
{
    return ComplexNumber(realNum+other.getR(),imaginaryNum+other.getI());
}

ComplexNumber ComplexNumber::operator-(ComplexNumber &other)    //Overloaded - operator
{
    return ComplexNumber(realNum-other.getR(),imaginaryNum-other.getI());
}

ComplexNumber ComplexNumber::operator*(ComplexNumber &other)    //Overloaded * operator
{
    double a = realNum;
    double b = imaginaryNum;
    double c = other.getR();
    double d = other.getI();

    return ComplexNumber((a*c) - (b*d) , (b*c) + (a*d));
}

ComplexNumber ComplexNumber::operator/(ComplexNumber &other)    //Overloaded / operator
{
    double a = realNum;
    double b = imaginaryNum;
    double c = other.getR();
    double d = other.getI();

    return ComplexNumber((a*c+b*d) / (c*c+d*d) , (b*c-a*d) / (c*c+d*d));
}


///////////////////////////////////Relational////////////////////////////////////////////



double ComplexNumber::getMagnitude(ComplexNumber in)    //Returns magnitude of complex number
{
    double ret = sqrt((in.getR() * in.getR()) + (in.getI() * in.getI()));
    return ret;
}

bool ComplexNumber::operator<(ComplexNumber in)     //Overloaded < operator
{
    if(getMagnitude(ComplexNumber(realNum,imaginaryNum)) < getMagnitude(in)){
        return true;
    }
    else{
        return false;
    }
}

bool ComplexNumber::operator>(ComplexNumber in)     //Overloaded > operator
{
    if(getMagnitude(ComplexNumber(realNum,imaginaryNum)) > getMagnitude(in)){
        return true;
    }
    else{
        return false;
    }
}

bool ComplexNumber::operator==(ComplexNumber in)     //Overloaded == operator
{
    if(realNum == in.getR() && imaginaryNum == in.getI()){
        return true;
    }
    else{
        return false;
    }
}

bool ComplexNumber::operator!=(ComplexNumber in)     //Overloaded != operator
{
    if(realNum == in.getR() && imaginaryNum == in.getI()){
        return false;
    }
    else{
        return true;
    }
}


/////////////////////////////////////// IO /////////////////////////////////////////////////////

ostream& operator<<(ostream &os, ComplexNumber& CN)    // Overloaded << operator
{
    char sign = '+';
    if(CN.getI() < 0){
        os <<fixed << setprecision(2) << CN.getR()<< CN.getI() << "i";
    }
    else{
        os << fixed << setprecision(2) <<CN.getR() <<sign<< CN.getI() << "i";
    }
    return os;
}

bool parseComplex(istream &input, double &real, double &imag)   //Parse the input and check if good.
{
    char filter;
    double temp;
    char next;
    if(input >> temp)   //Read double, check to make sure it is ok
    {
        next = input.peek();    //Check next char
        if(next != 'i') //Not imaginary
        {
            real = temp;
            if(next == '+' || next == '-'){ // Check if it is imaginary
                if(input >> imag >> filter && filter == 'i') //Read imaginary and make sure it has the i
                {
                    return true;
                }
            }
            else{
                return true;
            }
        }
        else{   //Just imaginary
            imag = temp;
            input >> filter;
            return true;
        }
    }
    return false;
}

istream& operator>>(istream &input , ComplexNumber& other)  //Overloaded >> operator
{
    double real = 0.0;
    double imaginary = 0.0;

    if(parseComplex(input,real,imaginary)){
        char next = input.peek();       //Peeks at next char
        if(isspace(next) || next == char_traits<char>::eof()){  //Checks if valid
            other.realNum = real;       //Sets variables
            other.imaginaryNum = imaginary;
            input.clear();  //May have read eof
            return input;
        }
    }

    input.setstate(ios::failbit);
    return input;

}




