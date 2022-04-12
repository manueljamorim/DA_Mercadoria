#ifndef DA_MERCADORIA_TASK2_H
#define DA_MERCADORIA_TASK2_H

#include <ilcplex/ilocplex.h>

#include "LoadData.h"


class Task2 {
	LoadData data;

public:
	Task2(vector<Carrinha> carrinhas, vector<Encomenda> encomendas) { this->data.carrinhas = carrinhas, this->data.encomendas = encomendas; };
	Task2(LoadData& ld) { this->data = ld; };
	int solve();

};
#endif  DA_MERCADORIA_TASK2_H
