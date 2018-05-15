#ifndef MTF_H
#define MTF_H

#define NB_SYMBOLES 256

typedef struct {
  char symbole;
  char valeur;
}code_lettre;

typedef code_lettre tab_mtf[NB_SYMBOLES];

#endif
