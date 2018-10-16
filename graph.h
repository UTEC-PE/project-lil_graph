#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <queue>

#include "edge.h"
#include "disjoint.h"
#include "my_priority_queue.h"

using namespace std;

class Traits {
	public:
		typedef char N; //nombre del nodo
		typedef int E;  //peso de la arista
};

template <typename G>
struct orderbyrank {
    bool operator() (Node<G>* const &a, Node<G>* const &b) {
        return a->rank > b->rank;
    }
};

template <typename Tr>
class Graph {
    public:
        typedef Graph<Tr> self;
        typedef Node<self> node;
        typedef Edge<self> edge;
        typedef vector<node*> NodeSeq;
        typedef list<edge*> EdgeSeq;
        typedef typename Tr::N N;
        typedef typename Tr::E E;
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;

        void addNode(N data){
            node* node1 =new node(data);
            nodes.push_back(node1);
        };
        node* find_node(N data){
            ni = nodes.begin();
            for(;ni !=nodes.end(); ++ni){
                if((*ni)->getData() == data)
                    return *ni;
            }
            return nullptr;
        }
        edge* find_edge(E weight, bool dir, node* nodes[2]){
            ei = edges.begin();
            for(;ei != edges.end(); ++ei){
                if((*ei)->getWeight() == weight && (*ei)->getDir() == dir &&
                        (*ei)->nodes[0] == nodes[0] && (*ei)->nodes[1] == nodes[1]){
                    return *ei;
                }
            }
            return nullptr;
        }
        void addEdge(N data_1, N data_2, bool dir, E weight){
            node* node1 = find_node(data_1);
            node* node2 = find_node(data_2);

            if(node1 && node2) {
                edge* edge1 = new edge(weight, dir);
                edge1->nodes[0] = node1;
                edge1->nodes[1] = node2;
                node1->edges.push_back(edge1);
                edges.push_back(edge1);
                if (!dir) {
                    node2->edges.push_back(edge1);
                }
            }
        }
        void deleteEdge(){
        }
        void deleteNode(N data){
        }
        EdgeSeq Kruskal(){
            EdgeSeq kruskal_edges;
            DisjointSet<self> disjointSet;

            for(ni = nodes.begin(); ni != nodes.end(); ++ni) {
                N name = (*ni)->getData();
                disjointSet.makeSet(name,*ni);
            }
            edges.sort([](edge* a, edge* b){
                int w1 = a->getWeight();
                int w2 = b->getWeight();
                return w1 < w2;
            });
            int mst_weight = 0, mst_edges =0, mst_i=0;
            ei = edges.begin();
            while( mst_i < edges.size() ) {
                node* node1 = (*ei)->nodes[0];
                node* node2 = (*ei)->nodes[1];
                E weight = (*ei)->getWeight();
                if( disjointSet.findSet(node1->getData()) != disjointSet.findSet(node2->getData()) ) {
                    disjointSet.unionSet(node1->getData(), node2->getData());
                    mst_weight += weight;
                    kruskal_edges.push_back(*ei);
                    mst_edges++;
                }
                mst_i++;
                ei++;
            }
            return kruskal_edges;
        };
        NodeSeq Prim(){
            my_priority_queue<node*,NodeSeq,orderbyrank<self>> cola_;
            for(ni = nodes.begin(); ni != nodes.end(); ++ni) {
                if (ni != nodes.begin()) (*ni)->rank = 999999;
                else (*ni)->rank = 0;
                (*ni)->parent = nullptr;
                cola_.push(*ni);
            }
            while(!cola_.empty()) {
                node* aux = cola_.top();
                cola_.pop();
                cola_.push(aux);
                node* u = cola_.top();  //extract min node from queue
                cola_.pop();
                for(ei=u->edges.begin(); ei!=u->edges.end(); ++ei){
                    node* v = (*ei)->nodes[1];
                    if((*ei)->getWeight() < v->rank && cola_.find(v)){
                        v->rank = (*ei)->getWeight();
                        v->parent = u;
                    }
                }
            }
            return nodes;
        }
    private:
        NodeSeq nodes;
        NodeIte ni;
        EdgeIte ei;
        EdgeSeq edges;
};

typedef Graph<Traits> graph;

#endif