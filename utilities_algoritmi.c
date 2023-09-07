//
// Created by nikoauso.
//

#include "utilities_algoritmi.h"

void aggiungi_info_processo(char *buffer, struct Processi processo) {
    sprintf(buffer + strlen(buffer), "Processo %s%d (T. arrivo: %s%d - T. burst: %s%d) -->",
            ((int) log10(processo.pid) + 1 < 2) ? " " : "",
            processo.pid,
            ((int) log10(processo.tempo_arrivo) + 1 < 2) ? " " : "",
            processo.tempo_arrivo,
            ((int) log10(processo.tempo_burst) + 1 < 2) ? " " : "",
            processo.tempo_burst);
}

void calcola_metriche_processo(struct Processi *processo, int tempo_corrente, int *tempo_medio_di_attesa,
                               int *tempo_medio_di_turnaround) {
    processo->tempo_fine = tempo_corrente;
    processo->tempo_turnaround = processo->tempo_fine - processo->tempo_arrivo;
    processo->tempo_attesa = processo->tempo_turnaround - processo->tempo_burst;

    // Aggiorna i valori dei tempi medi direttamente
    *tempo_medio_di_turnaround += processo->tempo_turnaround;
    *tempo_medio_di_attesa += processo->tempo_attesa;
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

    // Visualizza lo spinner di caricamento
    for (int i = 0; i < 20; i++) {
        loading_spinner();          // Visualizza l'effetto spinner per indicare un'operazione di caricamento in corso
        usleep(100000);    // Attendi 0.1 secondo (100000 microsecondi) prima di continuare
    }
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

void scegli_algoritmo(struct Processi *processi, int numero_processi) {
    printf("Scegli l'algoritmo di scheduling:\n");
    printf("1. FCFS (First-Come, First-Served)\n");
    printf("2. RR (Round Robin)\n");
    printf("3. SJF (Shortest Job First)\n");
    printf("4. SRTF (Shortest Remaining Time First)\n");
    printf("Inserisci la tua scelta: ");

    // Legge la scelta dell'utente
    int scelta_algoritmo = leggi_input_intero();
    ordine_arrivo_processi(processi, numero_processi);
    int burst_totale = calcola_burst_totale(processi, numero_processi);

    // Esegue l'azione corrispondente alla scelta dell'utente
    switch (scelta_algoritmo) {
        case 1:
            simulaFCFS(processi, numero_processi, burst_totale); // Avvia la simulazione FCFS
            break;
        case 2:
            // Chiede all'utente il quanto di tempo per l'algoritmo Round Robin
            printf("Inserisci il valore del quanto di tempo per l'algoritmo Round Robin: ");
            int quanto_di_tempo = leggi_input_intero();
            simulaRR(processi, numero_processi, quanto_di_tempo, burst_totale); // Avvia la simulazione RR
            break;
        case 3:
            simulaSJF(processi, numero_processi, burst_totale); // Avvia la simulazione SJF
            break;
        case 4:
            simulaSRTF(processi, numero_processi, burst_totale); // Avvia la simulazione SRTF
            break;
        default:
            printf("Scelta non valida.\n"); // Scelte non valide
            exit(1); // Esce con stato di errore
    }
}