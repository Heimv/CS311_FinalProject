//
// Created by Victor on 5/7/2020.
//

#pragma once
#include <iostream>

using namespace std;

class GenerateId {
    static GenerateId *instance;
    int id;
    GenerateId();
public:
    static GenerateId *getInstance();
    int getId();
};