//
// Created by nikoauso.
//

#include "algoritmo_RR.h"

void simulaRR(struct Processi processi[], int numero_processi, int quantum, int burst_totale) {
    char buffer[5000];
    system("clear");

    sprintf(buffer, "Simulazione Scheduling RR\n\n");
    strcat(buffer, "Diagramma di Gantt:\n");

    int tempo_corrente = 0;
    int processi_completati = 0;
    int tempo_medio_di_attesa = 0;
    int tempo_medio_di_turnaround = 0;

    while (processi_completati < numero_processi) {
        for (int i = 0; i < numero_processi; i++) {
            if (tempo_corrente < processi[i].tempo_arrivo) {
                tempo_corrente = processi[i].tempo_arrivo;
            }
            if (processi[i].tempo_rimanente > 0) {
                int burst = (processi[i].tempo_rimanente > quantum) ? quantum : processi[i].tempo_rimanente;
                sprintf(buffer + strlen(buffer), "Processo %s%d (T. arrivo: %s%d - T. burst: %s%d) -->",
                        ((int) log10(processi[i].pid) + 1 < 2) ? " " : "",
                        processi[i].pid,
                        ((int) log10(processi[i].tempo_arrivo) + 1 < 2) ? " " : "",
                        processi[i].tempo_arrivo,
                        ((int) log10(processi[i].tempo_burst) + 1 < 2) ? " " : "",
                        processi[i].tempo_burst);
                stampa_spazi(tempo_corrente, buffer);
                for (int t = 0; t < burst; t++) {
                    sprintf(buffer + strlen(buffer), "%c", '#');
                    fflush(stdout);  // Svuota il buffer di output per garantire una stampa immediata
                }
                processi[i].tempo_rimanente -= burst;
                tempo_corrente += burst;
                stampa_spazi(burst_totale - tempo_corrente, buffer);
                if (processi[i].tempo_rimanente == 0) {
                    processi_completati++;
                    processi[i].tempo_fine = tempo_corrente;
                    processi[i].tempo_turnaround = processi[i].tempo_fine - processi[i].tempo_arrivo;
                    processi[i].tempo_attesa = processi[i].tempo_turnaround - processi[i].tempo_burst;
                    tempo_medio_di_turnaround += processi[i].tempo_turnaround;
                    tempo_medio_di_attesa += processi[i].tempo_attesa;
                    sprintf(buffer + strlen(buffer), " - [Processo %d terminato (Tempo di fine: %d)]\n",
                            processi[i].pid, tempo_corrente);
                }else
                    sprintf(buffer + strlen(buffer),"\n");
            }
        }
    }
    sprintf(buffer + strlen(buffer), "\n");
    stampa_risultati(processi, numero_processi, tempo_medio_di_attesa, tempo_medio_di_turnaround, buffer);
    printf("%s", buffer);
    richiedi_salvataggio_su_file(buffer, "RR");
}