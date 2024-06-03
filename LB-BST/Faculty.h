// Faculty Class Header
// Created by Brian Cassriel on 11/3/23.
// The Faculty class represents a faculty member's file in the database.
// It provides useful methods for interacting with the faculty member's data.

#ifndef LB_BST_FACULTY_H
#define LB_BST_FACULTY_H

#include <ostream>
#include "Account.h"
#include "DoublyLinkedList.h"

class Faculty : public Account{
public:
    Faculty();
    Faculty(int ID);
    Faculty(std::string name, std::string level, std::string department);
    virtual ~Faculty();
    friend std::ostream& operator<<(std::ostream& os, const Faculty &obj);

    std::string getDepartment();
    DoublyLinkedList<int>* getAdviseeIDs();
    void setDepartment(std::string department);
    void addAdvisee(int studentID);
    void removeAdvisee(int studentID);
private:
    std::string department;
    DoublyLinkedList<int>* adviseeIDs;
};

#endif //LB_BST_FACULTY_H
