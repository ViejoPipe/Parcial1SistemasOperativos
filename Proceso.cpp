#include "Proceso.h"

Proceso::Proceso(const string& n, int bt, int at){
    name = n;
    burstTime = bt;
    remainingTime = bt;
    arrivalTime = at;
    completionTime = 0;
    responseTime = -1;
    waitingTime = 0;
    inQueue = false;
}

void Proceso::addInterval(int start, int end){
    intervals.push_back(make_pair(start, end));
}


