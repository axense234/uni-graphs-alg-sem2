export type Vertex = number;
export type EdgeCost = number;
export type Edge = [Vertex, Vertex];

export type Vertices = Vertex[];
export type Outbound = Map<Vertex, Vertices>;
export type Inbound = Map<Vertex, Vertices>;
export type EdgeCosts = Map<string, EdgeCost>;

export type OutboundIterator = Iterator<Vertex>;
export type EdgesIterator = Iterator<[Edge, EdgeCost]>;
export type VerticesIterator = Iterator<Vertex>;

import { ADTDirectedGraphIterator } from "./ADTDirectedGraphIterator";

export class ADTDirectedGraph {
  private outbound: Outbound;
  private inbound: Inbound;
  private costs: EdgeCosts;

  private edgeToKey(edge: Edge): string {
    return `${edge[0]},${edge[1]}`;
  }

  private keyToEdge(key: string): Edge {
    const parts = key.split(",").map(Number);
    return [parts[0], parts[1]];
  }

  /**
   * @brief Gets the keys of the outbound map. This should only be used by the iterator.
   *
   * @returns MapIterator<Vertex>
   */
  public getOutboundKeys(): IterableIterator<Vertex> {
    return this.outbound.keys();
  }

  /**
   * @brief Construct a new ADTDirectedGraph object.
   */
  constructor() {
    this.outbound = new Map<Vertex, Vertices>();
    this.inbound = new Map<Vertex, Vertices>();
    this.costs = new Map<string, EdgeCost>();
  }

  /**
   * @brief Returns the number of vertices in the graph.
   *
   * @return number
   */
  nbVertices(): number {
    return this.outbound.size;
  }

  /**
   * @brief Returns the number of edges in the graph.
   *
   * @return number
   */
  nbEdges(): number {
    return this.costs.size;
  }

  /**
   * @brief Checks if an edge between 2 vertexes exist.
   *
   * @param first First vertex.
   * @param second Second vertex.
   * @return true There is an edge between the vertexes.
   * @return false There is no edge between the vertexes.
   */
  isEdge(first: Vertex, second: Vertex): boolean {
    if (!this.outbound.has(first) || !this.inbound.has(second)) {
      return false;
    }

    const outboundNeigh = this.outbound.get(first)!;
    return outboundNeigh.includes(second);
  }

  /**
   * @brief Get the in-degree of a vertex.
   *
   * @param vertex The vertex in question.
   * @return number
   */
  getInDegree(vertex: Vertex): number {
    return this.inbound.get(vertex)?.length ?? 0;
  }

  /**
   * @brief Get the out-degree of a vertex.
   *
   * @param vertex The vertex in question.
   * @return number
   */
  getOutDegree(vertex: Vertex): number {
    return this.outbound.get(vertex)?.length ?? 0;
  }

  /**
   * @brief Adds an edge to the graph.
   *
   * @param edge Edge to be added.
   * @param cost Cost associated with the edge.
   * @return true If add was successful.
   * @return false If add was not successful.
   */
  addEdge(edge: Edge, cost: EdgeCost): boolean {
    // check if edge vertices exist in the graph
    if (!this.outbound.has(edge[0]) || !this.outbound.has(edge[1])) {
      return false;
    }

    const edgeKey = this.edgeToKey(edge);

    // check if edge is already in the graph
    if (this.costs.has(edgeKey)) {
      return false;
    }

    // handle outbound
    this.outbound.get(edge[0])!.push(edge[1]);
    // handle inbound
    this.inbound.get(edge[1])!.push(edge[0]);
    // handle the cost map
    this.costs.set(edgeKey, cost);

    return true;
  }

  /**
   * @brief Removes an edge from the graph.
   *
   * @param edge The edge to be removed.
   * @return true If edge was removed successfully.
   * @return false If edge was not removed successfully.
   */
  removeEdge(edge: Edge): boolean {
    const edgeKey = this.edgeToKey(edge);

    // check if edge exists in the graph
    if (!this.costs.has(edgeKey)) {
      return false;
    }

    // handle outbound
    const outboundNeigh = this.outbound.get(edge[0])!;
    const outIndex = outboundNeigh.indexOf(edge[1]);

    if (outIndex !== -1) {
      outboundNeigh.splice(outIndex, 1);
    }

    // handle inbound
    const inboundNeigh = this.inbound.get(edge[1])!;
    const inIndex = inboundNeigh.indexOf(edge[0]);

    if (inIndex !== -1) {
      inboundNeigh.splice(inIndex, 1);
    }

    // handle removing the edge from the costs
    this.costs.delete(edgeKey);

    return true;
  }

  /**
   * @brief Adds a vertex to the graph.
   *
   * @param vertex The vertex to be added.
   * @return true If adding the vertex was successful.
   * @return false If adding the vertex was not successful.
   */
  addVertex(vertex: Vertex): boolean {
    // check if vertex is in graph already
    if (this.outbound.has(vertex)) {
      return false;
    }

    // handle outbound
    this.outbound.set(vertex, []);
    // handle inbound
    this.inbound.set(vertex, []);

    return true;
  }

