#ifndef NODE_H
#define NODE_H


class Node
{
    public:
        Node(const Node& other){coefNume = other.coefNume;coefDenom = other.coefDenom;exp = other.exp;left = other.left;right = other.right;};  //Copy constructor
        Node(){exp = 0;coefNume=0;coefDenom=1,left=0;right=0;}; //Default constructor
        Node(int c,int e){coefNume=c;coefDenom=1;exp=e;left=0;right=0;};    //Overloaded constructor

        int getcn(){return coefNume;};  //get numerator
        int getcd(){return coefDenom;};     //get denominator
        int gete(){return exp;};    //get exponent
        void setcn(int in){coefNume=in;};   //set nume
        void setcd(int in){coefDenom=in;};  //set denom
        void sete(int in){exp=in;};     //set exponent
        Node* getLeft(){return left;};  //get left pointer
        Node* getRight(){return right;};    //get right pointer
        void setLeft(Node* ptr){left=ptr;};     //set left pointer
        void setRight(Node* ptr){right=ptr;};   //set right pointer

    private:
        int exp;
        int coefNume;
        int coefDenom;
        Node* left;
        Node* right;
};

#endif // NODE_H
