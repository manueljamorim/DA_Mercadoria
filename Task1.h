#ifndef DA_MERCADORIA_TASK1_H
#define DA_MERCADORIA_TASK1_H


#include "LoadData.h"
#include <algorithm>
#include <map>
#include <iostream>
#include <numeric>
#include <vector>


class Task1 {
    LoadData loadData;

    
    public:
    Task1(LoadData& ld){this->loadData = ld;};
    int Greedy();
    vector<bool> carrinhas_usadas;
    map<int, vector<Encomenda>> carrinha_encomendas;
    
    int Solver();

    
};


#endif //DA_MERCADORIA_TASK1_H
