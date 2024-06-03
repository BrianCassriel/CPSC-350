// WGraph Class Implementation
// Created by Erik Linstead & Brian Cassriel
// Represents a weighted graph and provides useful methods for working with the graph.

#include "WGraph.h"

/** Constructor
 * Initializes the WGraph with a size of 0 and a NULL adjacency matrix
 */
WGraph::WGraph(){
  m_size = 0;
  m_adj = NULL;
}

/** Overloaded Constructor
 * Initializes the WGraph with a size. Creates an adjacency matrix of size x size.
 * @param sz - the size of the WGraph
 */
WGraph::WGraph(unsigned int sz){
    m_size = sz;
    allocateMatrix(m_adj);
    allocateMatrix(m_conn);
    for(int i = 0; i < m_size; ++i){
        for(int j = 0; j < m_size; ++j){
          m_adj[i][j] = std::numeric_limits<double>::max();
          m_conn[i][j] = std::numeric_limits<double>::max();
        }
    }
}

/** Destructor
 * Releases the memory allocated for the adjacency matrix
 */
WGraph::~WGraph(){
    for(int i = 0; i < m_size; ++i){
        delete[] m_adj[i];
        delete[] m_conn[i];
    }
}

/** addEdge
 * Adds an edge to the WGraph
 * @param i - the first vertex
 * @param j - the second vertex
 * @param w - the weight of the edge
 */
void WGraph::addEdge(VertexID i, VertexID j, double w){
  if(i < m_size && j < m_size){
    m_adj[i][j] = w;
    m_adj[j][i] = w;
  }
}

/** removeEdge
 * Removes an edge from the WGraph
 * @param i - the first vertex
 * @param j - the second vertex
 */
void WGraph::removeEdge(VertexID i, VertexID j){
  if(i < m_size && j < m_size){
    m_adj[i][j] = std::numeric_limits<double>::max();
    m_adj[j][i] = std::numeric_limits<double>::max();
  }
}

/** areAdjacent
 * Checks if two vertices are adjacent
 * @param i - the first vertex
 * @param j - the second vertex
 * @return bool - true if the vertices are adjacent, false otherwise
 */
bool WGraph::areAdjacent(VertexID i, VertexID j){
  return (m_adj[i][j] < std::numeric_limits<double>::max());
}

/** calcFW
 * Computes the Floyd-Warshall algorithm and stores the results in the m_conn matrix
 */
void WGraph::calcFW(){
  for(int i = 0; i < m_size; ++i){
    for(int j = 0; j < m_size; ++j){
      m_conn[i][j] = m_adj[i][j]; //start with conn == adj matrix
    }
  }

  for(int im = 0; im < m_size; ++im){ //transitive closure
    for(int source = 0; source < m_size; ++source){
      for(int sink = 0; sink < m_size; ++sink){
        //every possible pair of source,sink and intermediate node
        if(source==sink){
          continue;
        }
        if(m_conn[source][im] != std::numeric_limits<double>::max() &&
           m_conn[im][sink] != std::numeric_limits<double>::max() &&
           m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink]){
          m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink];
        }

      }
    }
  }
}

/** cheapestCost
 * Returns the cheapest cost between two vertices
 * @param i - the first vertex
 * @param j - the second vertex
 * @return double - the cheapest cost between the two vertices
 */
double WGraph::cheapestCost(VertexID i, VertexID j){
  return m_conn[i][j];
}

/** computeMST()
 * Computes the Minimum Spanning Tree (MST) using Kruskal's algorithm and displays the MST cost and adjacency matrix
 */
