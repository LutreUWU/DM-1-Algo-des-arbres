#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

File initialisation(void){
    /*
        Fonction qui alloue l'espace mémoire nécessaire
        pour une File.
    */
    File tmp = (File) malloc(sizeof(Queue));
    if (tmp){
        tmp->debut = NULL;
        tmp->fin = NULL;
        tmp->taille = 0;
    } else{
        printf("Erreur : Allocution de la mémoire pour la file\n");
        return NULL;
    }
    return tmp;
}

int est_vide(File f){
    /*
        Fonction qui vérifie tout simplement
        si la file est vide
    */
    if (!(f->taille)){
        return 1;
    }
    return 0;
}

 int enfiler(File f, Noeud * n){
    /*
        Fonction qui ajoute un Noeud
        dans la file.

        Le noeud est ajouté à la fin de la file/
    */
    Cellule * tmp = alloue_cellule(n);
    if (!tmp) return 0;
    if (est_vide(f)) { 
        f->debut = tmp;
        f->fin = tmp;
    } else {
        f->fin->suivant = tmp;
        f->fin = tmp;
    }
    f->taille++;
    return 1;
 }

int defiler(File f, Noeud **sortant) {
    /*
        Fonction qui récupère le premier noeud
        qui est dans la file.
    */
    if (est_vide(f)) {  
        return 0;
    }
    Cellule *tmp = f->debut;
    *sortant = tmp->n;
    f->debut = f->debut->suivant;
    /* Si la file devient vide après extraction, on met aussi fin à NULL*/
    if (f->debut == NULL) {
        f->fin = NULL;
    }
    free(tmp);
    f->taille--;
    return 1;
}
