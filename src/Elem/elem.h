// CS311 Yoshii - el_t for HW8 Hash Table
// Element type of a list node is defined here
// el_t can be changed by the client to fit its needs
//-----------------------------------------------------

#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <QDate>
#include <map>
#include "generateId.h"

class BST;

using namespace std;

typedef QDate date;
typedef QDateTime dateTime;

class Elem_t {
public:
    enum importance {
        URGENT_IMPORTANT,
        URGENT_NOT_IMPORTANT,
        NOT_URGENT_IMPORTANT,
        NOT_URGENT_NOT_IMPORTANT,
        UNDEFINED
    };

    enum ElemType {
        ID,
        IMPORTANCE,
        TITLE,
        DONE,
        DUEDATE,
        REMINDERDATE,
    };

    Elem_t();  // to create a blank el_t object
    Elem_t(const Elem_t &);
    explicit Elem_t(int, BST *);
    explicit Elem_t(bool, BST *);
    explicit Elem_t(importance, BST *);
    explicit Elem_t(std::string &, BST *);
    Elem_t(bool done, importance, string, string, QDate, QDateTime, BST *); // to create an initialized el_t object
    int Id;
    importance Importance;
    string Title;
    string Description;
    bool Done;
    date DueDate;
    dateTime ReminderDate;
    bool operator==(Elem_t &);  // overload == for search
    bool operator!=(Elem_t &);  // overload != for search
    bool operator<(const Elem_t &rhs) const;
    bool operator>(const Elem_t &rhs) const;
    bool operator<=(const Elem_t &rhs) const;
    bool operator>=(const Elem_t &rhs) const;
    // In search == is used to compare node elements
    // but what does it mean for this client to compare
    // node elements?

    // this overloads cout for the el_t object
    // This is a friend function since the receiver object is not el_t
    friend ostream &operator<<(ostream &, const Elem_t &);
private:
    BST *parent;
};

