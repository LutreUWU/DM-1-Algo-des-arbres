#ifndef FILE_H
#define FILE_H

#include "arbre.h"
#include "cellule.h"


typedef struct {
    Liste debut ;
    Liste fin ;
    int taille ;
} Queue , * File ;

File initialisation(void);

int est_vide(File f);

int enfiler(File f, Noeud * n);

int defiler(File f, Noeud **sortant);
#endif
