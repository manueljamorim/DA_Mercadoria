#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdio.h>
using namespace std;
#include "vector"
// Objetivo: minimizar a média de tempo de entrega, ou seja, maximizar o número de entregas no espaço de tempo disponivel

// ordenar por ordem crescente de tempo e depois somar os tempos até dar (8h * 3600s)

//! Print array.
void vint_print(int a[], int size)
{

    cout << "[ ";
    for (int i = 0; i < size; i++)
        cout << a[i] << " ";
    cout << "]";
    cout << endl;
}

float task3()
{

    string line;
    string garbage;
    string space_delimiter = " ";

    int time_cap = (8 * 3600);

    int nline = -1; // iniciado a menos um pois não tirei a primeira linha no contadora de linhas

    ifstream MyReadFile("encomendas.txt");
    ifstream Garb("encomendas.txt");

    getline(MyReadFile, line); // eliminar 1º linha

    while (getline(Garb, garbage))
    { // conta as linhas

        nline++;
    }

    int vtempo[nline];
    int v_cont = 0;

    while (getline(MyReadFile, line))
    { // ler linha a linha

        string word = "";

        for (auto x : line)
        {

            if (x == ' ')
            {
                word = "";
            }

            else
            {

                word = word + x;
            }
        }

        vtempo[v_cont] = stoi(word);

        v_cont++;
    }

    int tam = sizeof(vtempo) / sizeof(int); // numero de elemntos do vetor

    // cout << "Antes" << '\n';
    // vint_print(vtempo, tam);

    // ordenar----------------------------------------------------------
    int prev, next, aux;

    for (prev = 0; prev < tam - 1; prev++)
        for (next = prev + 1; next < tam; next++)
        {
            aux = vtempo[prev];

            if (vtempo[next] < vtempo[prev])
            {
                vtempo[prev] = vtempo[next];
                vtempo[next] = aux;
            }
        }

    // vetor ja esta ordenado

    // cout << "Depois" << '\n';
    // vint_print(vtempo, tam);

    int res = 0; // numero de encomendas realizadas
    int sum = 0;

    while (sum <= time_cap)
    {

        sum = sum + vtempo[res];

        res++;
    }



    return (float)time_cap/(float)res;
}
