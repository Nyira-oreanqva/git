/*------------------------------------------------------------------------*/
/* FICHIER:                          usine.c                               */ 
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */    
/*DATE DE CREATIION:                26/09/2025                            */
/*DATE DE MODIFICATION:             17/10/2025                            */
/*DESCRIPTION:                      fichier contenant les fonctions de 
                                    gestion des usines.                   */
/*------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrep.h"
#include "time.h"

/*------------------------------------------------------------------------*/
/*FONCTION:                         ins_usine                             */ 
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */ 
/*PARAMETRE:                        ID de la commune où se trouve l'usine */
/*VALEUR DE RETOUR:                 Aucune                                */
/*DATE DE CREATIION:                27/09/2025                            */
/*DATE DE MODIFICATION:             03/10/2025                            */
/*DESCRIPTION:                      Fonction qui permet d'inserer une 
                                    usine                                 */
/*------------------------------------------------------------------------*/

//fonction pour inserer une usine
void ins_usine() 
{
    Usine nouvelleUsine;
    char texte[50];

    // Définir l'ID avant l'écriture
    nouvelleUsine.id_usine = obtenir_dernier_id_usine("usine.dat") + 1;\
    
    // Vider le buffer avant de lire une chaîne de caractères
    vider_buffer();  

    // Demander l'ID de la commune parente et vérifier son existence dans le fichier commune.dat
    int id_com_input;
    printf("Entrez l'ID de la commune parente de l'usine: ");
    if (scanf("%d", &id_com_input) != 1) {
        printf("Entrée invalide pour l'ID de la commune.\n");
        // vider le buffer
        vider_buffer();
        return;
    }
    // vider le reste du buffer
       vider_buffer();

    // Vérifier que le fichier existe et que l'ID correspond à une commune
    Commune com_tmp;
    if (!lire_commune("commune.dat", id_com_input, &com_tmp)) {
        printf("ERREUR: La commune avec l'ID %d n'existe pas. Veuillez créer la commune avant d'ajouter une usine.\n", id_com_input);
        return;
    }
    // Rattacher l'usine à l'ID de commune validé
    nouvelleUsine.id_com = com_tmp.id_commune;
  

    printf("Entrez le nom de l'usine: ");
    fgets(texte, sizeof(texte), stdin);
    texte[strcspn(texte, "\n")] = '\0';
    strcpy(nouvelleUsine.Usi_nom, texte);

    printf("Entrez la description de l'usine: ");
    fgets(texte, sizeof(texte), stdin);
    texte[strcspn(texte, "\n")] = '\0';
    strcpy(nouvelleUsine.Usin_desc, texte);

    // Écrire l'usine après avoir défini toutes ses propriétés
    int retour = ecrire_usine("usine.dat", &nouvelleUsine);
    if(retour == 1)
    {
        printf("Usine ajoutée avec succès\n");
        //affichage sur forme de tableau des infos de l'usine ajoutée
        printf("--------------------------------------------------\n");
        printf("| ID Commune | ID Usine | Nom Usine        | Description Usine    |\n");
        printf("--------------------------------------------------\n");
        printf("| %d         | %d        | %s           | %s                 |\n", nouvelleUsine.id_com, nouvelleUsine.id_usine, nouvelleUsine.Usi_nom, nouvelleUsine.Usin_desc);
        printf("--------------------------------------------------\n");
    }
    else 
    {
        printf("Erreur lors de l'ajout de l'usine.\n");
    }
}

/*------------------------------------------------------------------------*/
/*FONCTION:                         ecrire_usine                          */ 
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */ 
/*PARAMETRE:                        Nom du fichier/un pointeur vers une 
                                    usine                                 */
/*VALEUR DE RETOUR:                 Un entier                             */
/*DATE DE CREATIION:                27/09/2025                            */
/*DATE DE MODIFICATION:             18/10/2025                            */
/*DESCRIPTION:                      Fonction qui permet d'écrire les infos 
                                    de l'usine à inserer dans le fichier 
                                    usine.dat                             */
/*------------------------------------------------------------------------*/

