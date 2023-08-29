//
// Created by nikoauso on 28/08/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "controlla_input.h"

bool numero_intero(char input) {
    if (isdigit(input)) { // Verifica se il carattere è a una cifra
        int num = input - '0'; // Converte il carattere in un intero
        return num >= 0 && num <= 9; // Controlla se è un intero positivo a una cifra
    }
    return false;
}

int leggi_input_intero() {
    char input; // Variabile d'appoggio
    scanf("%c", &input); // Prelevo l'input dell'utente
    getchar();
    if (!numero_intero(input)) { // Controllo che l'input inserito sia un numero intero
        printf("Errore: Input non valido!\n");
        return -1;
    }

    // Converto il numero in un intero
    int numero = atoi(&input);

    return numero;
}