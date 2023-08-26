#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "leggi_file_JSON.h"
#include "algoritmi.h"

#define MAX_PROCESSES 10

int main() {
    int numProcessi;
    int usa_file;
    struct Process *processi = NULL;

    printf("Benvenuto nel SIMULATORE DI SCHEDULING DEI PROCESSI!\n");

    printf("Il simulatore offre un set di processi già pre-impostati che puoi utilizzare per semplificare l'inserimento dei dati.\n");
    printf("Puoi modificare ora il file o utilizzare i dati già inseriti.\n");
    printf("Vuoi utilizzare il file? (1->Si/0->No): ");
    scanf("%d", &usa_file);

    if (usa_file == 1) {
        numProcessi = leggi_file_JSON("/home/nikoauso/CLionProjects/SO-Project_1/processi.json", &processi);
        system("clear");
    } else {
        system("clear");
        printf("Inserisci il numero di processi da simulare (fino a %d): ", MAX_PROCESSES);
        scanf("%d", &numProcessi);

        if (numProcessi > MAX_PROCESSES) {
            printf("Il numero massimo di processi consentito è %d.\n", MAX_PROCESSES);
            return 1;
        }

        for (int i = 0; i < numProcessi; i++) {
            printf("Inserisci il tempo di arrivo per il processo %d: ", i + 1);
            scanf("%d", &processi[i].tempo_arrivo);

            printf("Inserisci il tempo di burst per il processo %d: ", i + 1);
            scanf("%d", &processi[i].tempo_burst);

            processi[i].pid = i + 1;
            processi[i].tempo_rimanente = processi[i].tempo_burst;
        }
        system("clear");
    }

    scegli_algoritmo(processi, numProcessi);

    return 0;
}
