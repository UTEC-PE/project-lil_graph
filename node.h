#ifndef NODE_H
#define NODE_H

template <typename G>
class Node {
    public:
        typedef typename G::N N; //char
        typedef typename G::EdgeSeq EdgeSeq; //lista de aristas

        int rank;        //

        Node* parent;    //para kruskal y prim

        EdgeSeq edges;
        Node(N data):data{data}, rank(0), parent(this){}
        N getData(){
            return data;
        }
        ~Node(){
            delete[] this;
        }
    private:
        N data;  //nombre
        double x;
        double y;
};

#endif