#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::node node;

        node* nodes[2];
        Edge(E data, bool dir):data{data},dir{dir}{}
        E getWeight() {
            return data;
        }
        bool getDir(){
            return dir;
        }
        ~Edge(){
            delete[] this;
        }
    private:
        E data;
        bool dir;
};

#endif
