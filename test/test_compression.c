#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compression.h"



void afficher_liste_noeud(pliste_t liste) {
  if (!liste)
    return;
  pnoeud_t n = liste->tete;
  while (n != NULL) {
    printf("%lu | ", n->poids);
    n = n->suiv;
  }
  printf("\n");
}

void afficher_arbre(pnoeud_t a, int niveau) {
  int i;
  if (a != NULL) {
    afficher_arbre(a->fdroit, niveau + 1);

    for (i = 0; i < niveau; i++)
      printf("\t");

    printf(" %lu %c (%d)\n\n", a->poids, a->c, niveau);
    afficher_arbre(a->fgauche, niveau + 1);
  }
}

void test_conversion_tableau_liste() {
  uint64_t *occ = malloc(sizeof(uint64_t) * 256);

  occ['b'] = 1;
  occ['d'] = 1;
  occ['c'] = 2;
  occ['a'] = 3;
  occ['f'] = 3;
  occ['e'] = 11;

  pnoeud_t racine = creer_arbre_quelconque(occ);
  afficher_arbre(racine, 0);
  pcodage_t tableau = arbre_to_table(racine, 6);

  tri_tableau(tableau, 6);
  for (int i = 0; i < 6; i++) {
    printf("%d char: %c  -->  code: %lu|%lu|%lu|%lu longueur: %d \n", i, tableau[i].c,
           tableau[i].code[0], tableau[i].code[1], tableau[i].code[2],
           tableau[i].code[3], tableau[i].longueur);
  }
  printf("\n\n\n");

  table_quelconque_to_canonique(tableau, 6);

  for (int i = 0; i < 6; i++) {
    printf("%d char: %c  -->  code: %lu|%lu|%lu|%lu longueur: %d \n", i, tableau[i].c,
           tableau[i].code[0], tableau[i].code[1], tableau[i].code[2],
           tableau[i].code[3], tableau[i].longueur);
  }
  printf("\n\n\n");
}

test_compression_fichier(){
  int * occurence = table_pourcentage_huffman("test.txt");
  int taille;
  pnoeud_t racine = creer_arbre_quelconque(occurence);
  pcodage_t codage = arbre_to_table(racine, taille);
  tri_tableau(codage, taille);
  table_quelconque_to_canonique(codage, taille);

}


int main(int argc, char const *argv[]) {
  //test_conversion_tableau_liste();
  test_compression_fichier();

  return 0;
}
