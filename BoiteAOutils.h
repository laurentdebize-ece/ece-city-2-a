#ifndef ECE_CITY_2_A_BOITEAOUTILS_H
#define ECE_CITY_2_A_BOITEAOUTILS_H

#include <stdio.h>
#include <windows.h>
#include "GrilleDeJeu.h"

typedef struct DonneesJoueur2 {
    int compteurTemps;
    int compteurMonnaie;
    int nombreDHabitants;
    int capaciteEau;
    int capaciteElectrique;
} DonneesJoueur2;

typedef struct Construction2 {
    int batiment;
    int cout;
    int revenu;
    int nombreDHabitant;
} Construction2;

void color(int couleurDuTexte, int couleurDeFond);

DonneesJoueur initialisationJoueur2(DonneesJoueur joueur);

void initialisationConstruction2(Construction construction);

void saisir_coordonnees_boite(int *x, int *y);

void placer_bloc_boite(char **plateau, int choix, int x, int y);

void verif_chevauchement_boite(char **plateau, int choix, int x, int y);

void valid_coordonnees_boite(int x, int y, int choix, char **plateau);

int choixBoite();

void afficherBoite(DonneesJoueur joueur, Construction construction[nbCases], int *i, char **plateau);

void route2(DonneesJoueur joueur, Construction construction[nbCases], int *i, int objetAPlacer, char **plateau);

void chateauDeau2(DonneesJoueur joueur, Construction construction[nbCases], int *i, int objetAPlacer, char **plateau);

void centraleElectrique2(DonneesJoueur joueur, Construction construction[nbCases], int *i, int objetAPlacer, char **plateau);

void terrainVague2(DonneesJoueur joueur, Construction construction[nbCases], int *i, int objetAPlacer, char **plateau);

#endif //ECE_CITY_2_A_BOITEAOUTILS_H
