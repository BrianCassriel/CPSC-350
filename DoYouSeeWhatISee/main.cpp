// Main Method
// Created by Brian Cassriel on 10/3/23.

#include <iostream>
#include "SpeakerView.h"

/** Main method
 * 1. Creates a SpeakerView object which reads in the file at the path specified by the first command line argument.
 * 2. Prints the results to the console.
 * @param argc - the number of command line arguments
 * @param argv - an array of strings containing the command line arguments
 * @return - 0 if the program ran successfully, 1 if not
 */
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    SpeakerView speakerView(argv[1]);
    speakerView.printResults();
    return 0;
}