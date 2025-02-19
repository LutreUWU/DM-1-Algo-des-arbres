#ifndef CELLULE_H
#define CELLULE_H
#include "arbre.h"

typedef struct cell {
    Noeud * n ;
    struct cell * suivant ;
} Cellule , * Liste ;

Cellule * alloue_cellule(Noeud * n);

void insere_en_tete(Liste * l, Cellule * c);

Cellule * extrait_tete(Liste * l);
#endif
