#ifndef DOUBLELINKNODE_H
#define DOUBLELINKNODE_H

#include "BaseNode.h"


class DoubleLinkNode : public BaseNode
{
    public:
        DoubleLinkNode();   //default constructor
        DoubleLinkNode(DoubleLinkNode* , DoubleLinkNode*);      //overloaded constructor
        DoubleLinkNode(const DoubleLinkNode& other);        //Copy constructor
        DoubleLinkNode* getNextPointer(){return next;};      //returns pointer to next node
        DoubleLinkNode* getPrevPointer(){return prev;};      //returns pointer to prev node
        void setNextPointer(DoubleLinkNode* np){next = np;};    //sets next pointer
        void setPrevPointer(DoubleLinkNode* pp){prev = pp;};    //sets prev pointer

    private:
        DoubleLinkNode* next;
        DoubleLinkNode* prev;
};

#endif // DOUBLELINKNODE_H
