#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////
/* FONCTION ELEMENTAIRE NOEUD */
////////////////////////////////

pnoeud_t creer_noeud(int poids) {
  pnoeud_t noeud = malloc(sizeof(noeud_t));
  noeud->poids = poids;
  return noeud;
}

void ajouter_queue(pnoeud_t noeud, pliste_t liste) {
  if (liste->tete == NULL) {
    liste->tete = liste->queue = noeud;
  } else {
    liste->queue->suiv = noeud;
    liste->queue = noeud;
  }
}

pnoeud_t retirer_noeud(pnoeud_t noeud, pliste_t liste) {
  if (liste->tete != NULL) {
    if (noeud == liste->tete) {
      liste->tete = liste->tete->suiv;
      return noeud;
    } else {
      pnoeud_t noeud_courant = liste->tete;
      while (noeud_courant->suiv != liste->queue &&
             noeud_courant->suiv != noeud) {
        noeud_courant = noeud_courant->suiv;
      }
      if (noeud == liste->queue) {
        liste->queue = noeud_courant;
      }
      noeud_courant->suiv = noeud_courant->suiv->suiv;
      return noeud;
    }
  } else {
    return NULL;
  }
}

pnoeud_t get_noeud_min(pliste_t liste) {
  if (liste->tete != NULL) {
    pnoeud_t noeud_courant = liste->tete;
    pnoeud_t noeud_min = noeud_courant;
    noeud_courant = noeud_courant->suiv;
    while (noeud_courant != NULL) {
      if (noeud_min->poids > noeud_courant->poids) {
        noeud_min = noeud_courant;
      }
      noeud_courant = noeud_courant->suiv;
    }
    return noeud_min;
  } else {
    return NULL;
  }
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

pnoeud_t creer_arbre_quelconque(int *occurence) {
  pliste_t liste = malloc(sizeof(liste_t));
  conversion_tableau_liste(occurence, liste);
  afficher_liste_noeud(liste);

  while (liste->tete != liste->queue) {
    pnoeud_t noeud1 = retirer_noeud(get_noeud_min(liste), liste);
    pnoeud_t noeud2 = retirer_noeud(get_noeud_min(liste), liste);
    if (noeud1 != NULL && noeud2 != NULL) {
      pnoeud_t parent = creer_noeud(noeud1->poids + noeud2->poids);
      parent->fgauche = noeud1;
      parent->fdroit = noeud2;
      noeud1->parent = parent;
      noeud2->parent = parent;
      ajouter_queue(parent, liste);
    }

    afficher_liste_noeud(liste);
    printf("Tete : %i \n", liste->tete->poids);
    printf("Tete : %i \n", liste->queue->poids);
  }


  return liste->tete;

}

pcodage_t arbre_to_table();
    ////////////////////////////////
    /* FONCTION TEST */
    ////////////////////////////////
void afficher_liste_noeud(pliste_t liste) {
  if (!liste)
    return;
  pnoeud_t n = liste->tete;
  while (n != NULL) {
    printf("%d | ", n->poids);
    n = n->suiv;
  }
  printf("\n");

}

void afficher_arbre(pnoeud_t a, int niveau) {
    int i ;
    if (a != NULL) {
        afficher_arbre (a->fdroit, niveau+1) ;

        for (i = 0; i < niveau; i++)
            printf ("\t");

        printf (" %d (%d)\n\n", a->poids, niveau) ;
        afficher_arbre (a->fgauche, niveau+1) ;
    }
}

void test_conversion_tableau_liste() {
  int *occ = malloc(sizeof(int) * 256);
  occ[2] = 1;
  occ[10] = 1;
  occ[240] = 1;
  occ[248] = 1;
  occ[3] = 1;
  pnoeud_t racine = creer_arbre_quelconque(occ);
  afficher_arbre(racine, 0);
}

int main(int argc, char const *argv[]) {
  test_conversion_tableau_liste();

  return 0;
}
