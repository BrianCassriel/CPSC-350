#include <iostream>
#include "FileProcessor.h"

int main(int argc, char** argv) {
    FileProcessor fileProcessor;
    fileProcessor.processFile(argv[1], argv[2]);
    return 0;
}
