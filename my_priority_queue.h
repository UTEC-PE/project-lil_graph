//
// Created by jaox on 10/16/18.
//

#ifndef GRAFO_PROYECTO_MY_PRIORITY_QUEUE_H
#define GRAFO_PROYECTO_MY_PRIORITY_QUEUE_H

#include <queue>

using namespace std;

template <class T,
        class Container = vector<T>,
                class Compare = less<typename Container::value_type>
> class my_priority_queue: public priority_queue<T, Container, Compare>
{
public:
    bool find(T val ){
        auto first = this->c.cbegin();
        auto last = this->c.end();
        while(first != last) {
            if(*first == val) return true;
            ++first;
        }
        return false;
    }
};

#endif //GRAFO_PROYECTO_MY_PRIORITY_QUEUE_H
