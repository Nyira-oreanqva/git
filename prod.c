/*------------------------------------------------------------------------*/
/* FICHIER:                         prod.c                                */ 
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */    
/*DATE DE CREATIION:                26/09/2025                            */
/*DATE DE MODIFICATION:             22/10/2025                            */
/*DESCRIPTION:                      fichier contenant les fonctions de 
                                    gestion des produits                  */
/*------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrep.h"

/*------------------------------------------------------------------------*/
/* FONCTION:                        insererProduit                                */ 
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */    
/*DATE DE CREATIION:                26/09/2025                            */
/*DATE DE MODIFICATION:             03/10/2025                            */
/*DESCRIPTION:                      fichier contenant les fonctions de 
                                    gestion des usines, des produits et de 
                                    l'historique de production            */
/*------------------------------------------------------------------------*/

int obtenir_dernier_id_produit(const char *nom_fichier);
int ecrire_produit(const char *nom_fichier, Produit *p);
int lire_produit(const char *nom_fichier, int id_recherche, Produit *resultat);

void insererProduit()
{
    Produit nouveauProduit;
    char texte[50]; // pour recevoir le texte à saisir

    nouveauProduit.Id_prod = obtenir_dernier_id_produit("produit.dat") + 1;
    //nouveauProduit.Id_usine= ID_usine;
    printf("Entrez le nom du produit: ");
    fgets(texte, sizeof(texte), stdin);

    // Supprime le retour à la ligne (\n) si présent
    texte[strcspn(texte, "\n")] = '\0';
    strcpy(nouveauProduit.Pro_nom, texte); //Pour copier le nom dans le champ nom de l'usine

    //description du produit
    printf("Entrez la description du produit: ");
    fgets(texte, sizeof(texte), stdin);
    texte[strcspn(texte, "\n")] = '\0';
    strcpy(nouveauProduit.pro_desc, texte); //Pour copier le nom dans le champ nom de l'usine

    //prix du produit
    printf("Entrez le prix du produit: ");
    scanf("%f", &nouveauProduit.pro_prix);
    getchar(); // absorber le \n restant

    // Quantité du produit
    printf("Entrez la quantité dont vous voulez ajouter: ");
    scanf("%d", &nouveauProduit.pro_qte);
    getchar(); // absorber le \n restant


    int retour = ecrire_produit("produit.dat", &nouveauProduit);
    if(retour == 1)
    {
        printf("Produit ajouté avec succes\n");
    }

    if (lire_produit("produit.dat", nouveauProduit.Id_prod, &nouveauProduit)) 
    {
        printf("Nom du produit : %s\n", nouveauProduit.Pro_nom);
        printf("ID du produit : %d\n", nouveauProduit.Id_prod);
        printf("Description du produit : %s\n", nouveauProduit.pro_desc);
        printf("Prix du produit : %.2f\n", nouveauProduit.pro_prix);
        printf("Quantité du produit disponible: %d\n", nouveauProduit.pro_qte);
    } 
    else 
    {
        printf("Produit non trouvé.\n");
    }
}

/*------------------------------------------------------------------------*/
/*FONCTION:                         ecrire_produit                        */
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */
/*PARAMETRE:                        Nom du fichier/un pointeur vers une 
                                    structure produit                     */
/*VALEUR DE RETOUR:                 Un entier                             */
/*DATE DE CREATION:                 18/10/2025                            */
/*DATE DE MODIFICATION:             18/10/2025                            */
/*DESCRIPTION:                      Fonction qui permet de stocker les 
                                    données d'une usine                   */
/*------------------------------------------------------------------------*/
int ecrire_produit(const char *nom_fichier, Produit *p) 
{
    FILE *f = fopen(nom_fichier, "ab"); // Ouvre le fichier en mode ajout binaire
    if (f == NULL) 
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }
    fwrite(p, sizeof(Produit), 1, f);
    fclose(f);
    return 1;
}

/*------------------------------------------------------------------------*/
/*FONCTION:                         lire_produit                          */ 
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */ 
/*PARAMETRE:                        Nom du fichier/ l'ID de l'usine qu'on 
                                    cherche/ un pointeur vers un produit  */
