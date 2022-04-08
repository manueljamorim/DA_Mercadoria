#include "Task1.h"

//Objetivo: minimizar o numero de estafetas
//carrinhas [0]-->volMax [1]-->pesoMax
//encomendas [0]-->volume [1]-->peso
//Bin packing com 2 restrições (peso e volume)



struct max_volume
{
    inline bool operator() (const Carrinha& a, const Carrinha& b)
    {
        return (a.volMax> b.volMax);
    }
    inline bool operator() (const Encomenda& a, const Encomenda& b)
    {
        return (a.volume> b.volume);
    }
};

struct max_peso
{
    inline bool operator() (const Carrinha& a, const Carrinha& b)
    {
        return (a.pesoMax> b.pesoMax);
    }
    inline bool operator() (const Encomenda& a, const Encomenda& b)
    {
        return (a.peso> b.peso);
    }
};

struct max_average
{
    inline bool operator() (const Carrinha& a, const Carrinha& b)
    {
        return (((a.pesoMax + a.volMax)/2.0)> ((a.pesoMax + a.volMax)/2.0));
    }
};


int Task1::Greedy() {

    int countNumCarrinhas = 0;

    for(Encomenda& encomenda: loadData.encomendas){
        sort(loadData.carrinhas.begin(),loadData.carrinhas.end(),max_peso());

        bool placed = 0;
        for(int i=0; i<loadData.carrinhas.size(); i++){ //dar preferencia a carrinhas já ocupadas
            if(loadData.carrinhas[i].used &&
            encomenda.volume <= loadData.carrinhas[i].volMax
            && encomenda.peso <= loadData.carrinhas[i].pesoMax ){
                loadData.carrinhas[i].pesoMax -= encomenda.peso;
                loadData.carrinhas[i].volMax -= encomenda.volume;
                placed = 1;
                break;
            }
        }
        if(!placed){
            for(int i=0; i<loadData.carrinhas.size(); i++){ //caso nao caiba em nenhuma carrinha já ocupada
                if(encomenda.volume <= loadData.carrinhas[i].volMax
                   && encomenda.peso <= loadData.carrinhas[i].pesoMax ){
                    loadData.carrinhas[i].pesoMax -= encomenda.peso;
                    loadData.carrinhas[i].volMax -= encomenda.volume;
                    loadData.carrinhas[i].used = 1;
                    placed = 1;
                    countNumCarrinhas +=1;
                    break;}
            }

            if(!placed){
                cout << "Encomenda sem lugar possivel" << endl;
            }
        }

    }

    return countNumCarrinhas;


}
//Max volume solucao: 24
//Max peso solucao: 23
 //Max average solucao: 24


