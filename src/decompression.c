#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "decompression.h"


int decompression(char* path){
  int nb;
  pcodage_t nouveau_codage = lire_entete(path,&nb);
  set_table_decompression(nouveau_codage,nb);
  affiche_table_de_codage(nouveau_codage,nb);
  ecriture_fichier_decompresse(nouveau_codage, nb, path);

  for (int i = 0; i < nb; i++) {
    printf("char %c --> %lu|%lu|%lu|%lu\n", nouveau_codage[i].c,nouveau_codage[i].code[3],nouveau_codage[i].code[2],nouveau_codage[i].code[1],nouveau_codage[i].code[0]);
  }
  return 1;
}

pcodage_t lire_entete(char* path,int *taille){
  int c;
  FILE *file = fopen(path,"r");

  if(file == NULL){
    printf("Le fichier %s est inconnnue \n",path );
    return 0;
  }

  if ( (c=fgetc(file)) != EOF){
    *taille=c;
      pcodage_t table = malloc(*taille*sizeof(codage_t)); // a faire quelque part, soit dans la fonction soit en dehors
      int i=0;
      while (i<*taille) {
          fscanf(file, "%c%c", &table[i].c, &table[i].longueur);
          i++;
      }

      return table;
  }
  fclose(file);
  return NULL;
}

void set_table_decompression(pcodage_t codage,int taille){
  int ancienne_longueur=codage[0].longueur;
  int i=0;
  int longueur_courante=codage[0].longueur;
  uint64_t code0=0;
  uint64_t code1=0;
  uint64_t code2=0;
  uint64_t code3=0;
  while(i < taille) {
    longueur_courante=codage[i].longueur;

    decalage_256_multiple(&code0,&code1,&code2,&code3,longueur_courante-ancienne_longueur);
    while (i<taille && longueur_courante == codage[i].longueur) {
      codage[i].code[0]=code0;
      codage[i].code[1]=code1;
      codage[i].code[2]=code2;
      codage[i].code[3]=code3;
      incremente(&code0,&code1,&code2,&code3);
      i++;
    }
    ancienne_longueur=longueur_courante;
  }
}

int egale256(uint256_t code,uint256_t buffer) {
    return code[0] == buffer[0] && code[1] == buffer[1] && code[2] == buffer[2] && code[3] == buffer[3];
}

int isInTableau(uint256_t buffer, int longueur_buffer, pcodage_t codage, int longueur_codage, uint8_t *c) {
  if(longueur_buffer == 0) {
    c = NULL;
    return 0;
  }
  int i=0;
  while( i < longueur_codage && longueur_buffer > codage[i].longueur ) {
    i++;
  }
  while( i < longueur_codage &&  longueur_buffer == codage[i].longueur && !egale256(codage[i].code,buffer) ) {
    i++;
  }

  if(i >= longueur_codage || longueur_buffer != codage[i].longueur ) {
    c = NULL;
    return 0;
  } else {
    *c = codage[i].c;
    return 1;
  }
}

int ecriture_fichier_decompresse(pcodage_t codage, int taille_codage, char* path) {
  FILE *file = fopen(path,"r");

  if(file == NULL){
    printf("Le fichier %s est inconnu \n",path );
    return 0;
  }

  FILE* fw = fopen("../test/testdecomp.txt", "w");

  uint256_t buffer;
  buffer[0]=0;
  buffer[1]=0;
  buffer[2]=0;
  buffer[3]=0;


  uint8_t c;
  uint8_t c_to_write;
  int indice;
  int longueur_buffer = 0;

  c = fgetc(file);
  for (int i = 0; i < taille_codage; i++) {
    c = fgetc(file);
    c = fgetc(file);
  }
  while((c = fgetc(file)) != (uint8_t)EOF) {
    indice = 7;
    while(indice >= 0) {
      while(!isInTableau(buffer, longueur_buffer, codage, taille_codage, &c_to_write) && indice >= 0) {
        decalage_256(&(buffer[0]), &(buffer[1]), &(buffer[2]), &(buffer[3]));
        if( (c & (1 << indice)) != 0 ) {
          incremente(&(buffer[0]), &(buffer[1]), &(buffer[2]), &(buffer[3]));
        }
        longueur_buffer++;
        indice--;
      }
      if(isInTableau(buffer, longueur_buffer, codage, taille_codage, &c_to_write)) {
        fprintf(fw, "%c", c_to_write);
        buffer[0] = 0;
        buffer[1] = 0;
        buffer[2] = 0;
        buffer[3] = 0;
        longueur_buffer = 0;
      }
    }
  }
  return 1;

}
