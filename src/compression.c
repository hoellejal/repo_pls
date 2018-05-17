#include "compression.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////
/*      FONCTION CONVERSION   */
////////////////////////////////
/**
 * \brief    Initialise une liste chainée des noeuds correspondant aux
 * caractères présents dans le fichier à compresser
 * \param    occurence    Tableau des occurrences des caractère ASCII
 * \param    liste        Structure représentatn la liste (tête et queue)
 */
int conversion_tableau_liste(uint64_t *occurence, pliste_t liste) {
  int i = 0;
  int nombre_caractere = 1;
  while (occurence[i] == 0 && i < 256) {
    i++;
  }

  if (i == 256) {
    return 0;
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
      nombre_caractere++;
    }
  }
  liste->queue = noeud_crt;
  return nombre_caractere;
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
      if (estFeuille(noeud1) && estFeuille(noeud2)) {
        parent->fgauche = noeud2;
        parent->fdroit = noeud1;
      } else if (estFeuille(noeud1) && !estFeuille(noeud2)) {
        parent->fgauche = noeud2;
        parent->fdroit = noeud1;
      } else if (estFeuille(noeud2) && !estFeuille(noeud1)) {
        parent->fgauche = noeud1;
        parent->fdroit = noeud2;
      } else {
        if (profondeur(noeud1) > profondeur(noeud2)) {
          parent->fgauche = noeud1;
          parent->fdroit = noeud2;
        } else {
          parent->fgauche = noeud2;
          parent->fdroit = noeud1;
        }
      }
      noeud1->parent = parent;
      noeud2->parent = parent;
      ajouter_queue(parent, liste);
    }
    afficher_liste_noeud(liste);
  }
  return liste->tete;
}

/**
 * \brief    Permet d'effectuer un décalage du type uint256_t (implémenté dans
 * compression.h)
 * \param    valeur0  64 premiers bits
 * \param    valeur1
 * \param    valeur2
 * \param    valeur3  64 derniers bits
 */
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

/**
 * \brief    Création de la table de codage à partir de l'arbre de Huffman
 * \param    racine  Racine de l'arbre de Huffman
 * \param    nombre_carractere
 * \return
 */
pcodage_t arbre_to_table(pnoeud_t racine, int nombre_carractere) {
  pcodage_t table = malloc(sizeof(codage_t) * nombre_carractere);
  int indice = 0;
  arbre_to_table_Worker(racine, &indice, 0, 0, 0, 0, table, 0);
  return table;
}

/**
 * \brief    Worker de la fonction arbre_to_table
 * \param    racine     Noeud courant
 * \param    indice     Indice de la table de codage
 * \param    valeur0..3 Le poids du noeud (uint256_t)
 * \param    table      Table de codage
 * \param    profondeur Profondeur du noeud courant
 * \return
 */
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

/**
 * \brief    Tri le tableau table selon la longueur des codages
 * \param    table  Tableau à trier
 * \param    taille Taille du tableau
 */
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

/**
 * \brief    Tri le tableau table selon les caractères
 * \details  Table doit avoir des éléments contigus selon la longueur des codage
 * \param    table_quelconque    Tableau de codage des caractères, les éléments
 * de même longueur de code sont contigus.
 * \param    longueur_table      Taille du tableau table_quelconque
 * \return   Table de huffman canonique (caractère, longueur de code)
 */
void table_quelconque_to_canonique(pcodage_t table, int taille) {

  int a = 0, b = 0;

  while (b < taille) {
    while (b < taille &&
           table[b].longueur ==
               table[b + 1].longueur) // borne sup du sous tableau
      b++;

    for (int i = a; i <= b; i++) {
      for (int j = a + 1; j <= b - i + a; j++) {
        if (table[j - 1].c > table[j].c) {
          char tampon = table[j - 1].c;
          table[j - 1].c = table[j].c;
          table[j].c = tampon;
        }
      }
    }
    a = b + 1;
    b = b + 1;
  }
}
