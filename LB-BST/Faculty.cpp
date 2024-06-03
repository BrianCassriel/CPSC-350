// Faculty Class Implementation
// Created by Brian Cassriel on 11/3/23.
// The Faculty class represents a faculty member's file in the database.
// It provides useful methods for interacting with the faculty member's data.

#include <iostream>
#include "Faculty.h"

/** Constructor
 * Initializes the faculty member to have no advisees.
 */
Faculty::Faculty() {
    ID = getNextID();
    name = "unnamed";
    level = "lecturer";
    department = "undeclared";
    adviseeIDs = new DoublyLinkedList<int>();
}

/** Overloaded Constructor
 * Initializes the faculty member to have a custom ID.
 * @param ID - the ID of the faculty member
 */
Faculty::Faculty(int ID) {
    this->ID = ID;
    name = "unnamed";
    level = "lecturer";
    department = "undeclared";
    adviseeIDs = nullptr;
}

/** Overloaded Constructor
 * Initializes the faculty member to have no advisees.
 * @param name - the name of the faculty member
 * @param level - the level of the faculty member
 * @param department - the department of the faculty member
 */
Faculty::Faculty(std::string name, std::string level, std::string department) {
    ID = getNextID();
    this->name = name;
    this->level = level;
    this->department = department;
    this->adviseeIDs = new DoublyLinkedList<int>();
}

/** Destructor
 * Deletes the faculty member's advisee list.
 */
Faculty::~Faculty() {
//    delete adviseeIDs;
}

/** Overloaded Insertion Operator
 * Passes the faculty member's information to the output stream.
 * @param os - the output stream
 * @param obj - the faculty member
 * @return - the output stream
 */
std::ostream& operator<<(std::ostream& os, const Faculty &obj) {
    os << obj.name
       << " (ID: " << obj.ID << ')'
       << " is a " << obj.level
       << " in the " << obj.department;
    if (obj.adviseeIDs->getSize() > 0) {
        os << " department and advises the following students: ";
        int size = obj.adviseeIDs->getSize();
        for (int i = 0; i < size; i++) {
            os << obj.adviseeIDs->get(i);
            if (i < size - 1)
                os << ", ";
        }
        os << ".";
    } else {
        os << " department and does not advise any students.";
    }
    return os;
}

/** getDepartment
 * @return the department of the faculty member
 */
std::string Faculty::getDepartment() {
    return department;
}

/** getAdviseeIDs
 * @return the list of advisee IDs
 */
DoublyLinkedList<int>* Faculty::getAdviseeIDs() {
    return adviseeIDs;
}

/** setDepartment
 * Sets the department of the faculty member.
 * @param department - the department of the faculty member
 */
void Faculty::setDepartment(std::string department) {
    this->department = department;
}

/** addAdvisee
 * Adds a student to the faculty member's advisee list.
 * @param studentID - the ID of the student to add
 */
void Faculty::addAdvisee(int studentID) {
    adviseeIDs->append(studentID);
}

/** removeAdvisee
 * Removes a student from the faculty member's advisee list if the student exists.
 * @param studentID - the ID of the student to remove
 */
void Faculty::removeAdvisee(int studentID) {
    if (adviseeIDs->find(studentID) != -1)
        adviseeIDs->remove(adviseeIDs->find(studentID));
    else
        std::cout << "Student ID not found in faculty advisee list." << std::endl;
}
