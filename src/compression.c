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
  strcat(comp_name,".xxx");
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
  uint64_t save,mask;
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
        for (int i = tab_poids_fort - 1; i > 0; i++) {
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
  fclose(fr);
  fclose(fw);

  return 1;
}

int main(int argc, char const *argv[]) {

  return 0;
}