  /**
   * @brief Removes a vertex from the graph.
   *
   * @param vertex The vertex to be removed.
   * @return true If removing the vertex was successful.
   * @return false If removing the vertex was not successful.
   */
  removeVertex(vertex: Vertex): boolean {
    // check if vertex is in the graph
    if (!this.outbound.has(vertex)) {
      return false;
    }

    // handle inbound first
    const outboundNeigh = this.outbound.get(vertex)!;
    for (const currOutVertex of outboundNeigh) {
      const currInboundNeigh = this.inbound.get(currOutVertex)!;
      const index = currInboundNeigh.indexOf(vertex);
      if (index !== -1) {
        currInboundNeigh.splice(index, 1);
      }
    }

    // delete the key from outbound
    this.outbound.delete(vertex);

    // handle outbound
    const inboundNeigh = this.inbound.get(vertex)!;
    for (const currInVertex of inboundNeigh) {
      const currOutboundNeigh = this.outbound.get(currInVertex)!;
      const index = currOutboundNeigh.indexOf(vertex);
      if (index !== -1) {
        currOutboundNeigh.splice(index, 1);
      }
    }

    // delete the key from inbound
    this.inbound.delete(vertex);

    // handle costs - remove alll
    const keysToDelete: string[] = [];
    for (const [edgeKey, _] of this.costs) {
      const edge = this.keyToEdge(edgeKey);
      if (edge[0] === vertex || edge[1] === vertex) {
        keysToDelete.push(edgeKey);
      }
    }
    for (const key of keysToDelete) {
      this.costs.delete(key);
    }

    return true;
  }

  /**
   * @brief Returns the iterator for the graph's vertices.
   *
   * @return ADTDirectedGraphIterator
   */
  parseVertices(): ADTDirectedGraphIterator {
    return new ADTDirectedGraphIterator(this);
  }

  /**
   * @brief Returns the iterator for the outbound neighbors of a given vertex from the beginning.
   *
   * @throws Throws an error if given vertex is not in the graph.
   * @param vertex The vertex in question.
   * @return VerticesIterator
   */
  parseOutboundOfGivenVertexBegin(vertex: Vertex): VerticesIterator {
    if (!this.outbound.has(vertex)) {
      throw new Error("Vertex not found in graph");
    }

    const vertices = this.outbound.get(vertex)!;
    return vertices[Symbol.iterator]();
  }

  /**
   * @brief Returns the iterator for the outbound neighbors of a given vertex from the end.
   *
   * @throws Throws an error if given vertex is not in the graph.
   * @param vertex The vertex in question.
   * @return VerticesIterator
   */
  parseOutboundOfGivenVertexEnd(vertex: Vertex): VerticesIterator {
    if (!this.outbound.has(vertex)) {
      throw new Error("Vertex not found in graph");
    }

    const exhaustedIterator: VerticesIterator = {
      next(): IteratorResult<Vertex> {
        return { done: true, value: undefined };
      },
    };
    return exhaustedIterator;
  }

  /**
   * @brief Returns the iterator for the inbound neighbors of a given vertex from the beginning.
   *
   * @throws Throws an error if given vertex is not in the graph.
   * @param vertex The vertex in question.
   * @return VerticesIterator
   */
  parseInboundOfGivenVertexBegin(vertex: Vertex): VerticesIterator {
    if (!this.inbound.has(vertex)) {
      throw new Error("Vertex not found in graph");
    }

    const vertices = this.inbound.get(vertex)!;
    return vertices[Symbol.iterator]();
  }

  /**
   * @brief Returns the iterator for the inbound neighbors of a given vertex from the end.
   *
   * @throws Throws an error if given vertex is not in the graph.
   * @param vertex The vertex in question.
   * @return VerticesIterator
   */
  parseInboundOfGivenVertexEnd(vertex: Vertex): VerticesIterator {
    if (!this.inbound.has(vertex)) {
      throw new Error("Vertex not found in graph");
    }

    const exhaustedIterator: VerticesIterator = {
      next(): IteratorResult<Vertex> {
        return { done: true, value: undefined };
      },
    };
    return exhaustedIterator;
  }

  /**
   * @brief Returns the iterator for the edges (with costs) from the beginning.
   *
   * @return EdgesIterator
   */
  parseEdgesBegin(): EdgesIterator {
    const entries = Array.from(this.costs.entries());
    let index = 0;

    const graphSelf = this;

    return {
      next(): IteratorResult<[Edge, EdgeCost]> {
        if (index < entries.length) {
          const [key, cost] = entries[index++];
          const edge = graphSelf.keyToEdge(key);
          return { done: false, value: [edge, cost] };
        }
        return { done: true, value: undefined };
      },
    };
  }

  /**
   * @brief Returns the iterator for the edges (with costs) from the end.
   *
   * @return EdgesIterator
   */
  parseEdgesEnd(): EdgesIterator {
    return {
      next(): IteratorResult<[Edge, EdgeCost]> {
        return { done: true, value: undefined };
      },
    };
  }
}
