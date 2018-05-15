#ifndef COMPRESSION_H
#define COMPRESSION_H
#include <stdint.h>

typedef uint64_t uint256_t[4];

typedef struct n {
    struct n *parent;
    struct n *fgauche;
    struct n *fdroit;
    int poids;
    char c;
    struct n *suiv;
} noeud_t, *pnoeud_t;

typedef struct {
    pnoeud_t tete;
    pnoeud_t queue;
} liste_t, *pliste_t;

typedef struct {
  char c;
  uint256_t code;
  uint8_t longueur;
} codage_t , *pcodage_t;

////////////////////////////////
/* FONCTION ELEMENTAIRE NOEUD */
////////////////////////////////
pnoeud_t creer_noeud(int poids);
void ajouter_queue(pnoeud_t noeud, pliste_t liste);
pnoeud_t retirer_noeud(pnoeud_t noeud, pliste_t liste);
pnoeud_t get_noeud_min(pliste_t liste);

////////////////////////////////
/*      FONCTION CONVERSION   */
////////////////////////////////
void conversion_tableau_liste(int *occurence, pliste_t liste);

pcodage_t arbre_to_table(pnoeud_t racine, int nombre_carractere);

void arbre_to_table_Worker(pnoeud_t racine, int indice, uint256_t valeur,
                           pcodage_t table, int profondeur);

void decalage_256(uint256_t valeur, uint256_t valeur_decalee);

////////////////////////////////
/*   FONCTION CREATION ARBRE  */
////////////////////////////////

pnoeud_t creer_arbre_quelconque(int *occurence);
pnoeud_t convertion_canonique(int *occurence);

////////////////////////////////
/* FONCTION TEST */
////////////////////////////////
void afficher_liste_noeud(pliste_t liste);
void test_conversion_tableau_liste();



#endif
