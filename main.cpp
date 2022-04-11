#include <iostream>
#include "LoadData.h"
#include "Task1.h"


int main() {
    LoadData ld;
    ld.loadCarrinhas();
    ld.loadEncomendas();
    
    Task1 t1(ld);
    t1.Solver();
}

