#include <stdio.h>
#include <stdlib.h>

#include "dm.h"

int powe(int n, int p){
    int nb_final = 1;
    for(int i = p; i >= 1; i--){
        nb_final *= n;
    }
    return nb_final;
}

/********** CELLULES / LISTES **********/
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

void affiche_liste_renversee(Liste lst){
    /*
        Fonction qui affiche les éléments d'une liste à l'envers

        Pour ce faire, on fait une récursivité sur la liste.
    */
    if (lst){
        affiche_liste_renversee(lst->suivant);
        printf("%d -> ", lst->n->valeur);
    }
}

/****************************/

/********** FILES  **********/
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
/**************************************/

/********** NOEUDS & ARBRES  **********/
Noeud * alloue_noeud(int val, Arbre fg, Arbre fd){
    /*
        Fonction qui alloue l'espace mémoire nécessaire
        pour un Noeud.
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

int hauteur_arbre(Arbre a){
    /*
        Fonction qui affiche la hauteur
        d'un arbre COMPLET.
    */
    if (!a) return -1;
    return 1 + hauteur_arbre(a->fg);
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
    if(!enfiler(f, *a)) return 0;
    // Valeur à assembler
    int current_value = 2;
    // Construction de l'arbre
    while(!est_vide(f)){
        Noeud *tmp = NULL;
        defiler(f, &tmp);
        if (current_value <= powe(2, h+1) - 1){
            // On enfile le noeud de gauche
            tmp->fg = alloue_noeud(current_value, NULL, NULL);
            if (!enfiler(f, tmp->fg)) return 0;
            current_value++;
        }
        if (current_value <= powe(2, h+1) - 1){
            // Puis on enfile le noeud de droite
            tmp->fd = alloue_noeud(current_value, NULL, NULL);
            if (!enfiler(f, tmp->fd)) return 0;
            current_value++;
        }
    }
    return 1;
}

void free_arbre(Arbre a){
    /*
        Fonction qui libère la mémoire
        pour un arbre donné.
    */
    if(a){
        Arbre g = a -> fg, d = a -> fd;
        free(a);
        free_arbre(g);
        free_arbre(d);
    }
}

int build_filiforme_aleatoire(int h, Arbre *a, int val) {
    /*
        Fonction qui construit un arbre filiforme
        aléatoire de hauteur h.
    */
    if (h < 0) {
        *a = NULL;
        return 1;
    }
    int direction = rand() % 2; // Choix entre le noeud gauche ou droite
    Arbre sg = NULL;
    Arbre sd = NULL;

    if(direction){
        if(!build_filiforme_aleatoire(h - 1, &sg, val + 1)){
            return 0;
        }
    }
    else{
        if(!build_filiforme_aleatoire(h - 1, &sd, val + 1)){
            return 0;
        }        
    }
    Arbre tree = alloue_noeud(val, sg, sd);
    if (!tree){
        free(sg);
        free(sd);
        return 0;
    }
    *a = tree;
    return 1;
}

int construit_filiforme_aleatoire(int h, Arbre *a, int graine){
    /*
        Fonction qui construit un arbre filiforme
        à partir de la fonction build_filiforme_aleatoire()

        Cette fonction permet de garder dans une graine
        la structure de l'arbre crée. 
    */
    srand(graine);
    return (build_filiforme_aleatoire(h, a, 1));
}



void Libere_Liste(Liste *l, Liste lst) {
    /*
        Fonction qui libère la mémoire
        pour une liste donnée.
    */
    for(;*l && *l != lst;){
        free(extrait_tete(l));
    }
}

int insere_niveau(Arbre a, int niv, Liste *lst) {
    /*
        Fonction qui fait le parcours en largeur
        jusqu'à atteindre le niveau niv.

        Pour ce faire, on fait le parcours en largeur classique
        avec une file, sauf qu'on rajoute une condition qui arrête
        d'enfiler lorsqu'on atteint le nombre de noeud max au niveau niv.
    */
    if(!a) return 1;
    if (hauteur_arbre(a) < niv || niv < 0) return 0; // Si niv > hauteur de l'arbre ou niv est négatif
    // Si niv = 0, on insère juste la racine.
    if(niv == 0){
        insere_en_tete(lst, alloue_cellule(a));
        return 1;
    }
    int compteur = 1; // Compteur pour savoir combien de noeud on a lu
    Liste tmp = *lst;
    File f = initialisation();
    if(!enfiler(f, a)) return 0;
    while(!est_vide(f)){
        Arbre n = NULL;
        if(!defiler(f, &n)){
            Libere_Liste(lst, tmp);
            return 0;
        }
        if(n){
            // Tant que le nombre de noeud max est supérieur au nombre de noeud lu, on enfile
            if (powe(2, niv + 1) - 1 > compteur){
                if(!enfiler(f, n -> fg)) return 0;
                if(!enfiler(f ,n -> fd)) return 0;
                compteur += 2; // Car on enfile à gauche ET à droite
            }
            insere_en_tete(lst, alloue_cellule(n));
        }
    }
    
    return 1;
}

int parcours_largeur_naif(Arbre a, Liste *lst) {
    /*
        Fonction qui fait le parcours en largeur naif.
        On appelle simplement la fonction
    */
    if (!insere_niveau(a, hauteur_arbre(a), lst)) return 0;
    return 1;
}

