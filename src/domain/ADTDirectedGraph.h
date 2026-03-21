#pragma once
#include <utility>
#include <map>
#include <vector>

typedef unsigned int Vertex;
typedef unsigned int EdgeCost;

typedef std::pair<Vertex, Vertex> Edge;

typedef std::vector<Vertex> Vertices;

typedef std::map<Vertex, Vertices> Outbound;
typedef std::map<Vertex, Vertices> Inbound;
typedef std::map<Edge, EdgeCost> EdgeCosts;

// forward declaration
class ADTDirectedGraphIterator;

class ADTDirectedGraph
{

    friend class ADTDirectedGraphIterator;

private:
    Outbound outbound;
    Inbound inbound;
    EdgeCosts costs;

public:
    /**
     * @brief Construct a new ADTDirectedGraph object.
     */
    ADTDirectedGraph();

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
     * @brief Parses through the vertices of the graph.
     *
     * @param display Display to stdin or not.
     */
    void parseVertices(bool display) const;

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
     * @brief Get the in-degree of a vertex.
     *
     * @param vertex The vertex in question.
     * @return unsigned int
     */
    unsigned int getInDegree(Vertex vertex) const;

    /**
     * @brief Get the out-degree of a vertex.
     *
     * @param vertex The vertex in question.
     * @return unsigned int
     */
    unsigned int getOutDegree(Vertex vertex) const;

    /**
     * @brief Parses through the outbound edges of a specified vertex.
     * @param display Display to stdin or not.
     * @param vertex The vertex in question.
     *
     */
    void parseOutboundEdges(Vertex vertex, bool display) const;

    /**
     * @brief Parses through the inbound edges of a specified vertex.
     * @param display Display to stdin or not.
     * @param vertex The vertex in question.
     *
     */
    void parseInboundEdges(Vertex vertex, bool display) const;

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
     * @return ADTDirectedGraphIterator
     */
    ADTDirectedGraphIterator verticesIterator() const;

    /**
     * @brief Returns the iterator for the outbound neighbors of a given vertex.
     *
     * @exception Throws an exception if given vertex is not in the graph.
     * @param vertex The vertex in question.
     * @return Outbound::const_iterator
     */
    Vertices::const_iterator outboundIterator(Vertex vertex) const;

    /**
     * @brief Returns the iterator for the inbound neighbors of a given vertex.
     *
     * @exception Throws an exception if given vertex is not in the graph.
     * @param vertex The vertex in question.
     * @return Inbound::const_iterator
     */
    Vertices::const_iterator inboundIterator(Vertex vertex) const;

    /**
     * @brief Returns the iterator for the edges (with costs) from the beginning of the iteratable.
     *
     * @return EdgeCosts::const_iterator
     */
    EdgeCosts::const_iterator edgesBeginIterator() const;
    /**
     * @brief Returns the iterator for the edges (with costs) from the end of the iteratable.
     *
     * @return EdgeCosts::const_iterator
     */
    EdgeCosts::const_iterator edgesEndIterator() const;
};