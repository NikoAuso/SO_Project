//
// Created by nikoauso.
//

#include <stdio.h>
#include <unistd.h>
#include "algoritmo_RR.h"

void simulaRoundRobin(struct Process processi[], int num_processi, int quantum) {
    printf("\nSimulazione Scheduling Round Robin:\n");

    int tempo_corrente = 0;
    int processi_rimasti = num_processi;

    while (processi_rimasti > 0) {
        for (int i = 0; i < num_processi; i++) {
            if (processi[i].tempo_rimanente > 0) {
                int esecuzione = (processi[i].tempo_rimanente > quantum) ? quantum : processi[i].tempo_rimanente;

                printf("Esecuzione processo %d (Tempo di Esecuzione: %d)\n", processi[i].pid, esecuzione);
                sleep(esecuzione);

                processi[i].tempo_rimanente -= esecuzione;
                tempo_corrente += esecuzione;

                if (processi[i].tempo_rimanente == 0) {
                    printf("Processo %d completato.\n", processi[i].pid);
                    processi_rimasti--;
                }
            }
        }
    }
}