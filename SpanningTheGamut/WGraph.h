// WGraph Class Header
// Created by Erik Linstead & Brian Cassriel
// Represents a weighted graph and provides useful methods for working with the graph.

#ifndef WGraph_H
#define WGraph_H

#include <cstdlib>
#include <set>
#include <iostream>
#include <limits>
#include "WEdge.h"

typedef unsigned int VertexID;

class WGraph{
public:
  WGraph();
  WGraph(unsigned int sz);
  ~WGraph();
  void addEdge(VertexID i, VertexID j, double w);
  void removeEdge(VertexID i, VertexID j);
  bool areAdjacent(VertexID i, VertexID j);
  double cheapestCost(VertexID i, VertexID j);
  void calcFW();
    void computeMST();

private:
  double** m_adj;
  double** m_conn;
  unsigned int m_size; //nodes in WGraph (fixed)

    void allocateMatrix(double** &matrix);
    WEdge<double> getSmallestEdge(std::set<WEdge<double>> &edgeList);
    void printMSTCost(std::set<WEdge<double>> &resultList);
    void printMSTAdjMatrix(double** &mstAdjMatrix);
    std::set<WEdge<double>> getEdges();
    std::set<int> setUnion(std::set<int> &setOne, std::set<int> &setTwo);
};






#endif
