//
// Created by nikoauso.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "algoritmo_FCFS.h"

void simulaFCFS(struct Process processi[], int numero_processi) {
    system("clear");

    printf("Simulazione Scheduling FCFS:\n");

    int tempo_corrente = 0;

    for (int i = 0; i < numero_processi; i++) {
        if (tempo_corrente < processi[i].tempo_arrivo) {
            tempo_corrente = processi[i].tempo_arrivo;
        }

        printf("Esecuzione processo %d (Tempo di Burst: %d)\n", processi[i].pid, processi[i].tempo_burst);
        sleep(processi[i].tempo_burst);

        tempo_corrente += processi[i].tempo_burst;
        processi[i].tempo_fine = tempo_corrente;
        processi[i].tempo_turnaround = processi[i].tempo_fine - processi[i].tempo_arrivo;
        processi[i].tempo_attesa = processi[i].tempo_turnaround - processi[i].tempo_burst;

        printf("Processo %d completato\n", processi[i].pid);
    }
}