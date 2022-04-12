#include "LoadData.h"

void LoadData::loadCarrinhas() {
    string textLine;

    ifstream MyReadFile("carrinhas.txt");

    if(!MyReadFile.is_open()) {
        cout << "ERRO";
        return;
    }

    vector<string> parsed_string;
    getline(MyReadFile,textLine); //discard first line
    int i =0;
    while (getline (MyReadFile, textLine)) {
        Carrinha carrinha;
        textLine.pop_back(); //remove r
        string del = " ";
        parsed_string = split(textLine,del);
        carrinha.volMax = stoi(parsed_string[0]);
        carrinha.pesoMax = stoi(parsed_string[1]);
        carrinha.custo = stoi(parsed_string[2]);
        
        carrinha.id_c = i;
        carrinhas.push_back(carrinha);
        i++;

    }

    MyReadFile.close();
}
void LoadData::loadEncomendas() {
    string textLine;

    ifstream MyReadFile("encomendas.txt");

    if(!MyReadFile.is_open()) {
        cout << "ERRO";
        return;
    }
    
    int count =0;
    vector<string> parsed_string;
    getline(MyReadFile,textLine); //discard first line
    while (getline (MyReadFile, textLine)) {
        Encomenda encomenda;
        textLine.pop_back(); //remove r
        string del = " ";
        parsed_string = split(textLine,del);
        encomenda.volume = stoi(parsed_string[0]);
        encomenda.peso = stoi(parsed_string[1]);
        encomenda.recompensa = stoi(parsed_string[2]);
        encomenda.duracao = stoi(parsed_string[3]);
        encomenda.id_e = count;
        encomendas.push_back(encomenda);
        
        count++;
    }

    MyReadFile.close();

}
vector<string> LoadData::split(const string &s,const string &del) {
    vector<string> final;

    unsigned int start = 0;
    unsigned int end = s.find(del);
    while (end != -1) {
        final.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    final.push_back(s.substr(start, end - start));

    return final;
}


