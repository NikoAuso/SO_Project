//
// Created by nikoauso.
//

#include "algoritmo_SRTF.h"

void simulaSRTF(struct Processi processi[], int numero_processi, int burst_totale) {
    char buffer[5000];
    system("clear"); // Pulisce la console

    sprintf(buffer, "Simulazione Scheduling SRTF:\n\n");
    strcat(buffer, "Diagramma di Gantt:\n");

    int tempo_corrente = 0;                 // Il tempo corrente della simulazione
    int tempo_medio_di_attesa = 0;          // Il tempo medio di attesa dei processi
    int tempo_medio_di_turnaround = 0;      // Il tempo medio di turnaround dei processi
    int processi_rimasti = numero_processi; // Il numero i processi rimasti da eseguire

    // Ciclo principale della simulazione
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
            // Aggiunge informazioni sul processo al diagramma di Gantt
            aggiungi_info_processo(buffer, processi[indice_piu_breve]);

            // Aggiunge spazi vuoti prima di iniziare l'esecuzione del processo se necessario
            stampa_spazi(tempo_corrente, buffer);

            // Simula l'esecuzione del processo aggiungendo '#' al diagramma di Gantt
            for (int t = 0; t < burst_piu_breve; t++) {
                sprintf(buffer + strlen(buffer), "%c", '#');
                fflush(stdout);  // Svuota il buffer di output per garantire una stampa immediata
                tempo_corrente++;
                processi[indice_piu_breve].tempo_rimanente--;

                // Controlla se è arrivato un processo con burst time più breve
                for (int j = 0; j < numero_processi; j++) {
                    if (processi[j].tempo_arrivo <= tempo_corrente && // Controllo che il processo sia arrivato
                        // Controlla che il processo abbia il burst più breve
                        processi[j].tempo_rimanente < processi[indice_piu_breve].tempo_rimanente &&
                        // Controlla che il processo non sia terminato
                        processi[j].tempo_rimanente > 0) {
                        // In questo caso è arrivato un processo con un burst minore e simula la messa in stato "waiting"
                        // del processo in esecuzione e la sottomissione del processo con burst minore
                        stampa_spazi(burst_totale - tempo_corrente, buffer);
                        sprintf(buffer + strlen(buffer), "\n");
                        goto inizio;
                    }
                }
            }

            // Verifica se il processo è stato completato
            if (processi[indice_piu_breve].tempo_rimanente == 0) {
                // Calcola le metriche per il processo
                calcola_metriche_processo(&processi[indice_piu_breve], tempo_corrente, &tempo_medio_di_attesa,
                                          &tempo_medio_di_turnaround);

                processi_rimasti--;

                // Aggiunge spazi vuoti dopo l'esecuzione del processo
                stampa_spazi(burst_totale - tempo_corrente, buffer);

                // Aggiunge informazioni sulla terminazione del processo
                sprintf(buffer + strlen(buffer), " - [Processo %d terminato (Tempo di fine: %d)]\n",
                        processi[indice_piu_breve].pid, tempo_corrente);
            } else
                // Aggiunge una nuova linea nel diagramma se il processo non è stato completato
                sprintf(buffer + strlen(buffer), "\n");
        }
    }
    // Aggiunge una riga vuota
    sprintf(buffer + strlen(buffer), "\n");

    // Stampa le statistiche generali
    stampa_risultati(processi, numero_processi, tempo_medio_di_attesa, tempo_medio_di_turnaround, buffer);

    // Stampa il contenuto del buffer (diagramma e tabella dei risultati)
    printf("%s", buffer);

    // Richiede il salvataggio su file all'utente
    richiedi_salvataggio_su_file(buffer, "SJF");
}
