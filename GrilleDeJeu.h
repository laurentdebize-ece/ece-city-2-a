#ifndef ECE_CITY_2_A_GRILLEDEJEU_H
#define ECE_CITY_2_A_GRILLEDEJEU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define nbLignes 35
#define nbColonnes 45
#define nbCases nbLignes*nbColonnes

void AllouerTableau(char ***plateau);

void creerTableau(char **plateau);

void saisir_coordonnees(int *x, int *y, char *element);

void placer_bloc(char **plateau, char element, int x, int y);

void verif_chevauchement(char **plateau, char element, int x, int y);

void valid_coordonnees(int x, int y, char element, char **plateau);

void afficherPlateau(char **plateau);

void free_plateau(char **plateau);

void compteur();

#endif //ECE_CITY_2_A_GRILLEDEJEU_H
