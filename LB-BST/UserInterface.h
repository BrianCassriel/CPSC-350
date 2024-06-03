// User Interface Class Header
// Created by Brian Cassriel on 11/8/23.
// This class is responsible for displaying the menu and getting user input.
// It also calls the appropriate methods in the Database class to perform the requested operations.

#ifndef LB_BST_USERINTERFACE_H
#define LB_BST_USERINTERFACE_H

#include "Database.h"

class UserInterface {
public:
    UserInterface();
    virtual ~UserInterface();

    bool isRunning();
    void displayMenu();
    void doUserSelection();
    void addDefaultData();
private:
    Database* database;
    bool running;

    int getUserSelection();
    int getStudentIDFromUser();
    int getFacultyIDFromUser();
    void displayAllStudents();
    void displayAllFaculty();
    void findStudent();
    void findFaculty();
    void addStudent();
    void deleteStudent();
    void addFaculty();
    void deleteFaculty();
    void changeAdvisor();
    void removeAdvisee();
};

#endif //LB_BST_USERINTERFACE_H
