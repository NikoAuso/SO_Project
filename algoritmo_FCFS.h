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
 * Simula l'algoritmo di scheduling FCFS (First-Come, First-Served) per una serie di processi.
 *
 * @param processi Array di processi da schedulare.
 * @param numero_processi Numero totale di processi nell'array.
 * @param burst_totale Il tempo totale di burst di tutti i processi.
 */
void simulaFCFS(struct Processi processi[], int numero_processi, int burst_totale);

#endif //SO_PROJECT_ALGORITMO_FCFS_H
