#ifndef COMPRESSION_H
#define COMPRESSION_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noeud.h"

typedef uint64_t uint256_t[4];

typedef struct {
  char c;
  uint256_t code;
  uint8_t longueur;
} codage_t , *pcodage_t;


void affiche_table_de_codage(pcodage_t codage,int taille);

void ecrire_buffer(FILE* f, uint64_t* buffer);

int ecrire_fichier_compresse(pcodage_t codage, int nb_codage,char* file_name);

uint64_t* table_pourcentage_huffman(char *file_name);

void compression(char* path);

void tri_arbre_largeur(pnoeud_t head);

int conversion_tableau_liste(uint64_t *occurence, pliste_t liste);

pcodage_t arbre_to_table(pnoeud_t racine, int nombre_carractere);

void arbre_to_table_Worker(pnoeud_t racine, int *indice, uint64_t valeur0, uint64_t valeur1, uint64_t valeur2, uint64_t valeur3, pcodage_t table, int profondeur);

void decalage_256(uint64_t *valeur0, uint64_t *valeur1, uint64_t *valeur2, uint64_t *valeur3);

void decalage_256_multiple(uint64_t *valeur0, uint64_t *valeur1, uint64_t *valeur2, uint64_t *valeur3,uint64_t decalage);

void incremente(uint64_t *valeur0, uint64_t *valeur1, uint64_t *valeur2, uint64_t *valeur3);

pnoeud_t creer_arbre_quelconque(pliste_t liste);

////////////////////////////////
/* FONCTION TEST */
////////////////////////////////
void afficher_liste_noeud(pliste_t liste);
void afficher_arbre(pnoeud_t a, int niveau);
void test_conversion_tableau_liste();



#endif
