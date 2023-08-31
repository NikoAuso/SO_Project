//
// Created by nikoauso.
//

#include "usa_file_JSON.h"

int leggi_file_JSON(const char *filename, struct Process **processi, int MAX_PROCESSES) {
    // Apre il file JSON in modalità di lettura
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Impossibile aprire il file %s.\n", filename);
        return 0;
    }

    // Calcola la lunghezza del file
    fseek(file, 0, SEEK_END);
    long lunghezzaFile = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Alloca memoria per il buffer
    char *buffer = (char *)malloc(lunghezzaFile + 1);

    // Legge il contenuto del file, lo mette nel buffer e chiudi il file
    fread(buffer, 1, lunghezzaFile, file);
    fclose(file);

    buffer[lunghezzaFile] = '\0';

    // Effettua il parsing del JSON
    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL) {
        const char *errore = cJSON_GetErrorPtr();
        if (errore != NULL) {
            fprintf(stderr, "Errore durante il parsing JSON: %s\n", errore);
        }
        free(buffer);
        return 0;
    }

    // Ottiene l'oggetto JSON contenente l'array di processi
    cJSON *processiJSON = cJSON_GetObjectItemCaseSensitive(json, "processi");
    if (!cJSON_IsArray(processiJSON)) {
        cJSON_Delete(json);
        free(buffer);
        return 0;
    }

    // Verifica il numero di processi nel JSON
    int numero_processi = cJSON_GetArraySize(processiJSON);
    if (numero_processi > MAX_PROCESSES) {
        printf("Il numero massimo di processi consentito è %d.\n", MAX_PROCESSES);
        cJSON_Delete(json);
        free(buffer);
        return 0;
    }

    // Alloca memoria dinamicamente per il numero di processi nel JSON
    *processi = (struct Process *)malloc(numero_processi * sizeof(struct Process));
    if (*processi == NULL) {
        printf("Errore nell'allocazione di memoria.\n");
        cJSON_Delete(json);
        free(buffer);
        return 0;
    }

    // Estrae le informazioni di ciascun processo dall'array JSON
    for (int i = 0; i < numero_processi; i++) {
        cJSON *processoJSON = cJSON_GetArrayItem(processiJSON, i);
        if (cJSON_IsObject(processoJSON)) {
            (*processi)[i].pid = cJSON_GetObjectItemCaseSensitive(processoJSON, "pid")->valueint;
            (*processi)[i].tempo_arrivo = cJSON_GetObjectItemCaseSensitive(processoJSON, "tempo_arrivo")->valueint;
            (*processi)[i].tempo_burst = cJSON_GetObjectItemCaseSensitive(processoJSON, "tempo_burst")->valueint;
            (*processi)[i].tempo_rimanente = (*processi)[i].tempo_burst;
            (*processi)[i].tempo_fine = 0;
            (*processi)[i].tempo_turnaround = 0;
            (*processi)[i].tempo_attesa = 0;
        }
    }

    // Libera la memoria allocata per il JSON e il buffer
    cJSON_Delete(json);
    free(buffer);

    // Restituisce il numero di processi letti
    return numero_processi;
}
