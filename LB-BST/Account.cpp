// Account Class Implementation
// Created by Brian Cassriel on 11/4/23.
// The Account class represents is a generalization of the Student and Faculty classes.
// It is designed to reduce code duplication in the codebase.

#include <ostream>
#include "Account.h"

/** lastID variable initialization
 * This variable is used to keep track of the last ID used for an account.
 * Putting this declaration here means that it will be initialized to 0 when the Account class is first used, but not again on repeated uses.
 */
int Account::lastID = 0;

/** getNextID
 * This method returns the next ID to be used for an account
 */
int Account::getNextID() {
    return ++lastID;
}

/** getID
 * @return - and int representing the ID of the account
 */
int Account::getID() {
    return this->ID;
}

/** getName
 * @return - a string representing the name of the account
 */
std::string Account::getName() {
    return this->name;
}

/** getLevel
 * @return - a string representing the level of the account
 */
std::string Account::getLevel() {
    return this->level;
}

/** setName
 * @param name - a string representing the name of the account
 */
void Account::setName(std::string name) {
    this->name = name;
}

/** setLevel
 * @param level - a string representing the level of the account
 */
void Account::setLevel(std::string level) {
    this->level = level;
}

/** == operator overload
 * Allows comparison of two accounts by their ID
 * @param o - the account to compare to
 * @return true if the accounts have the same ID, false otherwise
 */
bool Account::operator==(const Account &o) {
    if (this->ID == o.ID)
        return true;
    return false;
}

/** != operator overload
 * Allows comparison of two accounts by their ID
 * @param o - the account to compare to
 * @return true if the accounts have different IDs, false otherwise
 */
bool Account::operator!=(const Account &o) {
    if (this->ID != o.ID)
        return true;
    return false;
}

/** < operator overload
 * Allows comparison of two accounts by their ID
 * @param o - the account to compare to
 * @return true if the account on the left has a lower ID than the account on the right, false otherwise
 */
bool Account::operator<(const Account &o) {
    if (this->ID < o.ID)
        return true;
    return false;
}

/** > operator overload
 * Allows comparison of two accounts by their ID
 * @param o - the account to compare to
 * @return true if the account on the left has a higher ID than the account on the right, false otherwise
 */
bool Account::operator>(const Account &o) {
    if (this->ID > o.ID)
        return true;
    return false;
}

/** <= operator overload
 * Allows comparison of two accounts by their ID
 * @param o - the account to compare to
 * @return true if the account on the left has a lower or equal ID than the account on the right, false otherwise
 */
bool Account::operator<=(const Account &o) {
    if (this->ID <= o.ID)
        return true;
    return false;
}

/** >= operator overload
 * Allows comparison of two accounts by their ID
 * @param o - the account to compare to
 * @return true if the account on the left has a higher or equal ID than the account on the right, false otherwise
 */
bool Account::operator>=(const Account &o) {
    if (this->ID >= o.ID)
        return true;
    return false;
}

/** << operator overload
 * Allows printing of an account to an output stream
 * @param os - the output stream to print to
 * @param obj - the account to print
 * @return the output stream
 */
std::ostream& operator<<(std::ostream &os, const Account &obj) { // https://stackoverflow.com/questions/2981836/how-can-i-use-cout-myclass
    return os << obj.ID << " " << obj.name << " " << obj.level;
}
