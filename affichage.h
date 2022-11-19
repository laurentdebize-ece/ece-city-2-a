#ifndef VERSION_ABOUTIE_ECE_CITY_AFFICHAGE_H
#define VERSION_ABOUTIE_ECE_CITY_AFFICHAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <limits.h>
#include <allegro5/allegro5.h>


#define nbLignes 35
#define nbColonnes 45
#define nbCases nbLignes*nbColonnes

enum {ROUTE=1, MAISON=2, ELEC=3, EAU=4};

typedef struct DonneesJoueur {
    int compteurTemps;
    int compteurMonnaie;
    int nombreDHabitants;
    int capaciteEau;
    int capaciteElectrique;
    int mode_jeux;
    int nb_sommet;
} DonneesJoueur;

typedef struct Construction {
    int choixBatiment;
    int cout;
    int revenu;
    int nombreDHabitant;
    int x;
    int y;
    bool route;
    bool sousGraphe;
} Construction;


void locate(int x,int y);

void AllouerTableau(char ***plateau);
void AllouerSommet(int ***sommet);
void InitialisationSommet(int **sommet);

void creerTableau(char **plateau);

void saisir_coordonnees(Construction* construction);
void check_adjacent(char **plateau,Construction *construction, DonneesJoueur *joueur, int **sommet);
void placer_bloc(char **plateau, Construction *construction, DonneesJoueur *joueur, int** sommet);
void verif_chevauchement(char** plateau, Construction *construction, DonneesJoueur *joueur, int** sommet);
void valid_coordonnees(char** plateau, Construction *construction, DonneesJoueur *joueur, int** sommet);
void afficherPlateau(char **plateau);
void free_plateau(char **plateau);

void compteur();

void lire_fichier_grille(FILE* fichier, char* save, char** plateau);
void save_grille(FILE* fichier, char* save, char** plateau);
void lire_DonneesJoueur(char* save, DonneesJoueur *joueur);
void save_DonneesJoueur(char* save, DonneesJoueur *joueur);

void afficherMenu();
void choixElement();
DonneesJoueur initialisationJoueur(DonneesJoueur *joueur);
void initialisationConstruction(Construction *construction);
int argentJoueur(DonneesJoueur *joueur, Construction *construction);

void route(char** plateau, int choix, DonneesJoueur *joueur, Construction *construction, int** sommet);
void terrainVague(char** plateau, DonneesJoueur *joueur, Construction *construction, int** sommet);
void chateauDeau(char** plateau, DonneesJoueur *joueur, Construction *construction, int** sommet);
void centraleElectrique(char** plateau, DonneesJoueur *joueur, Construction *construction, int** sommet);
void afficherElement(char** plateau, int choix, DonneesJoueur *joueur, Construction *construction, int** sommet);
void afficherRessource(DonneesJoueur *joueur);

#endif //VERSION_ABOUTIE_ECE_CITY_AFFICHAGE_H
