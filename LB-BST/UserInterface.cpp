// User Interface Class Implementation
// Created by Brian Cassriel on 11/8/23.
// This class is responsible for displaying the menu and getting user input.
// It also calls the appropriate methods in the Database class to perform the requested operations.

#include "UserInterface.h"

/** Constructor
 * Initializes the database.
 */
UserInterface::UserInterface() {
    database = new Database();
    running = true;
}

/** Destructor
 * Deletes the database.
 */
UserInterface::~UserInterface() {
    delete database;
}

/** isRunning
 * @return true if the user has not selected the exit option, false otherwise.
 */
bool UserInterface::isRunning() {
    return running;
}

/** displayMenu
 * Displays the menu options to the user.
 */
void UserInterface::displayMenu() {
    std::cout << "--- Menu ---" << std::endl;
    std::cout << "1. Display all students" << std::endl;
    std::cout << "2. Display all faculty" << std::endl;
    std::cout << "3. Find student" << std::endl;
    std::cout << "4. Find faculty" << std::endl;
    std::cout << "5. Add new student" << std::endl;
    std::cout << "6. Delete a student" << std::endl;
    std::cout << "7. Add new faculty member" << std::endl;
    std::cout << "8. Delete a faculty member" << std::endl;
    std::cout << "9. Change a student’s advisor" << std::endl;
    std::cout << "10. Remove an advisee from a faculty member" << std::endl;
    std::cout << "11. Exit" << std::endl;
}

/** doUserSelection
 * Calls the appropriate method after getting the user's selection.
 */
void UserInterface::doUserSelection() {
    int selected = getUserSelection();
    switch (selected) {
        case 1:
            displayAllStudents();
            break;
        case 2:
            displayAllFaculty();
            break;
        case 3:
            findStudent();
            break;
        case 4:
            findFaculty();
            break;
        case 5:
            addStudent();
            break;
        case 6:
            deleteStudent();
            break;
        case 7:
            addFaculty();
            break;
        case 8:
            deleteFaculty();
            break;
        case 9:
            changeAdvisor();
            break;
        case 10:
            removeAdvisee();
            break;
        case 11:
            running = false;
            database->logToFile();
            break;
        default:
            std::cout << "Invalid input. Please try again." << std::endl;
            break;
    }
}

/** getUserSelection
 * Gets the user's selection from the menu as a terminal prompt.
 * @return the user's selection as an integer.
 */
int UserInterface::getUserSelection() {
    int input;
    std::cout << "Please enter your selection (1-11): ";
    std::cin >> input;
    if (input > 0 && input < 12)
        return input;
    else {
        std::cout << "Invalid input. Please try again." << std::endl;
        return getUserSelection();
    }
}

/** getStudentIDFromUser
 * Asks the user for a student ID through a terminal prompt.
 * @return the student's ID as an integer.
 */
int UserInterface::getStudentIDFromUser() {
    int ID;
    std::cout << "Please enter the student's ID: ";
    std::cin >> ID;
    return ID;
}

/** getFacultyIDFromUser
 * Asks the user for a faculty ID through a terminal prompt.
 * @return the faculty's ID as an integer.
 */
int UserInterface::getFacultyIDFromUser() {
    int ID;
    std::cout << "Please enter the faculty's ID: ";
    std::cin >> ID;
    return ID;
}

/** displayAllStudents
 * Prints all students in the database to the terminal.
 */
void UserInterface::displayAllStudents() {
    std::cout << "All students:" << std::endl;
    database->getStudentTree()->printTreeInOrder();
}

/** displayAllFaculty
 * Prints all faculty in the database to the terminal.
 */
void UserInterface::displayAllFaculty() {
    std::cout << "All faculty:" << std::endl;
    database->getFacultyTree()->printTreeInOrder();
}

/** findStudent
 * Finds a student in the database by ID and prints their information to the terminal.
 */
void UserInterface::findStudent() {
    int ID = getStudentIDFromUser();
    Student* student = database->findStudentByID(ID);
    if (student != nullptr)
        std::cout << *student << std::endl;
    else
        std::cout << "Student ID not found in database." << std::endl;
}

/** findFaculty
 * Finds a faculty member in the database by ID and prints their information to the terminal.
 */
void UserInterface::findFaculty() {
    int ID = getFacultyIDFromUser();
    Faculty* faculty = database->findFacultyByID(ID);
    if (faculty != nullptr)
        std::cout << *faculty << std::endl;
    else
        std::cout << "Faculty ID not found in database." << std::endl;
}

/** addStudent
 * Asks the user for information about a new student and then adds them to the database.
 */
