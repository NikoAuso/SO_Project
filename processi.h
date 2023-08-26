//
// Created by nikoauso.
//

#ifndef SO_PROJECT_PROCESSI_H
#define SO_PROJECT_PROCESSI_H

struct Process {
    int pid;
    int tempo_arrivo;
    int tempo_burst;
    int priorita;
    int tempo_rimanente;
};

#endif //SO_PROJECT_PROCESSI_H
