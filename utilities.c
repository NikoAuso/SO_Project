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

void stampa_riepilogo_processi(struct Processi processi[], int numero_processi) {
    printf("Ecco i dati dei processi selezionati:\n");
    printf("            | T. Arrivo  | T. Burst  |\n");

    // Itera attraverso ogni processo nell'array e stampa i dati formattati
    for (int i = 0; i < numero_processi; ++i) {
        // Formattazione del processo i-esimo
        printf("Processo %s%d |     %s%d     |     %s%d    |\n",
                // Aggiunge spazio prima di ogni numero se composto da una sola cifra
               ((int) log10(processi[i].pid) + 1 == 1) ? " " : "",
               processi[i].pid,
               ((int) log10(processi[i].tempo_arrivo) + 1 == 1) ? " " : "",
               processi[i].tempo_arrivo,
               ((int) log10(processi[i].tempo_burst) + 1 == 1) ? " " : "",
               processi[i].tempo_burst);
    }
    printf("\n");
}

void stampa_risultati(struct Processi processi[],
                      int numero_processi,
                      int tempo_totale_attesa,
                      int tempo_totale_turnaround,
                      char *buffer) {
    float tempo_medio_attesa = (float) tempo_totale_attesa / (float) numero_processi;
    float tempo_medio_turnaround = (float) tempo_totale_turnaround / (float) numero_processi;

    sprintf(buffer + strlen(buffer), "Tabella risultati:\n");
    sprintf(buffer + strlen(buffer), "    | T. Arrivo | T. Burst | T. Fine | T. Turnaround | T. Attesa |\n");
    for (int i = 0; i < numero_processi; ++i) {
        sprintf(buffer + strlen(buffer),
                "P%d%s |    %s%d     |    %s%d    |    %s%d   |       %s%d      |     %s%d    |\n",
                processi[i].pid,
                ((int) log10(processi[i].pid) + 1 < 2) ? " " : "",
                ((int) log10(processi[i].tempo_arrivo) + 1 < 2) ? " " : "",
                processi[i].tempo_arrivo,
                ((int) log10(processi[i].tempo_burst) + 1 < 2) ? " " : "",
                processi[i].tempo_burst,
                ((int) log10(processi[i].tempo_fine) + 1 < 2) ? " " : "",
                processi[i].tempo_fine,
                ((int) log10(processi[i].tempo_turnaround) + 1 < 2) ? " " : "",
                processi[i].tempo_turnaround,
                ((int) log10(processi[i].tempo_attesa) + 1 < 2) ? " " : "",
                processi[i].tempo_attesa);
    }
    sprintf(buffer + strlen(buffer), "                         Tempo medio |      %.*f     |    %.*f   |\n",
            tempo_medio_turnaround < 10 ? 2 : 1, tempo_medio_turnaround,
            tempo_medio_attesa < 10 ? 2 : 1, tempo_medio_attesa);
}


void stampa_spazi(int n, char *buffer) {
    for (int i = 0; i < n; i++) {
        sprintf(buffer + strlen(buffer), "_");
    }
}

void ordine_arrivo_processi(struct Processi processi[], int numero_processi) {
    for (int i = 0; i < numero_processi - 1; i++) {
        for (int j = 0; j < numero_processi - i - 1; j++) {
            if (processi[j].tempo_arrivo > processi[j + 1].tempo_arrivo) {
                // Scambia i processi[j] e processi[j + 1]
                struct Processi temp = processi[j];
                processi[j] = processi[j + 1];
                processi[j + 1] = temp;
            }
        }
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
        char nome_file[100] = "risultati_";
        strcat(nome_file, algoritmo);
        char nome_file_con_estensione[100];
        strcpy(nome_file_con_estensione, nome_file);

        file = fopen(strcat(nome_file_con_estensione, ".txt"), "r");
        if (file != NULL) {
            strcat(nome_file, "_1");
            fclose(file);
        }
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

int calcola_burst_totale(struct Processi processi[], int numero_processi) {
    int burst_totale = 0;
    int t_arrivo_piu_breve = INT_MAX;
    for (int i = 0; i < numero_processi; ++i) {
        if (t_arrivo_piu_breve > processi[i].tempo_arrivo) {
            t_arrivo_piu_breve = processi[i].tempo_arrivo;
            burst_totale += processi[i].tempo_arrivo;
        }
        burst_totale += processi[i].tempo_burst;
    }
    return burst_totale;
}