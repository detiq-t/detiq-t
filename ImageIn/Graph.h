#ifndef GRAPH_H
#define GRAPH_H

namespace imagein
{
    /*!
     * \brief Implementation of a graph with using linked lists of the edges between each vertex.
     *
     * An implementation of a graph with an adjacency matrix would have needed a large amount of memory 
	 * in order to represent a graph applied to an image in which each vertex is a pixel and its edges 
	 * link to the pixel's neighbours. A 100x100px image would have required 10000 vertices, which means a 
	 * 10000*10000 matrix for the edges, it is far too big when there are actually just a few edges for each vertex.
	 * That's why here the graph is implemented with a linked list of the edges for each vertex. 
	 * As a result, the time needed to find an edge capacity is a little higher than with an adjacency 
	 * matrix (but not much since there are just a few edges per vertex), but the saving in memory is very significant.
     */
    class Graph
    {
		private:
			/*!
			 * \brief Inner class representing an edge in the graph.
			 */
			class Edge {
				int _neighbour; //!< Vertex in the graph to which the edge is linked
				int _capacity; //!< Capacity of the edge
				Edge* _next; //!< Next edge of the vertex in the linked list
				
				/*!
				 * \brief Constructs an Edge.
				 *
				 * \param neighbour Vertex in the graph to which the edge is linked
				 * \param capacity Capacity of the edge
				 */
				inline Edge(int neighbour, int capacity=0) : _neighbour(neighbour), _capacity(capacity) {};
				/*!
				 * \brief Classical destructor for Edge.
				 */
				inline virtual ~Edge() { delete _next; };
			}
			
			/*!
			 * \brief Inner class representing a vertex in the graph.
			 */
			class Vertex {
				Edge* _edges; //!< Linked list of all the edges of the vertex
				
				/*!
				 * \brief Constructs a Vertex.
				 */
				inline Vertex() {};
				/*!
				 * \brief Classical destructor for Vertex.
				 */
				inline virtual ~Vertex() { delete _edges; };
				/*!
				 * \brief Add an edge to the vertex
				 *
				 * \param neighbour Vertex in the graph to which the edge is linked
				 * \param capacity Capacity of the edge
				 */
				void addEdge(int neighbour, int capacity=0);
			}
			
			int _nbVertices; //!< Number of vertices in the graph
			Vertex* _listOfVertices; //!< List of all the vertices of the graph
			
        public:
			/*!
			 * \brief Constructs an Graph.
			 *
			 * \param nbVertices Number of vertices in the graph
			 */
			inline Graph(int nbVertices) : _nbVertices(nbVertices) { _listOfVertices = new Vertex[nbVertices]; };
			/*!
			 * \brief Classical destructor for Graph.
			 */
			inline virtual ~Graph() { delete[] _listOfVertices; };
			
			/*!
             * \brief Add an edge between the vertices i and j.
			 *
             * \param i Head of the edge
			 * \param j Tail of the edge
			 * \param capacity Capacity of the edge
             * \throw std::invalid_argument if i or j is higher than the number of vertices in the graph
             */
			void addEdge(int i, int j, int capacity=0);
			
			/*!
             * \brief Return the capacity of the edge between the vertices i and j.
			 *
             * \param i Head of the edge
			 * \param j Tail of the edge
             * \throw std::invalid_argument if i or j is higher than the number of vertices in the graph
			 * \return The capacity of the edge, 0 if no edge between the vertices i and j was found
             */
			int getCapacity(int i, int j);
    };
}

#endif // GRAPH_H
