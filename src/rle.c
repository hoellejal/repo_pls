#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void decodage_rle(char const* coded_file_name) {
 
  FILE* f = fopen(coded_file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }
 
  char* new_file_name = "../test/decodage_rle";
  FILE* new_f = fopen(new_file_name, "w");
  char c1;
  char c2;
  while ((c1 = fgetc(f)) != EOF) {
    
  }
  fclose(f);
  fclose(new_f);
}

int main(int argc, char const *argv[]) {
  return 0;
}
