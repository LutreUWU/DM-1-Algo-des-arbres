#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbre.h"
#include "cellule.h"
#include "file.h"

void affiche_liste_renversee(Liste lst){
    /*
        Fonction qui affiche les éléments d'une liste à l'envers

        Pour ce faire, on fait une récursivité sur la liste.
    */
    if (lst){ 
        affiche_liste_renversee(lst->suivant);
        printf("Noeud valeur : %d\n", lst->n->valeur);
    }
}

void affiche_list(Liste lst){
    /*
        Fonction qui affiche les éléments d'une liste
    */
    if(!lst){
        return;
    }
    else{
        printf("%d -> ", lst -> n -> valeur);
        affiche_list(lst -> suivant);
    }
}

int powe(int n, int p){
    /*
        Fonction qui calcule n à la puissance p
    */
    int nb_final = 1;
    for(int i = p; i >= 1; i--){
        nb_final *= n;
    }
    return nb_final;
}


int construit_complet(int h, Arbre * a){
    /*
        Fonction qui construit un arbre dont le parcours
        en largeur est égal à 1, 2, 3 ... 2^(h+1) - 1

        Pour ce faire, on utilisera une file comme fait en TD 1
    */
    if (h <= 0) return 0;
    *a = alloue_noeud(1, NULL, NULL); // Initialisation de la racine
    if (!(*a)) return 0;
    File f = initialisation(); // File pour gérer le parcours en largeur    
    if (!f) return 0;   
    enfiler(f, *a);
    int current_value = 2; // Valeur à assembler
    while(!est_vide(f)){ // Construction de l'arbre
        Noeud *tmp = NULL;
        defiler(f, &tmp);
        if (current_value <= powe(2, h+1) - 1){ // On enfile le noeud de gauche
            tmp->fg = alloue_noeud(current_value, NULL, NULL);
            enfiler(f, tmp->fg);
            current_value++;
        }
        if (current_value <= powe(2, h+1) - 1){ // Puis on enfile le noeud de droite
            tmp->fd = alloue_noeud(current_value, NULL, NULL);
            enfiler(f, tmp->fd);
            current_value++;
        }
    }
    return 1;
}

int construit_filiforme_aleatoire(int h, Arbre * a, int graine){
    if(h <= 0) return 0;
    *a = alloue_noeud(1, NULL, NULL);
    if(!(*a)) return 0;
    File f = initialisation();
    if(!f) return 0;
    int current_value = 2;
    enfiler(f, *a);
    while(!est_vide(f)){
        srand(graine);
        Noeud *tmp = NULL;
        defiler(f, &tmp);
        int puissance = powe(2, h+1);
        if(current_value <= puissance - 1){
            // s'il n'y a pas de parent avec des enfants libre
            if(est_vide(f)){
                int r = rand() % 2;
                if(r){              
                    tmp->fg = alloue_noeud(current_value, NULL, NULL);
                    enfiler(f, tmp->fg);
                    current_value++;
                    graine += 5;
                    int r2 = rand() % 2;
                    if(r2 && (current_value <= puissance - 1)){
                        tmp->fd = alloue_noeud(current_value, NULL, NULL);
                        enfiler(f, tmp->fd);
                        current_value++;
                        graine += 1337;
                    }
                }
                else{            
                    tmp->fd = alloue_noeud(current_value, NULL, NULL);
                    enfiler(f, tmp->fd);
                    current_value++;
                    graine += 10;
                }
            }
            // sinon
            else{
                int r = rand() % 2, r2 = rand() % 2;
                if(r){
                    tmp->fg = alloue_noeud(current_value, NULL, NULL);
                    enfiler(f, tmp->fg);
                    current_value++;
                    graine += 27;
                }
                if(r2 && (current_value <= puissance - 1)){
                    tmp->fd = alloue_noeud(current_value, NULL, NULL);
                    enfiler(f, tmp->fd);
                    current_value++;
                    graine += 13;
                }
            }
        }
    }
    return 1;
}

int insere_niveau(Arbre a, int niv, Liste * lst){
    if(!a) return 0;

    if(!niv){
        Cellule *tmp = alloue_cellule(a);
        if(tmp) {
            insere_en_tete(lst, tmp);
            return 1;
        }
        return 0;
    }
    return insere_niveau(a -> fg, niv - 1, lst) + insere_niveau(a -> fd, niv - 1, lst);
}

