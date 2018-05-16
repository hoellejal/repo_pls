#include "noeud.h"
#include <stdlib.h>
#include <stdint.h>


#define max(a, b) ((a) > (b) ? (a) : (b))


////////////////////////////////
/* FONCTION ELEMENTAIRE NOEUD */
////////////////////////////////

pnoeud_t creer_noeud(uint64_t poids) {
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

int estFeuille(pnoeud_t noeud) {
  return (noeud->fgauche == NULL && noeud->fdroit == NULL);
}

int profondeur(pnoeud_t noeud) {
  if (noeud == NULL) {
    return 0;
  } else {
    return max(profondeur(noeud->fgauche), profondeur(noeud->fdroit)) + 1;
  }
}
