
#include <iostream>
#include "LoadData.h"
#include <time.h>
#include <limits>
//#include "Task1.h"
//#include "Task2.h"
#include "Task3.h"
#include <iomanip> 




void task1_menu(LoadData td) {
    return;
}
/*
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
    cin.clear();
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
*/


void task3_menu(LoadData ld) {
    
    Task3 td;
    char input;

    cout << setfill('-') << setw(10) << "" << "TASK 2" << setw(10) << "" << endl;
    cout << "1. Original Dataset Test" << endl;
    cout << "Choose which test to run (0 to return): ";

    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (input) {
    case '0':
        return;
    case '1':
        td.solver(ld.encomendas);
        break;
    default:
        cout << "Invalid input" << endl;
        break;
    }


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
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (input) {
        case '0':
            return 0;
            break;
        case '1':
            task1_menu(ld);
            break;
        case '2':
            //task2_menu(ld);
            break;
        case '3':
            task3_menu(ld);
            break;
        default:
            cout << "Invalid input" << endl;
            break;
        }
    } while (true);

    
    return 0;
  
}