// Database Class Implementation
// Created by Brian Cassriel on 11/4/23.
// This class holds the database for the university.
// It contains two LazyBSTs, one for students and one for faculty, and methods to manipulate them.

#include <fstream>
#include "Database.h"

/** Constructor
 * Initializes the student and faculty trees.
 */
Database::Database() {
    studentTree = new LazyBST<Student>();
    facultyTree = new LazyBST<Faculty>();
}

/** Destructor
 * Deletes the student and faculty trees.
 */
Database::~Database() {
    delete studentTree;
    delete facultyTree;
}

/** getStudentTree
 * @return a pointer to the student tree.
 */
LazyBST<Student>* Database::getStudentTree() {
    return studentTree;
}

/** getFacultyTree
 * @return a pointer to the faculty tree.
 */
LazyBST<Faculty>* Database::getFacultyTree() {
    return facultyTree;
}

/** findStudentByID
 * @param studentID the ID of the student to find.
 * @return the student with the given ID, or nullptr if not found.
 */
Student* Database::findStudentByID(int studentID) {
    Student* tempStudent = new Student(studentID);
    return studentTree->find(*tempStudent);
}

/** findFacultyByID
 * @param facultyID the ID of the faculty member to find.
 * @return the faculty member with the given ID, or nullptr if not found.
 */
Faculty* Database::findFacultyByID(int facultyID) {
    Faculty* tempFaculty = new Faculty(facultyID);
    return facultyTree->find(*tempFaculty);
}

/** addStudent
 * Adds a new student to the database and to a faculty member's advisee list.
 * @param student the student to add to the database.
 */
void Database::addStudent(Student* student) {
    Faculty *advisor = findFacultyByID(student->getAdvisorID());
    if (advisor == nullptr) {
        std::cout << "Faculty ID not found in database. Student has not been added." << std::endl;
        return;
    }
    advisor->addAdvisee(student->getID());
    studentTree->insert(*student);
}

/** deleteStudent
 * Deletes the student from the database and from their faculty member's advisee list.
 * @param studentID the ID of the student to delete.
 */
void Database::deleteStudent(int studentID) {
    Student* student = findStudentByID(studentID);
    Faculty* advisor = findFacultyByID(student->getAdvisorID());
    advisor->removeAdvisee(studentID);
    studentTree->remove(*student);
}

/** addFaculty
 * Adds a new faculty member to the database.
 * @param faculty the faculty member to add to the database.
 */
void Database::addFaculty(Faculty* faculty) {
    facultyTree->insert(*faculty);
}

/** deleteFaculty
 * Deletes the faculty member from the database and removes them as advisor from all their advisees.
 * @param facultyID the ID of the faculty member to delete.
 */
void Database::deleteFaculty(int facultyID) {
    Faculty* faculty = findFacultyByID(facultyID);
    if (faculty == nullptr) {
        std::cout << "Faculty ID not found in database." << std::endl;
        return;
    }
    int numAdvisees = faculty->getAdviseeIDs()->getSize();
    for (int i = 0; i < numAdvisees; i++) {
        int currStudentID = faculty->getAdviseeIDs()->get(i);
        Student* student = findStudentByID(currStudentID);
        student->setAdvisorID(-1);
    }
    facultyTree->remove(*faculty);
}

/** studentExists
 * Checks if a student with the given ID exists in the database.
 * @param studentID the ID of the student to check.
 * @return true if the student exists, false otherwise.
 */
bool Database::studentExists(int studentID) {
    Student* tempStudent = new Student(studentID);
    return studentTree->contains(*tempStudent);
}

/** facultyExists
 * Checks if a faculty member with the given ID exists in the database.
 * @param facultyID the ID of the faculty member to check.
 * @return true if the faculty member exists, false otherwise.
 */
bool Database::facultyExists(int facultyID) {
    Faculty* tempFaculty = new Faculty(facultyID);
    return facultyTree->contains(*tempFaculty);
}

/** logToFile
 * Logs the contents of the student and faculty trees to a file.
 */
void Database::logToFile() {
    std::ofstream file;
    file.open("databaseTables.txt", std::ios::out);
    file << "Student Table:" << std::endl;
    studentTree->printToFile(file);
    file << std::endl << "Faculty Table:" << std::endl;
    facultyTree->printToFile(file);
    file.close();
}
