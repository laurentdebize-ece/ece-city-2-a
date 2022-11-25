#include "affichage.h"

void color(int couleurDuTexte, int couleurDeFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

DonneesJoueur initialisationJoueur(DonneesJoueur *joueur) {
    joueur->compteurTemps = 0;
    joueur->compteurMonnaie = 500000;
    joueur->nombreDHabitants = 0;
    joueur->capaciteEau = 0;
    joueur->capaciteElectrique = 0;
    joueur->nb_sommet = 0;
    joueur->mode_jeux = 0; // 0 = mode communiste; 1 = mode capitaliste
    joueur->nb_maison = 0;
    joueur->nb_chateaueau = 0;
    joueur->nb_centraleelec = 0;
    return *joueur;
}

paramclock initialisationmajclock(paramclock *majclock) {
    majclock->majdon = 0;
    return *majclock;
}

void initialisationConstruction(Construction *construction) {

    construction->cout = 0;

    if (construction->choixBatiment == ROUTE) {
        construction->cout = 10;
        construction->nb_x = 1;
        construction->nb_y = 1;
    } else if (construction->choixBatiment == MAISON) {
        construction->cout = 1000;
        construction->nb_x = 3;
        construction->nb_y = 3;
    } else if (construction->choixBatiment == ELEC || construction->choixBatiment == EAU) {
        construction->cout = 100000;
        construction->nb_x = 6;
        construction->nb_y = 4;
    }
}

void initialisationChateaueau(Chateaueau listeChateau[]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 30; j++) {
            listeChateau[i].numchateau = 0;
            listeChateau[i].x = 0;
            listeChateau[i].y = 0;
            listeChateau[i].capa = 0;
            listeChateau[i].nextmaison = 0;
            listeChateau[i].listeMaisonconnecteau[j].nummaison = 99;
            listeChateau[i].listeMaisonconnecteau[j].distance = 99;
        }
    }
}

void initialisationCentraleelec(Centraleelec listeCentraleelec[]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 30; j++) {
            listeCentraleelec[i].numcentrale = 0;
            listeCentraleelec[i].x = 0;
            listeCentraleelec[i].y = 0;
            listeCentraleelec[i].capa = 0;
            listeCentraleelec[i].nextmaison = 0;
            listeCentraleelec[i].listeMaisonconnectelec[j].nummaison = 99;
            listeCentraleelec[i].listeMaisonconnectelec[j].distance = 99;
        }
    }
}

void Initialisationmaison(Maison listeMaison[]) {
    int i;
    for (i = 0; i < 30; i++) {
        listeMaison[i].nummaison = 0;
        listeMaison[i].type = 'X';
        listeMaison[i].x = 0;
        listeMaison[i].y = 0;
        listeMaison[i].eau1 = 99;
        listeMaison[i].disteau1 = 0;
        listeMaison[i].capaeau1use = 0;
        listeMaison[i].eau2 = 99;
        listeMaison[i].disteau2 = 0;
        listeMaison[i].capaeau2use = 0;
        listeMaison[i].elec = 99; //99 si non alimente ou num centrale sinon
        //listeMaison[i].elec = 1; //mis a 1 pour debuging
        listeMaison[i].nbhabmax = 0;
        listeMaison[i].nbhab = 0;
    }
}

void ChargeHabitat(FILE *fichier, Habitat listeHabitat[]) {
// Charge la liste de type d'habitation depuis le fichier listehabitat.txt

    int i = 0;
    char type[2];
    int nbhabitant;
    fichier = fopen("listehabitat.txt", "r");
    if (fichier != NULL) {
        for (i = 0; i < 5; i++) {
            fscanf(fichier, "Type : %s nbhab : %d\n", &type, &nbhabitant);
            listeHabitat[i].type = type[0];
            listeHabitat[i].nbhabitant = nbhabitant;
        }
        fclose(fichier);
    }
}

int argentJoueur(DonneesJoueur *joueur, Construction *construction) {
    initialisationConstruction(construction);
    return joueur->compteurMonnaie = joueur->compteurMonnaie - construction->cout;
}

void locate(int x, int y) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD C;
    C.X = x;
    C.Y = y;
    SetConsoleCursorPosition(H, C);
}

