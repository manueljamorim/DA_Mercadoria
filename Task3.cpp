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

int partition(int arr[], int start, int end)
{

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i] <= pivot)
            count++;
    }

    // posição correta pivot
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    // ordena parte da esquerda e da direita dividido pelo pivot
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex)
    {

        while (arr[i] <= pivot)
        {
            i++;
        }

        while (arr[j] > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(int arr[], int start, int end)
{

    // caso base
    if (start >= end)
        return;

    int p = partition(arr, start, end);

    // ordenar parte da esquerda
    quickSort(arr, start, p - 1);

    // ordenar parte da direita
    quickSort(arr, p + 1, end);
}

float task3()
{

    string line;
    string garbage;

    int time_cap = (8 * 3600);

    int nline = -1; // iniciado a menos um pois não tirei a primeira linha no contadora de linhas

    ifstream MyReadFile("encomendas.txt");
    ifstream Garb("encomendas.txt");

    getline(MyReadFile, line); // eliminar 1º linha

    while (getline(Garb, garbage)) // conta as linhas
    {

        nline++;
    }

    int vtempo[nline];
    int v_cont = 0;

    while (getline(MyReadFile, line)) // ler linha a linha
    {

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

    quickSort(vtempo, 0, tam - 1); // vetor ja esta ordenado

    int res = 0; // numero de encomendas realizadas
    int sum = 0; // soma do tempo gasto nas entregas

    while (sum + vtempo[res] <= time_cap)
    {

        sum = sum + vtempo[res];

        res++;
    }

    cout << sum << '\n';

    return (float)sum / (float)res;
}
