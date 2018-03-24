#include <iostream>
#include "Basenode.h"
#include "DoubleLinkNode.h"
#include "DoubleLinkNode.cpp"
#include "LinkedList.h"
#include "LinkedList.cpp"
#include <regex>
#include <fstream>
#include <stdlib.h>


using namespace std;



double solve(vector<double>& xArr, vector<double>& yArr ){     //Calculate the area
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

string getName(string inName){      //returns string of the name
    stringstream in(inName);

    string name = "";
    bool notNumber = true;
    while(in.peek() != '\n' && notNumber){  //While the input isn't a number
        string letter(1,in.peek());
        if(regex_match(letter ,regex("^[A-Za-z\\s]+$"))){   //check that the input is valid
            name += in.get();   //add it to the name
        }
        else{
            notNumber = false;  // no longer what we want
        }
    }
    return name;    //return name
}

bool nameValid(string name)     //Checks to make sure the name we got is a valid name
{
    if(regex_match(name,regex("^[A-Za-z\\s]+$")) && name.back() == ' ')     //Make sure is has no invalid characters and the last char is a space.
        return true;
    return false;
}

bool inputValid(string wholeLine)       //Makes sure the whole line is valid
{
    stringstream ss(wholeLine);
    string name = getName(wholeLine);
    if(nameValid(name)){  //Name is valid
        string temp = "";
        while(temp != name){        //Trimming ss so we don't have the name in it.
            temp+=ss.get();
        }
        string restOfLine;
        getline(ss,restOfLine);         //Possibly throw away next thing in stream. If there is an issue, try that here.

        if(regex_match(restOfLine,regex("^-?\\d*\\.{0,1}\\d+(?:\\.\\d+)?,(?:-?\\d*\\.{0,1}\\d+(?:\\.\\d+)? -?\\d*\\.{0,1}\\d+(?:\\.\\d+)?,)*-?\\d*\\.{0,1}\\d+(?:\\.\\d+)?$"))){    //Make sure the number section of the input is valid. makes sure it is a number/double separaed by a comma, then another number. No extra spaces or commas
            return true;
        }
    }
    return false;
}



void input1(ifstream& in, LinkedList &linList)      //Handles input for reading in the pilots and their areas
{

    string wholeLine;
    int len = in.tellg();
    while(getline(in,wholeLine)){       //Saves whole line



        //in.seekg(len);
        istringstream iss(wholeLine);

        string name;
        vector<double> xArr;                //Define x Coordinate vector
        vector<double> yArr;                //Define y Coordinate Vector

        if(inputValid(wholeLine)){           //checks to make sure input is valid
            name = getName(wholeLine);       //set name variable
            string temp = "";

            while(temp != name){        //Trimming stringstream so we don't have the name in it.
                temp+= (string(1,iss.get()));
            }


            DoubleLinkNode* node = new DoubleLinkNode();    //Create node for the pilot
            node->setName(name);    //add name to node

            while(!iss.eof()){  //going while there are still numbers on the line
                double doub;
                iss >> doub;        //Saves x-coord
                xArr.push_back(doub);   //Pushes the next double into the x Coordinate vector
                iss.get();           //Skips the comma
                iss >> doub;        //saves y-coord

                yArr.push_back(doub);   //Pushes the next double into the y Coordinate vector
            }

            double area = solve(xArr,yArr);     //Calculate area for pilot
            node->setArea(area);        //Sets the area variable in node
            linList.addNode(node);      //Add node to linkedlist
        }
        else{
            continue;       //If input isn't valid, skip.
        }

    }
}


bool input2(string wholeLine, string (&command)[2])     //Handles input for commands
{

    stringstream ss(wholeLine);     //creates stringstream of whole line of input

    if(wholeLine.find("sort") != string::npos){     //If input has 'sort' in it
        if(wholeLine.find("area") != string::npos || wholeLine.find("pilot") != string::npos){  //check that is also contains area or pilot
            string tempGetFirstWord;
            getline(ss,tempGetFirstWord,' ');       //Gets the first part of command
            if(tempGetFirstWord == "sort"){     //If it is sort
                command[0] = "sort";    //save the type of command in the first part of command array
                string restOfLine;
                getline(ss,restOfLine);
                command[1] = restOfLine;    //save the content for the command in the other part of command array
                return true;
            }
        }
        else
            return false;
    }
    else{
        if(regex_match(wholeLine,regex("^-?\\d*\\.{0,1}\\d+(?:\\.\\d+)?$"))){   //Contains only a positive or negative number
            command[0] = "searchNum";       //Command type is searchNum
            command[1] = wholeLine;     //search for this
            return true;
        }
        else{
            if(regex_match(wholeLine,regex("^[A-Za-z\\s]+$"))){    //Contains no unallowed characters. Search for name.
                command[0] = "searchName";      //Command type is searchName
                command[1] = wholeLine + " ";   //Content for search is the name with a trailing space
                return true;
            }
        }
    }
    return false;
}


void output(ofstream &out, string toOut)    //output to file
{
    out << toOut << endl;   //outputs to file
}

bool searchRecurNum(DoubleLinkNode* node , double target , LinkedList &linList)     //Recursive area search
{
    if(linList.getTail() == node){      //If we are on the last node
        if(node->getArea() == target)   //check if it is a match
            return true;
        return false;   //If not a match, linked List doesn't contain target
    }
    else{
        if(node->getArea() == target)   //Check if current node matches target
            return true;
        else
            searchRecurNum(node->getNextPointer(),target,linList);  //If not, call function again with next node
    }
}

bool searchRecurName(DoubleLinkNode* node , string target, LinkedList &linList)     //name search
{
    int count = 0;      // keep track of where we are
    do{
        if(count!=0)    //If it not our first time through, node to the next node
            node = node->getNextPointer();
        if(linList.getTail() == node){      //If we are on the last node
            if(node->getName() == target){  //Do a check
                return true;
            }
            return false;   //target is not in the list
        }
        else{
            if(node->getName() == target){  //Do check
                return true;
            }
            count++;    //try again
        }
    }while(node != linList.getTail());      //Do this while we are not on the last node
}


bool search(string type, string target , LinkedList& linList)   //search function
{
    if(type == "num"){      //Searching for an area
        double targetDouble = strtod(target.c_str(),NULL);      //Convert target to a double
        if(searchRecurNum(linList.getHead(),targetDouble,linList))      //If target is found return true
            return true;
        else
            return false;   //If it's not there, return false
    }
    else if(type == "name"){    //Searching for a name
        if(searchRecurName(linList.getHead(),target,linList)){      //If found, return true
            return true;
        }
        else
            return false;
    }
}

int main()
{
    string inFile1 = "pilot_routes.txt";    //Open pilot input file
    ifstream in(inFile1.c_str());


    LinkedList linList = LinkedList();      //Declare empty linked list

    input1(in,linList);     //Populate linked list

    ifstream in2("commands.txt");   //Open commands input file
    ofstream out;
    out.open("results.txt");    //Open first output file


    string wholeLine;
    int len = in2.tellg();
    while(getline(in2,wholeLine)){      //While we can get the next line
        string command[2];      //Declare command holder
        if(input2(wholeLine,command)){      //If there is a valid command

            if(command[0] == "sort"){       //If it's a sort
                if(command[1] == "area"){   //Sort by area
                    linList.listSort("num");
                }
                else if(command[1] == "pilot"){     //Sort by pilot name
                    linList.listSort("pilot");
                }
            }
            else if(command[0] == "searchNum"){     //Is it a searchNum?
                string result;
                if(search("num",command[1],linList)){       //If it is found
                    result = "found";   //Set result to found
                }
                else
                    result = "not found";   //Not found if it wasn't found
                string toOutput = command[1] + " " + result;        //build string to output
                output(out,toOutput);   //Output to file
            }
            else if(command[0] == "searchName"){        //Search for a name
                string result;
                if(search("name",command[1],linList)){      //If the name was found, set result to found
                    result = "found";
                }
                else
                    result = "not found";
                string toOutput = command[1] + "" + result;     //build string to output
                output(out,toOutput);   //output results
            }
        }
        else

        len = in2.tellg();
    }




    out.close();        //close output file
    out.open("pilot_areas.txt");    //Open other output file
    out << linList;     //output linked list to that file
    out.close();    //close output


    return 0;
}
