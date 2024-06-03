// FileProcessor Class Implementation
// Created by Brian Cassriel on 10/17/23.
// The FileProcessor class is responsible for processing the input file and passing the data to the DNAPalindromeFinder.

#include "FileProcessor.h"

/**
 * Constructor
 * Opens the file at filePath.
 * @param filePath - a string representing a path to the input file
 */
FileProcessor::FileProcessor(std::string filePath) {
    file.open(filePath, std::ios::in);
}

/**
 * Destructor
 * Closes the file.
 */
FileProcessor::~FileProcessor() {
    file.close();
}

/** processFile
 * Processes the input file. Passes each line to the DNAPalindromeFinder.
 * @param speakerView - a pointer to a SpeakerView object
 */
void FileProcessor::processFile(DNAPalindromeFinder* dnaPalindromeFinder) {
    if (!file.is_open()) {
        throw std::runtime_error("File not found.");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == "END") {
            continue;
        }
        dnaPalindromeFinder->processSequence(line);
    }
}