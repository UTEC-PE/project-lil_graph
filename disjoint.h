//
// Created by jaox on 10/13/18.
//

#ifndef GRAFO_PROYECTO_DISJOINT_H
#define GRAFO_PROYECTO_DISJOINT_H

#include "node.h"
#include <map>

using namespace std;

template <typename G>
class DisjointSet {
private:
    map<char,Node<G>*>  nodes;
public:
    typedef Node<G> node;
    DisjointSet() {}
    void makeSet(char data, node* node_){
        this->nodes[data] = node_;
    }
    bool unionSet(char data1, char data2){
        node* parent1 = findSet(data1);
        node* parent2 = findSet(data2);
        if(parent1 != parent2) {
            if(parent1->rank >= parent2->rank) {
                parent1->rank = (parent1->rank == parent2->rank) ? parent1->rank +1: parent1->rank;
                parent2->parent = parent1;
            }else {
                parent1->parent = parent2;
            }
            return true;
        }
        return false;
    }
    node* findSet(char data) {
        return findSet(this->nodes[data]);
    }
    node* findSet(node* node_){
        node* current = node_;
        while( current != current->parent){
            current = current->parent;
        }
        node_->parent = current;
        return current;
    }
    ~DisjointSet() {
    }
};

#endif //GRAFO_PROYECTO_DISJOINT_H
