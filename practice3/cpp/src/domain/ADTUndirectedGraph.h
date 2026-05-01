#pragma once
#include <utility>
#include <map>
#include <vector>
#include <set>
#include <string>

typedef unsigned int Vertex;
typedef unsigned int EdgeCost;
typedef std::pair<Vertex, Vertex> Edge;

class ADTUndirectedGraphIterator;

class ADTUndirectedGraph
{

    friend class ADTUndirectedGraphIterator;

private:
    std::map<Vertex, std::vector<Vertex>> vertices;
    std::map<Edge, EdgeCost> costs;

public:
    /**
     * @brief Construct a new ADTUndirectedGraph object.
     */
    ADTUndirectedGraph();

    /**
     * @brief Returns the number of vertices in the graph.
     *
     * @return unsigned int
     */
    unsigned int nbVertices() const;

    /**
     * @brief Returns the number of edges in the graph.
     *
     * @return unsigned int
     */
    unsigned int nbEdges() const;

    /**
     * @brief Checks if an edge between 2 vertexes exist.
     *
     * @param first First vertex.
     * @param second Second vertex.
     * @return true There is an edge between the vertexes.
     * @return false There is no edge between the vertexes.
     */
    bool isEdge(Vertex first, Vertex second) const;

    /**
     * @brief Gets the degree of a vertex from the graph.
     *
     * @param vertex The vertex in question.
     * @return unsigned int
     */
    unsigned int getDegree(Vertex vertex) const;

    /**
     * @brief Adds an edge to the graph.
     *
     * @param edge Edge to be added.
     * @param cost Cost associated with the edge.
     * @return true If add was successfull.
     * @return false If add was indeed not successfull.
     */
    bool addEdge(Edge edge, EdgeCost cost);

    /**
     * @brief Removes an edge from the graph.
     *
     * @param edge
     * @return true If edge was removed successfully.
     * @return false If edge was not removed successfully :(.
     */
    bool removeEdge(Edge edge);

    /**
     * @brief Adds a vertex to the graph.
     *
     * @param vertex The vertex to be added.
     * @return true If adding the vertex was successfull.
     * @return false If adding the vertex was not successfull.
     */
    bool addVertex(Vertex vertex);
    /**
     * @brief Removes a vertex from the graph.
     *
     * @param vertex The vertex to be removed.
     * @return true If removing the vertex was successfull.
     * @return false If removing the vertex was not successfull.
     */
    bool removeVertex(Vertex vertex);

    /**
     * @brief Returns the iterator for the graph's vertices.
     *
     * @return ADTUndirectedGraphIterator
     */
    ADTUndirectedGraphIterator parseVertices() const;

    /**
     * @brief Returns the iterator for the neighbors of a given vertex from the beginning.
     *
     * @exception Throws an exception if given vertex is not in the graph.
     * @param vertex The vertex in question.
     * @return std::vector<Vertex>::const_iterator the iterator
     */
    std::vector<Vertex>::const_iterator parseNeighOfGivenVertexBegin(Vertex vertex) const;

    /**
     * @brief Returns the iterator for the neighbors of a given vertex from the end.
     *
     * @exception Throws an exception if given vertex is not in the graph.
     * @param vertex The vertex in question.
     * @return std::vector<Vertex>::const_iterator iterator
     */
    std::vector<Vertex>::const_iterator parseNeighOfGivenVertexEnd(Vertex vertex) const;

    /**
     * @brief Returns the iterator for the edges (with costs) from the beginning of the iteratable.
     *
     * @return EdgeCosts::const_iterator
     */
    std::map<Edge, EdgeCost>::const_iterator parseEdgesBegin() const;
    /**
     * @brief Returns the iterator for the edges (with costs) from the end of the iteratable.
     *
     * @return EdgeCosts::const_iterator
     */
    std::map<Edge, EdgeCost>::const_iterator parseEdgesEnd() const;

    /**
     * @brief The algorith below visits all the vertices that are accessible from the start vertex. They are visited in the order of increasing distances from the starting vertex. A previous vector or map is computed, allowing us to compute the minimum length path from the starting vertex to any choosen accessible vertex.
     *
     * @param graph The graph in question.
     * @param start The starting vertex.
     * @return std::pair<std::set<Vertex>, std::map<Vertex, Vertex>> -> accessible vertices from s and the prev map
     */
    static std::pair<std::set<Vertex>, std::map<Vertex, Vertex>> forwardBreadthFirstTraversal(ADTUndirectedGraph graph, Vertex start);

    /**
     * @brief Finds the connected components of an undirected graph using a breadth-first traversal of the graph.
     *
     * @param graph The undirected graph in question.
     */
    static std::vector<std::set<Vertex>> findConnectedComponentsOfUndirectedGraph(ADTUndirectedGraph &graph);
};