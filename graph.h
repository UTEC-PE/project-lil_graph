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
                    edge* edge2 = new edge(weight, true);
                    edge2->nodes[0] = node2;
                    edge2->nodes[1] = node1;
                    node2->edges.push_back(edge2);
                }
            }
        }
        void deleteEdge(){
        }
        void deleteNode(N data){
        }
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

        NodeSeq BFS(){
            for(ni = nodes.begin(); ni != nodes.end(); ++ni){
                (*ni)->parent = nullptr;
                (*ni)->rank = 999999;
                (*ni)->color="WHITE";
            }
            queue<node*> cola;
            ni = nodes.begin();
            (*ni)->parent = nullptr;
            (*ni)->color = "GRAY";
            (*ni)->rank = 0;
            cola.push(*ni);
            while(!cola.empty()){
                node* u = cola.front();
                cola.pop();
                for(ei = u->edges.begin(); ei != u->edges.end(); ++ei) {
                    node* v = (*ei)->nodes[1];
                    if(v->color == "WHITE") {
                        v->color = "GRAY";
                        v->rank = u->rank + 1;
                        v->parent = u;
                        cola.push(v);
                    }
                }
                u->color = "BLACK";
            }
            return nodes;
        }
        void DFS() {
            for(ni = nodes.begin(); ni != nodes.end(); ++ni) {
                (*ni)->parent = nullptr;
                (*ni)->color = "WHITE";
            }
            for(ni = nodes.begin(); ni != nodes.end(); ++ni) {
               if ((*ni)->color == "WHITE") DFS(*ni);
            }
        }
        void DFS(node* u){
            u->color= "GRAY";
            int size = u->edges.size();
            for(int i = 0 ; i < size; i++) {
                ei = u->edges.begin();
                advance(ei,i);
                node* v = (*ei)->nodes[1];
                if(v->color == "WHITE") {
                    v->parent = u;
                    DFS(v);
                }
            }
            u->color = "BLACK";
        }
        void print_path(node* s, node* e) {
            if(s == e) cout<< s->getData() <<endl;
            else if( e->parent == nullptr)
                cout << "no path from "<< s->getData() << " to "<<e->getData() <<" exists"<<endl;
            else {
                print_path(s, e->parent);
                cout<<e->getData() << endl;
            }
        }
        double density(bool dir) {
            double e = edges.size();
            double v = nodes.size();
            double d = e/(v*(v-1));
            if(dir) return d;
            else return 2*d;
        }
        bool bipartite(){
            for(ni = nodes.begin(); ni != nodes.end(); ++ni){
                (*ni)->parent = nullptr;
                (*ni)->rank = 999999;
                (*ni)->color="WHITE";
            }
            queue<node*> cola;
            ni = nodes.begin();
            (*ni)->parent = nullptr;
            (*ni)->color =  "RED";
            (*ni)->rank = 0;
            cola.push(*ni);
            while(!cola.empty()){
                node* u = cola.front();
                cola.pop();
                if(u->rank % 2 == 0) {
                    for(ei = u->edges.begin(); ei != u->edges.end(); ++ei) {
                        node* v = (*ei)->nodes[1];
                        if(v->color == "WHITE") {
                            v->color = "BLUE";
                            v->rank = u->rank + 1;
                            cola.push(v);
                        } else if (v->color == "RED" ) {
                            return false;
                        }
                    }
                } else {
                    for(ei = u->edges.begin(); ei != u->edges.end(); ++ei) {
                        node* v = (*ei)->nodes[1];
                        if(v->color == "WHITE") {
                            v->color = "RED";
                            v->rank = u->rank + 1;
                            cola.push(v);
                        } else if (v->color == "BLUE" ) {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        void print_edges(NodeSeq n){
            ni= n.begin();
            for(; ni != n.end(); ni++){
                if((*ni)->parent != nullptr)
                    cout<<"{"<<(*ni)->parent->getData()<<","<<(*ni)->getData()<<"}"<<endl;
            }
        }
        void print_edges(){
            ni = nodes.begin();
            for(; ni != nodes.end(); ni++){
                if((*ni)->parent != nullptr)
                    cout<<"{"<<(*ni)->parent->getData()<<","<<(*ni)->getData()<<"}"<<endl;
            }
        }
        bool isconnected() {
            NodeSeq nodes_ = BFS();
            int contador = 0;
            for(ni = nodes_.begin(); ni != nodes_.end(); ni++){
                if((*ni)->parent== nullptr) contador++;
                if(contador > 1) return false;
            }
            return true;
        }
        ~Graph(){

        }
    private:
        NodeSeq nodes;
        NodeIte ni;
        EdgeIte ei;
        EdgeSeq edges;
};

typedef Graph<Traits> graph;

#endif