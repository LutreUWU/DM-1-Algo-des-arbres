#ifndef DM_H
#define DM_H

/********** STRUCTURE **********/
typedef struct _noeud {
    int valeur ;
    struct _noeud * fg , * fd ;
} Noeud , * Arbre ;

typedef struct cell {
    Noeud * n ;
    struct cell * suivant ;
} Cellule , * Liste ;

typedef struct {
    Liste debut ;
    Liste fin ;
    int taille ;
} Queue , * File ;

int powe(int n, int p); // Fonction renvoie 2 puissance n

Cellule * alloue_cellule(Noeud * n);
void insere_en_tete(Liste * l, Cellule * c);
Cellule * extrait_tete(Liste * l);
void affiche_liste_renversee(Liste l);

File initialisation();
int est_vide(File f);
int enfiler(File f, Noeud * n);
int defiler(File f, Noeud ** sortant);

Noeud * alloue_noeud(int val, Arbre fg, Arbre fd);
int hauteur_arbre(Arbre a); // Fonction annexe
int construit_complet(int h, Arbre * a);
void free_arbre(Arbre a); // Fonction annexe
int build_filiforme_aleatoire(int h, Arbre *a, int val); // Fonction annexe
int construit_filiforme_aleatoire(int h, Arbre * a, int graine);

void Libere_Liste(Liste *l, Liste lst); // Fonction annexe
int insere_niveau(Arbre a, int niv, Liste * lst);
int parcours_largeur_naif(Arbre a, Liste * lst);
int parcours_largeur(Arbre a, Liste * lst);

int insere_niveau_V2(Arbre a, int niv, Liste * lst, int * nb_visite);
int parcours_largeur_naif_V2(Arbre a, Liste * lst, int * nb_visite);
int parcours_largeur_V2(Arbre a, Liste * lst, int * nb_visite);

#endif
