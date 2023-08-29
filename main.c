//
// Created by nikoauso.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "usa_file_JSON.h"
#include "selezione_algoritmi.h"
#include "controlla_input.h"

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
void stampa_riepilogo_processi(struct Process processi[], int numero_processi) {
    printf("Ecco i dati dei processi selezionati:\n");
    printf("            | T. Arrivo  | T. Burst  |\n");
    for (int i = 0; i < numero_processi; ++i) {
        printf("Processo %s%d |     %s%d     |     %s%d    |\n",
               ((int)log10(processi[i].pid)+1 == 1) ? " " : "",
               processi[i].pid,
               ((int)log10(processi[i].tempo_arrivo)+1 == 1) ? " " : "",
               processi[i].tempo_arrivo,
               ((int)log10(processi[i].tempo_burst)+1 == 1) ? " " : "",
               processi[i].tempo_burst);
    }
    printf("\n");
}

/**
 * Gestisce la creazione e l'inserimento manuale dei dati dei processi senza utilizzare un file.
 * Chiede all'utente di inserire il numero di processi da simulare e raccoglie le informazioni necessarie per ciascun processo.
 * Successivamente, visualizza un riepilogo dei processi inseriti e avvia la selezione dell'algoritmo di scheduling.
 */
void senza_file() {
    struct Process **processi = NULL;
    printf("Inserisci il numero di processi da simulare (fino a %d): ", MAX_PROCESSES);
    int numero_processi = leggi_input_intero();
    if (numero_processi > MAX_PROCESSES) {
        printf("Il numero massimo di processi consentito è %d.\n", MAX_PROCESSES);
        exit(1);
    }
    processi = (struct Process **) malloc(numero_processi * sizeof(struct Process *));
    for (int i = 0; i < numero_processi; i++) {
        processi[i] = (struct Process *) malloc(sizeof(struct Process));
        printf("Inserisci il tempo di arrivo per il processo %d: ", i + 1);
        int tempo_arrivo = leggi_input_intero();
        processi[i]->tempo_arrivo = tempo_arrivo;
        printf("Inserisci il tempo di burst per il processo %d: ", i + 1);
        int tempo_burst = leggi_input_intero();
        processi[i]->tempo_burst = tempo_burst;
        processi[i]->pid = i + 1;
        processi[i]->tempo_rimanente = processi[i]->tempo_burst;
        processi[i]->tempo_fine = 0;
        processi[i]->tempo_turnaround = 0;
        processi[i]->tempo_attesa = 0;
    }
    stampa_riepilogo_processi(*processi, numero_processi);
    scegli_algoritmo(*processi, numero_processi);
    free(processi);
}

/**
 * Legge i dati dei processi da un file JSON e li utilizza per la simulazione dell'algoritmo di scheduling.
 * Mostra un riepilogo dei processi letti dal file e avvia la selezione dell'algoritmo di scheduling.
 */
void con_file() {
    struct Process processi[MAX_PROCESSES];
    int numero_processi = leggi_file_JSON("../processi.json", processi,
                                          MAX_PROCESSES);
    stampa_riepilogo_processi(processi, numero_processi);
    scegli_algoritmo(processi, numero_processi);
}

/**
 * Mostra un'intestazione di benvenuto e offre all'utente la scelta di utilizzare
 * i dati da un file JSON o inserirli manualmente. Dopo aver eseguito la simulazione dell'algoritmo di scheduling,
 * chiede all'utente se desidera riprovare o terminare il programma.
 *
 * @return 0 se il programma è eseguito correttamente, 1 in caso di errore.
 */
int main() {
    printf("Benvenuto nel SIMULATORE DI SCHEDULING DEI PROCESSI!\n\n");
    printf("$$$$$$$\\   $$$$$$\\   $$$$$$\\  \n"
           "$$  __$$\\ $$  __$$\\ $$  __$$\\ \n"
           "$$ |  $$ |$$ /  \\__|$$ /  \\__|\n"
           "$$$$$$$  |\\$$$$$$\\  \\$$$$$$\\  \n"
           "$$  ____/  \\____$$\\  \\____$$\\ \n"
           "$$ |      $$\\   $$ |$$\\   $$ |\n"
           "$$ |      \\$$$$$$  |\\$$$$$$  |\n"
           "\\__|       \\______/  \\______/\n\n");

    printf("Il tempo di esecuzione dei processi è espresso in secondi.\n");
    printf("Il simulatore offre un set di processi già pre-impostati che puoi utilizzare per semplificare l'inserimento dei dati.\n");
    printf("Puoi modificare ora il file o utilizzare i dati già inseriti.\n");
    while (true) {
        char usa_file;
        printf("Vuoi utilizzare il file? (y/N): ");
        scanf(" %c", &usa_file);
        getchar();

        if (usa_file == 'y' || usa_file == 'Y') {
            con_file();
        } else if (usa_file == 'n' || usa_file == 'N') {
            senza_file();
        } else {
            printf("Errore: input non valido!");
            return 1;
        }
        char riprova;
        printf("Vuoi riprovare? (y/N): ");
        scanf(" %c", &riprova);
        getchar();
        if (riprova == 'n' || riprova == 'N') {
            break;
        }
        system("clear");
    }
    return 0;
}
