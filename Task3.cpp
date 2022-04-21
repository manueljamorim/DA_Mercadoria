#include "Task3.h"



void v_print(int a[], int size){

    cout << "[ ";
    for (int i = 0; i < size; i++)
        cout << a[i] << " ";
    cout << "]";
    cout << endl;
}




int partition(vector<Encomenda>arr, int start, int end)
{

    int pivot = arr[start].duracao;

    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i].duracao <= pivot)
            count++;
    }

    // posição correta pivot
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    // ordena parte da esquerda e da direita dividido pelo pivot
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex)
    {

        while (arr[i].duracao <= pivot)
        {
            i++;
        }

        while (arr[j].duracao > pivot)
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



void quickSort(vector<Encomenda>arr, int start, int end)
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






float Task3::solver(vector<Encomenda> encomendas){


    const int time_cap = (8 * 3600);

    /*
    string line;
    string garbage;


    int nline = -1; // iniciado a menos um pois não retirei a primeira linha no contador de linhas

    ifstream MyReadFile("encomendas.txt");
    ifstream Garb("encomendas.txt");

    getline(MyReadFile, line); // eliminar 1º linha
    
    while (getline(Garb, garbage)) // conta as linhas
    {

        nline++;
    }

    int vtempo[nline]; // vetor que armazena a duração de cada tarefa
    int v_cont = 0; // index posição vetor vtempo
    

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

    MyReadFile.close();



    int tam = sizeof(vtempo) / sizeof(int); // numero de elemntos do vetor

    */

    quickSort(encomendas, 0, encomendas.size() - 1); /// vetor ja esta ordenado

    int res = 0; // numero de encomendas realizadas
    int sum = 0; // soma do tempo gasto nas entregas

    while (sum + encomendas[res].duracao <= time_cap)
    {

        sum = sum + encomendas[res].duracao;

        res++;
    }


    return (float)sum / (float)res;
}