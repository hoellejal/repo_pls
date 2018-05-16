#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "mtf.h"

void creation_tab_mtf(tab_mtf table) {
  for (int i = 0; i < NB_SYMBOLES; i++) {
    table[i] = i;
  }
}

void codage(char const* file_name) {
  tab_mtf tab;
  creation_tab_mtf(tab);

  FILE* f = fopen(file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }

  char* new_file_name = "../tests_fonctions/codage_mtf";
  FILE* new_f = fopen(new_file_name, "w");
  char c;
  int i;
  while ((c = fgetc(f)) != EOF) {
    for (i = 0; i < NB_SYMBOLES && tab[i] != c; i++);
    fputc(i, new_f);
    for (int j = i; j > 0; j--) {
      tab[j] = tab[j-1];
    }
    tab[0] = c;
  }
  fclose(f);
  fclose(new_f);
}

void decodage(char const* coded_file_name) {
  tab_mtf tab;
  creation_tab_mtf(tab);

  FILE* f = fopen(coded_file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }

  char* new_file_name = "../tests_fonctions/decodage_mtf";
  FILE* new_f = fopen(new_file_name, "w");
  char c;
  int i;
  while ((c = fgetc(f)) != EOF) {
    for (i = 0; i < NB_SYMBOLES && i != c; i++);
    c = tab[i];
    fputc(tab[i], new_f);
    for (int j = i; j > 0; j--) {
      tab[j] = tab[j-1];
    }
    tab[0] = c;
  }
  fclose(f);
  fclose(new_f);
}

int main(int argc, char const *argv[]) {
  codage(argv[1]);
  decodage("../tests_fonctions/codage_mtf");

  return 0;
}
