#include <iostream>
#include <filesystem>
#include "LoadData.h"
#include "Task1.h"
#include "Task2.h"


void task1_menu(LoadData td) {
    return;
}

void task2_menu(LoadData ld) {
    Task2 td;
    char input;

    cout << setfill('-') << setw(10) << "" << "TASK 2" << setw(10) << "" << endl;
    cout << "1. Sample Test 1" << endl;
    cout << "2. Sample Test 2" << endl;
    cout << "3. Random Data Test" << endl;
    cout << "4. Original Dataset Test" << endl;
    cout << "Choose which test to run (0 to return): ";
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (input) {
    case '0':
        return;
    case '1':
        td.test_1();
        break;
    case '2':
        td.test_2();
        break;
    case '3':
        td.test_random(ld);
        break;
    case '4':
        td.test_original(ld);
        break;
    default:
        cout << "Invalid input" << endl;
        break;
    }
    return;
}

void task3_menu(LoadData ld) {
    return;
}

int main() {
    srand(time(NULL));

    LoadData ld;
    ld.loadCarrinhas();
    ld.loadEncomendas();

    char input;
    do {
        cout << "Choose which task to run (1-3, 0 to exit): ";
        cin >> input;

        switch (input) {
        case '0':
            return 0;
            break;
        case '1':
            task1_menu(ld);
            break;
        case '2':
            task2_menu(ld);
            break;
        case '3':
            task3_menu(ld);
            break;
        default:
            cout << "Invalid input" << endl;
            break;
        }
    } while (true);

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

