#include <iostream>
using namespace std;

#include "domain/ADTDirectedGraph.h"
#include "ui/MenuUI.h"

int main()
{

    ADTDirectedGraph graph;
    MenuUI ui = MenuUI{graph};
    ui.start();

    return 0;
}