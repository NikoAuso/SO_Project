//
// Created by nikoauso.
//

#ifndef SO_PROJECT_SELEZIONE_ALGORITMI_H
#define SO_PROJECT_SELEZIONE_ALGORITMI_H

#include <stdio.h>
#include <stdlib.h>
#include "processi.h"
#include "algoritmo_FCFS.h"
#include "algoritmo_SJF.h"
#include "algoritmo_SRTF.h"
#include "algoritmo_RR.h"
#include "utilities.h"

/**
 * Funzione che permette all'utente di scegliere un algoritmo di scheduling
 * e avvia la simulazione dell'algoritmo scelto sui processi dati in input.
 *
 * @param processi Array di processi da schedulare.
 * @param numero_processi Numero totale di processi nell'array.
 */
void scegli_algoritmo(struct Process *processi, int numero_processi);

#endif //SO_PROJECT_SELEZIONE_ALGORITMI_H
