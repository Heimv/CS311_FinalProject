//
// Created by Victor on 5/11/2020.
//

#include <sys/stat.h>
#include "csvManager.h"

bool toBool(const std::string& str) {
    return str == "true" || str == "1";
}

Elem_t::importance toImportance(const std::string& str) {
    switch (stoi(str)) {
        case 0:
            return Elem_t::URGENT_IMPORTANT;
        case 1:
            return Elem_t::URGENT_NOT_IMPORTANT;
        case 2:
            return Elem_t::NOT_URGENT_IMPORTANT;
        case 3:
            return Elem_t::NOT_URGENT_NOT_IMPORTANT;
        default:
            return Elem_t::UNDEFINED;
    }
}

Elem_t::ElemType toElemType(const std::string &str) {
    switch (stoi(str)) {
        case 0:
            return Elem_t::ID;
        case 1:
            return Elem_t::IMPORTANCE;
        case 2:
            return Elem_t::TITLE;
        case 3:
            return Elem_t::DONE;
        case 4:
            return Elem_t::DUEDATE;
        case 5:
            return Elem_t::REMINDERDATE;
        default:
            return Elem_t::TITLE;
    }
}

csvManager::csvManager(BST *initialTree) : tree(initialTree) {
    struct stat buffer;

    if (stat("db.csv", &buffer) != 0) {
        cerr << "file not found" << endl;
    }
    db = rapidcsv::Document("db.csv");
    readFile();
}

csvManager::~csvManager() {
    writeFile();
}

bool checkEmpty(std::vector<std::string> &tmp) {
    return (tmp[0].empty() || tmp[0].empty());
}

void csvManager::readFile() {
    std::vector<std::string> tmp;
    std::string elemType;

    cout << "reading the file" << endl;
    try {
        elemType = db.GetColumnName(0);
        tree->setType(toElemType(elemType), false);
    } catch (const std::out_of_range &e) {
        tree->setType(Elem_t::TITLE, false);
    }
    //TODO read first line as header that contain the sorting method to apply at start
    for (size_t i = 0; i < db.GetRowCount(); ++i) {
        tmp = db.GetRow<std::string>(i);
        if (checkEmpty(tmp))
            continue;
        cout << QString::fromStdString(tmp[5]).toStdString() << endl;
        tree->InsertVertex(new Elem_t(
                toBool(tmp[0]),
                toImportance(tmp[1]),
                tmp[2],
                tmp[3],
                QDate::fromString(QString::fromStdString(tmp[4])),
                QDateTime::fromString(QString::fromStdString(tmp[5])),
                tree
        ));
    }
}

void csvManager::writeFile() {
    size_t idx = 1;
    fstream f = fstream("db.csv", ios::out | ios::trunc);
    f.close();
    std::vector<Elem_t*> *tmp = tree->getOrderdNodes();
    std::vector<std::string> elemAsString = std::vector<std::string>();

    cout << "writing to the file" << endl;
    for (const Elem_t *elem: *tmp) {
        elemAsString.push_back(std::to_string(elem->Done));
        elemAsString.push_back(std::to_string(elem->Importance));
        elemAsString.push_back(elem->Title);
        elemAsString.push_back(elem->Description);
        elemAsString.push_back(elem->DueDate.toString().toStdString());
        elemAsString.push_back(elem->ReminderDate.toString().toStdString());
        db.SetRow<std::string>(idx, elemAsString);
        elemAsString.clear();
        idx++;
    }
    try {
        db.SetColumnName(0, std::to_string(tree->getType()));
    } catch (const std::out_of_range &e) {
        cout << e.what() << endl;
    }
    db.Save("db.csv");
}
