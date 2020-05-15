// CS311 Yoshii - el_t for HW8 Hash Table
// Element type of a list node is defined here
// el_t can be changed by the client to fit its needs
//----------------------------------------------------

#include "elem.h"

#include <utility>
#include "../BinSearchSortTree/binstree.h"

// blank element
Elem_t::Elem_t() :
        Importance(Elem_t::importance::UNDEFINED),
        Title(""),
        Description(""),
        Done(false),
        DueDate(QDate::currentDate()),
        ReminderDate(QDateTime::currentDateTime()),
        parent(nullptr) {
    GenerateId *generator = GenerateId::getInstance();
    Id = generator->getId();
}

Elem_t::Elem_t(const Elem_t &prevElem) :
        Id(prevElem.Id),
        Importance(prevElem.Importance),
        Title(prevElem.Title),
        Description(prevElem.Description),
        Done(prevElem.Done),
        DueDate(prevElem.DueDate),
        ReminderDate(prevElem.ReminderDate),
        parent(prevElem.parent) {}

Elem_t::Elem_t(int id, BST *parent) :
        Id(id),
        Importance(Elem_t::importance::UNDEFINED),
        Title(""),
        Description(""),
        Done(false),
        DueDate(QDate::currentDate()),
        ReminderDate(QDateTime::currentDateTime()),
        parent(parent) {
}

Elem_t::Elem_t(bool done, BST *parent) :
        Id(-1),
        Importance(Elem_t::importance::UNDEFINED),
        Title(""),
        Description(""),
        Done(done),
        DueDate(QDate::currentDate()),
        ReminderDate(QDateTime::currentDateTime()),
        parent(parent) {

}

Elem_t::Elem_t(Elem_t::importance importance, BST *parent) :
        Id(-1),
        Importance(importance),
        Title(""),
        Description(""),
        Done(false),
        DueDate(QDate::currentDate()),
        ReminderDate(QDateTime::currentDateTime()),
        parent(parent) {

}

Elem_t::Elem_t(std::string &str, BST *parent):
        Id(-1),
        Importance(Elem_t::importance::UNDEFINED),
        Title(str),
        Description(str),
        Done(false),
        DueDate(QDate::fromString(QString::fromStdString(str))),
        ReminderDate(QDateTime::fromString(QString::fromStdString(str))),
        parent(parent) {

}

// initializing constructor to create an el_t object
Elem_t::Elem_t(
        bool done,
        importance importance,
        string title,
        string description,
        QDate dueDate,
        QDateTime reminderDate,
        BST *parent) :
        Importance(importance),
        Title(std::move(title)),
        Description(std::move(description)),
        Done(done),
        DueDate(dueDate),
        ReminderDate(std::move(reminderDate)),
        parent(parent) {
    GenerateId *generator = GenerateId::getInstance();
    Id = generator->getId();
}

// overload == for search based on the key part only
bool Elem_t::operator==(Elem_t &rhs) {
    switch (parent->getType()) {
        case ID:
            return Id == rhs.Id;
        case IMPORTANCE:
            return Importance == rhs.Importance;
        case TITLE:
            return Title == rhs.Title;
        case DONE:
            return Done == rhs.Done;
        case DUEDATE:
            return DueDate == rhs.DueDate;
        case REMINDERDATE:
            return ReminderDate == rhs.ReminderDate;
        default:
            return false;
    }
}

// overload != for search based on the key part only
bool Elem_t::operator!=(Elem_t &rhs) {
    return !(*this == rhs);
}

bool Elem_t::operator<(const Elem_t &rhs) const {
    switch (parent->getType()) {
        case ID:
            return Id == rhs.Id;
        case IMPORTANCE:
            return Importance < rhs.Importance;
        case TITLE:
            return Title < rhs.Title;
        case DONE:
            return Done < rhs.Done;
        case DUEDATE:
            return DueDate < rhs.DueDate;
        case REMINDERDATE:
            return ReminderDate < rhs.ReminderDate;
        default:
            return false;
    }
}

bool Elem_t::operator>(const Elem_t &rhs) const {
    return rhs < *this;
}

bool Elem_t::operator<=(const Elem_t &rhs) const {
    return !(rhs < *this);
}

bool Elem_t::operator>=(const Elem_t &rhs) const {
    return !(*this < rhs);
}

ostream &operator<<(ostream &os, const Elem_t &E) {
    os << E.Id << " + " << E.Title;
    return os;
}