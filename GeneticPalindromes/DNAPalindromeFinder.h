// DNA Palindrome Finder Class Header
// Created by Brian Cassriel on 10/17/23.
// The DNAPalindromeFinder Class is responsible for taking DNASequences and finding palindromes in them.

#ifndef GENETICPALINDROMES_DNAPALINDROMEFINDER_H
#define GENETICPALINDROMES_DNAPALINDROMEFINDER_H

#include <string>
#include <iostream>
#include "DNASequence.h"

class DNAPalindromeFinder {
public:
    DNAPalindromeFinder(std::string filePath);
    virtual ~DNAPalindromeFinder();

    void processSequence(std::string line);
private:
    DNASequence* sequence;

    void printSequence();
    void printSubsequences(DNASequence* sequence);
    void printSubsequencesOfLength(DNASequence *sequence, int length) const;
};


#endif //GENETICPALINDROMES_DNAPALINDROMEFINDER_H
