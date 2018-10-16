#include <iostream>

#include "read.h"

using namespace std;

int main(int argc, char *argv[]) {

    graph a;
    a.addNode('A');
    a.addNode('B');
    a.addNode('C');
    a.addNode('D');
    a.addNode('E');
    a.addNode('F');
    a.addEdge('A','B',false, 3);
    a.addEdge('A','D',false, 2);
    a.addEdge('A','E',false, 1);
    a.addEdge('D','B',false, 4);
    a.addEdge('D','E',false, 5);
    a.addEdge('E','F',false, 9);
    a.addEdge('B','C',false, 7);
    a.addEdge('D','F',false, 6);
    a.addEdge('C','F',false, 8);

    a.Kruskal();
    a.Prim();

    return 0;
}