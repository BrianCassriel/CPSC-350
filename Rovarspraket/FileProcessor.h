//
// Created by Brian Cassriel on 8/31/23.
//

#ifndef ROVARSPRAKET_FILEPROCESSOR_H
#define ROVARSPRAKET_FILEPROCESSOR_H
#include <string>

class FileProcessor {
public:
    FileProcessor();
    virtual ~FileProcessor();
    void processFile(std::string inputFile, std::string outputFile);
private:
    std::string readTXTFile(std::string filePath);
    std::string translateTXTFile(std::string filePath);
    std::string createHTMLContents(std::string filePath, std::string englishContents, std::string translatedContents);
    void writeFile(std::string contents, std::string filePath);
};


#endif //ROVARSPRAKET_FILEPROCESSOR_H
