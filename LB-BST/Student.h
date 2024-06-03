// Student Class Header
// Created by Brian Cassriel on 11/3/23.
// The Student class represents a student's file in the database.
// It provides useful methods for interacting with the student's data.

#ifndef LB_BST_STUDENT_H
#define LB_BST_STUDENT_H

#include "Account.h"
#include <ostream>

class Student : public Account{
public:
    Student();
    Student(int ID);
    Student(std::string name, std::string level, std::string major, double gpa, int advisorID);
    virtual ~Student();
    friend std::ostream& operator<<(std::ostream& os, const Student &obj);

    std::string getMajor();
    double getGPA();
    int getAdvisorID();
    void setMajor(std::string major);
    void setGPA(double gpa);
    void setAdvisorID(int advisorID);
private:
    std::string major;
    double gpa;
    int advisorID;
};

#endif //LB_BST_STUDENT_H
