// Database Class Header
// Created by Brian Cassriel on 11/4/23.
// This class holds the database for the university.
// It contains two LazyBSTs, one for students and one for faculty, and methods to manipulate them.

#ifndef LB_BST_DATABASE_H
#define LB_BST_DATABASE_H

#include "LazyBST.h"
#include "Student.h"
#include "Faculty.h"

class Database {
public:
    Database();
    virtual ~Database();
    LazyBST<Student>* getStudentTree();
    LazyBST<Faculty>* getFacultyTree();
    void addStudent(Student* student);
    void deleteStudent(int studentID);
    void addFaculty(Faculty* faculty);
    void deleteFaculty(int facultyID);
    Student* findStudentByID(int studentID);
    Faculty* findFacultyByID(int facultyID);
    bool studentExists(int studentID);
    bool facultyExists(int facultyID);
    void logToFile();
private:
    LazyBST<Student>* studentTree;
    LazyBST<Faculty>* facultyTree;
};


#endif //LB_BST_DATABASE_H
