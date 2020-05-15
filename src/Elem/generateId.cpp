//
// Created by Victor on 5/7/2020.
//

#include "generateId.h"

GenerateId *GenerateId::instance = nullptr;

GenerateId::GenerateId() {
    id = 0;
}

GenerateId *GenerateId::getInstance() {
    if (!instance)
        instance = new GenerateId;
    return instance;
}

int GenerateId::getId() {
    return (this->id++);
}