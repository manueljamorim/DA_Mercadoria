#include "Task1.h"
#include <ilcplex/ilocplex.h>

//Objetivo: minimizar o numero de estafetas
//carrinhas [0]-->volMax [1]-->pesoMax
//encomendas [0]-->volume [1]-->peso
//Bin packing com 2 restrições (peso e volume)

struct max_average
{
    inline bool operator() (const Carrinha& a, const Carrinha& b)
    {
        double av = (a.pesoMax + a.volMax)/2.0;
        double bv = (b.pesoMax + b.volMax)/2.0;
        return av>bv;
    }
    
    inline bool operator() (const Encomenda& a, const Encomenda& b)
    {
        double av = (a.peso + a.volume)/2.0;
        double bv = (b.peso + b.volume)/2.0;
        return av>bv;
    }
};

struct id_sorter
{
    inline bool operator() (const Carrinha& a, const Carrinha& b)
    {
        return a.id_c<b.id_c;
    }
};

int Task1::Greedy() {
    sort(loadData.encomendas.begin(),loadData.encomendas.end(),max_average());
    int countNumCarrinhas = 0;

    for(Encomenda& encomenda: loadData.encomendas){
        sort(loadData.carrinhas.begin(),loadData.carrinhas.end(),max_average());
        bool placed = 0;
        
        
        //Finds tightest spot
        int smallest_i = -1;
        float smallest_value = MAXFLOAT;
        
        
        for(int i=0; i<loadData.carrinhas.size(); i++){ //dar preferencia a carrinhas já ocupadas
            if(loadData.carrinhas[i].used &&
            encomenda.volume <= loadData.carrinhas[i].volMax
            && encomenda.peso <= loadData.carrinhas[i].pesoMax ){
                if(((loadData.carrinhas[i].volMax + loadData.carrinhas[i].pesoMax)/2.0)<smallest_value){
                    smallest_i = i;
                    smallest_value = (loadData.carrinhas[i].volMax + loadData.carrinhas[i].pesoMax)/2.0;
                }
            }
        }
        
        
        if(smallest_i != -1){
            loadData.carrinhas[smallest_i].pesoMax -= encomenda.peso;
            loadData.carrinhas[smallest_i].volMax -= encomenda.volume;
            encomenda.id_carrinha_mae = loadData.carrinhas[smallest_i].id_c;
            placed = 1;
        }
        
        if(!placed){
            for(int i=0; i<loadData.carrinhas.size(); i++){ //caso nao caiba em nenhuma carrinha já ocupada
                if(encomenda.volume <= loadData.carrinhas[i].volMax
                   && encomenda.peso <= loadData.carrinhas[i].pesoMax ){
                    loadData.carrinhas[i].pesoMax -= encomenda.peso;
                    loadData.carrinhas[i].volMax -= encomenda.volume;
                    loadData.carrinhas[i].used = 1;
                    encomenda.id_carrinha_mae = loadData.carrinhas[i].id_c;
                    
                    placed = 1;
                    countNumCarrinhas +=1;
                    break;}
            }

            if(!placed){
                cout << "Encomenda sem lugar possivel" << endl;
            }
        }

    }
    //Informacao de saida
    sort(loadData.carrinhas.begin(),loadData.carrinhas.end(),id_sorter());
    
    for(auto& carrinha: loadData.carrinhas){
        carrinhas_usadas.push_back(carrinha.used);
    }
    
    for(auto& encomenda: loadData.encomendas){
        auto it = carrinha_encomendas.find(encomenda.id_carrinha_mae);
        if(it != carrinha_encomendas.end()){
            it->second.push_back(encomenda);
        }else{
            vector<Encomenda> a = {encomenda};
            carrinha_encomendas.insert(pair<int,vector<Encomenda>>(encomenda.id_carrinha_mae, a));
        }
    }
    
    return countNumCarrinhas;


}

//Utilização de solver Cplex (aplica branch and bound)
//Necessario instalar e configurar no Visual Studio (ver no youtube)
//Mac --> utilizar Xcode
//Comentar caso não tenha instalado

int Task1::Solver() {
    IloEnv env;
    IloModel model(env);
    
    
    unsigned long int n_items = loadData.encomendas.size();
    unsigned long int n_bins = loadData.carrinhas.size();
    
    //Variaveis
    IloNumVarArray y(env);
    IloArray<IloNumVarArray> x(env);
    
    for(int j=0; j<n_bins; j++){
        string number = "y:" + to_string(j);
        char char_array[number.size() + 1];
        strcpy(char_array, number.c_str());
        
        y.add(IloNumVar(env,0,1, ILOBOOL, char_array));
    }
    
    for(int i=0; i<n_items; i++){
        
        IloNumVarArray linha(env);
        for(int j=0; j<n_bins; j++){
            string number2 = "x:" + to_string(i) + "," + to_string(j);
            char char_array2[number2.size() + 1];
            strcpy(char_array2, number2.c_str());
            
            linha.add(IloNumVar(env, 0, 1, ILOBOOL, char_array2));
        }
        x.add(linha);
    }
    
    //Função objetivo

    IloExpr obj(env);
    for(int j=0; j<n_bins;j++){
        obj += y[j];
    }
    model.add(IloMinimize(env, obj));
    
    //Restrições
    for(int i=0; i<n_items; i++){
        IloExpr con(env);
        for(int j=0; j<n_bins; j++){
            con += x[i][j];
        }
        model.add(con == 1);
    }
    
    
    for(int j=0; j<n_bins; j++){
        IloExpr con(env);
        for(int i=0; i<n_items; i++){
            con += x[i][j] * loadData.encomendas[i].peso;
        }
        model.add(con <= loadData.carrinhas[j].pesoMax * y[j]);
    }
    
    for(int j=0; j<n_bins; j++){
        IloExpr con(env);
        for(int i=0; i<n_items; i++){
            con += x[i][j] * loadData.encomendas[i].volume;
        }
        model.add(con <= loadData.carrinhas[j].volMax * y[j]);
    }
    
    IloCplex cplex(model);
    //cplex.exportModel("/Users/Manel/Documents/Xcode/Cplex/Cplex/lpex1.lp");
    cplex.setOut(env.getNullStream());
    
    if ( !cplex.solve() ) {
       env.error() << "Failed to optimize LP" << endl;
       throw(-1);
    }
    
    
    env.out() << "Tipo de solucao: " << cplex.getStatus() << endl;
    env.out() << "Número de estafetas utilizados: " << cplex.getObjValue() << endl;
    
    IloNumArray valsy(env);
    cplex.getValues(valsy, y);
    
    for(int i=0; i<valsy.getSize();i++){
        carrinhas_usadas.push_back(valsy[i]);
    }
    
    
    for(int i=0; i<n_items; i++){
        IloNumArray valsx(env);
        cplex.getValues(valsx, x[i]);
        
        for(int a=0; a<=valsx.getSize() ;a++){
            if(valsx[a]==1){
                auto it = carrinha_encomendas.find(a);
                if(it != carrinha_encomendas.end()){
                    it->second.push_back(loadData.encomendas[i]);
                }else{
                    vector<Encomenda> ae = {loadData.encomendas[i]};
                    carrinha_encomendas.insert(pair<int,vector<Encomenda>>(a, ae));
                }
                
                break;
            };
        }
        
    }
    
    return cplex.getObjValue();

}


