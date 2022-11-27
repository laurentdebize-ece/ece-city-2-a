#ifndef LAST_VERSION_ECE_CITY_GRAPHE_H
#define LAST_VERSION_ECE_CITY_GRAPHE_H

#include "structures.h"
#include "affichage.h"

Graphe *CreerGraphe(int ordre);

Graphe *charge_graphe(DonneesJoueur *joueur, int **sommet);

// Ajouter l'arete entre les sommets s1 et s2 du graphe
pSommet *CreerArete(pSommet *sommet, int s1, int s2);

void checkconnexionmaison(int *preds, DonneesJoueur *joueur, int s0, int **sommet, Maison listeMaison[], int numchateau, Chateaueau listeChateau[]);

void checkconnexionmaisonelec(int *preds, DonneesJoueur *joueur, int s0, int **sommet, Maison listeMaison[], int numelec, Centraleelec listeCentraleelec[]);

void check_maison(int s0, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], int nb_arrete, int numchateau, Chateaueau listeChateau[]);

void check_maison_elec(int s0, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], int nb_arrete, int numelec, Centraleelec listeCentraleelec[]);

void checkchateaumaison(int *preds, char **plateau, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], Chateaueau listeChateau[]);

void checkelecmaison(int *preds, char **plateau, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], Centraleelec listeCentraleelec[]);


#endif //LAST_VERSION_ECE_CITY_GRAPHE_H
