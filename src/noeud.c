#include "noeud.h"
#include <stdint.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))



void affiche_noueud_tableau(pnoeud_t *tableau,int longueur){
	for(int i=0;i<longueur;i++){
		printf("%u->%lu | ",tableau[i]->c, tableau[i]->poids);
	}
  printf("\n");
}


pnoeud_t get_precedent(pnoeud_t noeud_arriver,pliste_t liste){
  pnoeud_t head = liste->tete;
  while (head->suiv != noeud_arriver){
    head = head->suiv;
  }
  return head;
}


////////////////////////////////
/* FONCTION ELEMENTAIRE NOEUD */
////////////////////////////////

void inverser_noeuds(pnoeud_t n1, pnoeud_t n2) {
  if(n1 != NULL && n2 != NULL) {
    if(n1->parent == n2->parent) {
      pnoeud_t tmp = n1->parent->fgauche;
      n1->parent->fgauche = n1->parent->fdroit;
      n1->parent->fdroit = tmp;
    }else {// inverser noeud + changer parent des noeuds
      pnoeud_t tmp_parent1 = n1->parent;
      pnoeud_t tmp_parent2 = n2->parent;

      if(n1->parent->fdroit == n1) {
        n1->parent->fdroit = n2;
        n2->parent->fgauche = n1;
      }else {
        n1->parent->fgauche = n2;
        n2->parent->fdroit = n1;
      }
      n1->parent = tmp_parent2;
      n2->parent = tmp_parent1;

    }
  }
}

void afficher_arbre(pnoeud_t a, int niveau) {
  int i;
  if (a != NULL) {
    afficher_arbre(a->fdroit, niveau + 1);

    for (i = 0; i < niveau; i++)
      printf("\t");

    printf(" %lu %u (%d)\n\n", a->poids, a->c, niveau);
    afficher_arbre(a->fgauche, niveau + 1);
  }
}

void afficher_liste_noeud(pliste_t liste) {
  if (!liste)
    return;
  pnoeud_t n = liste->tete;
  while (n != NULL) {
    printf("%u->%lu | ", n->c, n->poids);
    n = n->suiv;
  }
  printf("\n");
}

pnoeud_t creer_noeud(uint64_t poids) {
  pnoeud_t noeud = malloc(sizeof(noeud_t));
  noeud->poids = poids;
  noeud->fgauche = NULL;
  noeud->fdroit = NULL;
  noeud->parent = NULL;
  noeud->suiv = NULL;
  return noeud;
}

void ajouter_queue(pnoeud_t noeud, pliste_t liste) {
	noeud->suiv = NULL;
  if (liste->tete == NULL) {
    liste->tete = liste->queue = noeud;
  } else {
    liste->queue->suiv = noeud;
    liste->queue = noeud;
  }
}

pnoeud_t retirer_noeud(pnoeud_t noeud, pliste_t liste) {
  if (liste->tete != NULL) {
    if (noeud == liste->tete && liste->tete == liste->queue) {
      liste->tete = NULL;
      liste->queue = NULL;
			noeud->suiv = NULL;
      return noeud;
    } else if(noeud == liste->tete && liste->tete != liste->queue){
			liste->tete = liste->tete->suiv;
			noeud->suiv = NULL;
      return noeud;
		}else {
      pnoeud_t noeud_courant = liste->tete;
      while (noeud_courant->suiv != liste->queue &&
             noeud_courant->suiv != noeud) {
        noeud_courant = noeud_courant->suiv;
      }
      if (noeud == liste->queue) {
        liste->queue = noeud_courant;
      }
      noeud_courant->suiv = noeud_courant->suiv->suiv;
			noeud->suiv = NULL;
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
      if (noeud_min->poids > noeud_courant->poids ||
          (noeud_min->poids == noeud_courant->poids &&
           profondeur(noeud_min) < profondeur(noeud_courant))) {
        noeud_min = noeud_courant;
      }
      noeud_courant = noeud_courant->suiv;
    }
    return noeud_min;
  } else {
    return NULL;
  }
}

int estFeuille(pnoeud_t noeud) {
  if (noeud != NULL) {
    return (noeud->fgauche == NULL && noeud->fdroit == NULL);
  } else {
    return 0;
  }
}

int profondeur(pnoeud_t noeud) {
  if (noeud == NULL) {
    return 0;
  } else {
    return max(profondeur(noeud->fgauche), profondeur(noeud->fdroit)) + 1;
  }
}
