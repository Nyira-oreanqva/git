/*------------------------------------------------------------------------*/
/* FCHIER:                          entrep.h                              */
/*AUTEUR:                           PIERRE-LOUIS Alven Bernadin           */    
/*DATE DE CREATIION:                26/09/2025                            */  
/*DATE DE MODIFICATION:             22/10/2025                            */ 
/*DESCRIPTION:                      fichier contenant les nouveaux types de
                                    données, les prototypes, les structures 
                                    de données et les constantes          */    
/*------------------------------------------------------------------------*/ 

#ifndef ENTREP_H
#define ENTREP_H

//structure usine
typedef struct{
    int Id_usine;
    int Id_com;
    char Usi_nom[50];
    char Usin_desc[200];
}Usine;

//structure produit
typedef struct{
    int Id_prod;
    int Id_usine;
    char Pro_nom[50];
    char pro_desc[200];
    float pro_prix;
    int pro_qte;
}Produit;

//structure Historique production
typedef struct{
    int Id_lot;
    int id_prod;
    char Dat_prod[11];
    char Dat_exp[11];
    int Lot_qte;
}Hist_production;

//Prototypes des fonctions
void insererUsine(int ID_commune);
int ecrire_usine(const char *nom_fichier, Usine *u);
int lire_usine(const char *nom_fichier, int id_recherche, Usine *resultat);
int lire_produit(const char *nom_fichier, int id_recherche, Produit *resultat);
void mod_usine();
void mod_produit();
void insererProduit();
int obtenir_dernier_id_usine(const char *nom_fichier);

#endif // ENTREP_H
