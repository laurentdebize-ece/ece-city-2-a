#ifndef ECE_CITY_2_A_GRILLEDEJEU_H
#define ECE_CITY_2_A_GRILLEDEJEU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

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

#define nbLignes 35
#define nbColonnes 45
#define nbCases nbLignes*nbColonnes

void AllouerTableau(char ***plateau);
void creerTableau(char **plateau);
void saisir_coordonnees(int *x, int *y);
void placer_bloc(char **plateau,int choix, int x, int y);
void verif_chevauchement(char** plateau, int choix, int x, int y);
void valid_coordonnees(int x, int y, int choix, char** plateau);
void afficherPlateau(char **plateau);
void free_plateau(char **plateau);
void compteur();
void lire_fichier_grille(FILE* fichier, char* save, char** plateau);
void save_grille(FILE* fichier, char* save, char** plateau);
void afficherMenu();

void choixElement();
DonneesJoueur initialisationJoueur(DonneesJoueur joueur);
void initialisationConstruction(Construction construction);
void route(char** plateau, int choix, int x, int y, DonneesJoueur joueur, Construction construction[nbCases], int* i);
void terrainVague(char** plateau, int choix, int x, int y, DonneesJoueur joueur, Construction construction[nbCases], int* i);
void chateauDeau(char** plateau, int choix, int x, int y, DonneesJoueur joueur, Construction construction[nbCases], int* i);
void centraleElectrique(char** plateau, int choix, int x, int y, DonneesJoueur joueur, Construction construction[nbCases], int* i);
void afficherElement(char** plateau, int choix, int x, int y, DonneesJoueur joueur, Construction construction[nbCases], int* i);

#endif //ECE_CITY_2_A_GRILLEDEJEU_H