int ecrire_usine(const char *nom_fichier, Usine *u) 
{
    FILE *f = fopen(nom_fichier, "ab"); // Ouvre le fichier en mode ajout binaire
    if (f == NULL) 
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }
    fwrite(u, sizeof(Usine), 1, f);
    fclose(f);
    return 1;
}

/*------------------------------------------------------------------------*/
/*FONCTION:                         lire_usine                            */ 
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */ 
/*PARAMETRE:                        Nom du fichier/ l'ID de l'usine qu'on 
                                    cherche/ un pointeur vers une usine   */
/*VALEUR DE RETOUR:                 Un entier                             */
/*DATE DE CREATIION:                27/09/2025                            */
/*DATE DE MODIFICATION:             03/10/2025                            */
/*DESCRIPTION:                      Fonction qui permet de lire les données
                                    stockés dans le fichier usine.dat     */
/*------------------------------------------------------------------------*/

int lire_usine(const char *nom_fichier, int id_recherche, Usine *resultat) 
{
    FILE *f = fopen(nom_fichier, "rb");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }
    
    while (fread(resultat, sizeof(Usine), 1, f) == 1)
    {
        if (resultat->id_usine == id_recherche) {
            fclose(f);
            return 1; // Usine trouvée
        }
    }
    
    fclose(f);
    return 0; // Usine non trouvée
}
/*------------------------------------------------------------------------*/
/*FONCTION:                         mod_usine                             */ 
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */ 
/*PARAMETRE:                        ID de l'usine à modifier              */
/*VALEUR DE RETOUR:                 Aucune                                */
/*DATE DE CREATIION:                27/09/2025                            */
/*DATE DE MODIFICATION:             03/10/2025                            */
/*DESCRIPTION:                      Fonction pour modifier les informations
                                    d'une usine                           */
/*------------------------------------------------------------------------*/

void mod_usine()
{   int ID;
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
                    break;
                    
                case 2:
                    printf("Entrer la nouvelle description: ");
                    fgets(texte, sizeof(texte), stdin);
                    texte[strcspn(texte, "\n")] = '\0';
                    strcpy(usine_a_modifier.Usin_desc, texte);
                    printf("Description modifiée avec succès!\n");
                    break;
                    
                case 3:
                    printf("Modification annulée\n");
                    break;
                    
                default: 
                    printf("Choix invalide. Veuillez réessayer.\n");
                    break;
            }
        } while (choix != 3);
    } else {
        printf("Aucune usine trouvée avec l'ID %d\n", ID);
    }
}

/*-----------------------------------------------------------------------------------*/
/* FONCTION:             lister usine                                                 */
/*DESCRIPTION:           Cette fonction permet de lister toutes les usines             */
/*VALEUR DE RETOUR:      Pas de valeur de retour                                       */
/*Auteur:                Blaise Elie                                                  */
void lister_usines()
{
    Usine usine;
    FILE *f = fopen("usine.dat", "rb");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    printf("\nListe des usines:\n");
    printf("--------------------------------------------------\n");
    printf("| ID Usine | ID Commune | Nom Usine        | Description Usine    |\n");
    printf("--------------------------------------------------\n");
    while (fread(&usine, sizeof(Usine), 1, f) == 1)
    {
        printf("| %d       | %d         | %s           | %s                 |\n", usine.id_usine, usine.id_com, usine.Usi_nom, usine.Usin_desc);
        printf("--------------------------------------------------\n");
    }

    fclose(f);
}

/*-------------------------------------------------------------------------------------*/
/* FONCTION:             Obtenir_dernier_id_usine                                      */
/*DESCRIPTION:           Cette fonction permet d'obtenir le dernier ID de departement  */
/*PARAMETRE:             Nom du fichier                                                */
/*VALEUR DE RETOUR:      Dernier ID de departement                                     */
/*AUTEUR:                Blaise Elie                                                   */
/*DATE DE CREATION:      10/10/2025                                                    */
/*DATE DE MODIFICATION:  10/10/2025                                                    */
int obtenir_dernier_id_usine(const char *nom_fichier)
{    
    int max_id = 0;
    Usine usine;
    FILE *f = fopen(nom_fichier, "rb");
    while (fread(&usine, sizeof(Usine), 1, f) == 1)
    {
        if (usine.id_usine > max_id)
        {
            max_id = usine.id_usine;
        }
    }
    fclose(f);
    return max_id;


}

