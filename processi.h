//
// Created by nikoauso.
//

#ifndef SO_PROJECT_PROCESSI_H
#define SO_PROJECT_PROCESSI_H

struct Process {
    int pid;
    int tempo_arrivo;
    int tempo_burst;
    int tempo_rimanente;
    int tempo_turnaround;
    int tempo_attesa;
    int tempo_fine;
};

#endif //SO_PROJECT_PROCESSI_H
