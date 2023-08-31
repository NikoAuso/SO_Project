//
// Created by nikoauso.
//

#ifndef SO_PROJECT_UTILITIES_H
#define SO_PROJECT_UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "usa_file_JSON.h"
#include "selezione_algoritmi.h"
#include "processi.h"

//Numero massimo di processi ammissibili
#define MAX_PROCESSES 10

/**
 * Stampa un riepilogo dei processi selezionati che il programma processerà.
 *
 * Prende in input un array di strutture "Process" contenente i dettagli dei processi da stampare
 * e il numero totale di processi presenti nell'array. Mostra a video un elenco dei processi con i relativi dati,
 * tra cui identificatore del processo (PID), tempo di arrivo e tempo di burst.
 *
 * @param processi[] Un array di strutture "Process" contenente i dettagli dei processi da stampare.
 * @param numero_processi Il numero totale di processi presenti nell'array.
 */
void stampa_riepilogo_processi(struct Process processi[], int numero_processi);

/**
 * Stampa i risultati dell'esecuzione dei processi, inclusi i tempi di arrivo,
 * burst, turnaround, attesa e tempo di fine.
 *
 * @param processi            L'array di strutture Process contenente i dati dei processi
 * @param numero_processi     Il numero totale di processi nell'array
 * @param tempo_totale_attesa Il tempo totale di attesa di tutti i processi
 * @param tempo_totale_turnaround Il tempo totale di turnaround di tutti i processi
 */
void stampa_risultati(struct Process processi[], int numero_processi, int tempo_totale_attesa, int tempo_totale_turnaround);

/**
 * Gestisce la creazione e l'inserimento manuale dei dati dei processi senza utilizzare un file.
 * Chiede all'utente di inserire il numero di processi da simulare e raccoglie le informazioni necessarie per ciascun processo.
 * Successivamente, visualizza un riepilogo dei processi inseriti e avvia la selezione dell'algoritmo di scheduling.
 */
void senza_file();

/**
 * Carica un file JSON contenente informazioni sui processi,
 * elabora i dati e infine libera la memoria allocata.
 *
 * @param filename Il nome del file JSON da cui caricare i dati dei processi.
 */
void con_file(char * filename);

/**
 * Verifica se un carattere rappresenta un numero intero di una cifra.
 *
 * @param input Il carattere da verificare.
 * @return True se il carattere è un numero intero di una cifra, altrimenti False.
 */
bool numero_intero(char input);

/**
 * Legge un carattere dall'input standard e restituisce un intero corrispondente.
 * Verifica se l'input è un numero intero valido e lo converte.
 *
 * @return L'intero letto dall'input, oppure -1 in caso di errore.
 */
int leggi_input_intero();

/**
 * Stampa un numero specificato di spazi.
 *
 * @param n Il numero di spazi da stampare.
 */
void stampaSpazi(int n);

/**
 * Ordina un array di processi in base al tempo di arrivo utilizzando l'algoritmo Bubble Sort
 * per simulare una coda di tipo FIFO.
 *
 * @param processi L'array di strutture Process da ordinare.
 * @param numero_processi Il numero totale di processi nell'array.
 */
void ordina_processi(struct Process processi[], int numero_processi);

#endif //SO_PROJECT_UTILITIES_H
