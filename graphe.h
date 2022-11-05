#ifndef ECE_CITY_2_A_GRAPHE_H
#define ECE_CITY_2_A_GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nbLignes 35
#define nbColonnes 45

struct Arc {
    char lettre;
    int sommet;// numero de sommet d'un arc adjacent au sommet initial
    int valeur;
    int distance;
    int couleur;
    struct Arc *arc_suivant;
};
typedef struct Arc *pArc;

struct Sommet {
    struct Arc *arc;
    char *lettre;
    int valeur;
    int distance;
    int connexe;
    int *debut;
    int *finxplo;
    char couleur;

};
typedef struct Sommet *pSommet;

typedef struct Graphe {
    int date;
    int taille;
    int orientation;
    int ordre;
    pSommet *pSommet;
} Graphe;

typedef struct maillon {
    //numéro du sommet
    int num;
//pointeur sur la maillon suivant
    struct maillon *suiv;
} t_maillon;

typedef struct file {
    t_maillon *tete; //pointeur sur le premier maillon
    t_maillon *fin; //pointeur sur le dernier maillon
} t_file;


Graphe *CreerGraphe(int ordre, FILE *ifs);

Graphe *lire_graphe(char *nomFichier);

#endif //ECE_CITY_2_A_GRAPHE_H
