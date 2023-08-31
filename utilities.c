//
// Created by nikoauso on.
//

#include "utilities.h"

void stampa_riepilogo_processi(struct Process processi[], int numero_processi) {
    printf("Ecco i dati dei processi selezionati:\n");
    printf("            | T. Arrivo  | T. Burst  |\n");

    // Itera attraverso ogni processo nell'array e stampa i dati formattati
    for (int i = 0; i < numero_processi; ++i) {
        // Formattazione del processo i-esimo
        printf("Processo %s%d |     %s%d     |     %s%d    |\n",
               ((int) log10(processi[i].pid) + 1 == 1) ? " " : "", // Aggiunge spazio prima di ogni numero se composto da una sola cifra
               processi[i].pid,
               ((int) log10(processi[i].tempo_arrivo) + 1 == 1) ? " " : "",
               processi[i].tempo_arrivo,
               ((int) log10(processi[i].tempo_burst) + 1 == 1) ? " " : "",
               processi[i].tempo_burst);
    }
    printf("\n");
}

void stampa_risultati(struct Process processi[], int numero_processi, int tempo_totale_attesa, int tempo_totale_turnaround) {
    float tempo_medio_attesa = (float)tempo_totale_attesa / (float) numero_processi;
    float tempo_medio_turnaround = (float)tempo_totale_turnaround / (float) numero_processi;

    printf("\nTabella risultati:\n");
    printf("    | T. Arrivo | T. Burst | T. Fine | T. Turnaround | T. Attesa |\n");
    for (int i = 0; i < numero_processi; ++i) {
        printf("P%d%s |    %s%d     |    %s%d    |    %s%d   |       %s%d      |     %s%d    |\n",
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
    printf("                         Tempo medio |      %.*f     |    %.*f   |\n\n",
           tempo_medio_turnaround < 10 ? 2 : 1, tempo_medio_turnaround,
           tempo_medio_attesa < 10 ? 2 : 1, tempo_medio_attesa);
}

void senza_file() {
    struct Process **processi = NULL;

    // Richiede il numero di processi da simulare all'utente
    printf("Inserisci il numero di processi da simulare (fino a %d): ", MAX_PROCESSES);
    int numero_processi = leggi_input_intero();

    // Verifica se il numero inserito supera il limite massimo consentito
    if (numero_processi > MAX_PROCESSES) {
        printf("Il numero massimo di processi consentito è %d.\n", MAX_PROCESSES);
        exit(1);
    }

    // Alloca memoria per l'array di puntatori alle strutture Process in base al numero di processi inseriti
    processi = (struct Process **) malloc(numero_processi * sizeof(struct Process *));

    // Legge i dati dei processi
    for (int i = 0; i < numero_processi; i++) {
        // Alloca memoria per una nuova struttura Process
        processi[i] = (struct Process *) malloc(sizeof(struct Process));

        // Richiede il tempo di arrivo e il tempo di burst per il processo
        printf("Inserisci il tempo di arrivo per il processo %d: ", i + 1);
        int tempo_arrivo = leggi_input_intero();
        processi[i]->tempo_arrivo = tempo_arrivo;
        printf("Inserisci il tempo di burst per il processo %d: ", i + 1);
        int tempo_burst = leggi_input_intero();

        // Inizializza i campi dell'array di processi
        processi[i]->tempo_burst = tempo_burst;
        processi[i]->pid = i + 1;
        processi[i]->tempo_rimanente = processi[i]->tempo_burst;
        processi[i]->tempo_fine = 0;
        processi[i]->tempo_turnaround = 0;
        processi[i]->tempo_attesa = 0;
    }
    // Stampa un riepilogo dei processi inseriti
    stampa_riepilogo_processi(*processi, numero_processi);

    // Chiama la funzione per scegliere l'algoritmo di simulazione
    scegli_algoritmo(*processi, numero_processi);

    // Libera la memoria allocata per le strutture Process
    for (int i = 0; i < numero_processi; i++) {
        free(processi[i]);
    }
    free(processi);
}

void con_file(char * filename) {
    struct Process *processi = NULL; // Puntatore all'array di strutture Process
    int numero_processi = leggi_file_JSON(filename, &processi, MAX_PROCESSES); // Carica i dati dal file JSON

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

bool numero_intero(char input) {
    if (isdigit(input)) { // Verifica se il carattere è a una cifra
        int num = input - '0'; // Converte il carattere in un intero
        return num >= 0 && num <= 9; // Controlla se è un intero positivo a una cifra
    }
    return false;
}

int leggi_input_intero() {
    char input;

    // Leggi un carattere dall'input standard
    scanf("%c", &input);

    // Consuma il carattere newline residuo nel buffer
    getchar();

    // Verifica se il carattere letto è un numero intero valido
    if (!numero_intero(input)) {
        printf("Errore: Input non valido!\n");
        return -1;
    }

    // Converte il carattere numerico in un intero usando la funzione atoi()
    int numero = atoi(&input);

    return numero;
}

void stampaSpazi(int n) {
    for (int i = 0; i < n; i++) {
        printf("_");
    }
}

void ordina_processi(struct Process processi[], int numero_processi) {
    for (int i = 0; i < numero_processi - 1; i++) {
        for (int j = 0; j < numero_processi - i - 1; j++) {
            if (processi[j].tempo_arrivo > processi[j + 1].tempo_arrivo) {
                // Scambia i processi[j] e processi[j + 1]
                struct Process temp = processi[j];
                processi[j] = processi[j + 1];
                processi[j + 1] = temp;
            }
        }
    }
}