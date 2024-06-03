// DNA Palindrome Finder Class Implementation
// Created by Brian Cassriel on 10/17/23.
// The DNAPalindromeFinder Class is responsible for taking DNASequences and finding palindromes in them.

#include "DNAPalindromeFinder.h"
#include "FileProcessor.h"

/**
 * Constructor
 * Creates a new FileProcessor and passes the file at filePath to it.
 * @param filePath - a string representing a path to the input file
 */
DNAPalindromeFinder::DNAPalindromeFinder(std::string filePath) {
    FileProcessor fileProcessor(filePath);
    fileProcessor.processFile(this);
}

/**
 * Destructor
 * Deletes the sequence.
 */
DNAPalindromeFinder::~DNAPalindromeFinder() {
    delete sequence;
}

/** processSequence
 * Processes a line from the input file.
 * 1. Prints the sequence and whether or not it is a genetic palindrome.
 * 2. Prints all of the subsequences of the sequence that are genetic palindromes.
 * @param line - a string representing a line from the input file
 */
void DNAPalindromeFinder::processSequence(std::string line) {
    sequence = new DNASequence(line);
    if (!sequence->isValid()) {
        std::cout << sequence->toString() << " is not valid. Moving on." << std::endl << std::endl;
        return;
    }
    printSequence();
    printSubsequences(sequence);
}

/** printSequence
 * Prints the sequence and whether or not it is a genetic palindrome.
 */
void DNAPalindromeFinder::printSequence() {
    std::cout << sequence->toString();
    if (sequence->isGeneticPalindrome())
        std::cout << " is a genetic palindrome." << std::endl;
    else
        std::cout << " is not a genetic palindrome." << std::endl;
}

/** printSubsequences
 * Prints all of the subsequences of the sequence that are genetic palindromes.
 * - Subsequences are only considered if they are more than 4 characters long and less than the length of the original sequence.
 * @param sequence - a pointer to a DNASequence object which represents the sequence to print subsequences of
 */
void DNAPalindromeFinder::printSubsequences(DNASequence* sequence) {
    std::cout << "Subsequence Palindromes: ";
    for (int currLength = 6; currLength < sequence->length(); currLength += 2) {
        printSubsequencesOfLength(sequence, currLength);
    }
    std::cout << std::endl << std::endl;
}

/** printSubsequencesOfLength
 * Prints all of the subsequences of the sequence that are genetic palindromes and are of length "length".
 * @param sequence - a pointer to a DNASequence object which represents the sequence to print subsequences of
 * @param length - an int which represents the length of the subsequences to print
 */
void DNAPalindromeFinder::printSubsequencesOfLength(DNASequence *sequence, int length) const {
    for (int startIndex = 0; startIndex < sequence->length() - length; startIndex++) {
        DNASequence* subsequence = sequence->subsequence(startIndex, startIndex + length);
        if (subsequence->isGeneticPalindrome()) {
            std::cout << subsequence->toString() << ", ";
        }
        delete subsequence;
    }
}
