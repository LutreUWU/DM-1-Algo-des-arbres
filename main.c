#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/********** STRUCTURE **********/
typedef struct _noeud {
    int valeur ;
    struct _noeud * fg , * fd ;
} Noeud , * Arbre ;

typedef struct cell {
    Noeud * n ;
    struct cell * suivant ;
    struct cell * precedent ;
} Cellule , * Liste ;

typedef struct {
    Liste debut ;
    Liste fin ;
    int taille ;
} Queue , * File ;
/*******************************/

/********** LISTES / CELLULES  **********/
Cellule * alloue_cellule(Noeud * n){
    Cellule * tmp = (Cellule *)malloc(sizeof(Cellule));
    if (tmp){
        tmp->n = n;
        tmp->suivant = NULL;
        tmp->precedent = NULL;
    } else{
        printf("Erreur : Allocution de la mémoire pour la cellule\n");
        return NULL;
    }
    return tmp;
}

void insere_en_tete(Liste * l, Cellule * c){
    if (!(*l)){
        /* Si la liste est vide, alors la liste est la cellule*/
        *l = c;
    } else {
        c->suivant = *l;
        c->precedent = NULL;
        (*l)->precedent = c;
        (*l) = c;
    }
}

Cellule * extrait_tete(Liste * l){
    if (!(*l)){
        printf("Erreur : Impossible d'extraire la tête d'une liste vide.\n");
        return NULL;
    } else {
        Cellule * tmp;
        tmp = *l;
        (*l) = (*l)->suivant;
        if (*l){
            /* Si la liste n'est toujours pas vide après extraction */
            (*l)->precedent = NULL;
        }
        tmp->suivant = NULL;
        return tmp;
    }
}

void affiche_liste_renversee(Liste lst){
    if (lst){
        affiche_liste_renversee(lst->suivant);
        printf("Noeud valeur : %d\n", lst->n->valeur);
    }
}
/****************************/

/********** FILES  **********/
File initialisation(void){
    File tmp = (File) malloc(sizeof(File));
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
    if (!(f->taille)){
        return 1;
    }
    return 0;
}

 int enfiler(File f, Noeud * n){
    Cellule * tmp = alloue_cellule(n);
    if (!tmp) return 0;
    if (est_vide(f)) {
        f->debut = tmp;
        f->fin = tmp;
    } else {
        f->fin->suivant = tmp;
        tmp->precedent = f->fin;
        f->fin = tmp;
    }
    f->taille++;
    return 1;
 }

int defiler(File f, Noeud **sortant) {
    /* Si la file est vide, on ne peut rien défiler */
    if (est_vide(f)) {  
        return 0;
    }
    Cellule *tmp = f->debut;
    *sortant = tmp->n;
    f->debut = f->debut->suivant;
    /* Si la file devient vide après extraction, on met aussi fin à NULL*/
    if (f->debut == NULL) {
        f->fin = NULL;
    } else {
        f->debut->precedent = NULL;
    }
    free(tmp);
    f->taille--;
    return 1;
}
/**************************************/

/********** NOEUDS & ARBRES  **********/
Noeud * alloue_noeud(int val, Arbre fg, Arbre fd){
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
    Parcours un arbre en profondeur préfixe.
    */
    if (a != NULL) {
        printf("%d ", a->valeur);
        affiche_arbre(a->fg);
        affiche_arbre(a->fd);
    }
}

int construit_complet(int h, Arbre * a){
    /*
    Fonction qui construit un arbre dont le parcours
    en largeur est égal à 1, 2, 3 ... 2^(h+1) - 1

    Pour ce faire, on utilisera une file comme on a fait en TD 1
    */
    if (h <= 0) return 0;
    // Initialisation de la racine
    *a = alloue_noeud(1, NULL, NULL);
    if (!(*a)) return 0;
    // File pour gérer le parcours en largeur    
    File f = initialisation();
    if (!f) return 0;   
    enfiler(f, *a);
    // Valeur à assembler
    int current_value = 2;
    // Construction de l'arbre
    while(!est_vide(f)){
        Noeud *tmp = NULL;
        defiler(f, &tmp);
        if (current_value <= pow(2, h+1) - 1){
            // On enfile le noeud de gauche
            tmp->fg = alloue_noeud(current_value, NULL, NULL);
            enfiler(f, tmp->fg);
            current_value++;
        }
        if (current_value <= pow(2, h+1) - 1){
            // Puis on enfile le noeud de droite
            tmp->fd = alloue_noeud(current_value, NULL, NULL);
            enfiler(f, tmp->fd);
            current_value++;
        }
    }
    return 1;
}
/**************************************/

/*Attention, il manque la question 3.c de la partie 1 préléminaire*/
int main() {
    Arbre a = NULL;
    // Création d'un arbre de hauteur 3, dont les valeurs en parcours en largeur sont 1, 2, 3, 4, 5 ... 15
    if (construit_complet(3, &a)) affiche_arbre(a);
    return 1;
}