//
// Created by nikoauso.
//

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "algoritmo_SRTF.h"

void simulaSRTF(struct Process processi[], int num_processi) {
    printf("\nSimulazione Scheduling SRTF:\n");

    int tempo_corrente = 0;
    int processi_rimasti = num_processi;

    while (processi_rimasti > 0) {
        int indice_piu_breve = -1;
        int burst_piu_breve = INT_MAX;

        for (int i = 0; i < num_processi; i++) {
            if (processi[i].tempo_arrivo <= tempo_corrente && processi[i].tempo_rimanente < burst_piu_breve && processi[i].tempo_rimanente > 0) {
                burst_piu_breve = processi[i].tempo_rimanente;
                indice_piu_breve = i;
            }
        }

        if (indice_piu_breve == -1) {
            tempo_corrente++;
        } else {
            printf("Esecuzione processo %d (Tempo di Burst: %d)\n", processi[indice_piu_breve].pid, processi[indice_piu_breve].tempo_rimanente);
            sleep(processi[indice_piu_breve].tempo_rimanente);

            tempo_corrente += processi[indice_piu_breve].tempo_rimanente;
            processi[indice_piu_breve].tempo_rimanente = 0;

            printf("Processo %d completato.\n", processi[indice_piu_breve].pid);
            processi_rimasti--;
        }
    }
}
