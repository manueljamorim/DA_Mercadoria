#include "LoadData.h"

void LoadData::loadCarrinhas() {
    string textLine;

    ifstream MyReadFile("carrinhas.txt");

    if(!MyReadFile.is_open()) {
        cout << "ERRO";
        return;
    }

    getline(MyReadFile,textLine); //discard first line
    int i = 0;
    int volMax, weightMax, cost;
    while (getline (MyReadFile, textLine)) {
        istringstream(textLine) >> volMax >> weightMax >> cost;
        carrinhas.push_back({ volMax, weightMax, cost, i });
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
    
    int count = 0;
    int volume, weight, payout, duration;
    getline(MyReadFile,textLine); //discard first line
    while (getline (MyReadFile, textLine)) {
        istringstream(textLine) >> volume >> weight >> payout >> duration;
        encomendas.push_back({ volume, weight, payout, duration, count });
        
        count++;
    }

    MyReadFile.close();

}


