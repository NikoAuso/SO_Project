//
// Created by nikoauso.
//

#ifndef SO_PROJECT_ALGORITMO_RR_H
#define SO_PROJECT_ALGORITMO_RR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "processi.h"
#include "utilities.h"

/**
 * Simula l'algoritmo di scheduling Round Robin su un array di processi.
 *
 * Questa funzione esegue la simulazione dell'algoritmo di scheduling Round Robin su un array di processi fornito.
 * Ogni processo viene eseguito per un periodo di tempo definito dal parametro "quantum". Quando il quantum scade,
 * il controllo passa al prossimo processo nella coda. Questo processo continua fino a quando tutti i processi
 * sono stati completati. Durante la simulazione, vengono visualizzati i dettagli di esecuzione di ciascun
 * processo, compresa la durata dell'esecuzione, il completamento, il tempo di turnaround (differenza tra il tempo
 * di completamento e il tempo di arrivo) e il tempo di attesa (differenza tra il tempo di turnaround e il tempo
 * di burst).
 *
 * @param processi[] Un array di strutture "Processi" contenente i dettagli dei processi da eseguire.
 * @param numero_processi Il numero totale di processi presenti nell'array.
 * @param quantum La durata massima dell'esecuzione per ciascun processo nell'algoritmo Round Robin.
 */
void simulaRR(struct Processi processi[], int numero_processi, int quantum, int burst_totale);

#endif //SO_PROJECT_ALGORITMO_RR_H
