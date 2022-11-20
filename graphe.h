#ifndef ECE_CITY_2_A_GRAPHE_H
#define ECE_CITY_2_A_GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"

typedef struct maillon{
    //numéro du sommet
    int num;
//pointeur sur la maillon suivant
    struct maillon*suiv;
}t_maillon;

typedef struct file{
    t_maillon*tete; //pointeur sur le premier maillon
    t_maillon*fin; //pointeur sur le dernier maillon
}t_file;

/* Structure d'un arc*/
struct Arc
{
    int sommet; // numero de sommet d'un arc adjacent au sommet initial
    int valeur;
    struct Arc* arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* Structure d'un sommet*/
struct Sommet
{
    struct Arc* arc;
    int valeur;
    int connexe;
    int* debut;
    int* finxplo;
    char couleur;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int date;
    int taille;
    int orientation;
    int ordre;
    pSommet* pSommet;
} Graphe;

// creer le graphe
Graphe* CreerGraphe(int ordre);

Graphe* charge_graphe(DonneesJoueur *joueur, int **sommet);

// Ajouter l'arete entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2);

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num);

void enfiler(t_file *f,int num);
int defiler(t_file *f);

int BFS(Graphe* graphe,int *preds,int s0);
void affichage(int* preds,int s0,Graphe * graphe);

#endif //ECE_CITY_2_A_GRAPHE_H
