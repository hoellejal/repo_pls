#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
  char c;
  uint256_t code;
  uint8_t longueur;
} codage_t , *pcodage_t;
 
typedef struct {
  char c;
  uint8_t longueur;
} codage_canonique_t , *pcodage_canonique_t;

int ecrire_fichier_compresse(pcodage_t){
  //Lit le fichier initial et compresse dans un autre fichier grâce à la table des longueurs.
  
  return 1;
}


int main(int argc, char const *argv[]) {

  return 0;
}
