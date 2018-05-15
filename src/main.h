#ifndef COMPRESSION_H
#define COMPRESSION_H

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


#endif
