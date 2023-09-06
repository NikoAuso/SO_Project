//
// Created by nikoauso.
//

#include "algoritmo_RR.h"

void simulaRR(struct Processi processi[], int numero_processi, int quantum, int burst_totale) {
    char buffer[5000];
    system("clear"); // Pulisce la console

    sprintf(buffer, "Simulazione Scheduling RR\n\n");
    strcat(buffer, "Diagramma di Gantt:\n");

    int tempo_corrente = 0;               // Il tempo corrente della simulazione
    int tempo_medio_di_attesa = 0;        // Il tempo medio di attesa dei processi
    int tempo_medio_di_turnaround = 0;    // Il tempo medio di turnaround dei processi
    int processi_completati = 0;          // Il numero i processi completato

    // Ciclo principale della simulazione
    while (processi_completati < numero_processi) {
        for (int i = 0; i < numero_processi; i++) {
            // Verifica se il tempo corrente è inferiore al tempo di arrivo del processo
            if (tempo_corrente < processi[i].tempo_arrivo) {
                tempo_corrente = processi[i].tempo_arrivo;
            }
            if (processi[i].tempo_rimanente > 0) {
                int burst = (processi[i].tempo_rimanente > quantum) ? quantum : processi[i].tempo_rimanente;

                // Aggiunge informazioni sul processo al diagramma di Gantt
                aggiungi_info_processo(buffer, processi[i]);

                // Aggiunge spazi vuoti prima di iniziare l'esecuzione del processo se necessario
                stampa_spazi(tempo_corrente, buffer);

                // Simula l'esecuzione del processo aggiungendo '#' al diagramma di Gantt
                for (int t = 0; t < burst; t++) {
                    sprintf(buffer + strlen(buffer), "%c", '#');
                    fflush(stdout);  // Svuota il buffer di output per garantire una stampa immediata
                }

                // Aggiorna il tempo rimanente del processo
                processi[i].tempo_rimanente -= burst;

                // Aggiorna il tempo corrente dopo l'esecuzione del processo
                tempo_corrente += burst;

                // Aggiunge spazi vuoti dopo l'esecuzione del processo
                stampa_spazi(burst_totale - tempo_corrente, buffer);

                // Verifica se il processo è stato completato
                if (processi[i].tempo_rimanente == 0) {
                    processi_completati++;

                    // Calcola le metriche per il processo
                    calcola_metriche_processo(&processi[i], tempo_corrente, &tempo_medio_di_attesa,
                                              &tempo_medio_di_turnaround);

                    // Aggiunge informazioni sulla terminazione del processo
                    sprintf(buffer + strlen(buffer), " - [Processo %d terminato (Tempo di fine: %d)]\n",
                            processi[i].pid, tempo_corrente);
                } else
                    // Aggiunge una nuova linea nel diagramma se il processo non è stato completato
                    sprintf(buffer + strlen(buffer), "\n");
            }
        }
    }
    // Aggiunge una riga vuota
    sprintf(buffer + strlen(buffer), "\n");

    // Stampa le statistiche generali
    stampa_risultati(processi, numero_processi, tempo_medio_di_attesa, tempo_medio_di_turnaround, buffer);

    // Stampa il contenuto del buffer (diagramma e tabella dei risultati)
    printf("%s", buffer);

    // Richiede il salvataggio su file all'utente
    richiedi_salvataggio_su_file(buffer, "RR");
}