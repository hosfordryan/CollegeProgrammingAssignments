#include "BinarySearchTree.h"
#include <iostream>
#include <fstream>

using namespace std;

void BinarySearchTree::deleteTree(Node* leaf)   //recursive delete function - post order traversal
{
    if(leaf!=0){    //if it's valid
        deleteTree(leaf->getLeft());
        deleteTree(leaf->getRight());
        delete(leaf);
    }
}


void BinarySearchTree::insertNode(Node* toInsert, Node* leaf)   //recursive insert function - in order traversal
{
    if(leaf == 0)
        leaf = root;
    if(root == 0)
        root = toInsert;
    else{
        if(toInsert->gete() == leaf->gete()){           //If they are equal, combine terms.
            leaf->setcn(leaf->getcn()+toInsert->getcn());
        }
        else if(toInsert->gete() > leaf->gete()){   // Because we want to print from highest exponent to lowest, insert it reverse to what it should be.
            if(leaf->getLeft() == 0)                // If it is greater than, insert left
                leaf->setLeft(toInsert);
            else{
                insertNode(toInsert,leaf->getLeft());
            }
        }
        else if(toInsert->gete() < leaf->gete()){
            if(leaf->getRight() == 0)
                leaf->setRight(toInsert);
            else{
                insertNode(toInsert,leaf->getRight());
            }
        }
    }
}

bool BinarySearchTree::search(Node* leaf, int target)       //Recursively search for a node with the exponent we send it.
{
    if(root == 0){  //make sure the tree is valid
        return false;
    }
    if(target == leaf->gete())  //if we find it, return true
        return true;
    else if(target > leaf->gete()){ //again, this is backwards to how BST's are usually done. This is because we are printing from highest to lowest
        if(leaf->getLeft()){
            if(search(leaf->getLeft(), target))
                return true;
        }
    }
    else if(target < leaf->gete()){
        if(leaf->getRight()){
            if(search(leaf->getRight(), target))
                return true;
        }
    }
    return false;
}

void outputNode(Node* node, int& cnt, ofstream& out)    //Outputs a given node
{
    if( (node->getcn() > 0 && node->getcd() > 0) && cnt > 0)    // check to see if we need a + sign before the term
        out << "+ ";
    if(node->getcd() == -1)     // check if the denominator is negative
        out << "-";
    if(node->getcd() != 1 && node->getcd() != -1){  //Need a fraction?
        out << "("<< node->getcn()<< "/"<< node->getcd()<< ")";
    }
    else if(node->getcn() != 1) //If it's not a fraction, just output the numerator
        out<< node->getcn();
    if(node->gete() != 0 && node->gete() != 1){     //Is x raised to the power of anything but 1?
        out << "x^" << node->gete();
    }
    else if(node->gete() == 1)      //If the exponent is 1, just output x
        out << "x";

    out << " ";
}

void BinarySearchTree::displayInOrder(Node* leaf, int& cnt ,ofstream& out)  //Traverse through the tree and output each node
{
    if(leaf->getLeft())     //In order traversal
        displayInOrder(leaf->getLeft(), cnt,out);
    outputNode(leaf, cnt,out);  //output the node
    cnt++;  //increment count to see if we need to add a sign before the term
    if(leaf->getRight())
        displayInOrder(leaf->getRight(), cnt,out);

}
