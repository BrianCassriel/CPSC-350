// FileProcessor Class Header
// Created by Brian Cassriel on 10/3/23.
// The FileProcessor class is responsible for processing the input file and passing the data to the SpeakerView.

#ifndef DOYOUSEEWHATISEE_FILEPROCESSOR_H
#define DOYOUSEEWHATISEE_FILEPROCESSOR_H

#include <fstream>
#include "SpeakerView.h"

class FileProcessor {
public:
    FileProcessor(std::string filePath);
    virtual ~FileProcessor();

    void processFile(SpeakerView *speakerView);
private:
    std::ifstream file;
};


#endif //DOYOUSEEWHATISEE_FILEPROCESSOR_H
