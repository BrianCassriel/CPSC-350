// FileProcessor Class Header
// Created by Brian Cassriel on 12/5/23.
// Opens a file and reads a WGraph

#ifndef SPANNINGTHEGAMUT_FILEPROCESSOR_H
#define SPANNINGTHEGAMUT_FILEPROCESSOR_H

#include <string>
#include <fstream>
#include <iostream>
#include "WGraph.h"

using namespace std;

class FileProcessor {
public:
    FileProcessor(string filePath);
    ~FileProcessor();
    WGraph* readGraph();
private:
    string filePath;
    ifstream fileStream;
};


#endif //SPANNINGTHEGAMUT_FILEPROCESSOR_H
