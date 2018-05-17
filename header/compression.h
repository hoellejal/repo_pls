#ifndef COMPRESSION_H
#define COMPRESSION_H
#include <stdint.h>
#include "noeud.h"

typedef uint64_t uint256_t[4];



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
/*      FONCTION CONVERSION   */
////////////////////////////////
int conversion_tableau_liste(uint64_t *occurence, pliste_t liste);

pcodage_t arbre_to_table(pnoeud_t racine, int nombre_carractere);

void arbre_to_table_Worker(pnoeud_t racine, int *indice, uint64_t valeur0, uint64_t valeur1, uint64_t valeur2, uint64_t valeur3, pcodage_t table, int profondeur);

void decalage_256(uint64_t *valeur0, uint64_t *valeur1, uint64_t *valeur2, uint64_t *valeur3);

void tri_tableau(pcodage_t table,int taille);

void table_quelconque_to_canonique(pcodage_t table_quelconque, int longueur_table);


////////////////////////////////
/*   FONCTION CREATION ARBRE  */
////////////////////////////////

pnoeud_t creer_arbre_quelconque(uint64_t *occurence);

////////////////////////////////
/* FONCTION TEST */
////////////////////////////////
void afficher_liste_noeud(pliste_t liste);
void afficher_arbre(pnoeud_t a, int niveau);
void test_conversion_tableau_liste();



#endif
