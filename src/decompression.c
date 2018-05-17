#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "decompression.h"
#include "compression.h"


int decompression(char* path){
  FILE *file = fopen(path,'r');

  if(file == NULL){
    printf("Le fichier %s est inconnnue \n",path );
    return 0;
  }
  int taille;
  pcodage_t code = lire_entete(file,&taille);
  set_table_decompression(code,taille);
  for (int i = 0; i < taille; i++) {
    printf("char %c --> %lu|%lu|%lu|%lu\n", table[i].c,table[i].code[3],table[i].code[2],table[i].code[1],table[i].code[0]);
  }


}

pcodage_t lire_entete(File *file,int *taille){
  int c;
  if ( (c=fgetc(f)) != EOF){
    *taille=c;
      pcodage_t table = malloc(*taille*sizeof(codage_t)); // a faire quelque part, soit dans la fonction soit en dehors
      int i=c;
      while (i<*taille) {
          fscanf(f, "%c%c", &table[i].c, &table[i].longueur);
          i++;
      }
  }

  return table;
}

void set_table_decompression(pcodage_t codage,int taille){
  int ancienne_longueur=1;
  int i=0;
  int logueur_courante=codage[0].longueur;
  uint64_t code1=0;
  uint64_t code2=0;
  uint64_t code3=0;
  uint64_t code4=0;

  while(i < taille) {
    longueur_courante=codage[i].longueur;
    decalage(code1,code2,code3,code4,logueur_courante-ancienne_longueur);

    while (i<taille && longueur_courante == codage[i].longueur) {
      codage[i].code[0]=code0;
      codage[i].code[1]=code1;
      codage[i].code[2]=code2;
      codage[i].code[3]=code3;
      incremente(code1,code2,code3,code4);
      i++;
    }
  }
}

int main(int argc, char const *argv[]){
  ptable_long y=lire_fichier(argv[1]);
}
