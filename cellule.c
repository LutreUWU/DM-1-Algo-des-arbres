#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cellule.h"

Cellule * alloue_cellule(Noeud * n){
    /*
    Fonction qui alloue l'espace mémoire nécessaire
    pour une Cellule.
    */
    Cellule * tmp = (Cellule *) malloc(sizeof(Cellule));
    if (tmp){
        tmp->n = n;
        tmp->suivant = NULL;
    } else{
        printf("Erreur : Allocution de la mémoire pour la cellule\n");
        return NULL;
    }
    return tmp;
}

void insere_en_tete(Liste * l, Cellule * c){
    /*
        Fonction qui insère en tête de liste,
        la cellule c.
    */
    if (!(*l)){
        /* Si la liste est vide, alors la liste est la cellule*/
        *l = c;
    } else {
        c->suivant = *l;
        (*l) = c;
    }
}

Cellule * extrait_tete(Liste * l){
    /*
        Fonction qui extrait le premier élément
        de la liste et qui la renvoie.
    */
    if (!(*l)){
        printf("Erreur : Impossible d'extraire la tête d'une liste vide.\n");
        return NULL;
    } else {
        Cellule * tmp;
        tmp = *l;
        (*l) = (*l)->suivant;
        tmp->suivant = NULL;
        return tmp;
    }
}
