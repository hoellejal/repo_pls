#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "rle.h"

void init_liste(nprev_c tete, uint8_t max) {
  nprev_c courant= malloc(max*sizeof(prev_c));
  nprev_c precedent = tete;
  for (int i = 0; i < max; i++) {
    courant->next = malloc(max*sizeof(prev_c));
    courant[i].c = EOF;
    courant[i].prev = precedent;
    precedent[i].next = courant;
    courant = courant->next;
  }
  courant->next = tete;
  tete->prev = courant;
}

void compression(char const* file_name) {
  FILE* f = fopen(file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }

  nprev_c tete = malloc(sizeof(prev_c));
  nprev_c courant = malloc(sizeof(prev_c));
  uint8_t max = 127;
  init_liste(tete, max);

  char* new_file_name = "../test/codage_rle";
  FILE* new_f = fopen(new_file_name, "w");
  int c1 = EOF;
  int c2 = EOF;
  uint8_t i;
  char not_i;
  while ((c1 = fgetc(f)) != EOF) {
    fputc(c1, new_f);
    if (c1 == c2) {
      i = 0;
      tete = tete->next;
      tete->c = c2;
      while ((c2 = fgetc(f)) == c1 && i < max) {i++;}
      if (i != 0) {
        fputc(i, new_f);
        if (c2 != EOF) {
          fputc(c2, new_f);
        }
      } else {
        i = 1;
        courant = tete;
        while (i < 129 && courant->c != c2) {
          printf("%d : %c\n", i, courant->c);
          i++;
          courant = courant->prev;
        }
        if (i < 128) {
          not_i = ~i;
          fputc(not_i, new_f);
        } else {
          fputc(0, new_f);
          fputc(c1, new_f);
          c2 = c1;
        }
      }
      tete = tete->next;
      tete->c = c1;
      tete = tete->next;
      tete->c = c2;
    } else {
      tete = tete->next;
      tete->c = c2;
      c2 = c1;
    }
  }
  fclose(f);
  fclose(new_f);
}

void decompression(char const* file_name) {
  FILE* f = fopen(file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }

  char* new_file_name = "../test/decodage_rle";
  FILE* new_f = fopen(new_file_name, "w");
  int c1 = EOF;
  int c2 = EOF;
  uint8_t i;
  while ((c1 = fgetc(f)) != EOF) {
    fputc(c1, new_f);
    if (c1 == c2) {
      i = fgetc(f);
      for (int j = 0; j < i; j++) {
        fputc(c1, new_f);
      }
    } else {
      c2 = c1;
    }
  }
  fclose(f);
  fclose(new_f);
}

int main(int argc, char const *argv[]) {
  compression(argv[1]);
  //decompression("../test/codage_rle");

  return 0;
}
