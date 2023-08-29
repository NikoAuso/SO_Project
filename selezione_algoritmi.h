//
// Created by nikoauso.
//

#ifndef SO_PROJECT_SELEZIONE_ALGORITMI_H
#define SO_PROJECT_SELEZIONE_ALGORITMI_H

#include "processi.h"

/**
 * Consente all'utente di selezionare e avviare un algoritmo di scheduling.
 *
 * Questa funzione visualizza un menu in cui l'utente può scegliere tra diversi algoritmi di scheduling.
 * Dopo aver fatto la scelta, l'algoritmo selezionato viene avviato sulla lista dei processi forniti.
 * Gli algoritmi disponibili sono: FCFS (First-Come, First-Served), SJF (Shortest Job First),
 * Round Robin e SRTF (Shortest Remaining Time First).
 *
 * @param processi Un array di strutture "Process" contenente i dettagli dei processi da eseguire.
 * @param numero_processi Il numero totale di processi presenti nell'array.
 */
void scegli_algoritmo(struct Process *processi, int numero_processi);

#endif //SO_PROJECT_SELEZIONE_ALGORITMI_H
