#ifndef DA_MERCADORIA_LOADDATA_H
#define DA_MERCADORIA_LOADDATA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "vector"

using namespace std;

class Carrinha{
public:
    Carrinha(int v, int p, int c, int id) : volMax(v), pesoMax(p), custo(c), id_c(id) {};
    int volMax, pesoMax, custo;
    bool used = 0;
    int id_c;
};

class Encomenda{
public:
    Encomenda(int v, int p, int r, int d, int id) : volume(v), peso(p), recompensa(r), duracao(d), id_e(id) {};
    int volume, peso, recompensa, duracao;
    int id_carrinha_mae;
    int id_e;

};


class LoadData{


public:
    vector<Carrinha> carrinhas; //volMax pesoMax custo
    vector<Encomenda> encomendas; //volume peso recompensa duração(s)

    void loadCarrinhas();
    void loadEncomendas();

};


#endif //DA_MERCADORIA_LOADDATA_H
