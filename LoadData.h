#ifndef DA_MERCADORIA_LOADDATA_H
#define DA_MERCADORIA_LOADDATA_H

#include <iostream>
#include <fstream>
#include "vector"

using namespace std;


class LoadData{
    vector<vector<int>> carrinhas; //volMax pesoMax custo
    vector<vector<int>> encomendas; //volume peso recompensa duração(s)
    vector<string> split(const string &s,const string &del);

    public:
    void loadCarrinhas();
    void loadEncomendas();



};


#endif //DA_MERCADORIA_LOADDATA_H
