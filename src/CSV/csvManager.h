#pragma once

#include <vector>
#include "../BinSearchSortTree/binstree.h"
#include "rapidcsv.h"

class csvManager {
private:
    rapidcsv::Document db;
    BST *tree;
public:
    explicit csvManager(BST *);

    virtual ~csvManager();

    void readFile();
    void writeFile();
};
