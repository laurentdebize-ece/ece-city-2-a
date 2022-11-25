#ifndef LAST_VERSION_ECE_CITY_GRAPHE_H
#define LAST_VERSION_ECE_CITY_GRAPHE_H

#include "structures.h"
#include "affichage.h"

pSommet *CreerArete(pSommet *sommet, int s1, int s2);

Graphe *CreerGraphe(int ordre);

Graphe *charge_graphe(DonneesJoueur *joueur, int **sommet);

Graphe *recharge_graphe(DonneesJoueur *joueur, int **sommet);

void enfiler(t_file *f, int num);

int defiler(t_file *f);

int BFS(Graphe *graphe, int *preds, int s0);

void checkconnexioneau(int *preds, DonneesJoueur *joueur, int s0, int s1, int **sommet, Graphe *g);

void checkconnexionmaisonelec(int *preds, DonneesJoueur *joueur, int s0, int **sommet, Maison listeMaison[], int numelec, Centraleelec listeCentraleelec[]);

void checkconnexionmaison(int *preds, DonneesJoueur *joueur, int s0, int **sommet, Maison listeMaison[], int numchateau, Chateaueau listeChateau[]);

void check_maison(int s0, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], int nb_arrete, int numchateau, Chateaueau listeChateau[]);

void check_maison_elec(int s0, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], int nb_arrete, int numelec, Centraleelec listeCentraleelec[]);

void checkelecmaison(int *preds, char **plateau, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], Centraleelec listeCentraleelec[]);

void checkchateaumaison(int *preds, char **plateau, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], Chateaueau listeChateau[]);

#endif //LAST_VERSION_ECE_CITY_GRAPHE_H
