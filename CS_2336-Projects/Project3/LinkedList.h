#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "DoubleLinkNode.h"

class LinkedList
{
    public:
        LinkedList(){head = 0;tail = 0;};   //Default constructor
        LinkedList(DoubleLinkNode *newHead){head = newHead; tail = newHead;};   //overloaded constructor

        void addNode(DoubleLinkNode*);      //Add node function

        ~LinkedList();      //Destructor
        Delete(DoubleLinkNode*);    //delete function

        DoubleLinkNode* getHead(){return head;};    //returns head pointer
        DoubleLinkNode* getTail(){return tail;};    //returns tail pointer
        void setHead(DoubleLinkNode* inputPtr){head = inputPtr;};   //set head pointer
        void setTail(DoubleLinkNode* inputPtr){tail = inputPtr;};   //set tail pointer

        friend std::ostream &operator<<(std::ostream& , DoubleLinkNode*);   // overloaded output operator

        bool nodeSwap(DoubleLinkNode* , DoubleLinkNode*);   //node swap function
        void listSort(string);  //list sort function


    private:
        DoubleLinkNode *head;   //head pointer
        DoubleLinkNode *tail;   //tail pointer

};

#endif // LINKEDLIST_H
