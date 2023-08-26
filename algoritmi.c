//
// Created by nikoauso.
//

#include <stdio.h>
#include <stdlib.h>
#include "algoritmi.h"
#include "algoritmo_FCFS.h"
#include "algoritmo_SJF.h"
#include "algoritmo_SRTF.h"
#include "algoritmo_RR.h"

void scegli_algoritmo(struct Process *processi, int numProcessi) {
    char scelta_algoritmo;
    int quantum;

    printf("Scegli l'algoritmo di scheduling:\n");
    printf("1. FCFS (First-Come, First-Served)\n");
    printf("2. SJF (Shortest Job First)\n");
    printf("3. Round Robin\n");
    printf("4. SRTF (Shortest Remaining Time First)\n");
    printf("Inserisci la tua scelta: ");
    scanf(" %c", &scelta_algoritmo);

    switch (scelta_algoritmo) {
        case '1':
            simulaFCFS(processi, numProcessi);
            break;
        case '2':
            simulaSJF(processi, numProcessi);
            break;
        case '3':
            printf("Inserisci il valore del quanto di tempo per l'algoritmo Round Robin: ");
            scanf("%d", &quantum);
            simulaRoundRobin(processi, numProcessi, quantum);
            break;
        case '4':
            simulaSRTF(processi, numProcessi);
            break;
        default:
            printf("Scelta non valida.\n");
            exit(1);
    }
}