int parcours_largeur_naif(Arbre a, Liste * lst){
    // Ne retourne pas les bonnes valeur en cas d'erreur d'allocation
    int i = 0;
    while(insere_niveau(a, i, lst))i++;
    return 1;
}

int parcours_largeur_naif_V2(Arbre a, Liste * lst, int *nb_visite){
    // Ne retourne pas les bonnes valeur en cas d'erreur d'allocation
    int i = 0;
    while(nb_visite += insere_niveau(a, i, lst))i++;
    return 1;
}

int parcours_largeur(Arbre a, Liste *lst){
    // ne gère pas le return 0 en cas de mauvaise allocation
    File f = initialisation();
    enfiler(f, a);
    while(!est_vide(f)){
        Arbre n = NULL;
        defiler(f, &n);
        if(n){
            enfiler(f, n -> fg);
            enfiler(f ,n -> fd);
            insere_en_tete(lst, alloue_cellule(n));
        }

    }
    return 1;
}

int parcours_largeur_V2(Arbre a, Liste *lst, int *nb_visite){
    // ne gère pas le return 0 en cas de mauvaise allocation
    File f = initialisation();
    enfiler(f, a);
    while(!est_vide(f)){
        Arbre n = NULL;
        defiler(f, &n);
        *nb_visite += 1;
        if(n){
            enfiler(f, n -> fg);
            enfiler(f ,n -> fd);
            insere_en_tete(lst, alloue_cellule(n));
        }

    }
    return 1;
}

/**************************************/
/*

void ecrireDebut(FILE *f){
    fprintf(f, "digraph arbre {\n");
    fprintf(f, "  node [shape=record , height=.1 ]\n");
    fprintf(f, "  edge [tailclip=false , arrowtail = dot , dir=both];\n\n");
}

void ecrireArbre(FILE *f, Arbre a){
    if(a){
        fprintf(f, "  n%p [label=\"<gauche> | <valeur> %d | <droit>\"];\n", a,a->valeur);
        if(a -> fg){
            fprintf(f, "  n%p:gauche:c -> n%p:valeur;\n", a, a -> fg);
            ecrireArbre(f, a -> fg);
        }
        if(a -> fd){
            fprintf(f, "  n%p:droit:c -> n%p:valeur;\n", a, a -> fd);
            ecrireArbre(f, a -> fd);
        }
    }
}

void ecrireFin(FILE *f){
    fprintf(f, "}");
}

void dessine(FILE *f, Arbre a){
    ecrireDebut(f);
    ecrireArbre(f, a);
    ecrireFin(f);
}


void creePDF(char *dot, char *pdf, Arbre a){
    FILE *out = fopen(dot, "w");
    dessine(out, a);
    fclose(out);
    int len = strlen(dot) + strlen(pdf) + 15;
    char *cmd = malloc(len);
    snprintf(cmd, len, "dot -Tpdf %s -o %s", dot, pdf);
    system(cmd);
    free(cmd);
}
*/

/********************************************************************************/
/*  Pour lancer le programme, taper la commande "make" simplement pour compiler */
/*  le programme.                                                               */
/*                                                                              */
/*  Le fichier compiler se nomme "main"                                         */
/*                                                                              */
/*  Pour supprimer les fichiers.o, taper la commande "make clean"               */
/********************************************************************************/

int main() {
    Arbre a = NULL;
    Liste lst = NULL;
    // Création d'un arbre de hauteur 3, dont les valeurs en parcours en largeur sont 1, 2, 3, 4, 5 ... 15
    if (construit_complet(3, &a)) affiche_arbre(a);

    // Création d'un arbre en filiforme de hauteur 3 avec une graine qui sauvegardera la forme de l'arbre.
    construit_filiforme_aleatoire(3, &a, 1453);
    
    printf("\n");
    parcours_largeur(a, &lst);
    affiche_list(lst);
    printf("\n");
    
    /* Marche pas sur Mac car j'ai pas dot MDR */
    //creePDF("arbre.dot", "arbre.pdf", a);
    //system("evince arbre.pdf &");
    return 0;
}
