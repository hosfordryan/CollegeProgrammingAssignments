#include "DoubleLinkNode.h"
#include "BaseNode.h"
#include <iostream>

using namespace std;

DoubleLinkNode::DoubleLinkNode() : BaseNode()       //Default constructor. Calls basenode constructor
{
    next = 0;
    prev = 0;
}

DoubleLinkNode::DoubleLinkNode(DoubleLinkNode* np , DoubleLinkNode* pp) : BaseNode(BaseNode::getName(),BaseNode::getArea()) //Overloaded constructor. Calls overloaded basenode constructor
{
    next = np;
    prev = pp;
}


DoubleLinkNode::DoubleLinkNode(const DoubleLinkNode& other)     //Copy constructor
{
    next = other.next;
    prev = other.prev;
    pilotName = other.pilotName;
    patrolArea = other.patrolArea;
}
