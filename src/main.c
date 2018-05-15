#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficher_liste_noeud(pliste_t liste) {
    if(!liste)
        return ;
    pnoeud_t n = liste->tete;
    while(n != NULL) {
        printf("%d | ", n->poids);
        n = n->suiv;
    }
    printf("\n");
}

////////////////////////////////
/* FONCTION ELEMENTAIRE NOEUD */
////////////////////////////////

pnoeud_t creer_noeud(int poids) {
  pnoeud_t noeud = malloc(sizeof(noeud_t));
  noeud->poids = poids;
  return noeud;
}

void ajouter_queue(pnoeud_t noeud, pliste_t liste) {
  liste->queue->suiv = noeud;
  liste->queue = noeud;
}

////////////////////////////////
/*      FONCTION CONVERSION   */
////////////////////////////////

void conversion_tableau_liste(int *occurence, pliste_t liste) {
  int i = 0;
  while (occurence[i] == 0) {
    i++;
  }
  pnoeud_t noeud = creer_noeud(occurence[i]);
  liste->tete = noeud;
  pnoeud_t noeud_crt = liste->tete;
  i++;

  for (; i < 256; i++) {
    if (occurence[i] != 0) {
      pnoeud_t noeud = creer_noeud(occurence[i]);
      noeud_crt->suiv = noeud;
      noeud_crt = noeud;
    }
  }
  liste->queue = noeud_crt;
}

////////////////////////////////
/*   FONCTION CREATION ARBRE  */
////////////////////////////////

pnoeud_t creer_arbre_canonique(int *occurence) {
  pliste_t liste = malloc(sizeof(liste_t));
  conversion_tableau_liste(occurence, liste);

  //TEST
  afficher_liste_noeud(liste);
}



void test_conversion_tableau_liste() {
    int *occ = malloc(sizeof(int) * 256);
    occ[2] = 5;
    occ[10] = 59;
    occ[240] = 9;
    creer_arbre_canonique(occ);
}



int main(int argc, char const *argv[]) {
    test_conversion_tableau_liste();


  return 0;
}
