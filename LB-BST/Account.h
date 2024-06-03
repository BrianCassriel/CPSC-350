// Account Class Header
// Created by Brian Cassriel on 11/4/23.
// The Account class represents is a generalization of the Student and Faculty classes.
// It is designed to reduce code duplication in the codebase.

#ifndef LB_BST_ACCOUNT_H
#define LB_BST_ACCOUNT_H

#include <string>

class Account {
public:
    bool operator==(const Account& o);
    bool operator!=(const Account& o);
    bool operator<(const Account& o);
    bool operator>(const Account& o);
    bool operator<=(const Account& o);
    bool operator>=(const Account& o);
    friend std::ostream& operator<<(std::ostream& os, const Account& obj);

    int getNextID();
    int getID();
    std::string getName();
    std::string getLevel();
    void setName(std::string name);
    void setLevel(std::string level);
protected:
    int ID;
    std::string name;
    std::string level;
private:
    static int lastID;
};

#endif //LB_BST_ACCOUNT_H
