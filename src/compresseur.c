#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "compression.h"
#include "decompression.h"
#include "rle.h"
#include "mtf.h"


int main(int argc, char const *argv[]) {

  if(argc == 1){
    printf("Manque un fichier\n");
    return 0;
  }
  char fichier[50];
  char fichier_compresse[50];
  strcpy(fichier,argv[1]);
  strcpy(fichier_compresse,argv[1]);
  strcat(fichier_compresse,".ggg");
  printf("==============PRE TRAITEMENT======================\n");
  rle(fichier);
  mtf(fichier);
  printf("Fichiers codage_mtf, codage_rle, decodage_mtf et decodage_rle crees dans ../test/\n", );
  printf("==============COMPRESSION/DECOMPRESSION======================\n");
  compression(fichier);
  decompression(fichier_compresse);

  return 1;
}
