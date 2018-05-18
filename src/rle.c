#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void compression_rle(char const* file_name) {
  FILE* f = fopen(file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }

  char* new_file_name = "../test/codage_rle";
  FILE* new_f = fopen(new_file_name, "w");
  int c1 = EOF;
  int c2 = EOF;
  uint8_t i;
  uint8_t max = ~0;
  while ((c1 = fgetc(f)) != EOF) {
    fputc(c1, new_f);
    if (c1 == c2) {
      i = 0;
      while (((c2 = fgetc(f)) == c1) && i<max) {i++;printf("i:%d \n",i);}
      fputc(i, new_f);
      if (c2!=EOF){
        fputc(c2, new_f);
      }
    }
    else{
      c2 = c1;
    }
  }
  fclose(f);
  fclose(new_f);
}

void decompression_rle(char const* file_name) {
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

int rle(char* path) {
  compression_rle(path);
  decompression_rle("../test/codage_rle");

  return 0;
}
