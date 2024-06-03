// FileProcessor Class Implementation
// Created by Brian Cassriel on 12/5/23.
// Opens a file and reads a WGraph

#include "FileProcessor.h"

/** Constructor
 * @param filePath - path of the file to be read
 */
FileProcessor::FileProcessor(string filePath) {
    this->filePath = filePath;
    fileStream.open(filePath);
    if (!fileStream.is_open()) {
        cout << "Error opening file: " << filePath << endl;
    }
}

/** Destructor
 * Closes the file stream
 */
FileProcessor::~FileProcessor() {
    if (fileStream.is_open())
        fileStream.close();
}

/** Reads a WGraph from a file
 * @return WGraph* - a pointer to the created WGraph
 */
WGraph* FileProcessor::readGraph() {
    string line;
    getline(fileStream, line);
    int numNodes = stoi(line);
    int vertex1 = 0;
    int vertex2 = 0;
    double weight;
    WGraph* graph = new WGraph(numNodes);
    while (getline(fileStream, line) && line != "END") {
        while (true) {
            int nextSpacePos = line.find(' ');
            weight = stod(line.substr(0, nextSpacePos));
            if (weight == 0.0)
                weight = std::numeric_limits<double>::max();
            graph->addEdge(vertex1, vertex2, weight);
            line = line.substr(nextSpacePos + 1);
            vertex2++;
            if (vertex2 == numNodes)
                break;
        }
        vertex2 = 0;
        vertex1++;
    }
    return graph;
}
