#ifndef NOEUD_H
#define NOEUD_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

////////////////////////////////
/* FONCTION ELEMENTAIRE NOEUD */
////////////////////////////////
void affiche_noueud_tableau(pnoeud_t *tableau,int longueur);
void afficher_arbre(pnoeud_t a, int niveau);
void afficher_liste_noeud(pliste_t liste);
pnoeud_t creer_noeud(uint64_t poids);
pnoeud_t get_precedent(pnoeud_t noeud_arriver,pliste_t liste);
void ajouter_queue(pnoeud_t noeud, pliste_t liste);
pnoeud_t retirer_noeud(pnoeud_t noeud, pliste_t liste);
pnoeud_t get_noeud_min(pliste_t liste);
int estFeuille(pnoeud_t noeud);
int profondeur(pnoeud_t noeud);
pnoeud_t get_precedent(pnoeud_t noeud_arriver,pliste_t liste);

#endif
