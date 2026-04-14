import {
  ADTDirectedGraph,
  Vertex,
  Edge,
  EdgeCost,
} from "../domain/ADTDirectedGraph";
import * as readline from "readline";
import { MenuController } from "./MenuController";

export class MenuUI {
  private graph: ADTDirectedGraph;
  private userMenuOption: number;

  /**
   * @brief Construct a new Menu UI object
   *
   * @param g Graph dependency.
   */
  constructor(g: ADTDirectedGraph) {
    this.graph = g;
    this.userMenuOption = 0;
  }

  /**
   * @brief Displays the available menu options.
   *
   */
  displayMenuOptions(): void {
    console.log("\n---------MENU OPTIONS---------");
    console.log("\n---------GRAPH PROPERTIES---------");
    console.log("1: Get the current number of Vertices of the Graph.");
    console.log("2: Get the current number of Edges of the Graph.");
    console.log("3: Display the Vertices of the Graph.");
    console.log("4: Display the Edges of the Graph (with cost included).");
    console.log("5: Display the Outbound Edges of a given Vertex.");
    console.log("6: Display the Inbound Edges of a given Vertex.");
    console.log("7: Check if a given Edge is an Edge of the Graph.");
    console.log("8: Get the in-degree of a given Vertex.");
    console.log("9: Get the out-degree of a given Vertex.");
    console.log("\n---------GRAPH MUTATION---------");
    console.log("10: Add a given Vertex to the Graph.");
    console.log("11: Remove a given Vertex from the Graph.");
    console.log("12: Add a given Edge to the Graph.");
    console.log("13: Remove a given Edge from the Graph.");
    console.log("\n---------UTILITIES---------");
    console.log(
      "14: Generate a random Graph with given nb of vertices and given nb of edges. This newly generated Graph replaces the current Graph.",
    );
    console.log(
      "15: Read from a given file graph data. This updates the current Graph.",
    );
    console.log("16: Write to a given filename graph data.");
    console.log("17: Exit program.");
    console.log();
  }

  /**
   * @brief Gets an unsigned int from the console.
   *
   * @param label Display label.
   * @return Promise<number>
   */
  async getUserUnsignedInt(label: string): Promise<number> {
    const rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
    });

    while (true) {
      const answer = await this.question(rl, label);
      const catcher = parseInt(answer);

      if (!isNaN(catcher) && catcher >= 0 && Number.isSafeInteger(catcher)) {
        rl.close();
        console.log();
        return catcher;
      }
      console.log("Invalid input, expected an unsigned int.");
    }
  }

  /**
   * @brief Gets a Vertex from the console.
   *
   * @return Promise<Vertex>
   */
  async getUserVertex(): Promise<Vertex> {
    const rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
    });

    while (true) {
      const answer = await this.question(rl, "Vertex (unsigned int): ");
      const catcher = parseInt(answer);

      if (!isNaN(catcher) && catcher >= 0 && Number.isSafeInteger(catcher)) {
        rl.close();
        console.log();
        return catcher;
      }
      console.log("Invalid input, expected a Vertex (unsigned int).");
    }
  }

  /**
   * @brief Gets an Edge from the console.
   *
   * @return Promise<Edge>
   */
  async getUserEdge(): Promise<Edge> {
    const rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
    });

    while (true) {
      const answer = await this.question(
        rl,
        "Edge (unsigned int, unsigned int): ",
      );
      const parts = answer.trim().split(/\s+/);

      if (parts.length >= 2) {
        const firstCatcher = parseInt(parts[0]);
        const secondCatcher = parseInt(parts[1]);

        if (
          !isNaN(firstCatcher) &&
          !isNaN(secondCatcher) &&
          firstCatcher >= 0 &&
          secondCatcher >= 0 &&
          Number.isSafeInteger(firstCatcher) &&
          Number.isSafeInteger(secondCatcher)
        ) {
          rl.close();
          console.log();
          return [firstCatcher, secondCatcher];
        }
      }
      console.log("Invalid input, expected an Edge (ex: 2 5).");
    }
  }

  /**
   * @brief Get an Edge Cost from the console.
   *
   * @return Promise<EdgeCost>
   */
  async getUserEdgeCost(): Promise<EdgeCost> {
    const rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
    });

    while (true) {
      const answer = await this.question(rl, "Cost (unsigned int): ");
      const catcher = parseInt(answer);

      if (!isNaN(catcher) && catcher >= 0 && Number.isSafeInteger(catcher)) {
        rl.close();
        console.log();
        return catcher;
      }
      console.log("Invalid input, expected an EdgeCost (unsigned int).");
    }
  }

  /**
   * @brief Gets a filename from the console.
   *
   * @return Promise<string>
   */
  async getUserFilename(): Promise<string> {
    const rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
    });

    while (true) {
      const answer = await this.question(rl, "Filename: ");
      if (answer.trim().length > 0) {
        rl.close();
        console.log();
        return answer.trim();
      }
      console.log("Invalid input, expected a Filename (string).");
    }
  }

  /**
   * @brief Starts the menu application.
   *
   */
  async start(): Promise<void> {
    const menuController = this.controller();

    while (true) {
      this.displayMenuOptions();
      this.userMenuOption = await this.getUserUnsignedInt("Menu Option: ");

      switch (this.userMenuOption) {
        case 1:
          menuController.displayCurrentNbVertices();
          break;
        case 2:
          menuController.displayCurrentNbEdges();
          break;
        case 3:
          await menuController.displayGraphVertices();
          break;
        case 4:
          await menuController.displayGraphEdges();
          break;
        case 5:
          await menuController.displayOutboundEdgesOfGivenVertex();
          break;
        case 6:
          await menuController.displayInboundEdgesOfGivenVertex();
          break;
        case 7:
          await menuController.checkIfGivenEdgeIsGraphEdge();
          break;
        case 8:
          await menuController.displayInDegreeOfGivenVertex();
          break;
        case 9:
          await menuController.displayOutDegreeOfGivenVertex();
          break;
        case 10:
          await menuController.addGivenVertexToGraph();
          break;
        case 11:
          await menuController.removeGivenVertexFromGraph();
          break;
        case 12:
          await menuController.addGivenEdgeToGraph();
          break;
        case 13:
          await menuController.removeGivenEdgeFromGraph();
          break;
        case 14:
          await menuController.generateRandomGraphOfGivenNbVerticesAndNbEdges();
          break;
        case 15:
          await menuController.readGraphDataFromGivenFile();
          break;
        case 16:
          await menuController.writeGraphDataToGivenFile();
          break;
        case 17:
          console.log("Exiting...");
          return;
        default:
          break;
      }
    }
  }

  /**
   * @brief Returns a newly created controller instance.
   *
   * @return MenuController
   */
  controller(): MenuController {
    return new MenuController(this, this.graph);
  }

  /**
   * @brief Helper function to prompt user input
   * @private
   */
  private question(rl: readline.Interface, prompt: string): Promise<string> {
    return new Promise((resolve) => {
      rl.question(prompt, (answer) => {
        resolve(answer);
      });
    });
  }
}
