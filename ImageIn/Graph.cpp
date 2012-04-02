#include "Graph.h"

using namespace imagein;

void Graph::Vertex::addEdge(int neighbour, int capacity) {
	Edge* newEdge = new Edge(neighbour,capacity);
	if(_edges) {
		// If an edge (or a list of edges) already exist, we add the new edge at the beginning of the linked list
		newEdge->_next = _edges;
	}
	_edges = newEdge;
}

void Graph::addEdge(int i, int j, int capacity) {
	if(i>=_nbVertices || j>=_nbVertices) throw std::invalid_argument("i and j must be smaller than the number of vertices : "+_nbVertices);
	_listOfVertices[i]->addEdge(j,capacity);
}

int Graph::getCapacity(int i, int j) {
	if(i>=_nbVertices || j>=_nbVertices) throw std::invalid_argument("i and j must be smaller than the number of vertices : "+_nbVertices);
	Edge* currentEdge;
	for (currentEdge = _listOfVertices[i]->_edges; currentEdge; currentEdge = currentEdge->_next) {
		if (currentEdge->_neighbour == j) return currentEdge->_capacity;
	}
	return 0;
}