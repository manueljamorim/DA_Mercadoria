#include <iostream>
#include <filesystem>
#include "LoadData.h"
#include "Task1.h"
#include "Task2.h"

int main() {

    LoadData ld;
    ld.loadCarrinhas();
    ld.loadEncomendas();
    Task2 t2(ld);
    t2.solve(); // boa sorte se chamares esta função

    /*
    vector<Carrinha> carrinhas;
    carrinhas.push_back({ 5, 6, 10 });
    carrinhas.push_back({ 5, 6, 12 });
    vector<Encomenda> encomendas;
    encomendas.push_back({ 1, 1, 3, 1 });
    encomendas.push_back({ 2, 3, 8, 1 });
    encomendas.push_back({ 3, 1, 6, 1 });
    encomendas.push_back({ 2, 2, 4, 1 });
    encomendas.push_back({ 4, 3, 10, 1 });
    Task2 t2(carrinhas, encomendas);

    // resultado ótimo pra este exemplo é 5
    //  encomenda 1, 2 e 4 pra carrinha 1
    //      (3 + 8 + 4) - 10 = 5
    //  ou encomenda 2 e 3 pra carrinha 1 e encomenda 1 e 5 pra carrinha 2
    //      ((8 + 6) - 10) + ((10 + 3) - 12) = 5
    */

    Task2 t2(ld);
    t2.solve();
    /*
    Task1 t1(ld);
    cout << "Cenário 1: otimização do número de estafetas" << endl;
    cout << "--------------------------------------------\n" << endl;
    cout << "\t\tAlgoritmo Greedy:\n" << endl;
    cout << "Número de estafetas utilizado: " << t1.Greedy() << endl;
    

    cout << "Estafetas utilizados:" << endl;
    cout << "[ ";
    for(auto used: t1.carrinhas_usadas){
        cout << used << ", ";
    }
    cout << "]\n" << endl;
    
    for(auto it = t1.carrinha_encomendas.begin(); it!= t1.carrinha_encomendas.end(); it++){
        cout << "Estafeta " << it->first << ": (p_max: "<< ld.carrinhas[it->first].pesoMax << ")(v_max: "<<ld.carrinhas[it->first].volMax <<")";
        
        int p_ocupado = 0;
        int v_ocupado = 0;
        
        //cout << " [";
        for(auto& encomenda: it->second){
            //cout << encomenda.id_e << ", ";
            p_ocupado += encomenda.peso;
            v_ocupado += encomenda.volume;
        }
        //cout << "]";
        
        cout << "(p_ocup: "<< p_ocupado <<")(v_ocup: " << v_ocupado << ")" <<endl;
    }
    
    cout << "\n\t\tCplex (branch and bound + simplex):\n" << endl;
    LoadData ld2;
    ld2.loadCarrinhas();
    ld2.loadEncomendas();
    Task1 t1_2(ld);
    t1_2.Solver();
    
    cout << "Estafetas utilizados:" << endl;
    cout << "[ ";
    for(auto used: t1_2.carrinhas_usadas){
        cout << used << ", ";
    }
    cout << "]\n" << endl;
    
    for(auto it = t1_2.carrinha_encomendas.begin(); it!= t1_2.carrinha_encomendas.end(); it++){
        cout << "Estafeta " << it->first << ": (p_max: "<< ld.carrinhas[it->first].pesoMax << ")(v_max: "<<ld.carrinhas[it->first].volMax <<")";
        
        int p_ocupado = 0;
        int v_ocupado = 0;
        
        //cout << " [";
        for(auto& encomenda: it->second){
            //cout << encomenda.id_e << ", ";
            p_ocupado += encomenda.peso;
            v_ocupado += encomenda.volume;
        }
        //cout << "]";
        
        cout << "(p_ocup: "<< p_ocupado <<")(v_ocup: " << v_ocupado << ")" <<endl;
    }
    */
    return 0;
  
}

