#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Node.h"
#include <fstream>

using namespace std;

class BinarySearchTree
{
    public:
        BinarySearchTree(){root = 0;};  //default constructor
        BinarySearchTree(Node* in){root = in;};     //overloaded constructor

        void deleteTree(Node*);     //recursive delete function
        ~BinarySearchTree(){deleteTree(root);};     //destructor, calls delete function

        Node* getRoot(){return root;};  //get root
        void setRoot(Node* in){root = in;}; //set root

        void insertNode(Node* toInsert, Node* leaf = 0);    //insert a node
        bool search(Node* leaf, int target);    //search for a node
        void displayInOrder(Node* leaf, int& cnt, ofstream& out);   //displays tree in order

        Node* root;

};

#endif // BINARYSEARCHTREE_H
