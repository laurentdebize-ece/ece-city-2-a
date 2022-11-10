#include "BoiteAOutils.h"

#include "BoiteAOutils.h"

void color(int couleurDuTexte, int couleurDeFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

DonneesJoueur initialisationJoueur2(DonneesJoueur joueur) {
    joueur.compteurMonnaie = 500000;
    return joueur;
}

///PROBLEME DANS LES INITIALISATIONS DE CONSTRUCTION MAIS NE GÊNE PAS POUR LE MOMENT
//Il faudra sûrement faire un tableau de construction, mais je ne sais pas encore
void initialisationConstruction2(Construction construction) {
    if (construction.batiment == 1) { // Château d'eau
        construction.cout = 100000;
        construction.revenu = 0;
        construction.nombreDHabitant = 0;
    }
    if (construction.batiment == 2) { // Centrale électrique
        construction.cout = 100000;
        construction.revenu = 0;
        construction.nombreDHabitant = 0;
    }
    if (construction.batiment == 3) { // Terrain Vague ou Ruine
        construction.cout = 1000;
        construction.revenu = 0;
        construction.nombreDHabitant = 0;
    }
    if (construction.batiment == 4) { // Cabane
        construction.cout = 0;
        construction.revenu = 100;
        construction.nombreDHabitant = 10;
    }
    if (construction.batiment == 5) { // Maison
        construction.cout = 0;
        construction.revenu = 500;
        construction.nombreDHabitant = 50;
    }
    if (construction.batiment == 6) { // Immeuble
        construction.cout = 0;
        construction.revenu = 1000;
        construction.nombreDHabitant = 100;
    }
    if (construction.batiment == 7) { // Gratte-ciel
        construction.cout = 0;
        construction.revenu = 10000;
        construction.nombreDHabitant = 1000;
    }
    if (construction.batiment == 8) { // Route
        construction.cout = 10;
        construction.revenu = 0;
        construction.nombreDHabitant = 0;
    }
}

void saisir_coordonnees_boite(int *x, int *y) {
    color(15, 0);
    printf("Saisissez des coordonnees :\n");
    int ret, continuer;
    do {
        continuer = 0;
        printf("x : \n");
        ret = scanf("%d", x);

        if (ret != 1 || *x <= 0 || *x > 35)
            continuer = 1;

        while (ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    } while (continuer);

    do {
        continuer = 0;
        printf("y : \n");
        ret = scanf("%d", y);
        //*y = modifier

        if (ret != 1 || *y <= 0 || *y > 45)
            continuer = 1;

        while (ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    } while (continuer);
}

void placer_bloc_boite(char **plateau, int choix, int x, int y) {
    if (choix == 1) {
        plateau[x - 1][y - 1] = -36;
    } else if (choix == 4) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                plateau[x - i - 1][y + j - 1] = 'M'; // Il faudra différencier terrain vague, cabane, ...
            }
        }
    } else if (choix == 2) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                plateau[x - i - 1][y + j - 1] = 'C'; // C pour Chateau d'eau
            }
        }
    } else if (choix == 3) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                plateau[x - i - 1][y + j - 1] = 'U'; // U pour Centrale électrique
            }
        }
    }
}

void verif_chevauchement_boite(char **plateau, int choix, int x, int y) {

    int verif = 0;

    int tailleX, tailleY = 0;

    switch (choix) {
        case 1 : {
            tailleX = 1;
            tailleY = 1;
            break;
        }
        case 4 : {
            tailleX = 3;
            tailleY = 3;
            break;
        }
        case 2 | 3 : {
            tailleX = 4;
            tailleY = 6;
            break;
        }
    }
    for (int i = 0; i < tailleX; i++) {
        for (int j = 0; j < tailleY; j++) {
            if (plateau[x - i - 1][y + j - 1] != '.') {
                verif = 1;
            }
        }
    }
    if (verif == 1) {
        saisir_coordonnees_boite(&x, &y);
        verif_chevauchement_boite(plateau, choix, x, y);
    } else {
        placer_bloc_boite(plateau, choix, x, y);
    }
}

void valid_coordonnees_boite(int x, int y, int choix, char **plateau) {

    int verif = 0;

    while (verif != 1) {
        if ((choix == 4) && (x < 3 || y > 43)) {
            saisir_coordonnees_boite(&x, &y);
        } else if ((choix == 2 || choix == 3) && (x < 4 || y > 40)) {
            saisir_coordonnees_boite(&x, &y);
        } else {
            verif = 1;
            verif_chevauchement_boite(plateau, choix, x, y);
        }
    }
}

int choixboite() {
    int objetAPlacer;
    do {
        color(0, 5);
        printf("BOITE A OUTILS\n\r");
        color(5, 0);
        printf("(0) : acces niveau 0\n\r");
        printf("(-1) : acces niveau -1\n\r");
        printf("(-2) : acces niveau 0\n\r");
        printf("(1) : Placer route\n\r");
        printf("(2) : Placer chateau d'eau\n\r");
        printf("(3) : Placer centrale electrique\n\r");
        printf("(4) : Placer terrain vague\n\r");
        printf("Vous voulez :\n\r");
        scanf("%d", &objetAPlacer);
        if (!(objetAPlacer >= -2 && objetAPlacer <= 4)) {
            printf("Desole, vous n'avez pas plus de possibilites. Veuillez saisir un numero valide s'il-vous-plait.\n\r");
        }
    } while (!(objetAPlacer >= -2 && objetAPlacer <= 4));
    return objetAPlacer;
}

