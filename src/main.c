#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int* table_pourcentage_huffman(char const* file_name){ //Recoit le nom du fichier a compresser (argv[1]) et renvoie un tableau a 256 cases des occurences des caractères
  FILE* f = fopen(file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }
  int* table = malloc(256 * sizeof(int));
  for (int i = 0; i < 256; i++) {
    table[i] = 0;
  }
  char c;
  while ((c = fgetc(f)) != EOF) {
    table[c]++;
  }
  fclose(f);

  return table;
}


int main(int argc, char const *argv[]) {

  return 0;
}
