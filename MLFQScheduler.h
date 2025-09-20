#ifndef MLFQSCHEDULER_H
#define MLFQSCHEDULER_H

#include <vector>
#include <iostream>
#include "QueueLevel.h"
#include "Proceso.h"

using namespace std;

// Clase que representa el scheduler MLFQ
class MLFQScheduler {
    public:
        vector<QueueLevel> queues;   // las diferentes colas del MLFQ
        vector<Proceso> procesos;    // todos los procesos que vamos a ejecutar
        int currentTime;             // tiempo global del sistema

        // Constructor por defecto
        MLFQScheduler(){}
        
        // Constructor
        MLFQScheduler(const vector<QueueLevel>& qs, const vector<Proceso>& ps);

        // Metodo principal que ejecuta la simulacion
        void run();

        // Metodo para imprimir los resultados finales (WT, RT, TAT, etc)
        void printResults();
};

#endif 