void afficherBoite(DonneesJoueur joueur, Construction construction[nbCases], int *i, char **plateau) {
    switch (choixboite()) {
        case 1 : {
            route2(joueur, construction, i, 1, plateau);
            afficherPlateau(plateau);
            afficherBoite(joueur, construction, i, plateau);
            break;
        }
        case 2 : {
            chateauDeau2(joueur, construction, i, 2, plateau);
            afficherPlateau(plateau);
            afficherBoite(joueur, construction, i, plateau);
            break;
        }
        case 3 : {
            centraleElectrique2(joueur, construction, i, 3, plateau);
            afficherPlateau(plateau);
            afficherBoite(joueur, construction, i, plateau);
            break;
        }
        case 4 : {
            terrainVague2(joueur, construction, i, 4, plateau);
            afficherPlateau(plateau);
            afficherBoite(joueur, construction, i, plateau);
            break;
        }
    }
}

//Faire une fonction d'affichage qui renseigne sur les prix de chaque construction

void route2(DonneesJoueur joueur, Construction construction[nbCases], int *i, int objetAPlacer, char **plateau) {
    construction[*i].batiment = 8;
    int x = 0, y = 0, choix;
    choix = 1;
    do {
        if (joueur.compteurMonnaie >= construction[*i].cout) {
            saisir_coordonnees_boite(&x, &y);
            valid_coordonnees_boite(x, y, objetAPlacer, plateau);
            afficherPlateau(plateau);
            printf("Souhaitez-vous placer une autre route ?\n\r");
            printf("(1) Oui      (2) Non\n\r");
            scanf("%d", &choix);
        } else {
            printf("Désolé ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
        }
    } while (choix == 1);
}

void chateauDeau2(DonneesJoueur joueur, Construction construction[nbCases], int *i, int objetAPlacer, char **plateau) {
    construction[*i].batiment = 1;
    int x = 0, y = 0, choix;
    choix = 1;
    do {
        if (joueur.compteurMonnaie >= construction[*i].cout) {
            saisir_coordonnees_boite(&x, &y);
            valid_coordonnees_boite(x, y, objetAPlacer, plateau);
            afficherPlateau(plateau);
            joueur.compteurMonnaie = joueur.compteurMonnaie - construction[*i].cout;
            printf("Il vous reste %d ECEflouz. Souhaitez-vous placer un autre chateau d'eau ?\n\r",
                   joueur.compteurMonnaie);
            printf("(1) Oui      (2) Non\n\r");
            scanf("%d", &choix);
        } else {
            printf("Désolé ! Vous n'avez pas assez d'ECEflouz pour construire un chateau d'eau !\n\r");
        }
    } while (choix == 1);
}

void centraleElectrique2(DonneesJoueur joueur, Construction construction[nbCases], int *i, int objetAPlacer, char **plateau) {
    construction[*i].batiment = 2;
    int x = 0, y = 0, choix;
    choix = 1;
    do {
        if (joueur.compteurMonnaie >= construction[*i].cout) {
            saisir_coordonnees_boite(&x, &y);
            valid_coordonnees_boite(x, y, objetAPlacer, plateau);
            afficherPlateau(plateau);
            joueur.compteurMonnaie = joueur.compteurMonnaie - construction[*i].cout;
            printf("Il vous reste %d ECEflouz. Souhaitez-vous placer une autre centrale électrique ?\n\r",
                   joueur.compteurMonnaie);
            printf("(1) Oui      (2) Non\n\r");
            scanf("%d", &choix);
        } else {
            printf("Désolé ! Vous n'avez pas assez d'ECEflouz pour construire une centrale électrique !\n\r");
        }
    } while (choix == 1);
}

void terrainVague2(DonneesJoueur joueur, Construction construction[nbCases], int *i, int objetAPlacer, char **plateau) {
    construction[*i].batiment = 3;
    int x = 0, y = 0, choix;
    choix = 1;
    do {
        if (joueur.compteurMonnaie >= construction[*i].cout) {
            saisir_coordonnees_boite(&x, &y);
            valid_coordonnees_boite(x, y, objetAPlacer, plateau);
            afficherPlateau(plateau);
            joueur.compteurMonnaie = joueur.compteurMonnaie - construction[*i].cout;
            printf("Il vous reste %d ECEflouz. Souhaitez-vous placer un autre terrain vague ?\n\r",
                   joueur.compteurMonnaie);
            printf("(1) Oui      (2) Non\n\r");
            scanf("%d", &choix);
        } else {
            printf("Désolé ! Vous n'avez pas assez d'ECEflouz pour construire une terrain vague !\n\r");
        }
    } while (choix == 1);
}
