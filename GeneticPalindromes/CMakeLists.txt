cmake_minimum_required(VERSION 3.26)
project(GeneticPalindromes)

set(CMAKE_CXX_STANDARD 17)

add_executable(GeneticPalindromes main.cpp
        DoublyLinkedList.h
        ListNode.h
        DNASequence.h
        DNAPalindromeFinder.h
        DNASequence.cpp
        DNAPalindromeFinder.cpp
        FileProcessor.cpp
        FileProcessor.h)
