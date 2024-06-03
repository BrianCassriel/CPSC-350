cmake_minimum_required(VERSION 3.26)
project(LB_BST)

set(CMAKE_CXX_STANDARD 17)

add_executable(LB_BST main.cpp
        TreeNode.h
        LazyBST.h
        Student.h
        Faculty.h
        Database.h
        Database.cpp
        Student.cpp
        Faculty.cpp
        Account.h
        Account.cpp
        DoublyLinkedList.h
        ListNode.h
        UserInterface.h
        UserInterface.cpp)
