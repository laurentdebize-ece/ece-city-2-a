#ifndef ECE_CITY_2_A_GRILLEDEJEU_H
#define ECE_CITY_2_A_GRILLEDEJEU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

typedef struct DonneesJoueur {
    int compteurTemps;
    int compteurMonnaie;
    int nombreDHabitants;
    int capaciteEau;
    int capaciteElectrique;
} DonneesJoueur;

typedef struct Construction {
    int choixBatiment;
    int cout;
    int revenu;
    int nombreDHabitant;
} Construction;

#define nbLignes 35
#define nbColonnes 45
#define nbCases nbLignes*nbColonnes

void locate(int x,int y);
void AllouerTableau(char ***plateau);
void creerTableau(char **plateau);
void saisir_coordonnees(int *x, int *y);
void placer_bloc(char **plateau, int x, int y, Construction *construction, DonneesJoueur *joueur);
void verif_chevauchement(char** plateau, int x, int y, Construction *construction, DonneesJoueur *joueur);
void valid_coordonnees(int x, int y, char** plateau, Construction *construction, DonneesJoueur *joueur);
void afficherPlateau(char **plateau);
void free_plateau(char **plateau);
void compteur();
void lire_fichier_grille(FILE* fichier, char* save, char** plateau);
void save_grille(FILE* fichier, char* save, char** plateau);

void afficherMenu();
void choixElement();
DonneesJoueur initialisationJoueur(DonneesJoueur *joueur);
void initialisationConstruction(Construction *construction);
int argentJoueur(DonneesJoueur *joueur, Construction *construction);

void route(char** plateau, int choix, int x, int y, DonneesJoueur *joueur, Construction *construction);
void terrainVague(char** plateau, int x, int y, DonneesJoueur *joueur, Construction *construction);
void chateauDeau(char** plateau, int x, int y, DonneesJoueur *joueur, Construction *construction);
void centraleElectrique(char** plateau, int x, int y, DonneesJoueur *joueur, Construction *construction);
void afficherElement(char** plateau, int choix, int x, int y, DonneesJoueur *joueur, Construction *construction);
void afficherRessource(DonneesJoueur *joueur);

#endif //ECE_CITY_2_A_GRILLEDEJEU_H
