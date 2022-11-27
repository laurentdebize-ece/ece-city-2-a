#ifndef LAST_VERSION_ECE_CITY_AFFICHAGE_H
#define LAST_VERSION_ECE_CITY_AFFICHAGE_H

#include "structures.h"
#include "graphe.h"

void locate(int x,int y);

void AllouerTableau(char ***plateau);

void AllouerSommet(int ***sommet);
void InitialisationSommet(int **sommet);

void Initialisationmaison(Maison listeMaison[]);


void initialisationChateaueau(Chateaueau listeChateau[]);


void initialisationCentraleelec(Centraleelec listeCentraleelec[]);

void initialisationConstruction(Construction *construction);


void creerTableau(char **plateau);

void saisir_coordonnees(Construction* construction);
void check_adjacent(char **plateau,Construction *construction, DonneesJoueur *joueur, int **sommet);
void placer_bloc(int* preds,char **plateau, Construction *construction, DonneesJoueur *joueur, int** sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

void verif_chevauchement(int* preds, char** plateau, Construction *construction, DonneesJoueur *joueur, int** sommet, Maison listeMaison[], Chateaueau listeChateau[],Centraleelec listeCentraleelec[]);

void valid_coordonnees(int* preds, char** plateau, Construction *construction, DonneesJoueur *joueur, int** sommet,Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

void afficherPlateau(char **plateau);
void free_plateau(char **plateau);

void save_grille(FILE* fichier, char* save, char** plateau);
void save_DonneesJoueur(char* save, DonneesJoueur *joueur);
void save_sommet(char* save, DonneesJoueur *joueur, int** sommet);
void save_listeChateau(char* save, DonneesJoueur *joueur,Chateaueau listeChateau[]);
void save_listeCentraleelec(char* save, DonneesJoueur *joueur,Centraleelec listeCentraleelec[]);
void save_listeMaison(char* save, DonneesJoueur *joueur,Maison listeMaison[]);

void lire_fichier_grille(FILE* fichier, char* save, char** plateau);
void lire_DonneesJoueur(char* save, DonneesJoueur *joueur);
void lire_sommet(char* save, DonneesJoueur *joueur, int** sommet);
void lire_listeChateau(char* save, DonneesJoueur *joueur,Chateaueau listeChateau[]);
void lire_listeCentraleelec(char* save, DonneesJoueur *joueur,Centraleelec listeCentraleelec[]);
void lire_listeMaison(char* save, DonneesJoueur *joueur,Maison listeMaison[]);



void afficherMenu();
void afficherRessource(DonneesJoueur *joueur, Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

void choixElement();
DonneesJoueur initialisationJoueur(DonneesJoueur *joueur);
paramclock initialisationmajclock(paramclock *majclock);

int argentJoueur(DonneesJoueur *joueur, Construction *construction);
void route(int* preds, char** plateau, int choix, DonneesJoueur *joueur, Construction *construction, int** sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

void terrainVague(int* preds,char** plateau, DonneesJoueur *joueur, Construction *construction, int** sommet, Maison listeMaison[], Chateaueau listeChateau[],Centraleelec listeCentraleelec[]);
void chateauDeau(int* preds,char** plateau, DonneesJoueur *joueur, Construction *construction, int** sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);
void centraleElectrique(int* preds,char** plateau, DonneesJoueur *joueur, Construction *construction, int** sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);
void afficherElement(int* preds,char** plateau, int choix, DonneesJoueur *joueur, Construction *construction, int** sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

int checksommet(DonneesJoueur *joueur, int x,int y, int** sommet);

void majdonnees(DonneesJoueur *joueur, char** plateau, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[],Habitat listeHabitat[]);
void ChargeHabitat(FILE* fichier,Habitat listeHabitat[]);
void lire_regle(FILE* fichier, char* save);
void majniveaueau(DonneesJoueur *joueur, char** niveaueau, int** sommet,  Maison listeMaison[], Chateaueau listeChateau[]);
void majniveauelec(DonneesJoueur *joueur, char** niveauelec, int** sommet,  Maison listeMaison[], Centraleelec listeCentraleelec[]);
void color(int couleurDuTexte, int couleurDeFond);
void checkmanqueeau(DonneesJoueur *joueur, Maison listeMaison[], Chateaueau listeChateau[]);
void checkmanqueelec(DonneesJoueur *joueur, Maison listeMaison[]);

#endif //LAST_VERSION_ECE_CITY_AFFICHAGE_H
