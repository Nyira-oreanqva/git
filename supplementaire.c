
/*------------------------------------------------------------------------*/
/* FCHIER:                          suplementaire.c                       */
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */
/*DATE DE CREATIION:                26/09/2025                            */
/*DATE DE MODIFICATION:             26/09/2025                            */
/*DESCRIPTION:                      fichier contenant des fonctions 
                                    supplémentaires necessaire.           */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entrep.h"

//fonction pour generer un ID de 10 chiffres de maniere aleatoire
char* creerID(int n) {
    char *ID = malloc((n + 1) * sizeof(char));
    if (ID == NULL) return NULL;

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        ID[i] = '0' + (rand() % 10); // chiffre aléatoire 0-9
    }
    ID[n] = '\0';
    return ID;
}