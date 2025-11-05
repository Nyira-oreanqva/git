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

//structure pour la date
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

// Fichiers de données
#define PRODUIT_FILE "produit.dat"
#define HIST_VENTES_FILE "Hist_Ventes.dat"

//structure usine
typedef struct{
    int id_usine;
    int id_com;
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

// structure vente
typedef struct {
    int id_vente;
    int id_prod;
    char dat_vente[11]; // format "JJ/MM/AAAA"
    int qte_vendue;
    float prix_unit;
    float prix_total;
} Vente;

// --- Prototypes des fonctions ---
int mettre_a_jour_stock(int id_prod, int qte_vendue);
int ajouter_vente(int id_prod, int qte_vendue, float prix_unit);
void generer_date_courante(char* date_str);
//structure commune
typedef struct 
{
    int id_commune;
    int id_departement;
    char nom_com[50];
    char desc_com[200];
}Commune;



//Prototypes des fonctions
void ins_usine();
int ecrire_usine(const char *nom_fichier, Usine *u);
int lire_usine(const char *nom_fichier, int id_recherche, Usine *resultat);
int lire_produit(const char *nom_fichier, int id_recherche, Produit *resultat);
void mod_usine();
void mod_produit();
void ins_Prod();
int obtenir_dernier_id_usine(const char *nom_fichier);
void lister_usines();

// structure vente
// typedef struct {
//     int id_vente;
//     int id_prod;
//     char dat_vente[11]; // format "JJ/MM/AAAA"
//     int qte_vendue;
//     float prix_unit;
//     float prix_total;
// } Vente;

// --- Prototypes des fonctions ---
int mettre_a_jour_stock(int id_prod, int qte_vendue);
int ajouter_vente(int id_prod, int qte_vendue, float prix_unit);
void generer_date_courante(char* date_str);

/*===========
=============================================================*/
/*                    PROTOTYPES - MENUS                                  */
/*========================================================================*/

void afficher_banniere(void);
void afficher_menu_principal(void);
void menu_departements(void);
void menu_production(void);
void menu_ventes(void);
void menu_rapports(void);
void menu_communes(void);
void menu_usines(void);
void mod_prod (void);
//Structures pour les départements et communes
typedef struct
{
    int id_departement;
    char nom_departement[50];
    char desc_departement[200];
} Departement;

// Prototype des fonctions pour les départements
void ins_dept();
int ecrire_departement(const char *nom_fichier, Departement *d);
int lire_departement(const char *nom_fichier, int id_recherche, Departement *resultat);
void mod_dept();

//prototype des fonctions pour gerer les ID
                                                   

int obtenir_dernier_id_dept(const char *nom_fichier);

//prototype des fonctions pour gerer les ID
                                                 

int obtenir_dernier_id_usine(const char *nom_fichier);

//prototype du fonction pour lister les departements
void lister_departements();
//prototype focntion pour  obtenir le dernier ID de commune
int obtenir_dernier_id_commune(const char *nom_fichier);
//prototype des fonctions pour ecrire une commune(mode ajout)
int ecrire_commune(const char *nom_fichier, Commune *c);
//prototype des fonctions pour lire une commune
int lire_commune(const char *nom_fichier, int id_recherche, Commune *resultat);
//prototype des fonctions pour modifier une commune
void mod_com();
//prototype des fonctions pour insérer une commune
void ins_com();
// prototype de la fonction qui permet de verifier si le nom d'un departement existe deja dans le fichier departement.dat
int verifier_nom_departement_existe(const char *nom_fichier, const char *nom_dept);
//prototype de la fonction pour obtenir le dernier ID de produit
int obtenir_dernier_id_produit(const char *nom_fichier);
//prototype des fonctions pour ecrire un produit(mode ajout)
int ecrire_produit(const char *nom_fichier, Produit *p);
//prototype des fonctions pour lire un produit
int lire_produit(const char *nom_fichier, int id_recherche, Produit *resultat);
//prototype des fonctions pour lister les communes
void lister_communes();
//prototype fonction pour lister les produits
void lister_produits();
//prototype de la focntion inserer une vente
int ins_vente();
//protype de la fonction pour verifier si un nom de commune existe déjà dans le même département
int verifier_nom_commune_existe(const char *nom_fichier, const char *nom_com);
//protype de la fonction generer la date courante
void generer_date_courante(char* date_str);
//protype de la fonction  menu pour les ventes
void menu_ventes(void);
//prototype de la fonction vifer buffer
void vider_buffer(void);

//prototype de la fonction pour incrementer l'id des ventes
int obtenir_dernier_id_vente(const char *nom_fichier);


















#endif // ENTREP_H