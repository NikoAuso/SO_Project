//
// Created by nikoauso.
//

#ifndef SO_PROJECT_USA_FILE_JSON_H
#define SO_PROJECT_USA_FILE_JSON_H

#include "processi.h"

/**
 * Legge e analizza un file JSON contenente informazioni sui processi.
 *
 * Questa funzione legge un file JSON specificato e ne estrae i dati dei processi.
 * I dati dei processi vengono memorizzati nella struttura `Process` fornita come argomento.
 *
 * @param filename Il nome del file JSON da leggere.
 * @param processi Un array di strutture `Process` in cui memorizzare i dati dei processi.
 * @param MAX_PROCESSES Il numero massimo di processi consentito nell'array `processi`.
 *
 * @return Il numero effettivo di processi letti dal file JSON, oppure 0 in caso di errore.
 */
int leggi_file_JSON(const char *filename, struct Process processi[], int MAX_PROCESSES);

#endif //SO_PROJECT_USA_FILE_JSON_H
