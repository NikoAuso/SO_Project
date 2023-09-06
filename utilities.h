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
#include <sys/stat.h>
#include "cJSON.h"
#include "utilities_algoritmi.h"
#include "processi.h"

/**
 * Verifica se una stringa contiene un numero intero valido.
 *
 * @param input La stringa da verificare.
 * @return `true` se la stringa contiene un numero intero valido, altrimenti `false`.
 */
bool numero_intero(const char *input);

/**
 * Legge un input intero dalla console.
 * Verifica se l'input è valido e lo converte.
 *
 * @return Il numero intero letto dalla console o -1 in caso di errore.
 */
int leggi_input_intero();

/**
 * Gestisce la creazione e l'inserimento manuale dei dati dei processi senza utilizzare un file.
 * Chiede all'utente di inserire il numero di processi da simulare e raccoglie le informazioni necessarie per ciascun processo.
 * Successivamente, visualizza un riepilogo dei processi inseriti e avvia la selezione dell'algoritmo di scheduling.
 */
void senza_file();

/**
 * Carica un file JSON contenente informazioni sui processi, elabora i dati
 * e infine libera la memoria allocata.
 *
 * @param filename Il nome del file JSON da cui caricare i dati dei processi.
 */
void con_file(char *filename);

/**
 * Richiede all'utente se desidera salvare il contenuto dei risultati in un file.
 *
 * @param buffer    Il contenuto da salvare nel file.
 * @param algoritmo Il nome dell'algoritmo utilizzato per la simulazione.
 */
void richiedi_salvataggio_su_file(char *buffer, const char *algoritmo);


/**
 * Legge e carica i dati dei processi da un file JSON.
 *
 * @param filename       Il nome del file JSON contenente i dati dei processi.
 * @param processi       Un puntatore all'array di strutture `Processi` da riempire con i dati del file.
 * @param numero_processi Un puntatore all'intero che conterrà il numero di processi caricati.
 */
void leggi_file_JSON(const char *filename, struct Processi **processi, int *numero_processi);

/**
 * Visualizza un effetto spinner per indicare un'operazione di caricamento in corso.
 */
void loading_spinner();

#endif //SO_PROJECT_UTILITIES_H
