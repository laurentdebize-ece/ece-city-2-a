#ifndef LAST_VERSION_ECE_CITY_STRUCTURES_H
#define LAST_VERSION_ECE_CITY_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <limits.h>
#include <allegro5/allegro5.h>

#define nbLignes 35
#define nbColonnes 45

enum {
    ROUTE = 1, MAISON = 2, ELEC = 3, EAU = 4
};

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

/* Structure d'un arc*/
struct Arc {
    int sommet; // numero de sommet d'un arc adjacent au sommet initial
    int valeur;
    struct Arc *arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc *pArc;

/* Structure d'un sommet*/
struct Sommet {
    struct Arc *arc;
    int valeur;
    char couleur;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet *pSommet;

/* Alias d'un Graphe */
typedef struct Graphe {
    int orientation;
    int ordre;
    pSommet *pSommet;
} Graphe;


typedef struct DonneesJoueur {
    clock_t compteurTemps;
    int compteurMonnaie;
    int nombreDHabitants;
    int capaciteEau;
    int capaciteElectrique;
    int mode_jeux;
    int nb_sommet;
    int nb_maison;
    int nb_chateaueau;
    int nb_centraleelec;
} DonneesJoueur;

typedef struct paramclock {
    clock_t t1;
    clock_t t2;
    int majdon;
} paramclock;

typedef struct Construction {
    int choixBatiment;
    int cout;
    int x;
    int y;
    int nb_x;  //largeur construction
    int nb_y;  //hauteur construction
} Construction;

typedef struct Maisonconnect {
    int nummaison;
    int distance;
} Maisonconnect;

typedef struct Chateaueau {
    int numchateau;
    int x;
    int y;
    int capa; // capacite restante
    int nextmaison;
    Maisonconnect listeMaisonconnecteau[30];
} Chateaueau;

typedef struct Centraleelec {
    int numcentrale;
    int x;
    int y;
    int capa; // capacite restante
    int nextmaison;
    Maisonconnect listeMaisonconnectelec[30];
} Centraleelec;

typedef struct Maison {
    int nummaison;
    int type;   // Terrain, Cabane, Maison, Immeuble, Gratte_cielle
    int x;
    int y;
    int eau1; // num du chateau d'eau principal - valeur 99 si pas alimente
    int disteau1; // distance avec chateau d'eau principal
    int capaeau1use;// eau puiser dans chateau 1
    int eau2; // num du chateau d'eau secondaire - valeur 99 si pas alimente
    int disteau2; // distance avec chateau d'eau secondaire
    int capaeau2use;// eau puiser dans chateau 2
    int elec; // 1 si alimente ou 99 si pas alimente
    int nextmaison;
    int nbhabmax; // nombre d'habitant max si elec et eau ok
    int nbhab; // nombre d'habitant
} Maison;

typedef struct Habitat {
    char type;
    int nbhabitant;
} Habitat;

#endif //LAST_VERSION_ECE_CITY_STRUCTURES_H
