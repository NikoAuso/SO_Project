//
// Created by nikoauso.
//

#include <stdio.h>
#include <stdlib.h>
#include "selezione_algoritmi.h"
#include "algoritmo_FCFS.h"
#include "algoritmo_SJF.h"
#include "algoritmo_SRTF.h"
#include "algoritmo_RR.h"
#include "controlla_input.h"

void scegli_algoritmo(struct Process *processi, int numero_processi) {
    printf("Scegli l'algoritmo di scheduling:\n");
    printf("1. FCFS (First-Come, First-Served)\n");
    printf("2. SJF (Shortest Job First)\n");
    printf("3. RR (Round Robin)\n");
    printf("4. SRTF (Shortest Remaining Time First)\n");
    printf("Inserisci la tua scelta: ");
    int scelta_algoritmo = leggi_input_intero();

    switch (scelta_algoritmo) {
        case 1:
            simulaFCFS(processi, numero_processi);
            break;
        case 2:
            simulaSJF(processi, numero_processi);
            break;
        case 3:
            printf("Inserisci il valore del quanto di tempo per l'algoritmo Round Robin: ");
            int quanto_di_tempo = leggi_input_intero();
            simulaRR(processi, numero_processi, quanto_di_tempo);
            break;
        case 4:
            simulaSRTF(processi, numero_processi);
            break;
        default:
            printf("Scelta non valida.\n");
            exit(1);
    }
}