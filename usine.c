
/*------------------------------------------------------------------------*/
/* FCHIER:                          usine.c                               */ 
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */    
/*DATE DE CREATIION:                27/09/2025                            */
/*DATE DE MODIFICATION:             27/09/2025                            */
/*DESCRIPTION:                      fichier contenant les fonctions de 
                                    gestion des usines.                   */
/*------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrep.h"

void insererUsine();
int ecrire_usine(const char *nom_fichier, Usine *u);
int lire_usine(const char *nom_fichier, Usine *resultat);

//fonction pour inserer une usine
void insererUsine() 
{
    Usine nouvelleUsine;

    nouvelleUsine.Id_usine= 1;
    nouvelleUsine.Id_com= 1;

    printf("inserer une usine\n");
    strcpy(nouvelleUsine.Usi_nom, "Usine A");
    strcpy(nouvelleUsine.Usin_desc, "Cet usine produit du Tafya");

    int retour= ecrire_usine("usine.dat", &nouvelleUsine);
    if(retour== 1)
    {
        printf("donnée ajoutée avec succes\n");
    }
    if (lire_usine("usine.dat", &nouvelleUsine)) 
    {
        printf("Usine trouvée : %s\n", nouvelleUsine.Usi_nom);
        printf("Description : %s\n", nouvelleUsine.Usin_desc);
    } 
    else 
    {
        printf("Usine non trouvée.\n");
    }
   
}

int ecrire_usine(const char *nom_fichier, Usine *u) 
{
    FILE *f = fopen(nom_fichier, "wb");
    if (f == NULL) 
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }
    fwrite(u, sizeof(Usine), 1, f);
    fclose(f);
    return 1;
}

int lire_usine(const char *nom_fichier, Usine *resultat) 
{
    FILE *f = fopen(nom_fichier, "rb");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }
    Usine temp;
    while (fread(&temp, sizeof(Usine), 1, f) == 1) {
        if (temp.Id_usine == resultat->Id_usine) {
            *resultat = temp;
            fclose(f);
            return 1; // trouvé
        }
    }
    fclose(f);
    return 0; // non trouvé
}

int main()
{
    insererUsine();
}