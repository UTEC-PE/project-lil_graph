cmake_minimum_required(VERSION 3.9.6)
project(grafo_proyecto)

set(CMAKE_CXX_STANDARD 17)

add_executable(grafo_proyecto main.cpp node.h read.h edge.h graph.h disjoint.h my_priority_queue.h)