#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

void set_table_decompression(pcodage_t codage,int taille);
pcodage_t lire_entete(File *file);
void decompression(char* path);

#endif
