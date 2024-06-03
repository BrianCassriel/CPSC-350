// DNASequence Class Implementation
// Created by Brian Cassriel on 10/17/23.
// The DNASequence class is responsible for storing and manipulating a DNA sequence.

#include <iostream>
#include "DNASequence.h"

/**
 * Constructor
 * Makes a new empty DNASequence object.
 */
DNASequence::DNASequence() {
    sequence = new DoublyLinkedList<char>();
}

/**
 * Overloaded Constructor
 * Creates a new DNASequence object initialized with a string.
 * @param sequence - a string representing a DNA sequence
 */
DNASequence::DNASequence(std::string sequence) {
    this->sequence = new DoublyLinkedList<char>();
    for (char c : sequence) {
        this->sequence->append(c);
    }
}

/**
 * Destructor
 * Deletes the DoublyLinkedList sequence.
 */
DNASequence::~DNASequence() {
    delete sequence;
}

/** getComplement
 * Returns a new DNASequence object that is the complement of the original sequence.
 * @return - a pointer to a DNASequence object representing the complement of the original sequence
 */
DNASequence* DNASequence::getComplement() {
    DNASequence* complement = new DNASequence();
    for (int i = 0; i < sequence->getSize(); i++) {
        complement->append(getSingleComplement(sequence->get(i)));
    }
    return complement;
}

/** getSingleComplement
 * @param character - a char representing a nucleotide
 * @return - a char representing the complement of the nucleotide
 */
char DNASequence::getSingleComplement(char character) {
    switch (character) {
        case 'A':
            return 'T';
            break;
        case 'T':
            return 'A';
            break;
        case 'C':
            return 'G';
            break;
        case 'G':
            return 'C';
            break;
        default:
            throw std::runtime_error("Invalid character.");
    }
}

/** subsequence
 * Returns a new DNASequence object that is a subsequence of the original sequence.
 * @param start - the starting index of the subsequence (inclusive)
 * @param end - the ending index of the subsequence (exclusive)
 * @return - a pointer to a DNASequence object representing the subsequence
 */
DNASequence* DNASequence::subsequence(int start, int end) {
    DNASequence* subsequence = new DNASequence();
    for (int i = start; i < end; i++) {
        subsequence->append(sequence->get(i)); // get() makes this slow, but I didn't want to give access to the Nodes.
    }
    return subsequence;
}


/** isGeneticPalindrome
 * Returns true if the sequence is a genetic palindrome.
 * @return - a bool representing whether or not the sequence is a genetic palindrome
 */
bool DNASequence::isGeneticPalindrome() {
    DNASequence* reversedComplement = getReverse(getComplement());
    if (equals(reversedComplement))
        return true;
    return false;
}

/** equals
 * Returns true if the two sequences are equal.
 * @param o - a pointer to a DNASequence object
 * @return - a bool representing whether or not the two sequences are equal
 */
bool DNASequence::equals(DNASequence* o) {
    bool isPalindrome = true;
    for (int i = 0; i < sequence->getSize(); i++) {
        if (sequence->get(i) != o->get(i))
            isPalindrome = false;
    }
    return isPalindrome;
}

/** getReverse
 * Returns a new DNASequence object that is the reverse of the original sequence.
 * @param sequence - a pointer to a DNASequence object
 * @return - a pointer to a DNASequence object representing the reverse of the original sequence
 */
DNASequence* DNASequence::getReverse(DNASequence *sequence) const {
    DNASequence* reversedComplement = new DNASequence();
    for (int i = 0; i < sequence->length(); i++) {
        reversedComplement->prepend(sequence->get(i));
    }
    return reversedComplement;
}

/** get
 * Returns the character at the specified position in the DNASequence.
 * @param position - an int representing the position of the character
 * @return - a char representing the character at the specified position
 */
char DNASequence::get(int position) {
    return sequence->get(position);
}

/** append
 * Appends the specified character to the end of the DNASequence.
 * @param data - a char representing the character to be appended
 */
void DNASequence::append(char data) {
    sequence->append(data);
}

/** prepend
 * Prepends the specified character to the beginning of the DNASequence.
 * @param data - a char representing the character to be prepended
 */
void DNASequence::prepend(char data) {
    sequence->prepend(data);
}

/** toString
 * Returns a string representation of the DNASequence.
 * @return - a string representation of the DNASequence
 */
std::string DNASequence::toString() {
    std::string output;
    for (int i = 0; i < sequence->getSize(); i++) {
        output.push_back(sequence->get(i));
    }
    return output;
}

/** isValid
 * Returns true if the sequence only includes valid nucleotides.
 * @return - a bool representing whether or not the sequence is valid
 */
bool DNASequence::isValid() {
    for (int i = 0; i < sequence->getSize(); i++) {
        if (sequence->get(i) != 'A'
            && sequence->get(i) != 'T'
            && sequence->get(i) != 'C'
            && sequence->get(i) != 'G')
            return false;
    }
    return true;
}

/** length
 * Returns the length of the DNASequence.
 * @return - an int representing the length of the DNASequence
 */
int DNASequence::length() {
    return sequence->getSize();
}