/*VALEUR DE RETOUR:                 Un entier                             */
/*DATE DE CREATIION:                18/10/2025                            */
/*DATE DE MODIFICATION:             18/10/2025                            */
/*DESCRIPTION:                      Fonction qui permet de lire les données
                                    stockés dans le fichier produit.dat   */
/*------------------------------------------------------------------------*/

int lire_produit(const char *nom_fichier, int id_recherche, Produit *resultat) 
{
    FILE *f = fopen(nom_fichier, "rb");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }
    
    while (fread(resultat, sizeof(Produit), 1, f) == 1)
    {
        if (resultat->Id_prod == id_recherche) {
            fclose(f);
            return 1; // Produit trouvé
        }
    }
    
    fclose(f);
    return 0; // Produit non trouvé
}


int obtenir_dernier_id_produit(const char *nom_fichier) 
{
    FILE *f = fopen(nom_fichier, "rb");
    if (f == NULL) return 0;

    Produit temp;
    int dernier_id = 0;

    while (fread(&temp, sizeof(Produit), 1, f) == 1) {
        if (temp.Id_prod > dernier_id) {
            dernier_id = temp.Id_prod;
        }
    }

    fclose(f);
    return dernier_id;
}

//fonction pour modifier un produit existant
void mod_produit()
{
    Produit produit_a_modifier;
    int choix, ID;
    char texte[200]; // pour stocker le texte saisi
    
    printf("Entrer l'Id du produit à modifier-> ");
    scanf("%d", &ID);
    getchar(); // absorber le \n restant
    
    if (lire_produit("produit.dat", ID, &produit_a_modifier)) 
    {
        printf("produit trouvée !\n");
        printf("Nom actuel: %s\n", produit_a_modifier.Pro_nom);
        printf("Description actuelle: %s\n", produit_a_modifier.pro_desc);
        printf("Prix actuel: %.2f\n", produit_a_modifier.pro_prix);
        printf("Quantité actuelle: %d\n", produit_a_modifier.pro_qte);
        
        do {
            printf("Que voulez-vous modifier ?\n");
            printf("1. Nom\n");
            printf("2. Description\n");
            printf("3. Prix\n");
            printf("4. Quantité\n");
            printf("5. Quitter\n");
            scanf("%d", &choix);
            getchar(); // absorber le \n

            switch(choix)
            {
                case 1: 
                    printf("Entrer le nouveau nom: ");
                    fgets(texte, sizeof(texte), stdin);
                    texte[strcspn(texte, "\n")] = '\0';
                    strcpy(produit_a_modifier.Pro_nom, texte);
                    printf("Nom modifié avec succès!\n");
                    printf("Nouveau nom: %s\n", produit_a_modifier.Pro_nom);
                    break;
                    
                case 2:
                    printf("Entrer la nouvelle description: ");
                    fgets(texte, sizeof(texte), stdin);
                    texte[strcspn(texte, "\n")] = '\0';
                    strcpy(produit_a_modifier.pro_desc, texte);
                    printf("Description modifiée avec succès!\n");
                    printf("Nouvelle description: %s\n", produit_a_modifier.pro_desc);
                    break;

                case 3:
                    printf("Entrer le nouveau prix: ");
                    float new_prix;
                    scanf("%f", &new_prix);
                    produit_a_modifier.pro_prix = new_prix;
                    printf("Prix modifié avec succès!\n");
                    printf("Nouveau prix: %.2f\n", produit_a_modifier.pro_prix);
                    break;
                 
                case 4: 
                    printf("Entrer la nouvelle quantité: ");
                    int new_qte;
                    scanf("%d", &new_qte);
                    produit_a_modifier.pro_qte = new_qte;
                    printf("Quantité modifiée avec succès!\n");
                    printf("Nouvelle quantité: %d\n", produit_a_modifier.pro_qte);
                    break;

                case 5:
                    printf("Modification annulée\n");
                    break;
                    
                default: 
                    printf("Choix invalide. Veuillez réessayer.\n");
                    break;
            }
        } while (choix != 5);
    } else {
        printf("Aucune usine trouvée avec l'ID %d\n", ID);
    }
}


int main()
{
    //insererProduit();
    mod_produit();
    return 0;
}