void UserInterface::addStudent() {
    std::string name;
    std::string level;
    std::string major;
    double gpa;
    int advisorID;
    std::cout << "Please enter the student's name (string): ";
    std::cin >> name;
    std::cout << "Please enter the student's level (string): ";
    std::cin >> level;
    std::cout << "Please enter the student's major (string): ";
    std::cin >> major;
    std::cout << "Please enter the student's GPA (double): ";
    std::cin >> gpa;
    std::cout << "Please enter the student's advisor's ID (integer): ";
    std::cin >> advisorID;
    if (!database->facultyExists(advisorID)) {
        cout << "Faculty ID not found in database. Student has not been added." << endl;
        return;
    }
    Student* student = new Student(name, level, major, gpa, advisorID);
    database->addStudent(student);
    cout << "Student (" << student->getID() << ") added." << endl;
}

/** deleteStudent
 * Asks the user for a student ID and then deletes that student from the database.
 */
void UserInterface::deleteStudent() {
    int ID = getStudentIDFromUser();
    database->deleteStudent(ID);
    cout << "Student (" << ID << ") deleted." << endl;
}

/** addFaculty
 * Asks the user for information about a new faculty member and then adds them to the database.
 */
void UserInterface::addFaculty() {
    std::string name;
    std::string level;
    std::string department;
    std::cout << "Please enter the faculty member's name (string): ";
    std::cin >> name;
    std::cout << "Please enter the faculty member's level (string): ";
    std::cin >> level;
    std::cout << "Please enter the faculty member's department (string): ";
    std::cin >> department;
    Faculty* faculty = new Faculty(name, level, department);
    database->addFaculty(faculty);
    cout << "Faculty member (" << faculty->getID() << ") added." << endl;
}

/** deleteFaculty
 * Asks the user for a faculty ID and then deletes that faculty member from the database.
 */
void UserInterface::deleteFaculty() {
    int ID = getFacultyIDFromUser();
    database->deleteFaculty(ID);
    cout << "Faculty member (" << ID << ") deleted." << endl;
}

/** changeAdvisor
 * Asks the user for a student ID and a faculty ID and then changes the student's advisor to the faculty member.
 * This method removed the old advisor from the student and also adds the student to the new advisor's advisee list.
 */
void UserInterface::changeAdvisor() {
    int studentID = getStudentIDFromUser();
    if (!database->studentExists(studentID)) {
        cout << "Student ID not found in database." << endl;
        return;
    }
    int newAdvisorID = getFacultyIDFromUser();
    if (!database->facultyExists(newAdvisorID)) {
        cout << "Faculty ID not found in database." << endl;
        return;
    }
    Student* student = database->findStudentByID(studentID);
    Faculty* oldAdvisor = database->findFacultyByID(student->getAdvisorID());
    Faculty* newAdvisor = database->findFacultyByID(newAdvisorID);
    if (oldAdvisor != nullptr) {
        oldAdvisor->removeAdvisee(studentID);
    }
    student->setAdvisorID(newAdvisorID);
    newAdvisor->addAdvisee(studentID);
    cout << "Student (" << studentID << ") now advised by faculty member (" << newAdvisorID << ")." << endl;
}

/** removeAdvisee
 * Asks the user for a faculty ID and a student ID and then removes the student from the faculty member's advisee list.
 * This method also removes the student's advisor.
 */
void UserInterface::removeAdvisee() {
    int adviseeID = getStudentIDFromUser();
    if (!database->studentExists(adviseeID)) {
        cout << "Student ID not found in database." << endl;
        return;
    }
    Student* advisee = database->findStudentByID(adviseeID);
    int advisorID = advisee->getAdvisorID();
    Faculty* advisor = database->findFacultyByID(advisorID);
    advisor->removeAdvisee(adviseeID);
    advisee->setAdvisorID(-1);
    cout << "Student (" << adviseeID << ") is no longer advised by faculty member (" << advisorID << ")." << endl;
}

/** addDefaultData
 * Adds default data to the database for testing purposes.
 */
void UserInterface::addDefaultData() {
    database->addFaculty(new Faculty("John Smith", "Professor", "CS"));
    database->addFaculty(new Faculty("Jane Smith", "Professor", "Business"));
    database->addFaculty(new Faculty("Bob Doe", "Associate", "Analytics"));
    database->addStudent(new Student("Brian Cassriel", "Senior", "CS", 3.9, 1));
    database->addStudent(new Student("John Doe", "Freshman", "Analytics", 3.2, 3));
    database->addStudent(new Student("Jane Doe", "Junior", "Business", 3.5, 9));
    database->addStudent(new Student("Bob Smith", "Senior", "CS", 3.8, 1));
    database->addStudent(new Student("Billy Bob", "Sophomore", "CS", 3.1, 3));
    database->addStudent(new Student("Joe Schmoe", "Freshman", "Business", 3.0, 9));
}
