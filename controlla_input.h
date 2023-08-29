//
// Created by nikoauso on 28/08/23.
//

#ifndef SO_PROJECT_CONTROLLA_INPUT_H
#define SO_PROJECT_CONTROLLA_INPUT_H

#include <stdbool.h>

/**
 * Verifica se un carattere rappresenta un numero intero di una cifra.
 *
 * Questa funzione verifica se il carattere dato rappresenta un numero intero positivo di una cifra.
 *
 * @param input Il carattere da verificare.
 * @return True se il carattere è un numero intero di una cifra, altrimenti False.
 */
bool numero_intero(char input);

/**
 * Legge un carattere da input, verifica se è un numero intero di una cifra e lo restituisce come intero.
 *
 * Questa funzione legge un carattere da input, verifica se rappresenta un numero intero positivo di una cifra.
 * Se l'input è valido, converte il carattere in un intero e lo restituisce. In caso contrario, stampa un messaggio
 * di errore e restituisce -1.
 *
 * @return L'intero letto da input, se valido; -1 in caso di input non valido.
 */
int leggi_input_intero();

#endif //SO_PROJECT_CONTROLLA_INPUT_H
