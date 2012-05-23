#include "Graph.h"
#include <cstdlib>
#include <stdexcept>

using namespace imagein;

void Graph::Vertex::addEdge(int neighbour, int capacity) {
	Edge* newEdge = new Edge(neighbour,capacity);
	// If an edge (or a list of edges) already exist, we add the new edge at the beginning of the linked list
	if(_edges) newEdge->_next = _edges;
	_edges = newEdge;
}

bool Graph::Vertex::removeEdge(int neighbour) {
	Edge* currentEdge;
	Edge* previousEdge;
	for (currentEdge = _edges; currentEdge; currentEdge = currentEdge->_next) {
		if (currentEdge->_neighbour == neighbour) {
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

Graph::Graph(int nbVertices, bool directed) : _nbVertices(nbVertices), _directed(directed) {
	_listOfVertices = new Vertex*[nbVertices];
	int i;
	for(i=0;i<nbVertices;i++) {
		_listOfVertices[i] = new Vertex();
	}
}

void Graph::addEdge(int i, int j, int capacity) {
	if(i>=_nbVertices || j>=_nbVertices) throw std::invalid_argument("i and j must be less than the number of vertices : "+_nbVertices);
	if(i<0 || j<0) throw std::invalid_argument("i and j must be greater than or equal to 0");
	_listOfVertices[i]->addEdge(j,capacity);
}

bool Graph::removeEdge(int i, int j) {
	if(i>=_nbVertices || j>=_nbVertices) throw std::invalid_argument("i and j must be less than the number of vertices : "+_nbVertices);
	if(i<0 || j<0) throw std::invalid_argument("i and j must be greater than or equal to 0");
	if(_listOfVertices[i]->removeEdge(j)) return true;
	else if(!_directed) return _listOfVertices[j]->removeEdge(i);
	return false;
}

int Graph::getCapacity(int i, int j) {
	if(i>=_nbVertices || j>=_nbVertices) throw std::invalid_argument("i and j must be less than the number of vertices : "+_nbVertices);
	if(i<0 || j<0) throw std::invalid_argument("i and j must be greater than or equal to 0");
	Edge* currentEdge;
	for (currentEdge = _listOfVertices[i]->_edges; currentEdge; currentEdge = currentEdge->_next) {
		if (currentEdge->_neighbour == j) return currentEdge->_capacity;
	}
	if(!_directed) {
		for (currentEdge = _listOfVertices[j]->_edges; currentEdge; currentEdge = currentEdge->_next) {
			if (currentEdge->_neighbour == i) return currentEdge->_capacity;
		}
	}
	return 0;
}

bool Graph::edgeExists(int i, int j) {
	if(i>=_nbVertices || j>=_nbVertices) throw std::invalid_argument("i and j must be less than the number of vertices : "+_nbVertices);
	if(i<0 || j<0) throw std::invalid_argument("i and j must be greater than or equal to 0");
	Edge* currentEdge;
	for (currentEdge = _listOfVertices[i]->_edges; currentEdge; currentEdge = currentEdge->_next) {
		if (currentEdge->_neighbour == j) return true;
	}
	if(!_directed) {
		for (currentEdge = _listOfVertices[j]->_edges; currentEdge; currentEdge = currentEdge->_next) {
			if (currentEdge->_neighbour == i) return true;
		}
	}
	return false;
}
