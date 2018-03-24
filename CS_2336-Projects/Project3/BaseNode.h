//Author Ryan Hosford - rph160030

#include <iostream>
using namespace std;

#ifndef BASENODE_H
#define BASENODE_H

class BaseNode
{
public:
    virtual BaseNode* getNextPointer() = 0;     //Makes the class abstract
    virtual BaseNode* getPrevPointer() = 0;
    BaseNode(){pilotName = "";patrolArea = 0.0;};   //Default constructor.
    BaseNode(string name , double area) {pilotName = name; patrolArea = area;}; //overloaded constructor
    string getName() {return pilotName;};   //return name
    double getArea(){return patrolArea;};   //return area
    void setName(string in){pilotName = in;};   //set name
    void setArea(double in){patrolArea = in;};  //set area
    string pilotName;
    double patrolArea;

};

#endif
