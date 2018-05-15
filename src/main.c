#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "main.h"

table_l_code* creer_table_arbre(pnoeud_t racine){
  table_l_code* tab = malloc(256*sizeof(table_l_code));
  pnoeud_t bl = racine;
  save = tab;
  int i=0;
  while(bl!=NULL){
    while((bl->fgauche!=NULL)&&(bl->fdroit!=NULL)){
      if(bl->fdroit != NULL){
        bl = bl->fdroit;
      }
      else if (bl->fgauche!=NULL){
        bl = bl->fgauche;
      }
      i++;
    }
    tab[i]->symbole=bl->c;
    //et pour le reste idk
  }
  return save;
}


int main(int argc, char const *argv[]) {

  return 0;
}
