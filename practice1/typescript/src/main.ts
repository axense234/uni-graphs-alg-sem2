import { ADTDirectedGraph } from "./domain/ADTDirectedGraph";
import { MenuUI } from "./ui/MenuUI";

async function main(): Promise<void> {
  const graph = new ADTDirectedGraph();
  const ui = new MenuUI(graph);
  await ui.start();
}

main();
