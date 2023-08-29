//
// Created by nikoauso.
//

#ifndef SO_PROJECT_ALGORITMO_SRTF_H
#define SO_PROJECT_ALGORITMO_SRTF_H

#include "processi.h"

/**
 * Simula l'algoritmo di scheduling Shortest Remaining Time First (SRTF) su un array di processi.
 *
 * Questa funzione esegue la simulazione dell'algoritmo di scheduling SRTF su un array di processi fornito.
 * Ogni processo viene selezionato in base al tempo di burst rimanente più breve tra i processi pronti all'esecuzione.
 * Durante la simulazione, vengono visualizzati i dettagli di esecuzione di ciascun processo, compresa la durata
 * dell'esecuzione, il completamento, il tempo di turnaround (differenza tra il tempo di completamento e il tempo
 * di arrivo) e il tempo di attesa (differenza tra il tempo di turnaround e il tempo di burst).
 *
 * @param processi[] Un array di strutture "Process" contenente i dettagli dei processi da eseguire.
 * @param numero_processi Il numero totale di processi presenti nell'array.
 */
void simulaSRTF(struct Process processi[], int numero_processi);

#endif //SO_PROJECT_ALGORITMO_SRTF_H
