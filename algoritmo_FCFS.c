//
// Created by nikoauso.
//

#include "algoritmo_FCFS.h"

void simulaFCFS(struct Processi processi[], int numero_processi, int burst_totale) {
    char buffer[5000];
    system("clear");

    sprintf(buffer, "Simulazione Scheduling FCFS\n\n");
    strcat(buffer, "Diagramma di Gantt:\n");

    int tempo_corrente = 0;
    int tempo_medio_di_attesa = 0;
    int tempo_medio_di_turnaround = 0;

    for (int i = 0; i < numero_processi; i++) {
        // Verifica se il tempo corrente è inferiore al tempo di arrivo del processo
        if (tempo_corrente < processi[i].tempo_arrivo) {
            tempo_corrente = processi[i].tempo_arrivo;
        }

        // Aggiunge informazioni sul processo al diagramma di Gantt
        sprintf(buffer + strlen(buffer), "Processo %s%d (T. arrivo: %s%d - T. burst: %s%d) -->",
                ((int) log10(processi[i].pid) + 1 < 2) ? " " : "",
                processi[i].pid,
                ((int) log10(processi[i].tempo_arrivo) + 1 < 2) ? " " : "",
                processi[i].tempo_arrivo,
                ((int) log10(processi[i].tempo_burst) + 1 < 2) ? " " : "",
                processi[i].tempo_burst);

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
        processi[i].tempo_fine = tempo_corrente;
        processi[i].tempo_turnaround = processi[i].tempo_fine - processi[i].tempo_arrivo;
        processi[i].tempo_attesa = processi[i].tempo_turnaround - processi[i].tempo_burst;
        tempo_medio_di_turnaround += processi[i].tempo_turnaround;
        tempo_medio_di_attesa += processi[i].tempo_attesa;

        // Aggiunge spazi vuoti dopo l'esecuzione del processo
        stampa_spazi(burst_totale - tempo_corrente, buffer);

        // Aggiunge informazioni sulla terminazione del processo
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