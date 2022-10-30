//
// Created by cleme on 30/10/2022.
//

#ifndef ECE_CITY_2_A_GRAPHE_H
#define ECE_CITY_2_A_GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Arc
{
    char lettre;
    int sommet;// numero de sommet d'un arc adjacent au sommet initial
    int valeur;
    int distance;
    int couleur;
    struct Arc* arc_suivant;
};
typedef struct Arc* pArc;

struct Sommet
{
    struct Arc* arc;
    char* lettre;
    int valeur;
    int distance;
    char couleur;
    int connexite;

};
typedef struct Sommet* pSommet;

typedef struct Graphe
{
    int taille;
    int orientation;
    int ordre;
    pSommet* pSommet;
} Graphe;


Graphe* CreerGraphe(int ordre,FILE * ifs);
Graphe * lire_graphe(char * nomFichier);

#endif //ECE_CITY_2_A_GRAPHE_H
