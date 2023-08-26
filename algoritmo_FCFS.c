//
// Created by nikoauso.
//

#include <stdio.h>
#include <unistd.h>
#include "algoritmo_FCFS.h"

void simulaFCFS(struct Process processi[], int num_processi) {
    printf("\nSimulazione Scheduling FCFS:\n");

    int tempo_corrente = 0;

    for (int i = 0; i < num_processi; i++) {
        if (tempo_corrente < processi[i].tempo_arrivo) {
            tempo_corrente = processi[i].tempo_arrivo;
        }

        printf("Esecuzione processo %d (Tempo di Burst: %d)\n", processi[i].pid, processi[i].tempo_burst);
        sleep(processi[i].tempo_burst);

        tempo_corrente += processi[i].tempo_burst;
        printf("Processo %d completato.\n", processi[i].pid);
    }
}