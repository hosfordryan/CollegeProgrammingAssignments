#include "BinarySearchTree.h"
#include "Node.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <iomanip>

using namespace std;

void buildNode(string input, BinarySearchTree &tree)    //Given an input, builds and inserts a node into the tree
{
    int exponent = 0;
    int coefNume = 0;
    istringstream ss(input);
    if(input.find("^") != string::npos){    //^ is present
        istringstream expss(input);
        string throwaway;
        getline(expss,throwaway,'^');   //getting to the exponent we want
        expss >> exponent;
    }
    if(input.find("x") != string::npos){    //x is present
        if(exponent == 0)   //if there is an x, our exponent has to be at least 1
            exponent = 1;
        istringstream coefss(input);
        string toConvert;
        getline(coefss,toConvert,'x');  //getting to the number before the x
        if(toConvert == ""){    //If there is no number, coef is 1
            coefNume = 1;
        }
        else{
            coefNume = atoi(toConvert.c_str());     //get numerator
        }
    }
    else{
        coefNume = atoi(input.c_str());     //If there isn't an exponent, just grab the number that's there
    }

    Node* newNode = new Node(coefNume,exponent);    //create the node
    tree.insertNode(newNode,tree.getRoot());    //insert it

}

int getGCD(int num1, int num2)      //Get the Greatest common denominator of 2 numbers
{
    int gcd, remainder;

    while (num1 != 0){
        remainder = num2 % num1;
        num2 = num1;
        num1 = remainder;
    }
    gcd = num2;

    return gcd;
}

void reduceFraction(int& nume , int& denom)     //Reduce given fraction
{
    int oldNume = nume;
    nume = nume / getGCD(nume,denom);
    denom = denom / getGCD(oldNume,denom);
}

Node* integrate(Node* inputNode)    //Returns the integrated version of a given node
{
    Node* newNode = new Node();     //initialize the node to return
    int CoefN = 0;
    int CoefD = 1;
    int exp = 0;

    exp = (inputNode->gete()) + 1;  //increment old exponent by 1
    if(exp > 1 || exp <= -1 ){      //If the exponent is greater than 1 or less than -1
        CoefN = inputNode->getcn();
        CoefD = exp;        //set the division
    }
    else{
        CoefN = inputNode->getcn();     //If it doesn't need to be divided, don't worry about it
    }
    newNode->sete(exp);     //setting values of node to return
    newNode->setcn(CoefN);
    newNode->setcd(CoefD);
    return newNode;     //return the integrated node
}

void IntegrateNodes(BinarySearchTree org,BinarySearchTree& newTree, Node* leaf)           //pre order traversal through tree, integrating the nodes and saving them to a new tree
{

    if(leaf != 0){      //If current node is valid
        Node* newNode = integrate(leaf);    //get integrated version
        newTree.insertNode(newNode);        //insert the new version into new tree
    }
    if(leaf->getLeft())
        IntegrateNodes(org,newTree,leaf->getLeft());    // go left

    if(leaf->getRight())
        IntegrateNodes(org,newTree,leaf->getRight());   //go right
}

void simplifyAllFractions(Node* leaf, BinarySearchTree& tree)       //In order traversal through tree, simplifying all fractions
{
    int newn = leaf->getcn(),newd = leaf->getcd();
    if(leaf->getLeft())
        simplifyAllFractions(leaf->getLeft() , tree);   //Go left
    if(leaf){
        reduceFraction(newn, newd);     //reduce the fraction
        leaf->setcn(newn);      //set the current node's values to the reduced versions
        leaf->setcd(newd);
    }
    if(leaf->getRight())
        simplifyAllFractions(leaf->getRight() , tree);  //Go right
}

void notDefinite(string wholeLine, ofstream& out)       //If the input is not definite
{
    BinarySearchTree orgTree = BinarySearchTree();  //declare the tree
    istringstream ss(wholeLine);
    string throwaway;
    getline(ss,throwaway,' ');  //throwaway the beginning we don't want
    if(ss.peek() == ' ')
        ss.get();
    string firstNodeString;
    firstNodeString += ss.get();    //get possible negative sign at start
    while(true){        //looping until we hit a +,-, or d
        if(ss.peek() == 43 || ss.peek() == 100)
            break;
        if(ss.peek() == 45 && firstNodeString.back() != '^'){     //Check if it is a - and if the previous character is not a ^
            break;  //Reached the end of what we want
        }
        if(ss.peek() != ' '){   //If the current char isn't a space, add it to our string
            firstNodeString += ss.get();
        }
        else
            ss.get();   //get rid of the space
    }

    buildNode(firstNodeString,orgTree);     //Build the first node
    while(true){        //Looping until we hit a 'd'
        if(ss.peek() == 100)
            break;
        char sign = ss.get();
        string nextNode;
        while(true){    //Looping until we hit a + or -
            if(ss.peek() == 43 || ss.peek() == 100){
                break;
            }
            if(ss.peek() == 45 && nextNode.back() != '^'){     //Check if it is a - and the last char gotten is a ^
                break;
            }
            if(ss.peek() != ' ')
                nextNode += ss.get();
            else
                ss.get();
        }
        if(sign == '-')
            nextNode = sign + nextNode;
        buildNode(nextNode, orgTree);   //Build that node
    }

    int count = 0;  //set the count for our output function call
    BinarySearchTree newTree = BinarySearchTree(integrate(orgTree.getRoot()));  //create new tree with the root being the integrated version of the current tree's root
    if(orgTree.getRoot()->getLeft())    //If there is a node to the left, call the integrate function starting there
        IntegrateNodes(orgTree,newTree,orgTree.getRoot()->getLeft());
    else if(orgTree.getRoot()->getRight())      //If there is a node to the right, call the integrate function starting there
        IntegrateNodes(orgTree,newTree,orgTree.getRoot()->getRight());


    simplifyAllFractions(newTree.getRoot(),newTree);    //Simplify all the fractions in the new tree
    newTree.displayInOrder(newTree.getRoot(),count,out);    //output the tree
    count = 0;
    out <<  " + C" << endl;     //add the + C that we need
}


