#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "mtf.h"

void creation_tab_mtf(tab_mtf* table) {
  for (int i = 0; i < NB_SYMBOLES; i++) {
    table[i]->symbole = i;
    table[i]->valeur = i;
  }
}

void modif_fichier(char const* file_name) {
  tab_mtf* tab = malloc(NB_SYMBOLES*sizeof(code_lettre));
  creation_tab_mtf(tab);

  FILE* f = fopen(file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }

  char* new_file_name = "codage_mtf";
  FILE* new_f = fopen(new_file_name, "w");
  char c;
  while ((c = fgetc(f)) != EOF) {
    for (int i = 0; i < NB_SYMBOLES && tab[i]->symbole != c; i++)
    fputc(tab[i]->valeur, new_f);
  }
}

int main(int argc, char const *argv[]) {
  modif_fichier(argv[1]);

  return 0;
}
