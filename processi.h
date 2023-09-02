//
// Created by nikoauso.
//

#ifndef SO_PROJECT_PROCESSI_H
#define SO_PROJECT_PROCESSI_H

// Definisce la struttura di un processo
struct Process {
    int pid;                // ID del processo
    int tempo_arrivo;       // Tempo di arrivo del processo
    int tempo_burst;        // Tempo di burst del processo
    int tempo_rimanente;    // Tempo di esecuzione rimanente del processo
    int tempo_turnaround;   // Tempo di turnaround del processo
    int tempo_attesa;       // Tempo di attesa del processo
    int tempo_fine;         // Tempo di completamento del processo
};

#endif //SO_PROJECT_PROCESSI_H
