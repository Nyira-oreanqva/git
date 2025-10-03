/*------------------------------------------------------------------------*/
/* FCHIER:                          usine.c                               */ 
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */    
/*DATE DE CREATIION:                27/09/2025                            */
/*DATE DE MODIFICATION:             28/09/2025                            */
/*DESCRIPTION:                      fichier contenant les fonctions de 
                                    gestion des usines.                   */
/*------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrep.h"


//fonction pour inserer une usine
void insererUsine() 
{
    Usine nouvelleUsine;
    char buffer[50]; // Buffer temporaire pour la saisie

    nouvelleUsine.Id_usine= 1;
    nouvelleUsine.Id_com= 1;

    printf("Entrez le nom de l'usine: ");
    fgets(buffer, sizeof(buffer), stdin);
    // Supprime le retour à la ligne (\n) si présent
    buffer[strcspn(buffer, "\n")] = '\0';
    strcpy(nouvelleUsine.Usi_nom, buffer); //Pour copier le nom dans le champ nom de l'usine

    printf("Entrez la description de l'usine: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcpy(nouvelleUsine.Usin_desc, buffer); //Pour copier le nom dans le champ nom de l'usine

    int retour= ecrire_usine("usine.dat", &nouvelleUsine);
    if(retour== 1)
    {
        printf("usine ajoutée avec succes\n");
    }

    if (lire_usine("usine.dat",nouvelleUsine.Id_usine, &nouvelleUsine)) 
    {
        printf("Nom de l'usine : %s\n", nouvelleUsine.Usi_nom);
        printf("Description de l'usine : %s\n", nouvelleUsine.Usin_desc);
    } 
    else 
    {
        printf("Usine non trouvée.\n");
    }
   
}
//cette fonction permet d'écrire les infos de l'usine à inserer dans le fichier usine.dat
int ecrire_usine(const char *nom_fichier, Usine *u) 
{
    FILE *f = fopen(nom_fichier, "wb");//ouvrir le fichier
    if (f == NULL) 
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }
    fwrite(u, sizeof(Usine), 1, f); //ecrire dans le fichier
    fclose(f);
    return 1;
}
//cette fonction permet de lire les données stockés dans le fichier usine.dat
int lire_usine(const char *nom_fichier, int id_recherche, Usine *resultat) 
{
    FILE *f = fopen(nom_fichier, "rb");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }
    
    while (fread(resultat, sizeof(Usine), 1, f) == 1)
    {
        if (resultat->Id_usine == id_recherche) {
            fclose(f);
            return 1; // Usine trouvée
        }
    }
    
    fclose(f);
    return 0; // Usine non trouvée
}

//Fonction pour modifier les informations d'une usine
void mod_usine(int ID)
{
    Usine usine_a_modifier;
    int choix;
    char texte[200]; // pour stocker le texte saisi
    
    printf("Entrer l'Id de l'usine à modifier-> ");
    scanf("%d", &ID);
    getchar(); // absorber le \n restant
    
    if (lire_usine("usine.dat", ID, &usine_a_modifier)) 
    {
        printf("Usine trouvée !\n");
        printf("Nom actuel: %s\n", usine_a_modifier.Usi_nom);
        printf("Description actuelle: %s\n", usine_a_modifier.Usin_desc);
        
        do {
            printf("Que voulez-vous modifier ?\n");
            printf("1. Nom\n");
            printf("2. Description\n");
            printf("3. Quitter\n");
            scanf("%d", &choix);
            getchar(); // absorber le \n

            switch(choix)
            {
                case 1: 
                    printf("Entrer le nouveau nom: ");
                    fgets(texte, sizeof(texte), stdin);
                    texte[strcspn(texte, "\n")] = '\0';
                    strcpy(usine_a_modifier.Usi_nom, texte);
                    printf("Nom modifié avec succès!\n");
                    return;
                    
                case 2:
                    printf("Entrer la nouvelle description: ");
                    fgets(texte, sizeof(texte), stdin);
                    texte[strcspn(texte, "\n")] = '\0';
                    strcpy(usine_a_modifier.Usin_desc, texte);
                    printf("Description modifiée avec succès!\n");
                    return;
                    
                case 3:
                    printf("Modification annulée\n");
                    return;
                    
                default: 
                    printf("Choix invalide. Veuillez réessayer.\n");
                    break;
            }
        } while (choix != 3);
    } else {
        printf("Aucune usine trouvée avec l'ID %d\n", ID);
    }
}

int main()
{
    insererUsine();
    mod_usine(1);
    return 0;
}