/*------------------------------------------------------------------------*/
/* FONCTION:                        insererProduit                                */ 
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */    
/*DATE DE CREATIION:                26/09/2025                            */
/*DATE DE MODIFICATION:             03/10/2025                            */
/*DESCRIPTION:                      fichier contenant les fonctions de 
                                    gestion des usines, des produits et de 
                                    l'historique de production            */
/*------------------------------------------------------------------------*/
void ins_Prod()
{
    Produit nouveauProduit;
    char texte[50]; // pour recevoir le texte à saisir

    nouveauProduit.Id_prod = obtenir_dernier_id_produit("produit.dat") + 1;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    // Demander et valider l'ID de l'usine parente
    int id_usine_input;
    printf("Entrez l'ID de l'usine parente du produit: ");
    if (scanf("%d", &id_usine_input) != 1) {
        printf("Entrée invalide pour l'ID de l'usine.\n");
        // vider le buffer
        while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }
    // vider le reste du buffer
    while ((c = getchar()) != '\n' && c != EOF) {}

    Usine usine_tmp;
    if (!lire_usine("usine.dat", id_usine_input, &usine_tmp)) {
        printf("ERREUR: L'usine avec l'ID %d n'existe pas. Veuillez créer l'usine avant d'ajouter un produit.\n", id_usine_input);
        return;
    }
    nouveauProduit.Id_usine = usine_tmp.id_usine;

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
    printf("Entrez le prix du produit en Gourdes: ");
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

    {  //affichage sous forme de tableau des infos du produit ajouté
        printf("--------------------------------------------------\n");
        printf("| ID Produit | ID Usine | Nom Produit      | Description Produit  | Prix | Quantité |\n");
        printf("--------------------------------------------------\n");
        printf("| %d         | %d        | %s           | %s                 | %.2f | %d       |\n", nouveauProduit.Id_prod, nouveauProduit.Id_usine, nouveauProduit.Pro_nom, nouveauProduit.pro_desc, nouveauProduit.pro_prix, nouveauProduit.pro_qte);
        printf("--------------------------------------------------\n");
    
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

/*------------------------------------------------------------------------*/
/* FONCTION:              lister produits                                 */
/*DESCRIPTION:            Cette fonction permet de lister  les produits */
/*VALEUR DE RETOUR:       Pas de valeur de retour                                       */
/*Auteur:                 Blaise Elie                                                  */
/*DATE DE CREATION:      22/10/2025                                                   */    
/*DATE DE MODIFICATION:  2/10/2025                                                   */    
void lister_produits() {
    Produit produit;
    FILE *f = fopen("produit.dat", "rb");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier des produits.\n");
        return;
    }

    //afficher les produits avec leurr id et l'ID de l'usine ou ils sont
   printf("\nListe des produits:\n");
   while(fread(&produit, sizeof(Produit), 1, f) == 1) {

     //affichage sous forme de tableau des infos du produit ajouté
        printf("--------------------------------------------------\n");
        printf("| ID Produit | ID Usine | Nom Produit      | Description Produit  | Prix | Quantité |\n");
        printf("--------------------------------------------------\n");
        printf("| %d         | %d        | %s           | %s                 | %.2f | %d       |\n", produit.Id_prod, produit.Id_usine, produit.Pro_nom, produit.pro_desc, produit.pro_prix, produit.pro_qte);
        printf("--------------------------------------------------\n");
        
    }

    fclose(f);
}

/*------------------------------------------------------------------------*/
/* FONCTION:    generer_date_courante                                         */
/* DESCRIPTION: Remplit la chaîne date_str (taille >= 11) avec la date      */
/*              courante au format "DD/MM/YYYY"                            */
/*------------------------------------------------------------------------*/
void generer_date_courante(char* date_str) {
    if (date_str == NULL) return;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    if (t == NULL) {
        date_str[0] = '\0';
        return;
    }
    strftime(date_str, 11, "%d/%m/%Y", t);
}

/*------------------------------------------------------------------------*/
/* FONCTION:                     obtenir_dernier_id_lot                   */
/* DESCRIPTION:          Cette fonction permet d'obtenir le dernier ID 
                         de lot                                           */
/* PARAMETRE:            Nom du fichier                                   */
/*VALEUR DE RETOUR:      Un entier                                        */
/*AUTEUR:                PIERRE-LOUIS Alven Bernadin                      */
/*DATE DE CREATION:      05/11/2025                                       */
/*DATE DE MODIFICATION:  05/11/2025                                       */
/*........................................................................*/

int obtenir_dernier_id_lot(const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "rb");
    if (f == NULL) return 0;

    Hist_production temp;
    int dernier_id = 0;

    while (fread(&temp, sizeof(Hist_production), 1, f) == 1) {
        if (temp.Id_lot > dernier_id) {
            dernier_id = temp.Id_lot;
        }
    }
    fclose(f);
    return dernier_id;
}

