#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "arbre.h"

Noeud * alloue_noeud(int val, Arbre fg, Arbre fd){
    /*
    Fonction qui alloue l'espace mémoire nécessaire
    pour un Noeud.

    On suppose que la valeur peut être négative
    */
    Noeud * tmp = (Noeud *)malloc(sizeof(Noeud));
    if (!tmp){
        printf("Erreur : Allocution de la mémoire pour le Noeud\n");
        return NULL;
    }
    tmp->valeur = val;
    tmp->fg = fg;
    tmp->fd = fd;
    return tmp;   
}

void affiche_arbre(Arbre a) {
    /*
    Fonction qui fait le parcours d'un arbre en profondeur
    d'ordre préfixe.
    */
    if (a != NULL) {
        printf("%d ", a->valeur);
        affiche_arbre(a->fg);
        affiche_arbre(a->fd);
    }
}
