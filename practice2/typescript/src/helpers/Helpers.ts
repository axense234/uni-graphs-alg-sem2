import { ADTDirectedGraph, Vertex, Edge } from "../domain/ADTDirectedGraph";
import * as fs from "fs";
import { randomInt } from "crypto";

export class Helpers {
  /**
   * @brief Construct a new Helpers object
   */
  constructor() {}

  /**
   * @brief Reads a graph from a specified text file.
   *
   * @param graph The graph where the data will be added.
   * @param filename The name of the file where we want to read from.
   * @return true If read was successful.
   * @return false If read was not successful.
   */
  static readGraph(graph: ADTDirectedGraph, filename: string): boolean {
    try {
      const content = fs.readFileSync(filename, "utf-8");
      const lines = content.trim().split("\n");

      if (lines.length === 0) {
        return false;
      }

      const [nbVerticesStr, nbEdgesStr] = lines[0].trim().split(/\s+/);
      const nbVertices = parseInt(nbVerticesStr);
      const nbEdges = parseInt(nbEdgesStr);

      let lineIndex = 1;
      for (let i = 0; i < nbEdges; i++) {
        if (lineIndex >= lines.length) {
          return false;
        }

        const [firstStr, secondStr, costStr] = lines[lineIndex]
          .trim()
          .split(/\s+/);
        const first = parseInt(firstStr);
        const second = parseInt(secondStr);
        const cost = parseInt(costStr);

        graph.addVertex(first);
        graph.addVertex(second);
        graph.addEdge([first, second], cost);

        lineIndex++;
      }

      return true;
    } catch (error) {
      return false;
    }
  }

  /**
   * @brief Writes to a text file with a specified filename the graph.
   *
   * @param graph The source graph.
   * @param filename The filename of the newly created file.
   * @return true If write was successful.
   * @return false If write was not successful.
   */
  static writeGraph(graph: ADTDirectedGraph, filename: string): boolean {
    try {
      let content = `${graph.nbVertices()} ${graph.nbEdges()}\n`;

      const edgesIterator = graph.parseEdgesBegin();
      let result = edgesIterator.next();

      while (!result.done) {
        const [edge, cost] = result.value;
        content += `${edge[0]} ${edge[1]} ${cost}\n`;
        result = edgesIterator.next();
      }

      fs.writeFileSync(filename, content, "utf-8");
      return true;
    } catch (error) {
      return false;
    }
  }

  /**
   * @brief Generates a random graph with nbVertices number of vertices and nbEdges number of edges.
   * @brief Needs nbVertices to be at least 1.
   *
   * @param nbVertices Number of vertices.
   * @param nbEdges Number of edges.
   * @return ADTDirectedGraph
   * @throws Error if nbEdges exceeds maximum possible edges
   */
  static generateRandomGraph(
    nbVertices: number,
    nbEdges: number,
  ): ADTDirectedGraph {
    // check if nbEdges exceeds maximum possible edges
    if (nbEdges > nbVertices * (nbVertices - 1)) {
      throw new Error(`too many edges man`);
    }

    const graph = new ADTDirectedGraph();

    // generate vertices with random values
    const generatedVertices: Vertex[] = [];

    for (let i = 0; i < nbVertices; i++) {
      const vertex = this.getRandomUnsignedInt();
      graph.addVertex(vertex);
      generatedVertices.push(vertex);
    }

    //generate random edges
    let generatedEdges = 0;
    while (generatedEdges < nbEdges) {
      const randomIndex1 = this.getRandomInt(0, nbVertices - 1);
      const randomIndex2 = this.getRandomInt(0, nbVertices - 1);

      const firstVertex = generatedVertices[randomIndex1];
      const secondVertex = generatedVertices[randomIndex2];

      // skip if edge already exists
      if (graph.isEdge(firstVertex, secondVertex)) {
        continue;
      }

      const randomCost = this.getRandomUnsignedInt();
      const createdEdge: Edge = [firstVertex, secondVertex];
      graph.addEdge(createdEdge, randomCost);

      generatedEdges++;
    }

    return graph;
  }

  /**
   * @brief Helper function to generate a random unsigned integer (0 to 2^32-1)
   * @private
   */
  private static getRandomUnsignedInt(): number {
    // randomInt is inclusive of min, exclusive of max
    // For 0 to 4294967295 (UINT_MAX)
    return randomInt(0, 4294967296);
  }

  /**
   * @brief Helper function to generate a random integer in range [min, max]
   * @private
   */
  private static getRandomInt(min: number, max: number): number {
    return randomInt(min, max + 1);
  }
}
