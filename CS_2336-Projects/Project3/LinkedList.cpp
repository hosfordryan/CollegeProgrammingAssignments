#include "LinkedList.h"
#include <iostream>
#include <iomanip>

using namespace std;


void LinkedList::addNode(DoubleLinkNode* newNode)   //Function to add a node
{
    newNode->setNextPointer(getHead());             //sets the next pointer of new node to head
    if(getHead())                                   //If there is a head
        getHead()->setPrevPointer(newNode);         //set the head's prev pointer to the new node
    if(!getTail())                                  //If there isn't a tail
        setTail(newNode);                           //Set the tail to the new node
    setHead(newNode);                               //Changes head to the new node
}

LinkedList::~LinkedList()   //Destructor
{
    Delete(getTail());      //Calls recursive function to delete
}

LinkedList::Delete(DoubleLinkNode *tailIn)      //recursive delete function
{
    if(LinkedList::head == LinkedList::tail){   //If there is only 1 node left
        delete tailIn;      //delete it
    }
    else{
        DoubleLinkNode *tempPtr;    //declare temp pointer
        tempPtr = tailIn->getPrevPointer(); //set temp to the current node's previous node
        setTail(tailIn->getPrevPointer());  //set the new tail to the current node's previous node
        delete tailIn;      //delete current node
        Delete(tempPtr);    //call function again with next node

    }
}
ostream& operator<<(ostream& os, LinkedList &linList)   //overloaded output operator
{
    DoubleLinkNode *cur = linList.getHead();    // declare a Node to the head
    while(cur){     //While there is a node
        os << cur->getName() << "\t" << fixed << setprecision(2) << cur->getArea() << endl;     //output the name along with area
        cur = cur->getNextPointer();    //set cur to the next node
    }
}

bool LinkedList::nodeSwap(DoubleLinkNode *a , DoubleLinkNode *b)    //Function to swap nodes
{
    if(!a)      //Make sure a exists
        return false;
    if(!b)      //Make sure b exists
        return false;

    if(a == head){      //If a is the head
        setHead(b);     //Set the new head to b
    }
    else if(b == getHead()) setHead(a);     //If b is the head, make a the head
    if(b == getTail()) setTail(a);          //If b is the tail, make a the tail
    else if(a == getTail()) setTail(b);     //If a is the tail, make b the tail

    if(a->getPrevPointer()){        //If a has a prev node
        a->getPrevPointer()->setNextPointer(b); //set the next pointer of a's previous node to b
    }

    if(b->getNextPointer()){        //If b has a next node
        b->getNextPointer()->setPrevPointer(a);     //set the previous pointer of b's next node to a
    }

    a->setNextPointer(b->getNextPointer());     //Set a's next pointer to b's next pointer
    b->setNextPointer(a);       //set b's next pointer to a

    b->setPrevPointer(a->getPrevPointer());     //set b's previous node to a's previous node
    a->setPrevPointer(b);       //set a's previous pointer to b



    return true;



}

void LinkedList::listSort(string sortType)      //Sorts the linkedList. Takes input based on the type of sort
{
    if(sortType == "num"){  //sorting by area
        DoubleLinkNode *n = head;
        while(n->getNextPointer()!=0){      //While there are node's to go through
             if(n->getArea() > n->getNextPointer()->getArea()){     //check area's
                nodeSwap(n,n->getNextPointer());    //swap nodes
                n = head;   //restart at the beginning
             }
             else{
                n = n->getNextPointer();    //Move on to the next node
             }
        }
    }
    else if(sortType == "pilot"){    //Sorting by name
        DoubleLinkNode *n = head;
        while(n->getNextPointer()!=0){
             if(n->getName().compare(n->getNextPointer()->getName()) >0){       //Compare names
                nodeSwap(n,n->getNextPointer());      //swap nodes
                n = head;       //restart at the beginning
             }
             else{
                n = n->getNextPointer();    //move on to the next node
             }
        }
    }
}