void WGraph::computeMST() { // Zybooks: 10.18 Minimum Spanning Tree
    std::set<WEdge<double>> edgeList = getEdges();
    std::set<std::set<int>> vertexSets;
    for (int i = 0; i < m_size; i++) {
        std::set<int> tempSet;
        tempSet.insert(i);
        vertexSets.insert(tempSet);
    }
    std::set<WEdge<double>> resultList;

    while (vertexSets.size() > 1 && !edgeList.empty()) {
        WEdge<double> nextEdge = getSmallestEdge(edgeList);
        std::set<int> vSet1;
        std::set<int> vSet2;
        for (std::set<int> vertexSet : vertexSets) {
            if (vertexSet.find(nextEdge.vertex1) != vertexSet.end()) {
                vSet1 = vertexSet;
            }
            if (vertexSet.find(nextEdge.vertex2) != vertexSet.end()) {
                vSet2 = vertexSet;
            }
        }
        if (vSet1 != vSet2) {
            resultList.insert(nextEdge);
            vertexSets.erase(vSet1);
            vertexSets.erase(vSet2);
            vertexSets.insert(setUnion(vSet1, vSet2));
        }
    }

    printMSTCost(resultList);
    double** mstAdjMatrix;
    allocateMatrix(mstAdjMatrix);
    for (WEdge<double> edge : resultList) {
        mstAdjMatrix[edge.vertex1][edge.vertex2] = edge.weight;
        mstAdjMatrix[edge.vertex2][edge.vertex1] = edge.weight;
    }
    printMSTAdjMatrix(mstAdjMatrix);
}

/** setUnion
 * Merges two sets
 * @param setOne - the first set
 * @param setTwo - the second set
 * @return std::set<int> - the merged set
 */
std::set<int> WGraph::setUnion(std::set<int> &setOne, std::set<int> &setTwo) {
    std::set<int> merged;
    for (int i : setOne)
        merged.insert(i);
    for (int i : setTwo)
        merged.insert(i);
    return merged;
}

/** getEdges
 * Gets all the edges in the WGraph
 * @return std::set<WEdge<double>> - a set of all the edges in the WGraph
 */
std::set<WEdge<double>> WGraph::getEdges() {
    std::set<WEdge<double>> edgeList;
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            edgeList.insert(WEdge<double>(i, j, m_adj[i][j]));
        }
    }
    return edgeList;
}

/** allocateMatrix
 * Allocates memory for a matrix
 * @param matrix - the matrix to be allocated
 */
void WGraph::allocateMatrix(double** &matrix) {
    matrix = new double*[m_size];
    for (int i = 0; i < m_size; i++) {
        matrix[i] = new double[m_size];
        for (int j = 0; j < m_size; j++)
            matrix[i][j] = 0;
    }
}

/** getSmallestEdge
 * Gets the smallest edge from a set of edges
 * @param edgeList - the set of edges
 * @return WEdge<double> - the smallest edge
 */
WEdge<double> WGraph::getSmallestEdge(std::set<WEdge<double>> &edgeList) {
    WEdge<double> smallestEdge;
    double smallestEdgeWeight = std::numeric_limits<double>::max();
    for (WEdge<double> edge : edgeList) {
        if (edge.weight < smallestEdgeWeight) {
            smallestEdgeWeight = edge.weight;
            smallestEdge = edge;
        }
    }
    edgeList.erase(smallestEdge);
    return smallestEdge;
}

/** printMSTCost
 * Prints the cost of the Minimum Spanning Tree to standard output
 * @param resultList - the set of edges in the MST
 */
void WGraph::printMSTCost(std::set<WEdge<double>> &resultList) {
    double mstCost = 0;
    for (WEdge<double> edge : resultList) {
        mstCost += edge.weight;
    }
    std::cout << "MST Cost: " << mstCost << std::endl;
}

/** printMSTAdjMatrix
 * Prints the adjacency matrix of the Minimum Spanning Tree to standard output
 * @param mstAdjMatrix - the adjacency matrix of the MST
 */
void WGraph::printMSTAdjMatrix(double** &mstAdjMatrix) {
    std::cout << "MST Adjacency Matrix: " << std::endl;
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            if (mstAdjMatrix[i][j] == std::numeric_limits<double>::max())
                std::cout << "0";
            else
                std::cout << mstAdjMatrix[i][j];
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}
