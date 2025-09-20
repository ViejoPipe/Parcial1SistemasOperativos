#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Proceso.h"
#include "QueueLevel.h"
#include "MLFQScheduler.h"

using namespace std;

int main(){
    string filename;
    cout << "Ingresa el nombre del archivo .txt: ";
    cin >> filename;

    ifstream file(filename);

    vector<Proceso> procesos;
    string line;
    
    // Leer archivo linea por linea
    while(getline(file, line)){
        if(line.empty() || line[0] == '#') continue; // saltar comentarios o lineas vacias
        
        stringstream ss(line);
        string name, temp;
        int bt, at;

        getline(ss, name, ';');
        getline(ss, temp, ';');
        bt = stoi(temp);
        getline(ss, temp, ';');
        at = stoi(temp);

        procesos.push_back(Proceso(name, bt, at)); 
    }

    file.close();

    // Caso 1: RR(1), RR(3), RR(4), SJF 
    vector<QueueLevel> caso1 = {
        QueueLevel(1,true),
        QueueLevel(3,true),
        QueueLevel(4,true),
        QueueLevel(0,false) // SJF ultima cola, quantum 0
    };

    MLFQScheduler scheduler1(caso1, procesos);
    scheduler1.run();
    cout << "=== Resultados Caso 1 ===" << endl;
    scheduler1.printResults();

    // Caso 2: RR(2), RR(3), RR(4), STCF 
    vector<QueueLevel> caso2 = {
        QueueLevel(2,true),
        QueueLevel(3,true),
        QueueLevel(4,true),
        QueueLevel(0,false) // STCF ultima cola
    };

    MLFQScheduler scheduler2(caso2, procesos);
    scheduler2.run();
    cout << "=== Resultados Caso 2 ===" << endl;
    scheduler2.printResults();

    // Caso 3: RR(3), RR(5), RR(6), RR(20) 
    vector<QueueLevel> caso3 = {
        QueueLevel(3,true),
        QueueLevel(5,true),
        QueueLevel(6,true),
        QueueLevel(20,true)
    };

    MLFQScheduler scheduler3(caso3, procesos);
    scheduler3.run();
    cout << "=== Resultados Caso 3 ===" << endl;
    scheduler3.printResults();

    return 0;
}
