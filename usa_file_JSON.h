//
// Created by nikoauso.
//

#ifndef SO_PROJECT_USA_FILE_JSON_H
#define SO_PROJECT_USA_FILE_JSON_H

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "processi.h"

/**
 * Legge e analizza un file JSON contenente informazioni sui processi.
 *
 * @param filename Il nome del file JSON da leggere.
 * @param processi Un puntatore a una variabile di tipo Processi per memorizzare le informazioni sui processi.
 * @return Il numero di processi letti dal file JSON o 0 in caso di errore.
 */
void leggi_file_JSON(const char *filename, struct Processi **processi, int *numero_processi);

#endif //SO_PROJECT_USA_FILE_JSON_H
