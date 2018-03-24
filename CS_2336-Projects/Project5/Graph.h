#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <vector>
#include <string>

using namespace std;

class Graph
{
    public:

        vector<vector<Node>> graph;     //Our adjacency list
        Graph(){size = 0;};     //Default constructor
        ~Graph(){graph.clear();graph.shrink_to_fit();};     //Destructor
        int getSize(){return size;};    //Get size
		vector<vector<Node>> getGraph(){return graph;};     //Get adjacency list
		void setSize(int in){size = in;};   //Set size
		void setGraph(vector<vector<Node>> in){graph = in;};    //Set adjacency list

        void addVertex(string); //Add a vertex to the graph
		int getIndexOfVert(int target);     //Get the index of a certain vertex
		bool isElementInList(int indexOfList,int target);   //See if a list contains an element
		int getIndexOfElementInList(int indexOfList, int target);   //Get index of the element in the list
		void print(int v, bool visited[]);  //Depth First Traversal Print
		void DFTPrint();    //Depth First Traversal Print

    private:
        int size;   //Size of graph
};

#endif // GRAPH_H
