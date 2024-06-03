cmake_minimum_required(VERSION 3.26)
project(DoYouSeeWhatISee)

set(CMAKE_CXX_STANDARD 14)

add_executable(DoYouSeeWhatISee
        main.cpp
        MonoStack.h
        ListNode.h
        DoublyLinkedList.h
        SpeakerView.h
        SpeakerView.cpp
        FileProcessor.h
        FileProcessor.cpp
)
