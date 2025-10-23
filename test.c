#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Ajout pour strcpy

typedef struct{
    int Id_usine;
    int Id_com;
    char Usi_nom[50];
    char Usin_desc[200];
}Usine;

int ecrire_usine_binaire(const char *nom_fichier, Usine *u);
int lire_usine_par_id(const char *nom_fichier, int id_recherche, Usine *resultat);

int main()
{
    printf("inserer une usine\n");
    Usine u1;
    u1.Id_usine = 1;
    u1.Id_com = 101;
    // Correction : utilisation de strcpy pour les chaînes de caractères
    strcpy(u1.Usi_nom, "Usine A");
    strcpy(u1.Usin_desc, "Cet usine produit du Tafya");
    
    int retour= ecrire_usine_binaire("usine.dat", &u1);
    if(retour== 1)
    {
        printf("donnée ajoutée avec succes\n");
    }
    if (lire_usine_par_id("usine.dat", 1, &recherchee)) 
    {
        printf("Usine trouvée : %s\n", recherchee.Usi_nom);
        printf("Description : %s\n", recherchee.Usin_desc);
    } 
    else 
    {
        printf("Usine non trouvée.\n");
    }
    return 0;
}

int ecrire_usine_binaire(const char *nom_fichier, Usine *u) 
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

int lire_usine_par_id(const char *nom_fichier, int id_recherche, Usine *resultat) 
{
    FILE *f = fopen(nom_fichier, "rb");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }
    Usine temp;
    while (fread(&temp, sizeof(Usine), 1, f) == 1) {
        if (temp.Id_usine == id_recherche) {
            *resultat = temp;
            fclose(f);
            return 1; // trouvé
        }
    }
    fclose(f);
    return 0; // non trouvé
}