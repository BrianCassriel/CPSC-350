// FileProcessor Class Header
// Created by Brian Cassriel on 10/17/23.
// The FileProcessor class is responsible for processing the input file and passing the data to the DNAPalindromeFinder.

#ifndef GENETICPALINDROMES_FILEPROCESSOR_H
#define GENETICPALINDROMES_FILEPROCESSOR_H

#include <string>
#include <fstream>
#include "DNAPalindromeFinder.h"

class FileProcessor {
public:
    FileProcessor(std::string filePath);
    virtual ~FileProcessor();

    void processFile(DNAPalindromeFinder* dnaPalindromeFinder);
private:
    std::ifstream file;
};


#endif //GENETICPALINDROMES_FILEPROCESSOR_H
