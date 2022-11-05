#ifndef ECE_CITY_2_A_BOITEAOUTILS_H
#define ECE_CITY_2_A_BOITEAOUTILS_H

#include <stdio.h>
#include <windows.h>
#include "GrilleDeJeu.h"

typedef struct DonneesJoueur {
    int compteurTemps;
    int compteurMonnaie;
    int nombreDHabitants;
    int capaciteEau;
    int capaciteElectrique;
} DonneesJoueur;

typedef struct Construction {
    int batiment;
    int cout;
    int revenu;
    int nombreDHabitant;
} Construction;

void color(int couleurDuTexte, int couleurDeFond);

DonneesJoueur initialisationJoueur(DonneesJoueur joueur);

void initialisationConstruction(Construction construction);

void saisir_coordonnees_boite(int *x, int *y);

void placer_bloc_boite(char **plateau, int choix, int x, int y);

void verif_chevauchement_boite(char **plateau, int choix, int x, int y);

void valid_coordonnees_boite(int x, int y, int choix, char **plateau);

int choixBoite();

void afficherBoite(DonneesJoueur joueur, Construction construction[nbCases], int *i, char **plateau);

void route(DonneesJoueur joueur, Construction construction[nbCases], int *i, int objetAPlacer, char **plateau);

void chateauDeau(DonneesJoueur joueur, Construction construction[nbCases], int *i, int objetAPlacer, char **plateau);

void centraleElectrique(DonneesJoueur joueur, Construction construction[nbCases], int *i, int objetAPlacer, char **plateau);

void terrainVague(DonneesJoueur joueur, Construction construction[nbCases], int *i, int objetAPlacer, char **plateau);

#endif //ECE_CITY_2_A_BOITEAOUTILS_H
