#include "Graph.h"

using namespace imagein;

void Graph::Vertex::addEdge(int neighbour, int capacity) {
	Edge* newEdge = new Edge(neighbour,capacity);
	// If an edge (or a list of edges) already exist, we add the new edge at the beginning of the linked list
	if(_edges) newEdge->_next = _edges;
	_edges = newEdge;
}

void Graph::Vertex::removeEdge(int neighbour) {
	Edge* currentEdge;
	Edge* previousEdge;
	for (currentEdge = _edges; currentEdge; currentEdge = currentEdge->_next) {
		if (currentEdge->_neighbour == j) {
			if(previousEdge) previousEdge->_next = currentEdge->_next;
			else _edges = currentEdge->_next;
			currentEdge->_next = NULL;
			delete currentEdge;
			return true;
		}
		previousEdge = currentEdge;
	}
	return false;
}

void Graph::addEdge(int i, int j, int capacity) {
	if(i>=_nbVertices || j>=_nbVertices) throw std::invalid_argument("i and j must be smaller than the number of vertices : "+_nbVertices);
	_listOfVertices[i]->addEdge(j,capacity);
}

bool Graph::removeEdge(int i, int j, bool directed) {
	if(i>=_nbVertices || j>=_nbVertices) throw std::invalid_argument("i and j must be smaller than the number of vertices : "+_nbVertices);
	if(_listOfVertices[i]->removeEdge(j)) return true;
	else if(!directed) return _listOfVertices[j]->removeEdge(i);
	return false;
}

int Graph::getCapacity(int i, int j, bool directed) {
	if(i>=_nbVertices || j>=_nbVertices) throw std::invalid_argument("i and j must be smaller than the number of vertices : "+_nbVertices);
	Edge* currentEdge;
	for (currentEdge = _listOfVertices[i]->_edges; currentEdge; currentEdge = currentEdge->_next) {
		if (currentEdge->_neighbour == j) return currentEdge->_capacity;
	}
	if(!directed) {
		for (currentEdge = _listOfVertices[j]->_edges; currentEdge; currentEdge = currentEdge->_next) {
			if (currentEdge->_neighbour == i) return currentEdge->_capacity;
		}
	}
	return 0;
}