/*------------------------------------------------------------------------*/
/* FONCTION:             enregistrer_production                  */
/* DESCRIPTION:          Cette fonction permet d'enregistrer un produit   */
/* PARAMETRE:            Aucun                                            */
/*VALEUR DE RETOUR:      Aucune                                           */
/*AUTEUR:                PIERRE-LOUIS Alven Bernadin                      */
/*DATE DE CREATION:      05/11/2025                                       */
/*DATE DE MODIFICATION:  05/11/2025                                       */
/*........................................................................*/

void enregistrer_production() {
    Hist_production nouveau_lot;
    Produit produit;
    char date_exp[11];
    
    // Générer ID lot unique
    nouveau_lot.Id_lot = obtenir_dernier_id_lot(HIST_VENTES_FILE) + 1;
    
    // Saisir ID produit et vérifier existence
    printf("Entrez l'ID du produit: ");
    scanf("%d", &nouveau_lot.id_prod);
    getchar();
    
    if (!lire_produit(PRODUIT_FILE, nouveau_lot.id_prod, &produit)) {
        printf("Erreur: Produit non trouvé!\n");
        return;
    }
    
    // Date de production (aujourd'hui)
    generer_date_courante(nouveau_lot.Dat_prod);
    
    // Date d'expiration
    printf("Entrez la date d'expiration (DD/MM/YYYY): ");
    fgets(date_exp, sizeof(date_exp), stdin);
    date_exp[strcspn(date_exp, "\n")] = '\0';
    strcpy(nouveau_lot.Dat_exp, date_exp);
    
    // Quantité du lot
    printf("Entrez la quantité produite: ");
    scanf("%d", &nouveau_lot.Lot_qte);
    getchar();
    
    // Enregistrer dans l'historique
    FILE *f = fopen(HIST_VENTES_FILE, "ab");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier historique.\n");
        return;
    }
    fwrite(&nouveau_lot, sizeof(Hist_production), 1, f);
    fclose(f);
    
    // Mettre à jour la quantité du produit
    produit.pro_qte += nouveau_lot.Lot_qte;
    
    // Réécrire le fichier produit avec la nouvelle quantité
    FILE *temp = fopen("temp.dat", "wb");
    FILE *orig = fopen(PRODUIT_FILE, "rb");
    Produit p;
    
    while(fread(&p, sizeof(Produit), 1, orig) == 1) {
        if(p.Id_prod == produit.Id_prod) {
            fwrite(&produit, sizeof(Produit), 1, temp);
        } else {
            fwrite(&p, sizeof(Produit), 1, temp);
        }
    }
    
    fclose(orig);
    fclose(temp);
    remove(PRODUIT_FILE);
    rename("temp.dat", PRODUIT_FILE);
    
    printf("Production enregistrée avec succès!\n");
    printf("Nouveau stock pour %s: %d unités\n", produit.Pro_nom, produit.pro_qte);
}
