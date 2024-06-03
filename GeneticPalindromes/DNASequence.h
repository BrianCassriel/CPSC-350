// DNASequence Class Header
// Created by Brian Cassriel on 10/17/23.
// The DNASequence class is responsible for storing and manipulating a DNA sequence.

#ifndef GENETICPALINDROMES_DNASEQUENCE_H
#define GENETICPALINDROMES_DNASEQUENCE_H

#include <string>
#include "DoublyLinkedList.h"

class DNASequence {
public:
    DNASequence();
    DNASequence(std::string sequence);
    virtual ~DNASequence();
    DNASequence* getComplement();
    DNASequence* subsequence(int start, int end);
    bool isGeneticPalindrome();
    std::string toString();
    bool isValid();
    int length();
private:
    DoublyLinkedList<char>* sequence;

    char get(int position);
    void append(char data);
    void prepend(char data);

    char getSingleComplement(char character);
    DNASequence* getReverse(DNASequence *sequence) const;
    bool equals(DNASequence *o);
};


#endif //GENETICPALINDROMES_DNASEQUENCE_H
