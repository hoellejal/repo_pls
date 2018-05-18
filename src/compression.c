#include "compression.h"
#include "decompression.h"



void tri_arbre_largeur(pnoeud_t head){
	int longueur = 2; 
	pnoeud_t  *tableau = malloc(2*sizeof(pnoeud_t));
	int indice=0;
  if (head->fgauche != NULL){
		tableau[indice] = head->fgauche;
		indice++;
	}
	if (head->fdroit != NULL){
		tableau[indice] = head->fdroit;
		indice++;
	}

	while (longueur > 0){
			affiche_noueud_tableau(tableau,longueur);
			for (int i = 0; i < longueur; i++) {
    		for (int j = 1; j < longueur - i; j++) {
					if ( ( profondeur(tableau[j-1]) < profondeur(tableau[j]) ) || ( estFeuille(tableau[j-1]) && estFeuille(tableau[j]) && ( (uint8_t)(tableau[j-1]->c) < (uint8_t)(tableau[j]->c) ) ) ){
							printf("========================\n");
							printf("swap entre :\n");
							afficher_arbre(tableau[j], 0);
    					printf("parent:%u->%lu | \n",tableau[j]->parent->c, tableau[j]->parent->poids);
							printf("et :\n");
  						afficher_arbre(tableau[j-1], 0);
    					printf("parent:%u->%lu | \n",tableau[j-1]->parent->c, tableau[j-1]->parent->poids);
							printf("========================\n");

							pnoeud_t tampon;
							//INVERSION DES NOEUDS//
							if (tableau[j-1]->parent != tableau[j]->parent){
								if (tableau[j-1]->parent->fgauche == tableau[j-1]){
									tableau[j-1]->parent->fgauche = tableau[j];
								}else{
									tableau[j-1]->parent->fdroit = tableau[j];
								}

								if (tableau[j]->parent->fgauche == tableau[j]){
									tableau[j]->parent->fgauche = tableau[j-1];
								}else{
									tableau[j]->parent->fdroit = tableau[j-1];
								}

							}else{
								if(tableau[j-1]->parent->fgauche == tableau[j-1]){
									tableau[j-1]->parent->fgauche = tableau[j];
									tableau[j-1]->parent->fdroit = tableau[j-1];
								}else{
									tableau[j-1]->parent->fgauche = tableau[j-1];
									tableau[j-1]->parent->fdroit = tableau[j];
								}

							}
							//INVERSION DES PARENT DES NOEUDS//
							if (tableau[j-1]->parent != tableau[j]->parent){
								tampon = tableau[j-1]->parent;
								tableau[j-1]->parent = tableau[j]->parent;
								tableau[j]->parent = tampon;
							}

							
							//INVERSION DANS LE TABLEAU//
							tampon = tableau[j-1];
							tableau[j-1] = tableau[j];
							tableau[j] = tampon;
					}
				}
			}
			//CREATION ET REMPLISSAGE D'UN NOUVEAUX TABLEAU//
			int new_longueur=0;
			pnoeud_t *nouveaux_tableau = malloc(2*longueur*sizeof(pnoeud_t));;
			for(int i=0;i<longueur;i++){
				if (tableau[i]->fgauche != NULL){
					nouveaux_tableau[new_longueur]=tableau[i]->fgauche;
					new_longueur++;
				}
				if (tableau[i]->fdroit != NULL){
					nouveaux_tableau[new_longueur]=tableau[i]->fdroit;
					new_longueur++;
				}
			}
			//ON L'IBERE L'ANCIEN TABLEAU//
			pnoeud_t *ancien_tableau = tableau;
			tableau = nouveaux_tableau;
			longueur = new_longueur;
			free(ancien_tableau);
		}
}

void affiche_table_de_codage(pcodage_t codage,int taille){
  for (int i = 0; i < taille; i++) {
    printf("char: %d;longueur: %d;code: %lu|%lu|%lu|%lu\n", codage[i].c,codage[i].longueur,codage[i].code[3],codage[i].code[2],codage[i].code[1],codage[i].code[0]);
  }

}

void compression(char* path){
  uint64_t *occurence = table_pourcentage_huffman(path);
  pliste_t liste = malloc(sizeof(liste_t));
  int nb_char = conversion_tableau_liste(occurence,liste);
  pnoeud_t racine = creer_arbre_quelconque(liste);
  afficher_arbre(racine, 0);
	printf("================================================================================\n");
	tri_arbre_largeur(racine);
	printf("================================================================================\n");
	printf("-----------------------------------------------------\n" );
  afficher_arbre(racine, 0);
  
	pcodage_t tableau = arbre_to_table(racine, nb_char);
  table_quelconque_to_canonique(tableau, nb_char);
  affiche_table_de_codage(tableau,nb_char);
  ecrire_fichier_compresse(tableau,nb_char,path);
printf("-----------------------------------------------------\n" );
  FILE* compress = fopen("../test/test.txt.ggg", "r");
  if (!compress) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }
  int nb;
  pcodage_t nouveau_codage = lire_entete(compress,&nb);
  set_table_decompression(nouveau_codage,nb);
  affiche_table_de_codage(nouveau_codage,nb);
  fclose(compress);

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

