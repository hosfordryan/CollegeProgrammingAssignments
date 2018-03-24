//Author Ryan Hosford (rph160030)

#include <iostream>
#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H


class ComplexNumber
{
    public:
        ComplexNumber();
        ComplexNumber(double,std::string); //String is to show if just imaginary or just real.
        ComplexNumber(double,double);
        ComplexNumber(const ComplexNumber& other);
        double getR();  //Accessor methods
        double getI(); //Accesspr methood
        void setR(double);
        void setI(double);

        double getMagnitude(ComplexNumber);
        ComplexNumber operator+(ComplexNumber&);
        ComplexNumber operator-(ComplexNumber&);
        ComplexNumber operator*(ComplexNumber&);
        ComplexNumber operator/(ComplexNumber&);

        bool operator<(ComplexNumber);
        bool operator>(ComplexNumber);
        bool operator==(ComplexNumber);
        bool operator!=(ComplexNumber);

        bool parseComplex(std::istream&, double&, double&);
        friend std::ostream &operator<<(std::ostream& , const ComplexNumber&);
        friend std::istream &operator>>(std::istream& , ComplexNumber&);


    private:
        double realNum, imaginaryNum;

};

#endif // COMPLEXNUMBER_H