int parcours_largeur(Arbre a, Liste *lst){
    /*
        Fonction qui fait le parcours en largeur
        en utilisant la méthode de la file.

        (Méthode vu au TD 1 d'Algo des Arbres)
    */
    Liste tmp = *lst;
    File f = initialisation();
    if(!enfiler(f, a)) return 0;;
    while(!est_vide(f)){
        Arbre n = NULL;
        if(!defiler(f, &n)){
            Libere_Liste(lst, tmp);
            return 0;
        }
        if(n){
            if(!enfiler(f, n -> fg)) return 0;
            if(!enfiler(f ,n -> fd)) return 0;
            insere_en_tete(lst, alloue_cellule(n));
        }

    }
    return 1;
}

int parcours_largeur_naif_V2(Arbre a, Liste * lst, int *nb_visite){
    /*
        Même fonction que insere_niveau() avec la hauteur de l'arbre.

        On ajoute un int nb_visite qui compte le nombre de fois qu'on visite un noeud.
        Pour ce faire on incrément juste le nb de visite chaque fois qu'on défile la file.
    */
    if(!a) return 1;
    int niv = hauteur_arbre(a);
    if(niv == 0){
        insere_en_tete(lst, alloue_cellule(a));
        return 1;
    }
    int compteur = 1;
    Liste tmp = *lst;
    File f = initialisation();
    if(!enfiler(f, a)) return 0;
    (*nb_visite) = 0;
    while(!est_vide(f)){
        (*nb_visite)++; // On l'ajoute au début de la boucle
        Arbre n = NULL;
        if(!defiler(f, &n)){
            Libere_Liste(lst, tmp);
            return 0;
        }
        if(n){
            if (powe(2, niv + 1) + 1 > compteur){
                if(!enfiler(f, n -> fg)) {Libere_Liste(lst, tmp); return 0;}
                if(!enfiler(f ,n -> fd)) {Libere_Liste(lst, tmp); return 0;}
                compteur += 2;
            }
            insere_en_tete(lst, alloue_cellule(n));
        }
    }
    return 1;
}

int parcours_largeur_V2(Arbre a, Liste *lst, int *nb_visite){
    /*
        Même fonction que parcours_largeur().

        On ajoute un int nb_visite qui compte le nombre de fois qu'on visite un noeud.
        Pour ce faire on incrément juste le nb de visite chaque fois qu'on défile la file.
    */
    Liste tmp = *lst; // Sauvegarde avant modification
    File f = initialisation();
    if (!f) return 0; // Vérification de l'allocation de la file
    if (!enfiler(f, a)) {
        return 0;
    }
    (*nb_visite) = 0;
    while (!est_vide(f)) {
        Arbre n = NULL;
        if (!defiler(f, &n)) {
            Libere_Liste(lst, tmp);
            return 0;
        }
        (*nb_visite)++; // Ajout du compteur de nb_visite
        if (n) {
            Cellule *tmp_cell = alloue_cellule(n);
            if (!tmp_cell) {
                Libere_Liste(lst, tmp);
                return 0;
            }
            insere_en_tete(lst, tmp_cell);
            if (n->fg && !enfiler(f, n->fg)) {
                Libere_Liste(lst, tmp);
                return 0;
            }
            if (n->fd && !enfiler(f, n->fd)) {
                Libere_Liste(lst, tmp);
                return 0;
            }
        }
    }
    return 1;
}

/* Pour lancer le programme, "make" sur le terminal, le fichier compilé se nomme "dm"*/
/* Construction d'un arbre de hauteur 4 */

int main(){
    Arbre a = NULL;
    Liste lst = NULL;
    int nb_visite;
    construit_complet(4, &a);
    printf("\n=================================================\n");
    printf("*** INFO SUR L'ARBRE ***\n\n");
    printf("Hauteur de l'arbre : %d\n", hauteur_arbre(a));
    printf("\nAffichage des noeuds au niv 0 :\n\t");
    insere_niveau(a, 0, &lst);
    affiche_liste_renversee(lst);
    printf("\nAffichage des noeuds au niv 1 :\n\t");
    insere_niveau(a, 1, &lst);
    affiche_liste_renversee(lst);
    lst = NULL;
    printf("\nAffichage des noeuds au niv 2 :\n\t");
    insere_niveau(a, 2, &lst);
    affiche_liste_renversee(lst);
    lst = NULL;
    printf("\nAffichage des noeuds au niv 3 :\n\t");
    insere_niveau(a, 3, &lst);
    affiche_liste_renversee(lst);
    lst = NULL;
    printf("\nAffichage des noeuds au niv 4 :\n\t");
    insere_niveau(a, 4, &lst);
    affiche_liste_renversee(lst);
    lst = NULL;
    parcours_largeur_naif_V2(a, &lst, &nb_visite);
    printf("\n\nParcours naif V2 (arbre complet) : nb_visite = %d\n", nb_visite);
    lst = NULL;
    parcours_largeur_V2(a, &lst, &nb_visite);
    printf("\nParcours par file V2 (arbre complet) : nb_visite = %d", nb_visite);
    printf("\n=================================================\n\n");
    return 1;
}
