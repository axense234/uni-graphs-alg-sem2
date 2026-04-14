#pragma once

#include <string>
#include "../domain/ADTDirectedGraph.h"

class Helpers
{

private:
public:
    /**
     * @brief Construct a new Helpers object
     */
    Helpers();
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
     * @brief Generates a random graph with nbVertices number of vertices and nbEdges number of edges. \n
     * @brief Needs nbVertices to be at least 1.
     *
     * @param nbVertices Number of vertices.
     * @param nbEdges Number of edges.
     * @return ADTDirectedGraph
     */
    static ADTDirectedGraph generateRandomGraph(unsigned int nbVertices, unsigned int nbEdges);
};