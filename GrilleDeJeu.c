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

void saisir_coordonnees(int *x, int *y) {
    printf("Saisissez des coordonnees :\n");
    int ret, continuer;
    do{
        continuer = 0;
        printf("x : \n");
        ret = scanf("%d", x);

        if(ret != 1 || *x <= 0 || *x > 35)
            continuer = 1;

        while(ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    }while(continuer);

    do{
        continuer = 0;
        printf("y : \n");
        ret = scanf("%d", y);
        //*y = modifier

        if(ret != 1 || *y <= 0 || *y > 45)
            continuer = 1;

        while(ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    }while(continuer);

}

void placer_bloc(char **plateau,int choix, int x, int y) {
    if(choix == 1){
        plateau[x-1][y-1] = -36;
    }
    else if(choix == 2){
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                plateau[x-i-1][y+j-1] = 'M';
            }
        }
    }
    else if(choix == 3){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                plateau[x-i-1][y+j-1] = 'U';
            }
        }
    }
    else if(choix == 4){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                plateau[x-i-1][y+j-1] = 'C';
            }
        }
    }
}

void verif_chevauchement(char** plateau, int choix, int x, int y) {

    int verif = 0;

    int tailleX, tailleY = 0;

    switch (choix) {
        case 1 :{
            tailleX = 1;
            tailleY = 1;
            break;
        }
        case 2 :{
            tailleX = 3;
            tailleY = 3;
            break;
        }
        case 3 :{
            tailleX = 4;
            tailleY = 6;
            break;
        }
        case 4 :{
            tailleX = 4;
            tailleY = 6;
            break;
        }
    }
    for (int i = 0; i < tailleX; i++) {
        for (int j = 0; j < tailleY; j++) {
            if(plateau[x-i-1][y+j-1] != '.'){
                verif = 1;
            }
        }
    }
    if(verif == 1){
        saisir_coordonnees(&x, &y);
        verif_chevauchement(plateau,choix, x, y);
    }
    else{
        placer_bloc(plateau,choix,x,y);
    }
}

void valid_coordonnees(int x, int y, int choix, char** plateau) {

    int verif = 0;

    while (verif != 1){
        if(((choix == 2) && (x < 3 || y > 43))){
            saisir_coordonnees(&x,&y);
        }
        else if((choix == 3 || choix == 4) && (x < 4 || y > 40)){
            saisir_coordonnees(&x,&y);
        }
        else{
            verif = 1;
            verif_chevauchement(plateau,choix, x, y);
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

void lire_fichier_grille(FILE* fichier, char* save, char** plateau) {

    int i = 0, j = 0;
    char element;

    fichier = fopen(save, "r");

    if (fichier != NULL)
    {
        // Boucle de lecture des caractères un à un
        do
        {

            if(j < (nbColonnes)){
                element = fgetc(fichier); // On lit le caractère vide entre chaque valeur
                element = fgetc(fichier); // On lit le caractère
                plateau[i][j] = element;
                j++;
            }
            else{
                element = fgetc(fichier); // On lit le caractère vide apres le saut de ligne
                j = 0;
                i++;
            }
        } while (element != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

        fclose(fichier);

    }
}

void save_grille(FILE* fichier, char* save, char** plateau) {

    int i = 0, j = 0, fin = 0;
    char element;
    fichier = fopen(save, "w");
    if(fichier != NULL){
        do
        {
            if(j < (nbColonnes)){
                element = plateau[i][j];
                fputc(' ', fichier);
                fputc(element, fichier);
                j++;
            }
            else{
                if(i < (nbLignes-1)){
                    fprintf(fichier, "\n");
                    j = 0;
                    i++;
                }
                else{
                    fin = 1;
                }
            }
        } while (fin != 1);
        fclose(fichier);
        //exit(1);
    }

}

void afficherMenu() {
    //int i, j;
    printf("\n");
    printf("Quelle action voulez vous realiser : \n");
    printf("- 1 : restaurer une sauvegarde \n");
    printf("- 2 : sauvegarder la partie en cours \n");
    printf("- 3 : ajouter un element \n");
    printf("- 4 : Sortir du jeux \n");

}

void choixElement() {
    printf("\n");
    printf("Quelle element voulez-vous placer ? \n");
    printf("- 1 : route \n");
    printf("- 2 : terrain vide \n");
    printf("- 3 : centrale electrique \n");
    printf("- 4 : chateau d'eau \n");
}

DonneesJoueur initialisationJoueur(DonneesJoueur joueur) {
    joueur.compteurMonnaie = 500000;
    return joueur;
}

void initialisationConstruction(Construction construction) {
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

void route(char** plateau, int choix, int x, int y, DonneesJoueur joueur, Construction construction[nbCases], int* i) {
    choix = 1;
    do {
        if(joueur.compteurMonnaie >= construction[*i].cout){
            saisir_coordonnees(&x, &y);
            valid_coordonnees(x, y, choix, plateau);
            printf("Souhaitez-vous placer une autre route ?\n\r");
            printf("(1) Oui      (2) Non\n\r");
            scanf("%d", &choix);
        }
        else{
            printf("Désolé ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
        }
    } while (choix == 1);
}

void terrainVague(char** plateau, int choix, int x, int y, DonneesJoueur joueur, Construction construction[nbCases], int* i) {
    if(joueur.compteurMonnaie >= construction[*i].cout){
        saisir_coordonnees(&x, &y);
        valid_coordonnees(x, y, choix, plateau);
    }
    else{
        printf("Désolé ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
    }
}

void chateauDeau(char** plateau, int choix, int x, int y, DonneesJoueur joueur, Construction construction[nbCases], int* i) {
    if(joueur.compteurMonnaie >= construction[*i].cout){
        saisir_coordonnees(&x, &y);
        valid_coordonnees(x, y, choix, plateau);
    }
    else{
        printf("Désolé ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
    }
}
void centraleElectrique(char** plateau, int choix, int x, int y, DonneesJoueur joueur, Construction construction[nbCases], int* i) {
    if(joueur.compteurMonnaie >= construction[*i].cout){
        saisir_coordonnees(&x, &y);
        valid_coordonnees(x, y, choix, plateau);
    }
    else{
        printf("Désolé ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
    }
}

void afficherElement(char** plateau, int choix, int x, int y, DonneesJoueur joueur, Construction construction[nbCases], int* i) {
    scanf("%d", &choix);
    switch (choix) {
        case 1:{
            route(plateau, choix, x, y, joueur, construction, i);
            break;
        }
        case 2:{
            terrainVague(plateau, choix, x, y, joueur, construction, i);
            break;
        }
        case 3:{
            centraleElectrique(plateau, choix, x, y, joueur, construction, i);
            break;
        }
        case 4:{
            chateauDeau(plateau, choix, x, y, joueur, construction, i);
            break;
        }
    }
}