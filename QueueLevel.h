#ifndef QUEUELEVEL_H
#define QUEUELEVEL_H

#include <deque>
#include <algorithm>
#include "Proceso.h"

using namespace std;

// Clase que representa una cola de nivel en el MLFQ
class QueueLevel {
public:
    int quantum;        // tiempo de quantum para RR, 0 si es SJF o STCF
    bool isRR;          // indica si la cola es Round-Robin
    deque<Proceso*> ready; // cola de procesos listos para ejecutar

    // Constructor por defecto
    QueueLevel(){}
    
    // Constructor
    QueueLevel(int q, bool rr);

    // Devuelve el siguiente proceso que se debe ejecutar en esta cola
    Proceso* getNextProcess();

    // Reinserta un proceso en la misma cola 
    void reinsertProcess(Proceso* p);
};

#endif 
