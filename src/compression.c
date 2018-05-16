#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint64_t uint256_t[4];

typedef struct {
  char c;
  uint256_t code;
  uint8_t longueur;
} codage_t , *pcodage_t;
 
typedef struct {
  char c;
  uint8_t longueur;
} codage_canonique_t , *pcodage_canonique_t;

int ecrire_fichier_compresse(pcodage_t codage, const char* file_name){
  //Lit le fichier initial et compresse dans un autre fichier grâce à la table des longueurs.
  FILE* f = fopen(file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }
  
  char* table = malloc(/*nbr elements ds fichier  */256 * sizeof(char));
  uint256_t * t = malloc(sizeof(uint256_t)* 256 /*nbr elements*/);

  for (int i = 0; i < 256; i++) {
    table[i] = 0;
  }

  char c;
  int i=0;
  while (((c = fgetc(f)) != EOF)) {
    table[i]=c;
    int j=0;
    while(table[i]!=codage[j].c){
      j++;
    }
    if(codage[j].longueur<64){
      t[i] = (codage[j].code[0]<<64-codage[j].longueur)>>64-codage[j].longueur;
    }
    else if(codage[j].longueur<64){
      t[i] = (codage[j].code[0]<<64-(codage[j].longueur -64))>>64-(codage[j].longueur -64)
    }
    i++;
  }
  fclose(f);

/* pour écriture: FILE *fp;
  fp = fopen( "compressed_file.txt" , "w" );
  fwrite(string où prendre les infos, 1(taille en octets) , sizeof(string) , fp );
  fclose(fp);*/
  return 1;
}

int main(int argc, char const *argv[]) {
  pcodage_t ugh=malloc(4*sizeof(pcodage_t));
  ugh[0].c='f';
  ugh[0].code[0]=0101;
  ugh[0].longueur=4;
  ugh[1].c='h';
  ugh[1].code[0]=101;
  ugh[1].longueur=3;
  int a = ecrire_fichier_compresse(ugh,argv[1]);
  return 0;
}
