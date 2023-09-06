//
// Created by nikoauso.
//

#ifndef SO_PROJECT_UTILITIES_ALGORITMI_H
#define SO_PROJECT_UTILITIES_ALGORITMI_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include "processi.h"
#include "algoritmo_FCFS.h"
#include "algoritmo_SJF.h"
#include "algoritmo_SRTF.h"
#include "algoritmo_RR.h"
#include "utilities.h"

void aggiungi_info_processo(char *buffer, struct Processi processo);
void calcola_metriche_processo(struct Processi *processo, int tempo_corrente, int *tempo_medio_di_attesa,
                               int *tempo_medio_di_turnaround);

/**
 * Stampa un riepilogo dei processi selezionati che il programma processerà.
 *
 * Prende in input un array di strutture "Processi" contenente i dettagli dei processi da stampare
 * e il numero totale di processi presenti nell'array. Mostra a video un elenco dei processi con i relativi dati,
 * tra cui identificatore del processo (PID), tempo di arrivo e tempo di burst.
 *
 * @param processi[] Un array di strutture "Processi" contenente i dettagli dei processi da stampare.
 * @param numero_processi Il numero totale di processi presenti nell'array.
 */
void stampa_riepilogo_processi(struct Processi processi[], int numero_processi);

/**
 * Stampa i risultati dell'esecuzione dei processi, inclusi i tempi di arrivo,
 * burst, turnaround, attesa e tempo di fine.
 *
 * @param processi            L'array di strutture Processi contenente i dati dei processi
 * @param numero_processi     Il numero totale di processi nell'array
 * @param tempo_totale_attesa Il tempo totale di attesa di tutti i processi
 * @param tempo_totale_turnaround Il tempo totale di turnaround di tutti i processi
 */
void stampa_risultati(struct Processi processi[],
                      int numero_processi,
                      int tempo_totale_attesa,
                      int tempo_totale_turnaround,
                      char *buffer);

/**
 * Stampa un numero specificato di spazi.
 *
 * @param n Il numero di spazi da stampare.
 */
void stampa_spazi(int n, char *buffer);

/**
 * Ordina un array di processi in base al tempo di arrivo utilizzando l'algoritmo Bubble Sort
 * per simulare una coda di tipo FIFO.
 *
 * @param processi L'array di strutture Processi da ordinare.
 * @param numero_processi Il numero totale di processi nell'array.
 */
void ordine_arrivo_processi(struct Processi processi[], int numero_processi);

int calcola_burst_totale(struct Processi processi[], int numero_processi);

/**
 * Funzione che permette all'utente di scegliere un algoritmo di scheduling
 * e avvia la simulazione dell'algoritmo scelto sui processi dati in input.
 *
 * @param processi Array di processi da schedulare.
 * @param numero_processi Numero totale di processi nell'array.
 */
void scegli_algoritmo(struct Processi *processi, int numero_processi);

#endif //SO_PROJECT_UTILITIES_ALGORITMI_H
