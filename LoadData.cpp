#include "LoadData.h"

void LoadData::loadCarrinhas() {
    string textLine;

    ifstream MyReadFile("/Users/Manel/Documents/GitHub/DA_Mercadoria/carrinhas.txt");

    if(!MyReadFile.is_open()) {
        cout << "ERRO";
        return;
    }

    vector<string> parsed_string;
    getline(MyReadFile,textLine); //discard first line
    while (getline (MyReadFile, textLine)) {
        vector<int> carrinha;
        textLine.pop_back(); //remove r
        string del = " ";
        parsed_string = split(textLine,del);
        for(string s: parsed_string){
            carrinha.push_back(stoi(s));
        }
        carrinhas.push_back(carrinha);
    }

    MyReadFile.close();
}
void LoadData::loadEncomendas() {
    string textLine;

    ifstream MyReadFile("/Users/Manel/Documents/GitHub/DA_Mercadoria/encomendas.txt");

    if(!MyReadFile.is_open()) {
        cout << "ERRO";
        return;
    }

    vector<string> parsed_string;
    getline(MyReadFile,textLine); //discard first line
    while (getline (MyReadFile, textLine)) {
        vector<int> encomenda;
        textLine.pop_back(); //remove r
        string del = " ";
        parsed_string = split(textLine,del);
        for(string s: parsed_string){
            encomenda.push_back(stoi(s));
        }
        encomendas.push_back(encomenda);
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


