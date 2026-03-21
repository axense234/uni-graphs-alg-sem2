#pragma once
#include <utility>
#include <map>
#include <vector>

typedef unsigned int Vertex;
typedef unsigned int EdgeCost;

typedef std::pair<Vertex, Vertex> Edge;

typedef std::map<Vertex, std::vector<Vertex>> Outbound;
typedef std::map<Vertex, std::vector<Vertex>> Inbound;
typedef std::map<Edge, EdgeCost> EdgeCosts;

// forward declaration
class ADTDirectedGraphIterator;

class ADTDirectedGraph
{

    friend class ADTDirectedGraphIterator;

private:
    int maxCapacity;

    Outbound outbound;
    Inbound inbound;
    EdgeCosts costs;

public:
    /**
     * @brief Construct a new ADTDirectedGraph object.
     * @param maxCapacity Max number of vertices possible in graph.
     */
    ADTDirectedGraph(int maxCapacity);

    /**
     * @brief Handle deep copy of a new ADTDirectedGraph object.
     *
     * @param g Input graph.
     */
    ADTDirectedGraph(const ADTDirectedGraph &g);

    /**
     * @brief Destroy the ADTDirectedGraph object.
     *
     */
    ~ADTDirectedGraph();

    /**
     * @brief Returns the number of vertices.
     *
     * @return unsigned int
     */
    unsigned int nbVertices() const;

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
     * @brief todo
     *
     */
    void parseOutboundEdges() const;

    /**
     * @brief todo
     *
     */
    void parseInboundEdges() const;

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
};