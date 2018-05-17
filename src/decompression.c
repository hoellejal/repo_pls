#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


ptable_long lire_table_longueur(const char* file_name){
  FILE* f = fopen(file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }

  int c;
  c=(fgetc(f))-'0';
  if (c==EOF){
    printf("Fichier vide. Abandon.\n");
    exit(0);
  }

  ptable_long t=malloc(c*sizeof(table_long)); // a faire quelque part, soit dans la fonction soit en dehors

  for(int h=0; h<c; h++){
      fscanf(f, "%c %hhi", &t[h].carac, &t[h].length);
  }

  int* table = malloc(256 * sizeof(int));

  fclose(f);

  return t;
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