void AllouerTableau(char ***plateau) {
    *plateau = malloc(nbLignes * sizeof(char *));
    for (int i = 0; i < nbLignes; i++)
        *(*plateau + i) = malloc(nbColonnes * sizeof(char));
}

void AllouerSommet(int ***sommet) {
    *sommet = malloc(1225 * sizeof(int *));//premier test avec 5 sommet
    for (int i = 0; i < 1225; i++)
        *(*sommet + i) = malloc(7 * sizeof(int));
}

void InitialisationSommet(int **sommet) {
    int i, j;
    for (i = 0; i < 1225; i++) {
        for (j = 0; j < 7; j++) {
            sommet[i][j] = 0;
        }
    }
}

void creerTableau(char **plateau) {
    int i, j;

    for (i = 0; i < nbLignes; i++) {
        for (j = 0; j < nbColonnes; j++) {
            plateau[i][j] = '.';
        }
    }
}

void saisir_coordonnees(Construction *construction) {
    locate(100, 18);
    color(8,0);
    printf("Saisissez des coordonnees :\n");
    int ret, continuer;
    do {
        continuer = 0;
        locate(100, 19);
        printf("x : \n");
        locate(100, 20);
        ret = scanf("%d", &construction->x);

        if (ret != 1 || construction->x <= 0 || construction->x > 35)
            continuer = 1;

        while (ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    } while (continuer);

    do {
        continuer = 0;
        locate(100, 21);
        printf("y : \n");
        locate(100, 22);
        ret = scanf("%d", &construction->y);

        if (ret != 1 || construction->y <= 0 || construction->y > 45)
            continuer = 1;

        while (ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    } while (continuer);
    color(15,0);
}

void check_adjacent(char **plateau, Construction *construction, DonneesJoueur *joueur, int **sommet) {

    // recherche adjacent horizontaux
    for (int boucle = 0; boucle < joueur->nb_sommet; boucle++) {
        if (construction->x == sommet[boucle][0]) {

            // recherche adjacent gauche
            if (construction->y - 1 == sommet[boucle][1]) {
                for (int boucleadj = 3; boucleadj < 6; boucleadj++) {
                    if (sommet[boucle][boucleadj] == 0) {

                        sommet[boucle][boucleadj] = joueur->nb_sommet;
                        break;
                    }
                }

            }
            // recherche adjacent droite
            if (construction->y + 1 == sommet[boucle][1]) {
                for (int boucleadj = 3; boucleadj < 6; boucleadj++) {
                    if (sommet[boucle][boucleadj] == 0) {

                        sommet[boucle][boucleadj] = joueur->nb_sommet;
                        break;
                    }
                }

            }
        }
    }

    // recherche adjacent verticaux

    for (int boucle = 0; boucle < joueur->nb_sommet; boucle++) {
        if (construction->y == sommet[boucle][1]) {
            // recherche adjacent inferieur

            if (construction->x - 1 == sommet[boucle][0]) {
                for (int boucleadj = 3; boucleadj < 6; boucleadj++) {
                    if (sommet[boucle][boucleadj] == 0) {

                        sommet[boucle][boucleadj] = joueur->nb_sommet;
                        break;
                    }
                }

            }
            // recherche adjacent superieur

            if (construction->x + 1 == sommet[boucle][0]) {
                for (int boucleadj = 3; boucleadj < 6; boucleadj++) {
                    if (sommet[boucle][boucleadj] == 0) {

                        sommet[boucle][boucleadj] = joueur->nb_sommet;
                        break;
                    }
                }

            }
        }
    }
}

void placer_bloc(int *preds, char **plateau, Construction *construction, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
    if (construction->choixBatiment == ROUTE) {
        plateau[construction->x - 1][construction->y - 1] = -36;
        argentJoueur(joueur, construction);
        sommet[joueur->nb_sommet][0] = construction->x;
        sommet[joueur->nb_sommet][1] = construction->y;
        sommet[joueur->nb_sommet][2] = joueur->nb_sommet;
        check_adjacent(plateau, construction, joueur, sommet);
        joueur->nb_sommet = joueur->nb_sommet + 1;
    } else if (construction->choixBatiment == MAISON) {
        for (int i = 0; i < construction->nb_x; i++) {
            for (int j = 0; j < construction->nb_y; j++) {
                plateau[construction->x - i - 1][construction->y + j - 1] = 'T';
            }
        }
        argentJoueur(joueur, construction);
        listeMaison[joueur->nb_maison].nummaison = joueur->nb_maison;
        listeMaison[joueur->nb_maison].type = 'T'; //Terrain Vague
        listeMaison[joueur->nb_maison].x = construction->x;
        listeMaison[joueur->nb_maison].y = construction->y;
        listeMaison[joueur->nb_maison].eau1 = 99;
        listeMaison[joueur->nb_maison].disteau1 = 0;
        listeMaison[joueur->nb_maison].capaeau1use = 0;
        listeMaison[joueur->nb_maison].eau2 = 99;
        listeMaison[joueur->nb_maison].disteau2 = 0;
        listeMaison[joueur->nb_maison].capaeau2use = 0;
        listeMaison[joueur->nb_maison].elec = 99;
        listeMaison[joueur->nb_maison].nbhabmax = 0;
        listeMaison[joueur->nb_maison].nbhab = 0;

        joueur->nb_maison = joueur->nb_maison + 1;
    } else if (construction->choixBatiment == ELEC) {
        for (int i = 0; i < construction->nb_x; i++) {
            for (int j = 0; j < construction->nb_y; j++) {
                plateau[construction->x - i - 1][construction->y + j - 1] = 'U';
            }
        }
        argentJoueur(joueur, construction);
        listeCentraleelec[joueur->nb_centraleelec].numcentrale = joueur->nb_centraleelec;
        listeCentraleelec[joueur->nb_centraleelec].x = construction->x;
        listeCentraleelec[joueur->nb_centraleelec].y = construction->y;
        listeCentraleelec[joueur->nb_centraleelec].capa = 5000;
        joueur->nb_centraleelec = joueur->nb_centraleelec + 1;
        joueur->capaciteElectrique = joueur->capaciteElectrique + 5000;
    } else if (construction->choixBatiment == EAU) {
        for (int i = 0; i < construction->nb_x; i++) {
            for (int j = 0; j < construction->nb_y; j++) {
                plateau[construction->x - i - 1][construction->y + j - 1] = 'E';
            }
        }
        argentJoueur(joueur, construction);
        listeChateau[joueur->nb_chateaueau].numchateau = joueur->nb_chateaueau;
        listeChateau[joueur->nb_chateaueau].x = construction->x;
        listeChateau[joueur->nb_chateaueau].y = construction->y;
        listeChateau[joueur->nb_chateaueau].capa = 5000;
        joueur->nb_chateaueau = joueur->nb_chateaueau + 1;
    }
    checkelecmaison(preds, plateau, joueur, sommet, listeMaison, listeCentraleelec);
    checkchateaumaison(preds, plateau, joueur, sommet, listeMaison, listeChateau);
}

void verif_chevauchement(int *preds, char **plateau, Construction *construction, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {

    int verif = 0;

    initialisationConstruction(construction);

    for (int i = 0; i < construction->nb_x; i++) {
        for (int j = 0; j < construction->nb_y; j++) {
            if (plateau[construction->x - i - 1][construction->y + j - 1] != '.') {
                verif = 1;
            }
        }
    }
    if (verif == 1) {
        saisir_coordonnees(construction);
        verif_chevauchement(preds, plateau, construction, joueur, sommet, listeMaison, listeChateau, listeCentraleelec);
    } else {
        placer_bloc(preds, plateau, construction, joueur, sommet, listeMaison, listeChateau, listeCentraleelec);
    }
}

void valid_coordonnees(int *preds, char **plateau, Construction *construction, DonneesJoueur *joueur, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
    initialisationConstruction(construction);
    int verif = 0;

    while (verif != 1) {
        if (((construction->choixBatiment == 2 || construction->choixBatiment == 3 ||
              construction->choixBatiment == 4) &&
             (construction->x < construction->nb_x || construction->y > 46 - construction->nb_y))) {
            saisir_coordonnees(construction);
        } else {
            verif = 1;
            verif_chevauchement(preds, plateau, construction, joueur, sommet, listeMaison, listeChateau,
                                listeCentraleelec);
        }
    }
}

void afficherPlateau(char **plateau) {
    int i, j;
    printf("\n");
    system("cls");
    locate(1, 1);
    printf("          5         10        15        20        25        30        35        40        45\n");
    for (i = 0; i < nbLignes; i++) {
        if (i + 1 < 10) {
            printf("%d  ", i + 1);
        } else {
            printf("%d ", i + 1);
        }
        for (j = 0; j < nbColonnes; j++) {
            if(plateau[i][j] == 'U') {
                color(6,0);
            }
            if(plateau[i][j] == 'E') {
                color(9,0);
            }
            if(plateau[i][j] == 'T') {
                color(7,0);
            }
            if(plateau[i][j] == 'C') {
                color(8,0);
            }
            if(plateau[i][j] == 'M') {
                color(10,0);
            }
            if(plateau[i][j] == 'I') {
                color(11,0);
            }
            if(plateau[i][j] == 'G') {
                color(4,0);
            }
            printf("%c ", plateau[i][j]);
            color(15,0);
        }
        printf("\n");
    }
}

void free_plateau(char **plateau) {
    for (int i = 0; i < nbLignes; i++)
        free(plateau[i]);
    free(plateau);
}

void lire_fichier_grille(FILE *fichier, char *save, char **plateau) {

    int i = 0, j = 0;
    char element;

    fichier = fopen(save, "r");

    if (fichier != NULL) {
        // Boucle de lecture des caracteres un a un
        do {

            if (j < (nbColonnes)) {
                element = fgetc(fichier); // On lit le caractere vide entre chaque valeur
                element = fgetc(fichier); // On lit le caractere
                plateau[i][j] = element;
                j++;
            } else {
                element = fgetc(fichier); // On lit le caractere vide apres le saut de ligne
                j = 0;
                i++;
            }
        } while (element != EOF); // On continue tant que fgetc n'a pas retourne EOF (fin de fichier)

        fclose(fichier);

    }
}

void save_grille(FILE *fichier, char *save, char **plateau) {

    int i = 0, j = 0, fin = 0;
    char element;
    fichier = fopen(save, "w");
    if (fichier != NULL) {
        do {
            if (j < (nbColonnes)) {
                element = plateau[i][j];
                fputc(' ', fichier);
                fputc(element, fichier);
                j++;
            } else {
                if (i < (nbLignes - 1)) {
                    fprintf(fichier, "\n");
                    j = 0;
                    i++;
                } else {
                    fin = 1;
                }
            }
        } while (fin != 1);
        fclose(fichier);
    }
}

void lire_DonneesJoueur(char *save, DonneesJoueur *joueur) {
    FILE *fichier = NULL;
    fichier = fopen(save, "r");

    if (fichier != NULL) {
        fscanf(fichier, "%d %d %d %d %d %d %d", &joueur->compteurTemps, &joueur->compteurMonnaie, &joueur->mode_jeux,
               &joueur->nombreDHabitants, &joueur->capaciteEau, &joueur->capaciteElectrique, &joueur->nb_sommet);
    }
    fclose(fichier);
}

void save_DonneesJoueur(char *save, DonneesJoueur *joueur) {
    FILE *fichier = NULL;
    fichier = fopen(save, "w");

    if (fichier != NULL) {

        fprintf(fichier, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n", joueur->compteurTemps, joueur->compteurMonnaie,
                joueur->mode_jeux, joueur->nombreDHabitants, joueur->capaciteEau, joueur->capaciteElectrique,
                joueur->nb_sommet);

        fclose(fichier);
    }
}

void afficherMenu() {
    int i, j;
    locate(100, 2);
    color(0,13);
    printf("Boite a outils : \n");
    color(13,0);
    locate(100, 3);
    printf("- (-1) : Affichage niveau -1   ");
    locate(100, 4);
    printf("- (-2) : Affichage niveau -2   ");
    locate(100, 5);
    printf("- 1 : restaurer une sauvegarde \n");
    locate(100, 6);
    printf("- 2 : sauvegarder la partie en cours \n");
    locate(100, 7);
    printf("- 3 : ajouter un element \n");
    locate(100, 8);
    printf("- 4 : Sortir du jeux \n");
    locate(100, 9);
    color(15,0);
}

void choixElement() {
    locate(100, 11);
    printf("Quelle element voulez-vous placer ? \n");
    locate(100, 12);
    printf("- 1 : route \n");
    locate(100, 13);
    printf("- 2 : terrain vide \n");
    locate(100, 14);
    printf("- 3 : centrale electrique \n");
    locate(100, 15);
    printf("- 4 : chateau d'eau \n");
    locate(100, 16);
}

void route(int *preds, char **plateau, int choix, DonneesJoueur *joueur, Construction *construction, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
    choix = 1;
    do {
        if (joueur->compteurMonnaie >= construction->cout) {
            locate(100, 20);
            printf("                                            ");
            locate(100, 21);
            printf("                                            ");
            locate(100, 22);
            printf("                                            ");
            locate(100, 23);
            printf("                                            ");
            locate(100, 24);
            printf("                                            ");
            locate(100, 25);
            printf("                                            ");
            saisir_coordonnees(construction);
            valid_coordonnees(preds, plateau, construction, joueur, sommet, listeMaison, listeChateau,
                              listeCentraleelec);
            locate(100, 23);
            color(12,0);
            printf("Souhaitez-vous placer une autre route ?\n\r");
            locate(100, 24);
            printf("(1) Oui      (2) Non\n\r");
            locate(100, 25);
            scanf("%d", &choix);
            locate(100, 23);
            printf("                                            ");
            locate(100, 24);
            printf("                                            ");
        } else {
            locate(100, 23);
            color(4,0);
            printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
            sleep(3);
        }
    } while (choix == 1);
    color(15,0);
}

void terrainVague(int *preds, char **plateau, DonneesJoueur *joueur, Construction *construction, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
    if (joueur->compteurMonnaie >= construction->cout) {
        saisir_coordonnees(construction);
        valid_coordonnees(preds, plateau, construction, joueur, sommet, listeMaison, listeChateau, listeCentraleelec);
    } else {
        locate(100, 23);
        color(4,0);
        printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
        sleep(3);
    }
    color(15,0);
}

void chateauDeau(int *preds, char **plateau, DonneesJoueur *joueur, Construction *construction, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
    if (joueur->compteurMonnaie >= construction->cout) {
        saisir_coordonnees(construction);
        valid_coordonnees(preds, plateau, construction, joueur, sommet, listeMaison, listeChateau, listeCentraleelec);
    } else {
        locate(100, 23);
        color(4,0);
        printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
        sleep(3);
    }
    color(15,0);
}

void centraleElectrique(int *preds, char **plateau, DonneesJoueur *joueur, Construction *construction, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
    if (joueur->compteurMonnaie >= construction->cout) {
        saisir_coordonnees(construction);
        valid_coordonnees(preds, plateau, construction, joueur, sommet, listeMaison, listeChateau, listeCentraleelec);
    } else {
        locate(100, 23);
        color(4,0);
        printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
        sleep(3);
    }
    color(15,0);
}

void afficherElement(int *preds, char **plateau, int choix, DonneesJoueur *joueur, Construction *construction, int **sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
    scanf("%d", &construction->choixBatiment);
    switch (construction->choixBatiment) {
        case 1: {
            route(preds, plateau, choix, joueur, construction, sommet, listeMaison, listeChateau, listeCentraleelec);
            break;
        }
        case 2: {
            terrainVague(preds, plateau, joueur, construction, sommet, listeMaison, listeChateau, listeCentraleelec);
            break;
        }
        case 3: {

            centraleElectrique(preds, plateau, joueur, construction, sommet, listeMaison, listeChateau,
                               listeCentraleelec);
            break;
        }
        case 4: {
            chateauDeau(preds, plateau, joueur, construction, sommet, listeMaison, listeChateau, listeCentraleelec);
            break;
        }
    }
}

void afficherRessource(DonneesJoueur *joueur, Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
    locate(92, 30);
    color(11, 0);
    printf(" Compteur temporel :  %ld s   ", joueur->compteurTemps);
    locate(92, 31);
    printf(" Monnaie :  %d   ", joueur->compteurMonnaie);
    locate(92, 32);
    printf(" Nb Habitants : %d ", joueur->nombreDHabitants);
    locate(92, 33);
    printf(" Capacite electrique : %d ", joueur->capaciteElectrique);
    locate(92, 34);
    printf(" Capacite eau :");
    locate(107, 34);
    for (int i = 0; i < joueur->nb_chateaueau; i++) {
        printf(" n%d %d/5000 :", i + 1, listeChateau[i].capa);
    }
    color(15,0);
}

int checksommet(DonneesJoueur *joueur, int x, int y, int **sommet) {
    for (int i = 0; i <= joueur->nb_sommet; i++) {
        if (sommet[i][0] == x && sommet[i][1] == y) {
            return i;
        }
    }
}

void afficheph(Chateaueau listeChateau[]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 20; j++) {
            printf("arg1 %d", listeChateau[i].numchateau);
            printf("arg2 %d", listeChateau[i].x);
            printf("arg3 %d", listeChateau[i].y);
            printf("arg4 %d", listeChateau[i].capa);
            printf("arg5 %d", listeChateau[i].listeMaisonconnecteau[j].nummaison);
            printf("arg5 %d", listeChateau[i].listeMaisonconnecteau[j].distance);
            printf("\n\n=========");
        }
    }
}

void majdonnees(DonneesJoueur *joueur, char **plateau, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[], Habitat listeHabitat[]) {
    int eaudispo = 0;
    int nexthab, actuhab, actueauuse;
    char typeactu, nexttype, actuelec;
    joueur->compteurMonnaie = joueur->compteurMonnaie + (10 * joueur->nombreDHabitants);
    for (int nummaison = 0; nummaison < joueur->nb_maison; nummaison++) {
        typeactu = listeMaison[nummaison].type;
        actuhab = listeMaison[nummaison].nbhab;
        if (typeactu != 'G') {
            for (int i = 0; i < 5; i++) {
                if (listeHabitat[i].type == typeactu) {
                    nexttype = listeHabitat[i + 1].type;
                    actuelec = listeHabitat[i].nbhabitant;
                    nexthab = listeHabitat[i + 1].nbhabitant;
                }
            }
            if (listeMaison[nummaison].eau1 != 99 && listeMaison[nummaison].elec != 99) {
                eaudispo = listeChateau[listeMaison[nummaison].eau1].capa;
                actueauuse = listeMaison[nummaison].capaeau1use;
                if (nexthab <= eaudispo && eaudispo > 0 && nexthab <= joueur->capaciteElectrique) {
                    listeMaison[nummaison].type = nexttype;
                    listeMaison[nummaison].nbhabmax = nexthab;
                    listeMaison[nummaison].nbhab = nexthab;
                    listeMaison[nummaison].capaeau1use = listeMaison[nummaison].capaeau1use + nexthab - actueauuse;
                    listeChateau[listeMaison[nummaison].eau1].capa = listeChateau[listeMaison[nummaison].eau1].capa - listeMaison[nummaison].capaeau1use + actueauuse;
                    joueur->capaciteElectrique = joueur->capaciteElectrique - nexthab + actuelec;
                    joueur->nombreDHabitants = joueur->nombreDHabitants + nexthab - actuhab;
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            plateau[listeMaison[nummaison].x - i - 1][listeMaison[nummaison].y + j - 1] = listeMaison[nummaison].type;
                        }
                    }
                } else {
                    if (eaudispo > 0) {
                        listeMaison[nummaison].type = nexttype;
                        listeMaison[nummaison].nbhabmax = nexthab;
                        listeMaison[nummaison].nbhab = listeMaison[nummaison].nbhab + eaudispo;
                        listeMaison[nummaison].capaeau1use = listeMaison[nummaison].capaeau1use + eaudispo;
                        listeChateau[listeMaison[nummaison].eau1].capa = listeChateau[listeMaison[nummaison].eau1].capa - listeMaison[nummaison].capaeau1use + actueauuse;
                    }
                }
            }
        }
    }
}
