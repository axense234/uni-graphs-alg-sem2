#include "Helpers.h"

#include <fstream>
#include <random>
#include <climits>
#include <exception>

Helpers::Helpers() {};

bool Helpers::readGraph(ADTDirectedGraph &graph, const std::string &filename)
{
    std::ifstream inputFile(filename);

    // forgot to reset the damn graph
    graph = ADTDirectedGraph{};

    if (!inputFile.is_open())
    {
        return false;
    }

    unsigned int nbVertices, nbEdges;
    inputFile >> nbVertices >> nbEdges;

    Vertex first, second;
    EdgeCost cost;

    for (unsigned int i = 0; i < nbEdges; i++)
    {
        inputFile >> first >> second >> cost;

        graph.addVertex(first);
        graph.addVertex(second);

        graph.addEdge({first, second}, cost);
    }

    return true;
}

bool Helpers::writeGraph(const ADTDirectedGraph &graph, const std::string &filename)
{
    std::ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        return false;
    }

    outputFile << graph.nbVertices() << ' ' << graph.nbEdges() << std::endl;

    EdgeCosts::const_iterator startIt = graph.parseEdgesBegin();
    EdgeCosts::const_iterator endIt = graph.parseEdgesEnd();

    while (startIt != endIt)
    {

        Edge currEdge = startIt->first;
        EdgeCost currCost = startIt->second;

        outputFile << currEdge.first << ' ' << currEdge.second << ' ' << currCost << std::endl;

        ++startIt;
    }

    return true;
}

ADTDirectedGraph Helpers::generateRandomGraph(unsigned int nbVertices, unsigned int nbEdges)
{

    // so if we have nbEdges > nbVertices * (nbVertices - 1) we have a problemo
    if (nbEdges > nbVertices * (nbVertices - 1))
    {
        throw std::exception();
    }

    ADTDirectedGraph graph = ADTDirectedGraph{};

    // way of generating numbers from 0 to the limit of unsigned int
    // rd is a seed gen, gen is a mersenne twister engine
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> randomUnsignedInt(0, UINT_MAX);
    std::uniform_int_distribution<unsigned int> randomVerticesIndex(0, nbVertices - 1);

    Vertices generatedVertices = Vertices{};

    // we generate nbVertices number of vertices
    for (unsigned int i = 0; i < nbVertices; ++i)
    {
        unsigned int vertex = Vertex{randomUnsignedInt(gen)};
        graph.addVertex(vertex);
        generatedVertices.push_back(vertex);
    }

    // we handle generating random edges
    unsigned int generatedEdges = 0;
    while (generatedEdges < nbEdges)
    {

        Vertex firstVertex = generatedVertices.at(randomVerticesIndex(gen));
        Vertex secondVertex = generatedVertices.at(randomVerticesIndex(gen));

        // if we got unlucky and we already have an edge we just skip
        if (graph.isEdge(firstVertex, secondVertex))
        {
            continue;
        }

        // we create an edge with unsigned int cost as well
        unsigned int randomCost = EdgeCost{randomUnsignedInt(gen)};
        Edge createdEdge = Edge{firstVertex, secondVertex};
        graph.addEdge(createdEdge, randomCost);

        generatedEdges++;
    }

    return graph;
}
