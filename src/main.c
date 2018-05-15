#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "main.h"

int* table_pourcentage_huffman(char const* file_name){ //Recoit le nom du fichier a compresser (argv[1]) et renvoie un tableau a 256 cases des occurences des caractères
  FILE* f = fopen(file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }
  int* table = malloc(256 * sizeof(int));
  for (int i = 0; i < 256; i++) {
    table[i] = 0;
  }
  char c;
  while ((c = fgetc(f)) != EOF) {
    table[c]++;
  }
  fclose(f);

  return table;
}

table_l_code* creer_table_arbre(pnoeud_t racine){
  table_l_code* tab = malloc(256*sizeof(table_l_code));
  pnoeud_t bl = racine;
  save = tab;
  int i=0;
  while(racine!=NULL){
    while((temp->fgauche!=NULL)&&(temp->fdroit!=NULL)){
      if(temp->fdroit != NULL){
        temp = temp->fdroit;
      }
      else if (temp->fgauche!=NULL){
        temp = temp->fgauche;
      }
      i++;
    }
    tab[i]->symbole=temp->c;
    //et pour le reste idk
  }
  return tab;
}


int main(int argc, char const *argv[]) {
  int* t = table_pourcentage_huffman(argv[1]);
 // for (int i=0; i<256;i++){
    
  //}
  return 0;
}
