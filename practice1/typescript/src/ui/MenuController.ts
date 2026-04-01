import { MenuUI } from "./MenuUI";
import { ADTDirectedGraph } from "../domain/ADTDirectedGraph";
import { Helpers } from "../helpers/Helpers";

export class MenuController {
  private ui: MenuUI;
  private graph: ADTDirectedGraph;

  /**
   * @brief Constructor.
   *
   * @param ui MenuUI dependency.
   * @param g Graph dependency.
   */
  constructor(ui: MenuUI, g: ADTDirectedGraph) {
    this.ui = ui;
    this.graph = g;
  }

  displayCurrentNbVertices(): void {
    console.log(`Number of Vertices: ${this.graph.nbVertices()}`);
  }

  displayCurrentNbEdges(): void {
    console.log(`Number of Edges: ${this.graph.nbEdges()}`);
  }

  async displayGraphVertices(): Promise<void> {
    if (this.graph.nbVertices() === 0) {
      console.log("No Vertices in Graph to display.");
      return;
    }

    console.log("Vertices: \n");

    const it = this.graph.parseVertices();

    it.first();
    while (it.valid()) {
      console.log(it.getCurrent());
      it.next();
    }

    console.log();
  }

  async displayGraphEdges(): Promise<void> {
    if (this.graph.nbEdges() === 0) {
      console.log("No Edges in Graph to display.");
      return;
    }

    console.log("Edges: \n");

    const startIt = this.graph.parseEdgesBegin();
    let result = startIt.next();

    while (!result.done) {
      const [edge, cost] = result.value;
      console.log(`${edge[0]} ${edge[1]} ${cost}`);
      result = startIt.next();
    }

    console.log();
  }

  async displayOutboundEdgesOfGivenVertex(): Promise<void> {
    const vertex = await this.ui.getUserVertex();

    console.log("Outbound Edges: \n");

    try {
      const startIt = this.graph.parseOutboundOfGivenVertexBegin(vertex);

      let result = startIt.next();
      while (!result.done) {
        console.log(result.value);
        result = startIt.next();
      }

      console.log();
    } catch (error) {
      console.log("Vertex doesn't exist in graph.");
    }
  }

  async displayInboundEdgesOfGivenVertex(): Promise<void> {
    const vertex = await this.ui.getUserVertex();

    console.log("Inbound Edges: \n");

    try {
      const startIt = this.graph.parseInboundOfGivenVertexBegin(vertex);
      let result = startIt.next();

      while (!result.done) {
        console.log(result.value);
        result = startIt.next();
      }

      console.log();
    } catch (error) {
      console.log("Vertex doesn't exist in graph.");
    }
  }

  async checkIfGivenEdgeIsGraphEdge(): Promise<void> {
    const edge = await this.ui.getUserEdge();

    if (this.graph.isEdge(edge[0], edge[1])) {
      console.log("Given Edge is IN the graph.");
    } else {
      console.log("Given Edge is NOT in the graph.");
    }

    console.log();
  }

  async displayInDegreeOfGivenVertex(): Promise<void> {
    const vertex = await this.ui.getUserVertex();

    try {
      const degree = this.graph.getInDegree(vertex);
      console.log(`In Degree of Given Vertex: ${degree}`);
    } catch (error) {
      console.log(`Vertex ${vertex} is not in the graph.`);
    }
  }

  async displayOutDegreeOfGivenVertex(): Promise<void> {
    const vertex = await this.ui.getUserVertex();

    try {
      const degree = this.graph.getOutDegree(vertex);
      console.log(`Out Degree of Given Vertex: ${degree}`);
    } catch (error) {
      console.log(`Vertex ${vertex} is not in the graph.`);
    }
  }

  async addGivenVertexToGraph(): Promise<void> {
    const vertex = await this.ui.getUserVertex();

    if (this.graph.addVertex(vertex)) {
      console.log("Successfully added Vertex");
    } else {
      console.log("FAILED to add Vertex");
    }
  }

  async removeGivenVertexFromGraph(): Promise<void> {
    const vertex = await this.ui.getUserVertex();

    if (this.graph.removeVertex(vertex)) {
      console.log("Successfully removed Vertex");
    } else {
      console.log("FAILED to remove Vertex");
    }
  }

  async addGivenEdgeToGraph(): Promise<void> {
    const edge = await this.ui.getUserEdge();
    const cost = await this.ui.getUserEdgeCost();

    if (this.graph.addEdge(edge, cost)) {
      console.log("Successfully added Edge");
    } else {
      console.log("FAILED to add Edge");
    }
  }

  async removeGivenEdgeFromGraph(): Promise<void> {
    const edge = await this.ui.getUserEdge();

    if (this.graph.removeEdge(edge)) {
      console.log("Successfully removed Edge");
    } else {
      console.log("FAILED to remove Edge");
    }
  }

  async generateRandomGraphOfGivenNbVerticesAndNbEdges(): Promise<void> {
    const nbVertices = await this.ui.getUserUnsignedInt("Number of Vertices: ");
    const nbEdges = await this.ui.getUserUnsignedInt("Number of Edges: ");

    console.log("Generating a Random Graph....bz....z......");

    try {
      const newGraph = Helpers.generateRandomGraph(nbVertices, nbEdges);
      Object.assign(this.graph, newGraph);
      console.log("Random graph generated successfully.");
    } catch (error) {
      console.log("Too many edges man.");
    }
  }

  async readGraphDataFromGivenFile(): Promise<void> {
    const filename = await this.ui.getUserFilename();

    const res = Helpers.readGraph(this.graph, filename);

    if (res) {
      console.log(`Reading from ${filename} was successful.`);
    } else {
      console.log(`Reading from ${filename} FAILED.`);
    }
  }

  async writeGraphDataToGivenFile(): Promise<void> {
    const filename = await this.ui.getUserFilename();

    const res = Helpers.writeGraph(this.graph, filename);

    if (res) {
      console.log(`Writing to ${filename} was successful.`);
    } else {
      console.log(`Writing to ${filename} FAILED.`);
    }
  }
}
