#include "Graph.h"

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


void Graph::addVertex(string inputLine)     //Adds a vertex to the adjacency list
{
    stringstream ss(inputLine);
    vector<Node> toAdd;
    int vert;
    ss >> vert; //Gets first number as the vertex for this list
    Node vertex = Node(vert);   //Creates a Node of that vertex
    toAdd.push_back(vertex);    //Adds it the list to be added to the adjacency lists

    		//LOOP THROUGH AND MAKE THE NODES AND ADD THEM TO VECTOR
    while(ss.peek() != -1){
        int nextValue;
        ss >> nextValue;    //Get next vertex
        int weight;
        ss.get();   //Throw away the comma
        ss >> weight;   //Get the weight of that vertex
        Node newNode = Node(nextValue,weight);  //Create a node for that vertex
        toAdd.push_back(newNode);       //Add it to list
    }

    graph.push_back(toAdd); //Add list to the main adjacency list
    size++; //Add 1 to the size of graph
}

int Graph::getIndexOfVert(int target)   //Get index of vertex
{
    int index = -1; //Set default return value

    for(int i = 0; i < graph.size(); i++){
        if(graph[i][0].getV() == target)    //If we find the vertex we are looking for
            index = i;  //Set index to the index of the vertex
    }
    return index;   //return it
}

bool Graph::isElementInList(int indexOfList, int target)    //Get whether or not an element is in a certain vertex's list
{
    for(int i = 0; i < graph[indexOfList].size();i++){
        if(graph[indexOfList][i].getV() == target)  //Check if we find the target in the list of the vertex we are searching
            return true;
    }

    return false;
}

int Graph::getIndexOfElementInList(int indexOfList, int target) //Get index of element in a list
{
    int index = -1; //Set default return value (not found)

    for(int i = 0; i < graph[indexOfList].size();i++){
        if(graph[indexOfList][i].getV() == target)      //If we find the element we are looking for
            index = i;  //save index
    }

    return index;   //Return it
}

void Graph::print(int v, bool visited[])    //DFT print of graph's vertices
{
    int index = getIndexOfVert(v);  //Getting the index of the current vertex
    visited[index] = true;  //Set that vertex to visited
    cout << graph[index][0].getV() << ", "; //Print that vertex

    for(int i = 0; i < graph[index].size();i++){
        if(!visited[getIndexOfVert(graph[index][i].getV())])    //Find the next vertex
            print(graph[index][i].getV(),visited);  //Call Print function
        }
}

void Graph::DFTPrint()
{

    bool *visited = new bool[size]; //Create visited array
    for(int i = 0; i < size; i++){
        visited[i] = false;     //Initialize to false
    }

    print(graph[0][0].getV(),visited);  //Call recursive function
    cout << endl;
}


