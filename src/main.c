#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

////////////////////////////////
/*      FONCTION CONVERSION   */
////////////////////////////////
/**
 * \brief    Initialise une liste chainée des noeuds correspondant aux
 * caractères présents dans le fichier à compresser
 * \param    occurence    Tableau des occurrences des caractère ASCII
 * \param    liste        Structure représentatn la liste (tête et queue)
 */
void conversion_tableau_liste(uint64_t *occurence, pliste_t liste) {
  int i = 0;
  while (occurence[i] == 0) {
    i++;
  }

  pnoeud_t noeud = creer_noeud(occurence[i]);
  noeud->c = i;
  liste->tete = noeud;
  i++;

  pnoeud_t noeud_crt = liste->tete;
  for (; i < 256; i++) {
    if (occurence[i] != 0) {
      pnoeud_t noeud = creer_noeud(occurence[i]);
      noeud->c = i;
      noeud_crt->suiv = noeud;
      noeud_crt = noeud;
    }
  }
  liste->queue = noeud_crt;
}

////////////////////////////////
/*   FONCTION CREATION ARBRE  */
////////////////////////////////
/**
 * \brief    Retourne un arbre de huffman a partir d'un tableau des occurences
 * des caractères
 * \param    occurence    Tableeau des occurrences des caractère ASCII
 * \return   Noeud racine de l'arbre de huffman
 */
pnoeud_t creer_arbre_quelconque(uint64_t *occurence) {
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
  }
  return liste->tete;
}

void decalage_256(uint64_t *valeur0, uint64_t *valeur1, uint64_t *valeur2,
                  uint64_t *valeur3) {
  uint64_t masque = 1;
  masque <<= 63;

  *valeur3 <<= 1;
  if ((*valeur2 & masque) != 0) {
    *valeur3 += 1;
  }
  *valeur2 <<= 1;

  if ((*valeur1 & masque) != 0) {
    *valeur2 += 1;
  }
  *valeur1 <<= 1;

  if ((*valeur0 & masque) != 0) {
    *valeur1 += 1;
  }
  *valeur0 <<= 1;
}

pcodage_t arbre_to_table(pnoeud_t racine, int nombre_carractere) {
  pcodage_t table = malloc(sizeof(codage_t) * nombre_carractere);
  int indice = 0;
  arbre_to_table_Worker(racine, &indice, 0, 0, 0, 0, table, 0);
  return table;
}

void arbre_to_table_Worker(pnoeud_t racine, int *indice, uint64_t valeur0,
                           uint64_t valeur1, uint64_t valeur2, uint64_t valeur3,
                           pcodage_t table, int profondeur) {

  if (racine != NULL) {

    if (racine->fdroit == NULL && racine->fgauche == NULL) {
      table[*indice].c = racine->c;
      table[*indice].code[0] = valeur0;
      table[*indice].code[1] = valeur1;
      table[*indice].code[2] = valeur2;
      table[*indice].code[3] = valeur3;
      table[*indice].longueur = profondeur;
      *indice = *indice + 1;
    } else {
      decalage_256(&valeur0, &valeur1, &valeur2, &valeur3);

      arbre_to_table_Worker(racine->fdroit, indice, valeur0, valeur1, valeur2,
                            valeur3, table, profondeur + 1);
      arbre_to_table_Worker(racine->fgauche, indice, valeur0 + 1, valeur1,
                            valeur2, valeur3, table, profondeur + 1);
    }
  }
}

void tri_tableau(pcodage_t table, int taille) {

  for (int i = 0; i < taille; i++) {
    for (int j = 1; j < taille - i; j++) {
      if (table[j - 1].longueur > table[j].longueur) {
        codage_t tampon = table[j - 1];
        table[j - 1] = table[j];
        table[j] = tampon;
      }
    }
  }
}
// MEMO
// Creation structure codage canonique
// Creation fonction table quelquonque to canonique
// Affichage des caractère pour les noeuds feuilles

/**
 * \brief    Retourne une table de huffman canonique à partir d'une table
 * quelconque
 * \details  A partir d'une tableau quelconque de huffman (caractère, code,
 * lonugueur du code => codage_t) on retourne une table de Huffman canonique
 * (caractère, longueur du code => codage_canonique_t). Les éléments de la table
 * du huffman quelconque de même longueure doivent être contigus.
 * \param    table_quelconque    Tableau de codage des caractères, les éléments
 * de même longueur de code sont contigus.
 * \param    longueur_table      Taille du tableau table_quelconque
 * \return   Table de huffman canonique (caractère, longueur de code)
 */
pcodage_canonique_t table_quelconque_to_canonique(pcodage_t table_quelconque,
                                                  int longueur_table) {

  pcodage_canonique_t table_canonique =
      malloc(sizeof(codage_canonique_t) * longueur_table);

  int a = 0, b = 0;
  int max;

  while (b < longueur_table) {
    while (table_quelconque[b].longueur ==
           table_quelconque[b + 1].longueur) // borne sup du sous tableau
      b++;

    for (int j = a; j <= b; j++) { // Recherche des max successivement du sous
                                   // tableau pour trier en ordre decroissant
      max = a;
      for (int k = a; k <= b; k++) {
        if (table_quelconque[k].c != -1 &&
            table_quelconque[k].c > table_quelconque[max].c)
          max = k;
      }

      table_canonique[j].c = table_quelconque[max].c;
      table_canonique[j].longueur = table_quelconque[max].longueur;
      table_quelconque[max].c = -1; // traité
    }
    // Initialisation des bornes du prochain sous tableau
    a = b + 1;
    b = b + 1;
  }

  return table_canonique;
}

////////////////////////////////
/* FONCTIONS TESTS */
////////////////////////////////

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
  for (int i = 33; i <= 126; i++) {
    occ[i] = occurence;
    occurence += 20;
  }
  pnoeud_t racine = creer_arbre_quelconque(occ);
  afficher_arbre(racine, 0);
  pcodage_t tableau = arbre_to_table(racine, 94);
  //
  // pcodage_t test = malloc(sizeof(codage_t) * 6);
  // codage_t p1;
  // p1.c = 'a';
  // p1.longueur = 2;
  // p1.code[0] = 1;
  // codage_t p2;
  // p2.c = 'b';
  // p2.longueur = 2;
  // p2.code[0] = 2;
  // codage_t p3;
  // p3.c = 'c';
  // p3.longueur = 2;
  // p3.code[0] = 3;
  // codage_t p4;
  // p4.c = 'd';
  // p4.longueur = 3;
  // p4.code[0] = 4;
  // codage_t p5;
  // p5.c = 'e';
  // p5.longueur = 3;
  // p5.code[0] = 5;
  // codage_t p6;
  // p6.c = 'f';
  // p6.longueur = 4;
  // p6.code[0] = 6;
  // test[0] = p1;
  // test[1] = p1;
  // test[2] = p1;
  // test[3] = p1;
  // test[4] = p1;
  // test[5] = p1;
  // table_quelconque_to_canonique(test, 6);
  tri_tableau(tableau, 94);
  for (int i = 0; i <= 93; i++) {
    printf("char: %c  -->  code: %lu|%lu|%lu|%lu longueur: %d \n", tableau[i].c,
           tableau[i].code[0], tableau[i].code[1], tableau[i].code[2],
           tableau[i].code[3], tableau[i].longueur);
  }
}

int main(int argc, char const *argv[]) {
  test_conversion_tableau_liste();

  return 0;
}
