#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

#include "Graph.h"
#include "Pilot.h"


using namespace std;


void buildGraph(Graph &graph)   //Build graph function
{
    ifstream inFile("galaxy.txt");  //Open input for graph

    while(!inFile.eof()){   //Loop through file
        string wholeLine;
        getline(inFile,wholeLine);
        graph.addVertex(wholeLine); //Call add vertex for each line
    }
}

void routesTesting(Graph &graph)    //Tests to see if a route is valid
{
    ifstream in("pilot_routes.txt");    //Open input for routes
    ofstream out("patrols.txt");    //Open output file

    vector<Pilot> pList;    //Create a vector of Pilots

    while(!in.eof()){   //Loop through file

        string wholeLine;
        getline(in,wholeLine);
        stringstream ss(wholeLine);     //Create a stringstream for line

        string name;
        while(!isdigit(ss.peek()) && ss.peek() != '-'){
            name+=ss.get();     //Looping until we are no longer at the name
        }

        Pilot pil = Pilot(name);    //Create a pilot with that name
        int start;
        ss >> start;    //Get starting vertex

        int curIndex;

        if(graph.getIndexOfVert(start) == -1){  //Make sure first vertex is there
            pil.setValid(false);    //If it's not set valid to false
            pil.setLengthOfPath(INT_MIN);   //Setting length to smallest int for sorting purposes
        }
        else{	    //If the first vertex is valid
            curIndex = graph.getIndexOfVert(start);     //Save current index in list
            while(!ss.eof()){   //Loop through the rest of the line
                int nextLoc;
                ss >> nextLoc;      //Get the next Target Vertex
                if(graph.getIndexOfVert(nextLoc) == -1){    //If it doesn't exist in the galaxy
                    pil.setValid(false);    //Not valid
                    pil.setLengthOfPath(INT_MIN);   //Setting length to smallest int for sorting purposes
                    break;
                }
                else{
                    if(graph.isElementInList(curIndex,nextLoc)){       //Checking if target vertex is in the list of connected vertices
                        pil.incrementLength(graph.getGraph()[curIndex][graph.getIndexOfElementInList(curIndex,nextLoc)].getW());    //Increment the length variable of the weight of the target vertex
                    }
                    else{
                        pil.setValid(false);    //If it's not found, set to not valid
                        pil.setLengthOfPath(INT_MIN);   //Lowest int for sorting
                    }
                    curIndex = graph.getIndexOfVert(nextLoc);   //Update curIndex
                }


            }
        }

        pList.push_back(pil);   //Add that pilot to the list

    }

		//AT THIS POINT WE HAVE MADE A LIST OF THE PILOTS AND WHATNOT. JUST NEED TO SORT AND OUTPUT

    sort(pList.begin(),pList.end());	//Sorts in ascending order
    for(int i = 0; i < pList.size(); i++){  //Loop through list of Pilots
        if(pList[i].getValid() == false){   //If it wasn't valid, output without length
            out << left << setw(20) << pList[i].getName();
            out << left << setw(20) << "";
            if(pList[i].getValid())
                out << left << setw(20) << "Valid";
            else
                out << left << setw(20) <<"Invalid";
        }
        else{   //If It was valid
            out << left << setw(20) << pList[i].getName();
            out << left << setw(20) << pList[i].getLength();
            if(pList[i].getValid())
                out << left << setw(20) << "Valid";
            else
                out << left << setw(20) <<"Invalid";
        }
        out << endl;
    }
}

int main()
{

    Graph graph = Graph();  //Declare graph
    buildGraph(graph);  //Build the graph
    //graph.DFTPrint(); Commented out because it isn't needed to solve problem. Showing here because a traversal of some kind is required

    routesTesting(graph);   //Test the routes

    return 0;
}
