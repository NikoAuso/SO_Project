//
// Created by nikoauso.
//

#include "algoritmo_SRTF.h"

void simulaSRTF(struct Process processi[], int numero_processi) {
    ordina_processi(processi, numero_processi);
    system("clear");

    printf("Simulazione Scheduling SRTF:\n\n");
    printf("Diagramma di Gantt:\n");

    int tempo_corrente = 0;
    int processi_rimasti = numero_processi;
    int tempo_medio_di_attesa = 0;
    int tempo_medio_di_turnaround = 0;

    inizio:
    while (processi_rimasti > 0) {
        int indice_piu_breve = -1;
        int burst_piu_breve = INT_MAX;

        // Trova il processo con il burst più breve tra quelli arrivati e in esecuzione
        for (int i = 0; i < numero_processi; i++) {
            if (processi[i].tempo_arrivo <= tempo_corrente && // Controllo che il processo sia arrivato
                processi[i].tempo_rimanente < burst_piu_breve && // Controllo che il processo abbia il burst più breve
                processi[i].tempo_rimanente > 0) { // Controllo che il processo non sia terminato
                // Imposto il burst del processo selezionato come il più breve
                burst_piu_breve = processi[i].tempo_rimanente;
                // Imposto l'indice di scorrimento dell'array sull'indice che corrisponde al processo selezionato
                indice_piu_breve = i;
            }
        }

        if (indice_piu_breve == -1) {
            tempo_corrente++; //Nessun processo selezionato
        } else {
            // Processo selezionato
            printf("Processo %s%d (T. arrivo: %s%d - T. burst: %s%d) -->",
                   ((int) log10(processi[indice_piu_breve].pid) + 1 < 2) ? " " : "",
                   processi[indice_piu_breve].pid,
                   ((int) log10(processi[indice_piu_breve].tempo_arrivo) + 1 < 2) ? " " : "",
                   processi[indice_piu_breve].tempo_arrivo,
                   ((int) log10(processi[indice_piu_breve].tempo_burst) + 1 < 2) ? " " : "",
                   processi[indice_piu_breve].tempo_burst);
            stampaSpazi(tempo_corrente);
            for (int t = 0; t < burst_piu_breve; t++) {
                printf("%c", '#');
                fflush(stdout);  // Svuotare il buffer di output per garantire una stampa immediata
                sleep(1);
                tempo_corrente++;
                processi[indice_piu_breve].tempo_rimanente--;

                // Controllo se è arrivato un processo con burst time più breve
                for (int j = 0; j < numero_processi; j++) {
                    if (processi[j].tempo_arrivo <= tempo_corrente && // Controllo che il processo sia arrivato
                        // Controllo che il processo abbia il burst più breve
                        processi[j].tempo_rimanente < processi[indice_piu_breve].tempo_rimanente &&
                        // Controllo che il processo non sia terminato
                        processi[j].tempo_rimanente > 0) {
                        // In questo caso è arrivato un processo con un burst minore e simulo la messa in stato "waiting"
                        // del processo in esecuzione e la sottomissione del processo con burst minore
                        printf("\n");
                        goto inizio;
                    }
                }
            }

            if (processi[indice_piu_breve].tempo_rimanente == 0) {
                processi[indice_piu_breve].tempo_fine = tempo_corrente;
                processi[indice_piu_breve].tempo_turnaround =
                        processi[indice_piu_breve].tempo_fine - processi[indice_piu_breve].tempo_arrivo;
                processi[indice_piu_breve].tempo_attesa =
                        processi[indice_piu_breve].tempo_turnaround - processi[indice_piu_breve].tempo_burst;
                processi_rimasti--;
                tempo_medio_di_turnaround += processi[indice_piu_breve].tempo_turnaround;
                tempo_medio_di_attesa += processi[indice_piu_breve].tempo_attesa;
                printf("   [Processo %d terminato (Tempo di fine: %d)]", processi[indice_piu_breve].pid,
                       tempo_corrente);
            }
            printf("\n");
        }
    }
    stampa_risultati(processi, numero_processi,tempo_medio_di_attesa,tempo_medio_di_turnaround);
}
