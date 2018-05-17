#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H
#include "compression.h"
#include <stdio.h>
#include <stdint.h>
void set_table_decompression(pcodage_t codage,int taille);
pcodage_t lire_entete(FILE *file,int *taille);
int decompression(char* path);

#endif
