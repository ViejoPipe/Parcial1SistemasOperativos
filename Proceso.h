#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <utility>

using namespace std;

// Clase que representa un proceso en el scheduler
class Proceso {
    public:
        string name;            // nombre del proceso
        int burstTime;          // tiempo total de ejecucion requerido
        int remainingTime;      // tiempo que le queda por ejecutar
        int arrivalTime;        // tiempo en que llega al sistema
        int completionTime;     // tiempo en que termina de ejecutarse
        int responseTime;       // primer momento en que comienza a ejecutarse
        int waitingTime;        // tiempo total que paso esperando
        vector<pair<int,int>> intervals; // lista de intervalos de ejecucion (start,end)
        bool inQueue;           // indica si ya fue insertado en la cola

        // Constructor por defecto
        Proceso(){}

        // Constructor
        Proceso(const string& n, int bt, int at); 

        // Metodo para agregar un intervalo de ejecucion
        void addInterval(int start, int end);
};

#endif 
