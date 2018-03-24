#ifndef NODE_H
#define NODE_H


class Node
{
    public:
        Node(){value = 0;weight = 0;};      //Default const.
        Node(int v){value = v; weight = 0;};    //Overloaded constructor
        Node(const Node& other){value = other.value; weight = other.weight;};   //Copy Constructor
		Node(int v, int w){value = v; weight = w;}; //Other Overloaded constructor
		int getV(){return value;};  //Return value
		int getW(){return weight;}; //Return weight
		void setV(int in){value = in;};     //Set value
		void setW(int in){weight = in;};    //Set weight

    private:
        int value;
        int weight;
};

#endif // NODE_H

