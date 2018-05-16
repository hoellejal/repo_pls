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
  uint64_t occurence = 1;

  occ['b'] = 1;
  occ['d'] = 1;
  occ['c'] = 2;
  occ['a'] = 3;
  occ['f'] = 3;
  occ['e'] = 11;

  pnoeud_t racine = creer_arbre_quelconque(occ);
  afficher_arbre(racine, 0);
  pcodage_t tableau = arbre_to_table(racine, 6);

  pcodage_t test = malloc(sizeof(codage_t) * 6);
/*  codage_t p1;
  p1.c = 'b';
  p1.longueur = 1;
  p1.code[0] = 1;
  codage_t p2;
  p2.c = 'b';
  p2.longueur = 2;
  p2.code[0] = 2;
  codage_t p3;
  p3.c = 'c';
  p3.longueur = 2;
  p3.code[0] = 3;
  codage_t p4;
  p4.c = 'd';
  p4.longueur = 3;
  p4.code[0] = 4;
  codage_t p5;
  p5.c = 'e';
  p5.longueur = 3;
  p5.code[0] = 5;
  codage_t p6;
  p6.c = 'f';
  p6.longueur = 4;
  p6.code[0] = 6;
  test[0] = p1;
  test[1] = p1;
  test[2] = p1;
  test[3] = p1;
  test[4] = p1;
  test[5] = p1;*/
  table_quelconque_to_canonique(test, 6);
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

int main(int argc, char const *argv[]) {
  test_conversion_tableau_liste();

  return 0;
}
