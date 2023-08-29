//
// Created by nikoauso.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "algoritmo_RR.h"

void simulaRR(struct Process processi[], int numero_processi, int quantum) {
    system("clear");

    printf("Simulazione Scheduling Round Robin:\n");

    int tempo_corrente = 0;
    int processi_rimasti = numero_processi;

    while (processi_rimasti > 0) {
        for (int i = 0; i < numero_processi; i++) {
            if (processi[i].tempo_rimanente > 0) {
                int burst = (processi[i].tempo_rimanente > quantum) ? quantum : processi[i].tempo_rimanente;

                printf("Esecuzione processo %d (Tempo di Burst: %d)\n", processi[i].pid, burst);
                sleep(burst);

                processi[i].tempo_rimanente -= burst;
                tempo_corrente += burst;

                if (processi[i].tempo_rimanente == 0) {
                    printf("Processo %d completato.\n", processi[i].pid);
                    processi_rimasti--;
                    processi[i].tempo_fine = tempo_corrente;
                    processi[i].tempo_turnaround = processi[i].tempo_fine - processi[i].tempo_arrivo;
                    processi[i].tempo_attesa = processi[i].tempo_turnaround - processi[i].tempo_burst;
                }
            }
        }
    }
}