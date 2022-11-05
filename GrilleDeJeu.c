#include "GrilleDeJeu.h"

void AllouerTableau(char ***plateau) {
    *plateau = malloc(nbLignes * sizeof(char *));
    for (int i = 0; i < nbLignes; i++)
        *(*plateau + i) = malloc(nbColonnes * sizeof(char));

}

void creerTableau(char **plateau) {
    int i, j;

    for (i = 0; i < nbLignes; i++) {
        for (j = 0; j < nbColonnes; j++) {
            plateau[i][j] = '.';
        }
    }
}

void saisir_coordonnees(int *x, int *y, char *element) {
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

    do {
        continuer = 0;
        printf("element : \n");
        ret = scanf("%c", element);

        if (ret != 1)
            continuer = 1;

        while (ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    } while (continuer);

}

void placer_bloc(char **plateau, char element, int x, int y) {
    if (element == 'r' || element == 'R') {
        plateau[x - 1][y - 1] = -36;
    } else if (element == 'm' || element == 'M') {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                plateau[x - i - 1][y + j - 1] = 'M';
            }
        }
    } else if (element == 'c' || element == 'C') {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                plateau[x - i - 1][y + j - 1] = 'C';
            }
        }
    }
}

void verif_chevauchement(char **plateau, char element, int x, int y) {

    int verif = 0;

    int tailleX, tailleY = 0;

    switch (element) {
        case 'm' : {
            tailleX = 3;
            tailleY = 3;
            break;
        }
        case 'c' : {
            tailleX = 4;
            tailleY = 6;
            break;
        }
        case 'r' : {
            tailleX = 1;
            tailleY = 1;
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
        saisir_coordonnees(&x, &y, &element);
        verif_chevauchement(plateau, element, x, y);
    } else {
        placer_bloc(plateau, element, x, y);
    }
}

void valid_coordonnees(int x, int y, char element, char **plateau) {

    int verif = 0;

    while (verif != 1) {
        if (((element == 'm' || element == 'M') && (x < 3 || y > 43)) ||
            ((element == 'c' || element == 'C') && (x < 4 || y > 40))) {
            saisir_coordonnees(&x, &y, &element);
        } else {
            verif = 1;
            verif_chevauchement(plateau, element, x, y);
        }
    }
}

void afficherPlateau(char **plateau) {
    int i, j;
    printf("\n");
    printf("           5         10        15        20        25        30        35        40        45\n");
    for (i = 0; i < nbLignes; i++) {

        if (i + 1 < 10) {
            printf("%d  ", i + 1);
        } else {
            printf("%d ", i + 1);
        }

        for (j = 0; j < nbColonnes; j++) {
            printf("%c ", plateau[i][j]);
        }
        printf("\n");
    }
}

void free_plateau(char **plateau) {
    for (int i = 0; i < nbLignes; i++)
        free(plateau[i]);
    free(plateau);

}

void compteur() {     // A MODIFIER POUR LES CYCLES
    clock_t temps;
    srand(time(NULL));
    temps = clock();
    printf("%f", (double) temps / CLOCKS_PER_SEC);
}