//
// Created by nikoauso.
//

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "usa_file_JSON.h"

int leggi_file_JSON(const char *filename, struct Process processi[], int MAX_PROCESSES) {
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

    int numero_processi = cJSON_GetArraySize(processiJSON);
    if (numero_processi > MAX_PROCESSES) {
        printf("Il numero massimo di processi consentito è %d.\n", MAX_PROCESSES);
        cJSON_Delete(json);
        free(buffer);
        return 0;
    }

    for (int i = 0; i < numero_processi; i++) {
        cJSON *processoJSON = cJSON_GetArrayItem(processiJSON, i);
        if (cJSON_IsObject(processoJSON)) {
            processi[i].pid = cJSON_GetObjectItemCaseSensitive(processoJSON, "pid")->valueint;
            processi[i].tempo_arrivo = cJSON_GetObjectItemCaseSensitive(processoJSON, "tempo_arrivo")->valueint;
            processi[i].tempo_burst = cJSON_GetObjectItemCaseSensitive(processoJSON, "tempo_burst")->valueint;
            processi[i].tempo_rimanente = processi[i].tempo_burst;
            processi[i].tempo_fine = 0;
            processi[i].tempo_turnaround = 0;
            processi[i].tempo_attesa = 0;
        }
    }

    cJSON_Delete(json);
    free(buffer);

    return numero_processi;
}
