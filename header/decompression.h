#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H
#include "compression.h"
#include <stdio.h>
#include <stdint.h>

void set_table_decompression(pcodage_t codage,int taille);
pcodage_t lire_entete(char* path ,int *taille);
int decompression(char* path);
int ecriture_fichier_decompresse(pcodage_t codage, int taille_codage, char* path);
int egale256(uint256_t code,uint256_t buffer) ;
int isInTableau(uint256_t buffer, int longueur_buffer, pcodage_t codage, int longueur_codage, uint8_t *c);
#endif