uint64_t* table_pourcentage_huffman(char * path){ //Recoit le nom du fichier a compresser (argv[1]) et renvoie un tableau a 256 cases des occurences des caractères

  FILE* f = fopen(path, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }

  uint64_t* table = malloc(256 * sizeof(uint64_t));
  for (int i = 0; i < 256; i++) {
    table[i] = 0;
  }
  uint8_t c;
  while ((c = fgetc(f)) != (uint8_t)EOF) {
    table[c]++;
  }
  table[255]=1;
  fclose(f);
  return table;
}

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
pnoeud_t creer_arbre_quelconque(pliste_t liste) {
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
			noeud1->suiv=NULL;
      noeud2->suiv=NULL;
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

void decalage_256_multiple(uint64_t *valeur0, uint64_t *valeur1, uint64_t *valeur2,
                  uint64_t *valeur3,uint64_t decalage) {
  for (int i = 0; i < decalage; i++) {
    decalage_256(valeur0,valeur1,valeur2,valeur3);
  }
}


void incremente(uint64_t *valeur0, uint64_t *valeur1, uint64_t *valeur2,
                  uint64_t *valeur3) {

  uint64_t mask= 0;
  if (*valeur2 == ~mask ) {
    *valeur3 += 1;
  }

  if (*valeur1 == ~mask) {
    *valeur2 += 1;
  }

  if (*valeur0 == ~mask) {
    *valeur1 += 1;
  }
  *valeur0 +=1;
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
  tri_tableau(table, taille);

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


void ecrire_buffer(FILE* f, uint64_t* buffer){
  char* tmp = (char*)buffer;
  for (int i = 7; i >= 0; i--) {
    fprintf(f, "%c", tmp[i]);
  }
  *buffer = 0;
}

int ecrire_fichier_compresse(pcodage_t codage, int nb_codage,char* file_name){

    FILE* fr = fopen(file_name, "r");
    if (!fr) {
      printf("Ouverture du fichier impossible. Abandon.\n");
      exit(0);
    }

  char* comp_name = malloc(strlen(file_name) + 4);
  strcpy(comp_name,file_name);
  strcat(comp_name,".ggg");
  FILE* fw = fopen(comp_name, "w");
  fprintf(fw,"%c",nb_codage);
  for (int i = 0; i < nb_codage; i++) {
    fprintf(fw, "%c%c", codage[i].c, codage[i].longueur );
  }
  uint8_t c;
  int nb_bits_restant = 64;
  int decalage,tab_poids_fort,nb_bits_fort;
  codage_t code;
  int i;
  uint64_t buffer = 0;
  uint64_t save,mask;
  while ((c = fgetc(fr)) != (uint8_t)EOF) {
    i=0;
    while(codage[i].c != c){
      i++;
    }
    code = codage[i];
    if(code.longueur <= nb_bits_restant){
      buffer = (code.code[0]<< (nb_bits_restant-code.longueur )) | buffer;
      nb_bits_restant -= code.longueur;
      if(nb_bits_restant == 0){
        ecrire_buffer(fw,&buffer);
      }
    }
    else{
      tab_poids_fort = code.longueur / 64;
      nb_bits_fort = code.longueur % 64;
      decalage = nb_bits_fort - nb_bits_restant;
      mask = ((1 << decalage) - 1);
      if (decalage > 0) {
        save = code.code[0] & mask;
        for (int i = 0; i < tab_poids_fort; i++) {
          code.code[i] >>= decalage;
          if (i+1 != tab_poids_fort) {
            code.code[i] |= (code.code[i+1] & mask) << (64 - decalage);
          }
        }
        buffer |= code.code[tab_poids_fort] >> decalage;
        ecrire_buffer(fw,&buffer);
        for(int i = tab_poids_fort - 1; i >= 0; i++){
          ecrire_buffer(fw,&code.code[i]);
        }
        buffer = save << (64 - decalage);
        nb_bits_restant = 64 - decalage;
      }
      else if (decalage == 0) {
        buffer |= code.code[tab_poids_fort] & ((1 << nb_bits_restant) - 1);
        ecrire_buffer(fw,&buffer);
        for(int i = tab_poids_fort - 1; i >= 0; i++){
          ecrire_buffer(fw,&code.code[i]);
        }
        nb_bits_restant = 64;
      }
      else {
        decalage = -decalage;
        code.code[tab_poids_fort] <<= decalage;
        code.code[tab_poids_fort] |= (code.code[tab_poids_fort-1] >> (64 - decalage));
        buffer |= code.code[tab_poids_fort];
        ecrire_buffer(fw,&code.code[tab_poids_fort]);
        for (int i = tab_poids_fort - 1; i > 0; i--) {
          code.code[i] <<= decalage;
          code.code[i] |= (code.code[i-1] >> (64 - decalage));
          buffer |= code.code[i];
          ecrire_buffer(fw,&code.code[i]);
        }
        code.code[0] <<= decalage;
        buffer |= code.code[0];
        nb_bits_restant = decalage;
      }
    }
  }
  if (nb_bits_restant != 64) {
    ecrire_buffer(fw,&buffer);
  }
  fclose(fw);
  fclose(fr);
  return 1;
}
