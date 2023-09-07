//
// Created by nikoauso.
//

#include "utilities.h"

bool numero_intero(const char *input) {
    // Verifica se tutti i caratteri nella input sono cifre
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

int leggi_input_intero() {
    char input[2];

    // Leggi una linea dall'input standard
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Errore nella lettura dell'input.\n");
        return -1;
    }

    // Rimuovi il carattere di nuova riga (se presente)
    if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }

    // Consuma il carattere newline residuo nel buffer
    getchar();

    // Verifica se il carattere letto è un numero intero valido
    if (!numero_intero(input)) {
        printf("Errore: Input non valido!\n");
        return -1;
    }

    // Converte il carattere numerico in un intero usando la funzione atoi()
    int numero = atoi(input);

    return numero;
}

void senza_file() {
    struct Processi **processi = NULL;

    // Richiede il numero di processi da simulare all'utente
    printf("Inserisci il numero di processi da simulare (fino a %d): ", MAX_PROCESSES);
    int numero_processi = leggi_input_intero();

    // Verifica se il numero inserito supera il limite massimo consentito
    if (numero_processi > MAX_PROCESSES) {
        printf("Il numero massimo di processi consentito è %d.\n", MAX_PROCESSES);
        exit(1);
    }

    // Alloca memoria per l'array di puntatori alle strutture Processi in base al numero di processi inseriti
    processi = (struct Processi **) malloc(numero_processi * sizeof(struct Processi *));

    // Legge i dati dei processi
    for (int i = 0; i < numero_processi; i++) {
        // Alloca memoria per una nuova struttura Processi
        processi[i] = (struct Processi *) malloc(sizeof(struct Processi));

        // Richiede il tempo di arrivo e il tempo di burst per il processo
        printf("Inserisci il tempo di arrivo per il processo %d: ", i + 1);
        int tempo_arrivo = leggi_input_intero();
        printf("Inserisci il tempo di burst per il processo %d: ", i + 1);
        int tempo_burst = leggi_input_intero();

        // Inizializza i campi dell'array di processi
        processi[i]->pid = i + 1;
        processi[i]->tempo_arrivo = tempo_arrivo;
        processi[i]->tempo_burst = tempo_burst;
        processi[i]->tempo_rimanente = processi[i]->tempo_burst;
        processi[i]->tempo_fine = 0;
        processi[i]->tempo_turnaround = 0;
        processi[i]->tempo_attesa = 0;
    }

    // Stampa un riepilogo dei processi inseriti
    stampa_riepilogo_processi(*processi, numero_processi);

    // Chiama la funzione per scegliere l'algoritmo di simulazione
    scegli_algoritmo(*processi, numero_processi);

    // Libera la memoria allocata per le strutture Processi
    for (int i = 0; i < numero_processi; i++) {
        free(processi[i]);
    }
    free(processi);
}

void con_file(char *filename) {
    struct Processi *processi = NULL;
    int numero_processi = 0;
    leggi_file_JSON(filename, &processi, &numero_processi); // Carica i dati dal file JSON

    // Verifica se sono stati caricati con successo dei processi dal file
    if (numero_processi > 0) {
        // Stampa un riepilogo dei processi caricati
        stampa_riepilogo_processi(processi, numero_processi);

        // Sceglie l'algoritmo da utilizzare per elaborare i processi
        scegli_algoritmo(processi, numero_processi);

        // Libera la memoria allocata per l'array di processi una volta finito l'uso
        free(processi);
    }
}

void richiedi_salvataggio_su_file(char *buffer, const char *algoritmo) {
    // Chiede all'utente se vuole utilizzare un file per i dati o inserirli manualmente
    char salva_file;
    printf("Vuoi salvare i risultati in file? (y/N): ");
    scanf(" %c", &salva_file);
    getchar(); // Consume il carattere di nuova riga nel buffer

    if (salva_file == 'y' || salva_file == 'Y') {
        FILE *file;

        // Inizializza il nome del file contenente i risultati
        char nome_file[100] = "risultati_";
        strcat(nome_file, algoritmo);

        // Crea una copia del nome inizializzato sopra
        // Questa variabile verrà utilizzata per controllare se esiste già un file con questo nome
        char nome_file_con_estensione[100];
        strcpy(nome_file_con_estensione, nome_file);

        file = fopen(strcat(nome_file_con_estensione, ".txt"), "r");
        if (file != NULL) {
            // Esiste già un file; aggiunge "_1" al nome e chiude il file aperto
            strcat(nome_file, "_1");
            fclose(file);
        }
        // Aggiunge l'estensione al file
        strcat(nome_file, ".txt");

        // Apri il file in modalità di scrittura
        file = fopen(nome_file, "w");

        // Verifica se l'apertura del file ha avuto successo
        if (file == NULL) {
            perror("Errore nell'apertura del file");
            return;
        }

        // Scrivi il contenuto di buffer nel file
        fprintf(file, "%s", buffer);

        // Chiudi il file
        fclose(file);

        printf("Dati salvati con successo nel file: %s\n", nome_file);
    } else if (salva_file == 'n' || salva_file == 'N') {
        return;
    } else {
        // Messaggio di errore per input non valido
        printf("Errore: input non valido!");
        return; // Termina il programma con codice di errore
    }
}

void leggi_file_JSON(const char *filename, struct Processi **processi, int *numero_processi) {
    // Apre il file JSON in modalità di lettura
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Impossibile aprire il file %s.\n", filename);
        exit(1);
    }

    // Calcola la lunghezza del file
    fseek(file, 0, SEEK_END);
    long lunghezzaFile = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Alloca memoria per il buffer
    char *buffer = (char *) malloc(lunghezzaFile + 1);

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
        exit(1);
    }

    // Ottiene l'oggetto JSON contenente l'array di processi
    cJSON *processiJSON = cJSON_GetObjectItemCaseSensitive(json, "processi");
    if (!cJSON_IsArray(processiJSON)) {
        cJSON_Delete(json);
        free(buffer);
        exit(1);
    }

    // Verifica il numero di processi nel JSON
    int numero_processi_ottenuti = cJSON_GetArraySize(processiJSON);
    if (numero_processi_ottenuti > MAX_PROCESSES) {
        printf("Il numero massimo di processi consentito è %d.\n", MAX_PROCESSES);
        cJSON_Delete(json);
        free(buffer);
        exit(1);
    }
    *numero_processi = numero_processi_ottenuti;

    // Alloca memoria dinamicamente per il numero di processi nel JSON
    *processi = (struct Processi *) malloc(*numero_processi * sizeof(struct Processi));
    if (*processi == NULL) {
        printf("Errore nell'allocazione di memoria.\n");
        cJSON_Delete(json);
        free(buffer);
        exit(1);
    }

    // Estrae le informazioni di ciascun processo dall'array JSON
    for (int i = 0; i < *numero_processi; i++) {
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
}

void loading_spinner() {
    static char bars[] = { '/', '-', '\\', '|' }; // Array di caratteri per l'effetto spinner
    static int nbars = sizeof(bars) / sizeof(char); // Numero di caratteri nell'array
    static int pos = 0; // Posizione corrente nel ciclo di caratteri

    // Stampa il carattere corrente del ciclo di caratteri sovrascrivendo la riga precedente
    printf("Calcolando %c\r", bars[pos]);

    fflush(stdout); // Assicura che il testo venga visualizzato immediatamente

    pos = (pos + 1) % nbars; // Passa al carattere successivo nel ciclo
}
