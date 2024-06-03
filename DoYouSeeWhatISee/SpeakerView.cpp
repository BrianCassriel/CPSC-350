// SpeakerView Class Implementation
// Created by Brian Cassriel on 10/3/23.
// The SpeakerView class is responsible for processing the input file and printing the results.
// It uses a DoublyLinkedList of MonoStacks to store the heights of the participants.

#include <iostream>
#include <sstream>
#include <iomanip>
#include "SpeakerView.h"
#include "FileProcessor.h"

/**
 * Constructor
 * Initializes the DoublyLinkedList of MonoStacks and the number of columns.
 * Creates a FileProcessor object to process the input file & starts processing the file at filePath.
 * @param filePath - a string representing a path to the input file
 */
SpeakerView::SpeakerView(std::string filePath){
    participantHeights = new DoublyLinkedList<MonoStack<double>*>();
    numberOfColumns = 0;
    FileProcessor fileProcessor(filePath);
    fileProcessor.processFile(this);
}

/**
 * Destructor
 * Deletes the DoublyLinkedList of MonoStacks.
 */
SpeakerView::~SpeakerView() {
    delete participantHeights;
}

/** processLine
 * Processes a line of the input file. Creates a MonoStack of doubles from the string of heights.
 * @param line - a string containing the heights of the participants in a column separated by spaces
 */
void SpeakerView::processLine(std::string line) {
    std::string height;
    std::istringstream iss(line); // https://cplusplus.com/reference/sstream/istringstream/str/
    MonoStack<double>* column = new MonoStack<double>('d');
    while (iss >> height) {
        column->push(std::stod(height)); // https://cplusplus.com/reference/string/stod/
    }
    participantHeights->append(column);
    numberOfColumns++;
}

/** printResults
 * Prints a layout of the participants and the speaker to the console.
 */
void SpeakerView::printResults() {
    for (int columnNum = 0; columnNum < numberOfColumns; columnNum++) {
        printNumSeeingParticipants(columnNum);
        printColumn(columnNum);
        printSpeaker(columnNum);
        std::cout << std::endl;
    }
}

/** printColumn
 * Prints one line of doubles from the MonoStack to the console.
 * @param columnNum - the column number of the participants to print
 */
void SpeakerView::printColumn(int columnNum) {
    MonoStack<double>* column = participantHeights->get(columnNum);
    while (!column->isEmpty()) {
        std::cout << std::fixed << std::setprecision(1) << column->pop() << " ";
    }
}

/** printNumSeeingParticipants
 * Prints the number of participants that can see the speaker in the column.
 * @param columnNum - the column number of the participants to print
 */
void SpeakerView::printNumSeeingParticipants(int columnNum) {
    std::cout << "(" << getNumSeeingParticipants(columnNum) << ")   ";
}

/** printSpeaker
 * Prints the location of the speaker to the console.
 * @param columnNum - the current column number of the participants
 */
void SpeakerView::printSpeaker(int columnNum) const {
    if (columnNum == numberOfColumns / 2)
        std::cout << "      (Speaker)";
}

/** getNumSeeingParticipants
 * Counts the number of participants that can see the speaker in the column.
 * @param column - the column number of the participants
 * @return - the number of participants that can see the speaker in the column
 */
int SpeakerView::getNumSeeingParticipants(int column) {
    return participantHeights->get(column)->getSize();
}
