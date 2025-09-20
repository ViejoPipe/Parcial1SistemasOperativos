#include "MLFQScheduler.h"

MLFQScheduler::MLFQScheduler(const vector<QueueLevel>& qs, const vector<Proceso>& ps){
    queues = qs;
    procesos = ps;
    currentTime = 0;
}

void MLFQScheduler::run(){
    int n = procesos.size(), finished, insertedCount, qIdx, execTime, start, end, prevEnd, wt, i;
    bool allInserted, foundQueue;

    finished = 0, currentTime = 0;
    allInserted = false;

    // Mientras no todos los procesos hayan terminado
    while(finished < n){
        // Repetir todos estos pasos hasta que todos los procesos terminen
        // Paso 1: Insertar procesos que acaban de llegar
        insertedCount = 0;
        if(!allInserted){
            for(auto &p : procesos){
                if(!p.inQueue && p.arrivalTime <= currentTime){
                    queues[0].ready.push_back(&p); // insertar en Q1
                    p.inQueue = true;
                }
                if(p.inQueue) insertedCount++;
            }
            if(insertedCount == n) allInserted = true;
        }

        // Paso 2: Seleccion de la cola, CABE ACLARAR se busca la cola con la mayor prioridad que tenga procesos listos
        // La primera cola no vacia en orden de prioridad
        qIdx = -1;
        foundQueue = false;
        for(i=0;i<queues.size() && !foundQueue;i++){
            if(!queues[i].ready.empty()){
                qIdx = i;
                foundQueue = true;
            }
        }

        // Paso 3: Ejecutar proceso
        if(foundQueue){
            // Obtenemos una referencia a la cola seleccionada (la de mayor prioridad disponible)
            QueueLevel &queue = queues[qIdx];
            
            // De la cola seleccionada, tomamos el siguiente proceso listo para ejecutar
            Proceso* p = queue.getNextProcess();

            // Primer inicio (RT)
            if(p->responseTime == -1) p->responseTime = currentTime;

            // Determinar tiempo de ejecucion
            if(queue.isRR) execTime = min(queue.quantum, p->remainingTime); // RR
            else execTime = p->remainingTime;                               // SJF o STCF

            // Registrar intervalo de ejecucion
            start = currentTime;
            end = currentTime + execTime;
            p->intervals.push_back({start,end});

            // Actualizar tiempo global y remainingTime
            currentTime += execTime;
            p->remainingTime -= execTime;

            // Verificar si termino
            if(p->remainingTime == 0){
                p->completionTime = currentTime;
                finished++;
            }
            else{
                if(queue.isRR && qIdx + 1 < queues.size())
                    queues[qIdx + 1].ready.push_back(p); // baja de cola, castigo
                else
                    queue.reinsertProcess(p);           // reinserta en la misma cola
            }
        }
        else{
            currentTime++;
        }
    }

    // Calcular WT manualmente
    for(auto &p : procesos){
        wt = 0, prevEnd = p.arrivalTime;
        for(auto &seg : p.intervals){
            wt += seg.first - prevEnd;
            prevEnd = seg.second;
        }
        p.waitingTime = wt;
    }
}

void MLFQScheduler::printResults(){
    int TAT;
    double totalWT = 0, totalRT = 0;
    cout << "Name\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    
    for(auto &p : procesos){
        TAT = p.completionTime - p.arrivalTime;
        cout << p.name << "\t" << p.arrivalTime << "\t" << p.burstTime
            << "\t" << p.completionTime << "\t" << TAT
            << "\t" << p.waitingTime << "\t" << p.responseTime << "\n";
        totalWT += p.waitingTime;
        totalRT += p.responseTime;
    }   
    cout << "Promedio WT: " << totalWT / procesos.size() << ", Promedio RT: " << totalRT / procesos.size() << "\n";
}
