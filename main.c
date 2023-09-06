//
// Created by nikoauso.
//

#include "utilities.h"

/**
 * Funzione principale del programma.
 *
 * @return 0 se il programma è eseguito correttamente, 1 in caso di errore.
 */
int main() {
    printf("Benvenuto nel SIMULATORE DI SCHEDULING DEI PROCESSI!\n\n");
    printf(" $$$$$$\\   $$$$$$\\  $$$$$$$\\  \n"
           "$$  __$$\\ $$  __$$\\ $$  __$$\\ \n"
           "$$ /  \\__|$$ /  \\__|$$ |  $$ |\n"
           "\\$$$$$$\\  \\$$$$$$\\  $$$$$$$  |\n"
           " \\____$$\\  \\____$$\\ $$  ____/ \n"
           "$$\\   $$ |$$\\   $$ |$$ |      \n"
           "\\$$$$$$  |\\$$$$$$  |$$ |      \n"
           " \\______/  \\______/ \\__|\n\n");

    printf("Il tempo di esecuzione dei processi è espresso in secondi.\n");
    printf("Il simulatore offre un set di processi già pre-impostati che puoi utilizzare per semplificare l'inserimento dei dati.\n");
    printf("Puoi modificare ora il file (\"processi.json\") o utilizzare i dati già inseriti.\n");
    while (true) {
        // Chiede all'utente se vuole utilizzare un file per i dati o inserirli manualmente
        char usa_file;
        printf("Vuoi utilizzare il file? (y/N): ");
        scanf(" %c", &usa_file);
        getchar(); // Consume il carattere di nuova riga nel buffer

        if (usa_file == 'y' || usa_file == 'Y') {
            // Chiama la funzione "con_file" per utilizzare i dati da un file JSON
            con_file("processi.json");
        } else if (usa_file == 'n' || usa_file == 'N') {
            // Chiama la funzione "senza_file" per inserire manualmente i dati
            senza_file();
        } else {
            // Messaggio di errore per input non valido
            printf("Errore: input non valido!");
            return 1; // Termina il programma con codice di errore
        }

        // Chiede all'utente se vuole riprovare o terminare il programma
        char riprova;
        printf("Vuoi riprovare (Y) o terminare il programma (N)? ");
        scanf(" %c", &riprova);
        getchar(); // Consume il carattere di nuova riga nel buffer
        if (riprova == 'n' || riprova == 'N') {
            break; // Esce dal ciclo se l'utente desidera terminare il programma
        } else if(riprova == 'y' || riprova == 'Y'){
            system("clear"); // Pulisce lo schermo prima di iniziare una nuova simulazione
            continue;
        } else {
            // Messaggio di errore per input non valido
            printf("Errore: input non valido!");
            return 1; // Termina il programma con codice di errore
        }
    }
    return 0;
}
