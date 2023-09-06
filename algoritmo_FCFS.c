//
// Created by nikoauso.
//

#include "algoritmo_FCFS.h"

void simulaFCFS(struct Processi processi[], int numero_processi, int burst_totale) {
    char buffer[5000];
    system("clear"); // Pulisce la console

    sprintf(buffer, "Simulazione Scheduling FCFS\n\n");
    strcat(buffer, "Diagramma di Gantt:\n");

    int tempo_corrente = 0;               // Il tempo corrente della simulazione
    int tempo_medio_di_attesa = 0;        // Il tempo medio di attesa dei processi
    int tempo_medio_di_turnaround = 0;    // Il tempo medio di turnaround dei processi

    // Ciclo principale della simulazione
    for (int i = 0; i < numero_processi; i++) {
        // Verifica se il tempo corrente è inferiore al tempo di arrivo del processo
        if (tempo_corrente < processi[i].tempo_arrivo) {
            tempo_corrente = processi[i].tempo_arrivo;
        }

        // Aggiunge informazioni sul processo al diagramma di Gantt
        aggiungi_info_processo(buffer, processi[i]);

        // Aggiunge spazi vuoti prima di iniziare l'esecuzione del processo se necessario
        stampa_spazi(tempo_corrente, buffer);

        // Simula l'esecuzione del processo aggiungendo '#' al diagramma di Gantt
        for (int t = 0; t < processi[i].tempo_burst; t++) {
            sprintf(buffer + strlen(buffer), "%c", '#');
            fflush(stdout);  // Svuota il buffer di output per garantire una stampa immediata
        }

        // Aggiorna il tempo corrente dopo l'esecuzione del processo
        tempo_corrente += processi[i].tempo_burst;

        // Calcola le metriche per il processo
        calcola_metriche_processo(&processi[i], tempo_corrente, &tempo_medio_di_attesa, &tempo_medio_di_turnaround);

        // Aggiunge spazi vuoti dopo l'esecuzione del processo
        stampa_spazi(burst_totale - tempo_corrente, buffer);

        // Aggiunge una riga al diagramma di Gantt indicando la terminazione del processo
        sprintf(buffer + strlen(buffer), " - [Processo %d terminato (Tempo di fine: %d)]\n", processi[i].pid,
                tempo_corrente);
    }
    // Aggiunge una riga vuota
    sprintf(buffer + strlen(buffer), "\n");

    // Stampa le statistiche generali
    stampa_risultati(processi, numero_processi, tempo_medio_di_attesa, tempo_medio_di_turnaround, buffer);

    // Stampa il contenuto del buffer (diagramma e tabella dei risultati)
    printf("%s", buffer);

    // Richiede il salvataggio su file all'utente
    richiedi_salvataggio_su_file(buffer, "FCFS");
}