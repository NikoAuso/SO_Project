//
// Created by nikoauso.
//

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "leggi_file_JSON.h"

// Funzione per leggere e analizzare il file JSON
int leggi_file_JSON(const char *filename, struct Process *processi[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Impossibile aprire il file %s.\n", filename);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long lunghezzaFile = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(lunghezzaFile + 1);
    fread(buffer, 1, lunghezzaFile, file);
    fclose(file);

    buffer[lunghezzaFile] = '\0';

    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL) {
        const char *errore = cJSON_GetErrorPtr();
        if (errore != NULL) {
            fprintf(stderr, "Errore durante il parsing JSON: %s\n", errore);
        }
        free(buffer);
        return 0;
    }

    cJSON *processiJSON = cJSON_GetObjectItemCaseSensitive(json, "processi");
    if (!cJSON_IsArray(processiJSON)) {
        cJSON_Delete(json);
        free(buffer);
        return 0;
    }

    int numProcessi = cJSON_GetArraySize(processiJSON);
    if (numProcessi > MAX_PROCESSES) {
        printf("Il numero massimo di processi consentito è %d.\n", MAX_PROCESSES);
        cJSON_Delete(json);
        free(buffer);
        return 0;
    }

    *processi = (struct Process *)malloc(numProcessi * sizeof(struct Process));

    for (int i = 0; i < MAX_PROCESSES; i++) {
        cJSON *processoJSON = cJSON_GetArrayItem(processiJSON, i);
        if (cJSON_IsObject(processoJSON)) {
            (*processi)[i].pid = cJSON_GetObjectItemCaseSensitive(processoJSON, "pid")->valueint;
            (*processi)[i].tempo_arrivo = cJSON_GetObjectItemCaseSensitive(processoJSON, "tempo_arrivo")->valueint;
            (*processi)[i].tempo_burst = cJSON_GetObjectItemCaseSensitive(processoJSON, "tempo_burst")->valueint;
            (*processi)[i].tempo_rimanente = (*processi)[i].tempo_burst;
        }
    }

    cJSON_Delete(json);
    free(buffer);

    return numProcessi;
}
