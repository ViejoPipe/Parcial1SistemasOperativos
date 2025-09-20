#include "QueueLevel.h"

QueueLevel::QueueLevel(int q, bool rr){
    quantum = q;
    isRR = rr;
}

Proceso* QueueLevel::getNextProcess(){
    Proceso* ans = nullptr; 
    int minIndex, i;

    if(!ready.empty()){
        if(isRR){
            ans = ready.front();    // tomamos el primero
            ready.pop_front();
        } 
        else{ // SJF o STCF
            // buscamos el proceso con menor remainingTime 
            minIndex = 0;
            for(i=1;i<ready.size();i++){
                if(ready[i]->remainingTime < ready[minIndex]->remainingTime) minIndex = i;
            }
            ans = ready[minIndex];             // guardamos el proceso
            ready.erase(ready.begin() + minIndex); // lo eliminamos de la cola
        }
    }

    return ans; 
}

// Reinserta proceso 
void QueueLevel::reinsertProcess(Proceso* p) {
    ready.push_back(p); 
}
