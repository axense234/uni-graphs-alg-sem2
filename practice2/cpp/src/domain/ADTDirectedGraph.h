#pragma once
#include <utility>
#include <map>
#include <vector>
#include <set>
#include <string>

typedef unsigned int Vertex;
typedef unsigned int EdgeCost;
typedef std::pair<Vertex, Vertex> Edge;

class ADTDirectedGraphIterator;

class ADTDirectedGraph
{

    friend class ADTDirectedGraphIterator;

private:
    std::map<Vertex, std::vector<Vertex>> outbound;
    std::map<Vertex, std::vector<Vertex>> inbound;
    std::map<Edge, EdgeCost> costs;

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
     * @attention Vertex must exist in the graph.
     * @param vertex The vertex in question.
     * @return unsigned int
     */
    unsigned int getInDegree(Vertex vertex) const;

    /**
     * @brief Get the out-degree of a vertex.
     *
     * @attention Vertex must exist in the graph.
     * @param vertex The vertex in question.
     * @return unsigned int
     */
    unsigned int getOutDegree(Vertex vertex) const;

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
    ADTDirectedGraphIterator parseVertices() const;

    /**
     * @brief Returns the iterator for the outbound neighbors of a given vertex from the beginning.
     *
     * @exception Throws an exception if given vertex is not in the graph.
     * @param vertex The vertex in question.
     * @return Outbound::const_iterator
     */
    std::vector<Vertex>::const_iterator parseOutboundOfGivenVertexBegin(Vertex vertex) const;

    /**
     * @brief Returns the iterator for the outbound neighbors of a given vertex from the end.
     *
     * @exception Throws an exception if given vertex is not in the graph.
     * @param vertex The vertex in question.
     * @return Outbound::const_iterator
     */
    std::vector<Vertex>::const_iterator parseOutboundOfGivenVertexEnd(Vertex vertex) const;

    /**
     * @brief Returns the iterator for the inbound neighbors of a given vertex from the end.
     *
     * @exception Throws an exception if given vertex is not in the graph.
     * @param vertex The vertex in question.
     * @return Inbound::const_iterator
     */
    std::vector<Vertex>::const_iterator parseInboundOfGivenVertexEnd(Vertex vertex) const;

    /**
     * @brief Returns the iterator for the inbound neighbors of a given vertex from the beginning.
     *
     * @exception Throws an exception if given vertex is not in the graph.
     * @param vertex The vertex in question.
     * @return Inbound::const_iterator
     */
    std::vector<Vertex>::const_iterator parseInboundOfGivenVertexBegin(Vertex vertex) const;

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
    static std::pair<std::set<Vertex>, std::map<Vertex, Vertex>> forwardBreadthFirstTraversal(ADTDirectedGraph graph, Vertex start);

    /**
     * @brief Given a directed graph and two vertices, finds a lowest length path between them, by using a forward breadth-first search from the starting vertex.
     *
     * @param graph The graph in question.
     * @param start The starting vertex.
     * @param end The end vertex.
     * @return std::vector<Vertex> -> path
     */
    static std::vector<Vertex> findLowestLengthPathBetweenTwoVertices(ADTDirectedGraph graph, Vertex start, Vertex end);

    /**
     * @brief Reads a graph from a specified text file.
     *
     * @param graph The graph where the data will be added.
     * @param filename The name of the file where we want to read from.
     * @return true If read was successfull.
     * @return false If read was not successful >:(.
     */
    static bool readGraph(ADTDirectedGraph &graph, const std::string &filename);

    /**
     * @brief Writes to a text file with a specified filename the graph.
     *
     *
     * @param graph The source graph.
     * @param filename The filename of the newly created file.
     * @return true If write was successful.
     * @return false If write was indeed not successful.
     */
    static bool writeGraph(const ADTDirectedGraph &graph, const std::string &filename);

    /**
     * @brief Generates a random graph with nbVertices number of vertices and nbEdges number of edges.
     * @brief Needs nbVertices to be at least 1.
     *
     * @param nbVertices Number of vertices.
     * @param nbEdges Number of edges.
     * @return ADTDirectedGraph
     */
    static ADTDirectedGraph generateRandomGraph(unsigned int nbVertices, unsigned int nbEdges);
};