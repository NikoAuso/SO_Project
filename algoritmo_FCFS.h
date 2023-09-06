//
// Created by nikoauso.
//

#ifndef SO_PROJECT_ALGORITMO_FCFS_H
#define SO_PROJECT_ALGORITMO_FCFS_H

#include "utilities_algoritmi.h"

/**
 * Simula l'algoritmo di scheduling First-Come, First-Served (FCFS).
 *
 * Questa funzione esegue la simulazione dell'algoritmo di scheduling FCFS su un array di processi fornito.
 * Ogni processo viene eseguito nell'ordine in cui è arrivato (first-come) e completato interamente prima
 * di passare al successivo. Durante la simulazione, vengono visualizzati i dettagli di esecuzione di ciascun
 * processo, compreso il tempo di burst, il completamento, il tempo di turnaround (differenza tra il tempo
 * di completamento e il tempo di arrivo) e il tempo di attesa (differenza tra il tempo di turnaround e
 * il tempo di burst).
 *
 * @param processi        Un array di strutture `Processi` che rappresenta i processi da schedulare.
 * @param numero_processi Il numero totale di processi nell'array.
 * @param burst_totale    La somma dei tempi di burst di tutti i processi.
 */
void simulaFCFS(struct Processi processi[], int numero_processi, int burst_totale);

#endif //SO_PROJECT_ALGORITMO_FCFS_H
