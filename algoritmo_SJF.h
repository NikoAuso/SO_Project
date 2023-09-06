//
// Created by nikoauso.
//

#ifndef SO_PROJECT_ALGORITMO_SJF_H
#define SO_PROJECT_ALGORITMO_SJF_H

#include "utilities_algoritmi.h"

/**
 * Simula l'algoritmo di scheduling Shortest Job First (SJF).
 *
 * Questa funzione esegue la simulazione dell'algoritmo di scheduling SJF su un array di processi fornito.
 * Ogni processo viene selezionato in base al tempo di burst più breve tra i processi pronti all'esecuzione.
 * Durante la simulazione, vengono visualizzati i dettagli di esecuzione di ciascun processo, compresa la durata
 * dell'esecuzione, il completamento, il tempo di turnaround (differenza tra il tempo di completamento e il tempo
 * di arrivo) e il tempo di attesa (differenza tra il tempo di turnaround e il tempo di burst).
 *
 * @param processi        Un array di strutture `Processi` che rappresenta i processi da schedulare.
 * @param numero_processi Il numero totale di processi nell'array.
 * @param burst_totale    La somma dei tempi di burst di tutti i processi.
 */
void simulaSJF(struct Processi processi[], int numero_processi, int burst_totale);

#endif //SO_PROJECT_ALGORITMO_SJF_H