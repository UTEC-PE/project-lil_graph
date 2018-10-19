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
    a.addNode('G');
    a.addNode('H');
    a.addEdge('A','B',false, 2);
    a.addEdge('A','C',false, 3);
    a.addEdge('A','G',false, 15);
    a.addEdge('B','C',false, 5);
    a.addEdge('B','E',false, 7);
    a.addEdge('B','G',false, 8);
    a.addEdge('C','D',false, 4);
    a.addEdge('C','E',false, 6);
    a.addEdge('D','F',false, 6);
    a.addEdge('E','F',false, 9);
    a.addEdge('E','G',false, 7);
    a.addEdge('F','G',false, 9);
    a.addEdge('G','H',false, 1);

    cout<<"Density : "<<a.density(false)<<endl;

    cout<<"KRUSKAL ALGORITHM"<<endl;
    typedef list<Edge<Graph<Traits>>*> list;
    list kruskal = a.Kruskal();
    for(list::iterator it = kruskal.begin(); it != kruskal.end(); it++){
        cout<<"{"<<(*it)->nodes[0]->getData()<<","<<(*it)->nodes[1]->getData()<<"}"<<endl;
    }
    cout<<"PRIM ALGORTIHM starting with A"<<endl;
    a.print_edges(a.Prim());
    //a.print_path(a.find_node('A'), a.find_node('H'));
    cout<<"BFS ALGORITHM starting with A"<<endl;
    a.BFS();
    a.print_edges(a.BFS());
    //a.print_path(a.find_node('A'), a.find_node('H'));
    cout<<"DFS ALGORITHM starting with A"<<endl;
    a.DFS();
    a.print_edges();
    //a.print_path(a.find_node('A'), a.find_node('E'));
    cout<<"grafo a es bipartito ? "<<a.bipartite()<<endl;
    graph b;
    b.addNode('X');
    b.addNode('Y');
    b.addNode('Z');
    b.addEdge('X','Y',false, 1);
    b.addEdge('Y','Z',false, 1);
    cout<<"grafo b es bipartito ? "<<b.bipartite();

    return 0;
}