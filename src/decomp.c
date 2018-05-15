#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct table{
  char carac;
  short length;
};

int* lire_fichier(char const* file_name){
  FILE* f = fopen(file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }
  int* table = malloc(256 * sizeof(int));
  for (int i = 0; i < 256; i++) {
    table[i] = 0;
  }
  
  fclose(f);

  return table;
}

int main(){
  return 0;
}