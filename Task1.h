#ifndef DA_MERCADORIA_TASK1_H
#define DA_MERCADORIA_TASK1_H


#include "LoadData.h"

class Task1 {
    LoadData loadData;

    public:
    Task1(LoadData& ld){this->loadData = ld;};
    int Greedy();


};


#endif //DA_MERCADORIA_TASK1_H
