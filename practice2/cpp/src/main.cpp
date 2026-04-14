#include <iostream>
using namespace std;

#include "../tests/Tests.h"
#include "domain/ADTDirectedGraph.h"
#include "ui/MenuUI.h"

int main()
{
    // testInit();
    // testAddVertex();
    // testRemoveVertex();
    // testAddEdge();
    // testRemoveEdge();
    // testIsEdge();

    ADTDirectedGraph graph;
    MenuUI ui = MenuUI{graph};
    ui.start();

    return 0;
}