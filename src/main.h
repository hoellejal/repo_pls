#ifndef COMPRESSION_H
#define COMPRESSION_H

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
} codage_t , *pcodage_t;

////////////////////////////////
/* FONCTION ELEMENTAIRE NOEUD */
////////////////////////////////
pnoeud_t creer_noeud(int poids);
ajouter_queue(pnoeud_t noeud, pliste_t liste);
pnoeud_t retirer_noeud(pnoeud_t noeud, pliste_t liste);
pnoeud_t get_noeud_min(pliste_t liste);

////////////////////////////////
/*      FONCTION CONVERSION   */
////////////////////////////////
void conversion_tableau_liste(int *occurence, pliste_t liste);

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
