// Student Class Implementation
// Created by Brian Cassriel on 11/3/23.
// The Student class represents a student's file in the database.
// It provides useful methods for interacting with the student's data.

#include "Student.h"

/** Constructor
 * Initializes the student's data to default values.
 * The ID is set to the next available ID.
 */
Student::Student() {
    ID = getNextID();
    name = "unnamed";
    level = "unknown";
    major = "undeclared";
    gpa = 0.0;
    advisorID = -1;
}

/** Overloaded Constructor
 * Initializes the student's data to default values, except with a custom studentID.
 * @param ID - the ID to assign to the student
 */
Student::Student(int ID) {
    this->ID = ID;
    name = "unnamed";
    level = "unknown";
    major = "undeclared";
    gpa = 0.0;
    advisorID = -1;
}

/** Overloaded Constructor
 * Initializes the student's data to the provided values.
 * The ID is set to the next available ID.
 * @param name - the student's name as a string
 * @param level - the student's academic level as a string
 * @param major - the student's major as a string
 * @param gpa - the student's GPA as a double
 * @param advisorID - the ID of the student's advisor as an int
 */
Student::Student(std::string name, std::string level, std::string major, double gpa, int advisorID) {
    ID = getNextID();
    this->name = name;
    this->level = level;
    this->major = major;
    this->gpa = gpa;
    this->advisorID = advisorID;
}

/** Destructor
 * Unused.
 */
Student::~Student() {

}

/** Overloaded Insertion Operator
 * Passes the student's data to the provided output stream.
 * @param os - the output stream to print to
 * @param obj - the student to print
 * @return - the output stream
 */
std::ostream& operator<<(std::ostream& os, const Student &obj) {
    os << obj.name
        << " (ID: " << obj.ID << ')'
        << " is a " << obj.level
        << " majoring in " << obj.major
        << " with a GPA of " << obj.gpa;
    if (obj.advisorID == -1)
        os << " and has no advisor.";
    else
        os << " and is advised by " << obj.advisorID << ".";
    return os;
}

/** getMajor
 * @return - the student's major as a string
 */
std::string Student::getMajor() {
    return major;
}

/** getGPA
 * @return - the student's GPA as a double
 */
double Student::getGPA() {
    return gpa;
}

/** getAdvisorID
 * @return - the ID of the student's advisor as an int
 */
int Student::getAdvisorID() {
    return advisorID;
}

/** setMajor
 * @param major - the student's major as a string
 */
void Student::setMajor(std::string major) {
    this->major = major;
}

/** setGPA
 * @param gpa - the student's GPA as a double
 */
void Student::setGPA(double gpa) {
    this->gpa = gpa;
}

/** setAdvisorID
 * @param advisorID - the ID of the student's advisor as an int
 */
void Student::setAdvisorID(int advisorID) {
    this->advisorID = advisorID;
}
