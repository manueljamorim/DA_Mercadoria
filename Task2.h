#ifndef DA_MERCADORIA_TASK2_H
#define DA_MERCADORIA_TASK2_H

#include <ilcplex/ilocplex.h>
#include <algorithm>

#include "LoadData.h"


class Task2 {
	LoadData data;

public:
	Task2() {};
	void test_1();
	void test_2();
	void test_random(LoadData data);
	void test_original(LoadData& data);
	void print_entry_data();
	int solve();

};
#endif  DA_MERCADORIA_TASK2_H
