#ifndef MTF_H
#define MTF_H

#define NB_SYMBOLES 256

typedef uint8_t tab_mtf[NB_SYMBOLES];

void creation_tab_mtf(tab_mtf table) ;
void codage(char const* file_name) ;
void decodage(char const* coded_file_name) ;
int mtf(char* path) ;


#endif
