#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


pnoeud_t creer_noeud(int poids) {
    pnoeud_t noeud = malloc(sizeof(noeud_t));
    noeud->poids = poids;
    return noeud;
}

void ajouter_queue(pnoeud_t noeud, pliste_t liste){
    liste->queue->suiv = noeud;
    liste->queue = noeud;
}

void conversion_tableau_liste(int* occurence, pliste_t liste) {
    int i = 0;
    while(occurence[i] == 0) {
        i++;
    }
    pnoeud_t noeud = creer_noeud(occurence[i]);
    liste->tete->noeud = noeud;
    pnoeud_t noeud_crt = tete->noeud;

    for( ; i<256; i++) {
        if(occurence[i] != 0) {
            pnoeud_t noeud = creer_noeud(occurence[i]);
            noeud_crt->suiv = noeud;
            noeud_crt = noeud;
        }
    }
    liste->queue = noeud_crt;
}





pnoeud_t creer_arbre_canonique(int* occurence) {
    pliste_t liste = malloc(sizeof(liste_t));
    conversion_tableau_liste(occurence, liste);
}


int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
