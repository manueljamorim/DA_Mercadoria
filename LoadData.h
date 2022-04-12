#ifndef DA_MERCADORIA_LOADDATA_H
#define DA_MERCADORIA_LOADDATA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "vector"

using namespace std;

class Carrinha{
public:
    int volMax, pesoMax, custo;
    bool used = 0;
    int id_c;
};

class Encomenda{
public:
    int volume, peso, recompensa, duracao;
    int id_carrinha_mae;
    int id_e;

};


class LoadData{


public:
    vector<Carrinha> carrinhas; //volMax pesoMax custo
    vector<Encomenda> encomendas; //volume peso recompensa duração(s)


    vector<string> split(const string &s,const string &del);

public:
    void loadCarrinhas();
    void loadEncomendas();



};


#endif //DA_MERCADORIA_LOADDATA_H
