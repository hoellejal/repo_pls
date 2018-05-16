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

void ecrire_buffer(FILE* f, uint64_t* buffer){
  fprintf(f, "%ld", *buffer);
  *buffer = 0;
}

int ecrire_fichier_compresse(pcodage_t codage, int nb_codage, const char* file_name){
  //Lit le fichier initial et compresse dans un autre fichier grâce à la table des longueurs.
  FILE* fr = fopen(file_name, "r");
  if (!fr) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }

  char* comp_name = malloc(strlen(file_name) + 4);
  strcpy(comp_name,file_name);
  strcat(comp_name,".xxx")
  FILE* fw = fopen(comp_name, "w");
  fprintf(fw,"%d",nb_codage);
  for (int i = 0; i < nb_codage; i++) {
    fprintf(fw, "%c%c", codage[i].c, codage[i].longueur );
  }

  char c;
  int nb_bits_restant = 64;
  int decalage,tab_poids_fort,nb_bits_fort;
  codage_t code;
  int i;
  uint64_t buffer = 0;
  while (((c = fgetc(fr)) != EOF)) {
    i=0;
    while(codage[i].c != c){
      i++;
    }
    code = codage[i];
    if(code.longueur <= nb_bits_restant){
      buffer = (code.code[0]<<nb_bits_restant-code.longueur) | buffer;
      nb_bits_restant -= code.longueur;
      if(nb_bits_restant == 0){
        ecrire_buffer(fw,&buffer);
      }
    }
    else{
      tab_poids_fort = code.longueur / 64;
      nb_bits_fort = code.longueur % 64;
      decalage = nb_bits_fort - nb_bits_restant;
      if (decalage > 0) {
        
      }
    }

  }
  fclose(fr);
  fclose(fw);

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
