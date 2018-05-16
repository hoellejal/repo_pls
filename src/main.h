#ifndef COMPRESSION_H
#define COMPRESSION_H
#include <stdint.h>

typedef uint64_t uint256_t[4];

typedef struct n {
    struct n *parent;
    struct n *fgauche;
    struct n *fdroit;
    uint64_t poids;
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

typedef struct {
  char c;
  uint8_t longueur;
} codage_canonique_t , *pcodage_canonique_t;

////////////////////////////////
/* FONCTION ELEMENTAIRE NOEUD */
////////////////////////////////
pnoeud_t creer_noeud(uint64_t poids);
void ajouter_queue(pnoeud_t noeud, pliste_t liste);
pnoeud_t retirer_noeud(pnoeud_t noeud, pliste_t liste);
pnoeud_t get_noeud_min(pliste_t liste);

////////////////////////////////
/*      FONCTION CONVERSION   */
////////////////////////////////
void conversion_tableau_liste(uint64_t *occurence, pliste_t liste);

pcodage_t arbre_to_table(pnoeud_t racine, int nombre_carractere);

void arbre_to_table_Worker(pnoeud_t racine, int *indice, uint64_t valeur0,
                           uint64_t valeur1, uint64_t valeur2, uint64_t valeur3,
                           pcodage_t table, int profondeur);

void decalage_256(uint64_t *valeur0, uint64_t *valeur1, uint64_t *valeur2,
                  uint64_t *valeur3);

pcodage_canonique_t table_quelconque_to_canonique(pcodage_t table_quelconque, int longueur_table);
void tri_tableau(pcodage_t table,int taille);

////////////////////////////////
/*   FONCTION CREATION ARBRE  */
////////////////////////////////

pnoeud_t creer_arbre_quelconque(uint64_t *occurence);
pnoeud_t convertion_canonique(uint64_t *occurence);

////////////////////////////////
/* FONCTION TEST */
////////////////////////////////
void afficher_liste_noeud(pliste_t liste);
void test_conversion_tableau_liste();



#endif
