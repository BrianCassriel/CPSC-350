// SpeakerView Class Header
// Created by Brian Cassriel on 10/3/23.
// The SpeakerView class is responsible for processing the input file and printing the results.
// It uses a DoublyLinkedList of MonoStacks to store the heights of the participants.

#ifndef DOYOUSEEWHATISEE_SPEAKERVIEW_H
#define DOYOUSEEWHATISEE_SPEAKERVIEW_H

#include <string>
#include "MonoStack.h"

class SpeakerView {
public:
    SpeakerView(std::string filePath);
    virtual ~SpeakerView();

    void processLine(std::string line);
    void printResults();
    int getNumSeeingParticipants(int column);
private:
    DoublyLinkedList<MonoStack<double>*>* participantHeights;
    int numberOfColumns;

    void printSpeaker(int columnNum) const;
    void printNumSeeingParticipants(int columnNum);
    void printColumn(int columnNum);
};


#endif //DOYOUSEEWHATISEE_SPEAKERVIEW_H
