#include <iostream>
#include "LoadData.h"
#include "Task1.h"


int main() {
    LoadData ld;
    ld.loadCarrinhas();
    ld.loadEncomendas();
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
}

