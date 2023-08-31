//
// Created by nikoauso.
//

#ifndef SO_PROJECT_ALGORITMO_FCFS_H
#define SO_PROJECT_ALGORITMO_FCFS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "processi.h"
#include "utilities.h"

/**
 * Simula l'algoritmo di scheduling First-Come, First-Served (FCFS) su un array di processi.
 *
 * Esegue la simulazione dell'algoritmo di scheduling FCFS su un array di processi fornito.
 * Ogni processo viene eseguito nell'ordine in cui è arrivato (first-come) e completato interamente prima
 * di passare al successivo. Durante la simulazione, vengono visualizzati i dettagli di esecuzione di ciascun
 * processo, compreso il tempo di burst, il completamento, il tempo di turnaround (differenza tra il tempo
 * di completamento e il tempo di arrivo) e il tempo di attesa (differenza tra il tempo di turnaround e
 * il tempo di burst).
 *
 * @param processi[] Un array di strutture "Process" contenente i dettagli dei processi da eseguire.
 * @param num_processi Il numero totale di processi presenti nell'array.
 */
void simulaFCFS(struct Process processi[], int numero_processi);

#endif //SO_PROJECT_ALGORITMO_FCFS_H
