#include <unordered_map>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>

#include "Graph.h"

using namespace std;


Graph::Graph() {}

Graph::Graph(ifstream & fName) {
	map<string, int> graph;
	int numNodes, numEdges;
	string tempVal;
	
	fName >> numNodes >> numEdges;
	
	for (int i = 0; i < numNodes; i++) {
		fName >> tempVal;
		Vertex tempVert;
		tempVert.label = tempVal;
		vertices.push_back(tempVert);
		graph[tempVal] = i;
	}
	
	string v1, v2;
	int cost, index;
	
	for (int i = 0; i < numEdges; i++) {
		fName >> v1 >> v2 >> cost;
		index = graph[v1];
		pair<int, int> p(graph[v2], cost);
		vertices.at(index).neighbors.push_back(p);
	}
}

Graph::~Graph() { 
    while(vertices.size() != 0){
        vertices.pop_back();
    }
}


void Graph::output_graph(const string & outputFilename) {
    
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    
    // for (unsigned i = 0; i < vertices.size(); i++) {
    // 	if (!vertices.at(i).neighbors.empty()) {
    // 		list<pair<int, int> >::iterator it = vertices.at(i).neighbors.begin();
    // 		while (it != vertices.at(i).neighbors.end()) {
    // 			outFS << "\"" << vertices.at(i).label << ", " << vertices.at(i).distance << "\" -> \""
    // 			<< vertices.at(it->first).label << ", " << vertices.at(it->first).distance
    // 			<< "\";" << endl;
    // 			++it;
    // 		}
    // 	}
    for (unsigned i = 0; i < vertices.size(); i++) {
    	if (vertices.at(i).distance != INT_MAX) {
        outFS << vertices.at(i).label << "[label = \"" << vertices.at(i).label << ", " << vertices.at(i).distance << "\"]" << endl;
    	}
     	if (!vertices.at(i).neighbors.empty()) {
     	    list<pair<int, int> > ::iterator it = vertices.at(i).neighbors.begin();
     		while (it != vertices.at(i).neighbors.end()) {
     				if (vertices.at(i).distance!= INT_MAX) {
     		    outFS << vertices.at(i).label << " -> " << vertices.at(it->first).label << endl;
     				}
     		    it++;
     		}
     	}
     	    
    }

    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tpng " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
    return;
}

// Breadth First Search. Via a BFS traversal, this function should assign each individual vertex's distance to the number of hops that the vertex is from the start vertex. 
// You can find the pseudo code for BFS on graphs.pdf
void Graph::bfs() {
	map<string, unsigned> graph;
	for (unsigned i = 0; i < vertices.size(); i++) {
		vertices.at(i).color = "WHITE";
		vertices.at(i).distance = INT_MAX;
		vertices.at(i).prev = 0;
		graph[vertices.at(i).label] = i;
	}
	
	vertices.at(0).color = "GRAY";
	vertices.at(0).distance = 0;
	queue<Vertex> q;
	
	q.push(vertices.at(0));
	Vertex currVert;
	
	while (!q.empty()) {
		currVert = q.front();
		q.pop();
		list<pair<int, int> >::iterator it = currVert.neighbors.begin();
		while (it != currVert.neighbors.end()) {
			if (vertices.at(it->first).color == "WHITE") {
				vertices.at(it->first).color = "GRAY";
				vertices.at(it->first).distance = currVert.distance + it->second;
				vertices.at(it->first).prev = &vertices.at(graph[currVert.label]);
				q.push(vertices.at(it->first));
			}
			
			++it;
		}
	}
}