void evaluateFunction(double &total, int x, BinarySearchTree tree, Node* leaf)      //Evaluate the function with given x value - in order traversal
{
    if(leaf->getLeft())
        evaluateFunction(total,x,tree,leaf->getLeft());
    if(leaf->gete() != 0 ){
        double product = (leaf->getcn() * pow(x,leaf->gete())) / leaf->getcd();

        total+= product;

    }
    else
        total+= leaf->getcn();
    if(leaf->getRight())
        evaluateFunction(total,x,tree,leaf->getRight());
}

void isDefinite(string wholeLine, ofstream& out)        //The input is a definite integral
{
    BinarySearchTree orgTree = BinarySearchTree();
    istringstream ss(wholeLine);

    int startInteger, endInteger;
    ss>> startInteger;  //get first number
    ss.get();   //Throw away the |
    ss >> endInteger;   //Get the second number
    if(ss.peek() == ' ')
        ss.get();


    string firstNodeString;
    firstNodeString += ss.get();    //get possible negative sign at start
    while(true){        //looping until we hit a +,-, or d
        if(ss.peek() == 43 || ss.peek() == 100)
            break;
        if(ss.peek() == 45 && firstNodeString.back() != '^'){     //Check if it is a - and the previous char is not a ^
            break;
        }
        if(ss.peek() != ' '){       //If it isn't a space, we want it
            firstNodeString += ss.get();
        }
        else
            ss.get();       //throw away spaces
    }

    buildNode(firstNodeString,orgTree);
    while(true){        //Looping until we hit a 'd'
        if(ss.peek() == 100){
            break;
        }
        char sign = ss.get();
        string nextNode;
        while(true){    //Looping until we hit a + or -
            if(ss.peek() == 43 || ss.peek() == 100){
                break;
            }
            if(ss.peek() == 45 && nextNode.back() != '^'){     //Check if it is a - and the last char gotten isn't a ^
                break;
            }
            if(ss.peek() != ' ')
                nextNode += ss.get();
            else
                ss.get();
        }
        if(sign == '-')
            nextNode = sign + nextNode;
        buildNode(nextNode, orgTree);       //Build node
    }

    int count = 0;
    BinarySearchTree newTree = BinarySearchTree(integrate(orgTree.getRoot()));      //create new tree with the root being the integrated version of the current tree's root
    if(orgTree.getRoot()->getLeft())    //If there is something to the left, integrate starting there
        IntegrateNodes(orgTree,newTree,orgTree.getRoot()->getLeft());
    else if(orgTree.getRoot()->getRight())  //If there is something to the right, integrate starting there
        IntegrateNodes(orgTree,newTree,orgTree.getRoot()->getRight());

    simplifyAllFractions(newTree.getRoot(),newTree);        //Simplify all the fractions in the tree


    double firstEval, secondEval;
    evaluateFunction(firstEval,startInteger,newTree,newTree.getRoot());     //Get the functions evaluated value with start x
    evaluateFunction(secondEval,endInteger,newTree,newTree.getRoot());      //Get the functions evaluated value with end x

    count = 0;
    newTree.displayInOrder(newTree.getRoot(),count,out);        //Display the tree
    out << ", " << startInteger << "|" << endInteger << " = " << fixed <<setprecision(3) << (secondEval - firstEval) <<endl;        //Display the value of the definite integral
}

int main()
{

    string inputFile = "integrals4.txt";

    ifstream in(inputFile.c_str());     //open input file
    ofstream out("answers.txt");        //open output file

    while(!in.eof()){       //loop while the input isn't empty
        bool definite = true;
        string wholeLine;
        getline(in,wholeLine);  //get the line of input
        if(wholeLine[0] == '|')     //check to see if it is a definite integral
            definite = false;
        if(!definite)
            notDefinite(wholeLine,out);
        else{
            isDefinite(wholeLine,out);
        }
    }

    in.close();
    out.close();

    return 0;
}
