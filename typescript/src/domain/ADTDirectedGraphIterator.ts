import { ADTDirectedGraph, Vertex } from "./ADTDirectedGraph";

export class ADTDirectedGraphIterator {
  private graph: ADTDirectedGraph;
  private vertices: Vertex[];
  private currentIndex: number;

  /**
   * @brief Construct a new ADTDirectedGraphIterator object.
   * @param graph The graph to iterate over
   * @throws Throws an error if the graph has no vertices
   */
  constructor(graph: ADTDirectedGraph) {
    this.graph = graph;

    if (this.graph.nbVertices() === 0) {
      throw new Error("Cannot create iterator on empty graph");
    }

    this.vertices = Array.from(this.graph.getOutboundKeys());
    this.currentIndex = 0;
  }

  /**
   * @brief Resets the iterator to the first vertex.
   * @throws Throws an error if the graph has no vertices
   */
  first(): void {
    if (this.graph.nbVertices() === 0) {
      throw new Error("Graph has no vertices");
    }

    this.currentIndex = 0;
  }

  /**
   * @brief Advances the iterator to the next vertex.
   * @throws Throws an error if the iterator is not valid
   */
  next(): void {
    if (!this.valid()) {
      throw new Error("Iterator is not valid");
    }

    this.currentIndex++;
  }

  /**
   * @brief Returns the current vertex.
   * @throws Throws an error if the iterator is not valid
   * @return Vertex The current vertex
   */
  getCurrent(): Vertex {
    if (!this.valid()) {
      throw new Error("Iterator is not valid");
    }

    return this.vertices[this.currentIndex];
  }

  /**
   * @brief Checks if the iterator points to a valid vertex.
   * @return boolean True if the iterator is valid, false otherwise
   */
  valid(): boolean {
    return this.currentIndex >= 0 && this.currentIndex < this.vertices.length;
  }
}
