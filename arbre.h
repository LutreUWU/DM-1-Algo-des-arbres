#ifndef ARBRE_H
#define ARBRE_H

typedef struct _noeud {
    int valeur ;
    struct _noeud * fg , * fd ;
} Noeud , * Arbre ;

Noeud * alloue_noeud(int val, Arbre fg, Arbre fd);

void affiche_arbre(Arbre a);
#endif
