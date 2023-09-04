//
// Created by nikoauso.
//

#include "selezione_algoritmi.h"

void scegli_algoritmo(struct Processi *processi, int numero_processi) {
    printf("Scegli l'algoritmo di scheduling:\n");
    printf("1. FCFS (First-Come, First-Served)\n");
    printf("2. RR (Round Robin)\n");
    printf("3. SJF (Shortest Job First)\n");
    printf("4. SRTF (Shortest Remaining Time First)\n");
    printf("Inserisci la tua scelta: ");

    // Legge la scelta dell'utente
    int scelta_algoritmo = leggi_input_intero();
    ordine_arrivo_processi(processi, numero_processi);
    int burst_totale = calcola_burst_totale(processi, numero_processi);

    // Esegue l'azione corrispondente alla scelta dell'utente
    switch (scelta_algoritmo) {
        case 1:
            simulaFCFS(processi, numero_processi, burst_totale); // Avvia la simulazione FCFS
            break;
        case 2:
            // Chiede all'utente il quanto di tempo per l'algoritmo Round Robin
            printf("Inserisci il valore del quanto di tempo per l'algoritmo Round Robin: ");
            int quanto_di_tempo = leggi_input_intero();
            simulaRR(processi, numero_processi, quanto_di_tempo, burst_totale); // Avvia la simulazione RR
            break;
        case 3:
            simulaSJF(processi, numero_processi, burst_totale); // Avvia la simulazione SJF
            break;
        case 4:
            simulaSRTF(processi, numero_processi, burst_totale); // Avvia la simulazione SRTF
            break;
        default:
            printf("Scelta non valida.\n"); // Scelte non valide
            exit(1); // Esce con stato di errore
    }
}