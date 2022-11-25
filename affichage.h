#ifndef LAST_VERSION_ECE_CITY_AFFICHAGE_H
#define LAST_VERSION_ECE_CITY_AFFICHAGE_H

#include "structures.h"
#include "graphe.h"

void color(int couleurDuTexte, int couleurDeFond);

void locate(int x, int y);

void AllouerTableau(char ***plateau);

void AllouerSommet(int ***sommet);

void InitialisationSommet(int **sommet);

void Initialisationmaison(Maison listeMaison[]);

void initialisationChateaueau(Chateaueau listeChateau[]);

void initialisationCentraleelec(Centraleelec listeCentraleelec[]);

void initialisationConstruction(Construction *construction);

void creerTableau(char **plateau);

void saisir_coordonnees(Construction *construction);

void saisir_coordonnees(Construction *construction);

void checkAjoutSommet(char **plateau, Construction *construction, DonneesJoueur *joueur, int **sommet);

void check_adjacent_sommet(int num_sommet, DonneesJoueur *joueur, int **sommet);

void check_adjacent(char **plateau, Construction *construction, DonneesJoueur *joueur, int **sommet);

void placer_bloc(int *preds, char **plateau, Construction *construction, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

void verif_chevauchement(int *preds, char **plateau, Construction *construction, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

void valid_coordonnees(int *preds, char **plateau, Construction *construction, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

void afficherPlateau(char **plateau);

void free_plateau(char **plateau);

void lire_fichier_grille(FILE *fichier, char *save, char **plateau);

void save_grille(FILE *fichier, char *save, char **plateau);

void lire_DonneesJoueur(char *save, DonneesJoueur *joueur);

void save_DonneesJoueur(char *save, DonneesJoueur *joueur);

void afficherMenu();

void afficherRessource(DonneesJoueur *joueur, Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

void choixElement();

DonneesJoueur initialisationJoueur(DonneesJoueur *joueur);

paramclock initialisationmajclock(paramclock *majclock);

int argentJoueur(DonneesJoueur *joueur, Construction *construction);

void route(int *preds, char **plateau, int choix, DonneesJoueur *joueur, Construction *construction, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

void terrainVague(int *preds, char **plateau, DonneesJoueur *joueur, Construction *construction, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

void chateauDeau(int *preds, char **plateau, DonneesJoueur *joueur, Construction *construction, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

void centraleElectrique(int *preds, char **plateau, DonneesJoueur *joueur, Construction *construction, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

void afficherElement(int *preds, char **plateau, int choix, DonneesJoueur *joueur, Construction *construction, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]);

int checksommet(DonneesJoueur *joueur, int x, int y, int **sommet);

void majdonnees(DonneesJoueur *joueur, char **plateau, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[], Habitat listeHabitat[]);

void ChargeHabitat(FILE *fichier, Habitat listeHabitat[]);

#endif //LAST_VERSION_ECE_CITY_AFFICHAGE_H
