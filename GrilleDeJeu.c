#include "GrilleDeJeu.h"

DonneesJoueur initialisationJoueur(DonneesJoueur *joueur) {
    joueur->compteurMonnaie = 500000;
    return *joueur;
}

void initialisationConstruction(Construction *construction) {
    if (construction->choixBatiment == 1){
        construction->cout = 10;
    }
    else if (construction->choixBatiment == 2){
        construction->cout = 1000;
    }
    else if (construction->choixBatiment == 3){
        construction->cout = 100000;
    }
    else if (construction->choixBatiment == 4){
        construction->cout = 100000;
    }
}

int argentJoueur(DonneesJoueur *joueur, Construction *construction) {
    initialisationConstruction(construction);
    return joueur->compteurMonnaie = joueur->compteurMonnaie - construction->cout;
}


void locate(int x,int y)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD C;
    C.X=x;
    C.Y=y;
    SetConsoleCursorPosition(H,C);
}

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
    locate(100,18);
    printf("Saisissez des coordonnees :\n");
    int ret, continuer;
    do{
        continuer = 0;
        locate(100,19);
        printf("x : \n");
        locate(100,20);
        ret = scanf("%d", x);

        if(ret != 1 || *x <= 0 || *x > 35)
            continuer = 1;

        while(ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    }while(continuer);

    do{
        continuer = 0;
        locate(100,21);
        printf("y : \n");
        locate(100,22);
        ret = scanf("%d", y);
        //*y = modifier

        if(ret != 1 || *y <= 0 || *y > 45)
            continuer = 1;

        while(ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    }while(continuer);

}


void placer_bloc(char **plateau, int x, int y, Construction *construction, DonneesJoueur *joueur) {
    if(construction->choixBatiment == 1){
        plateau[x-1][y-1] = -36;
        argentJoueur(joueur, construction);
    }
    else if(construction->choixBatiment == 2){
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                plateau[x-i-1][y+j-1] = 'M';
            }
        }
        argentJoueur(joueur, construction);
    }
    else if(construction->choixBatiment == 3){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                plateau[x-i-1][y+j-1] = 'U';
            }
        }
        argentJoueur(joueur, construction);
    }
    else if(construction->choixBatiment == 4){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                plateau[x-i-1][y+j-1] = 'C';
            }
        }
        argentJoueur(joueur, construction);
    }
}

void verif_chevauchement(char** plateau, int x, int y, Construction *construction, DonneesJoueur *joueur) {

    int verif = 0;

    int tailleX, tailleY = 0;

    switch (construction->choixBatiment) {
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
        verif_chevauchement(plateau, x, y, construction, joueur);
    }
    else{
        placer_bloc(plateau,x,y, construction, joueur);
    }
}

void valid_coordonnees(int x, int y, char** plateau, Construction *construction, DonneesJoueur *joueur) {

    int verif = 0;

    while (verif != 1){
        if(((construction->choixBatiment == 2) && (x < 3 || y > 43))){
            saisir_coordonnees(&x,&y);
        }
        else if((construction->choixBatiment == 3 || construction->choixBatiment == 4) && (x < 4 || y > 40)){
            saisir_coordonnees(&x,&y);
        }
        else{
            verif = 1;
            verif_chevauchement(plateau, x, y, construction, joueur);
        }
    }
}

void afficherPlateau(char **plateau) {
    int i, j;
    printf("\n");
    system("cls");
    locate(1,1);
    printf("          5         10        15        20        25        30        35        40        45\n");
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
        // Boucle de lecture des caract�res un � un
        do
        {

            if(j < (nbColonnes)){
                element = fgetc(fichier); // On lit le caract�re vide entre chaque valeur
                element = fgetc(fichier); // On lit le caract�re
                plateau[i][j] = element;
                j++;
            }
            else{
                element = fgetc(fichier); // On lit le caract�re vide apres le saut de ligne
                j = 0;
                i++;
            }
        } while (element != EOF); // On continue tant que fgetc n'a pas retourn� EOF (fin de fichier)

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
    int i, j;
    //printf("\n");
    locate(100,2);
    printf("Quelle action voulez vous realiser : \n");
    locate(100,3);
    printf("- (-1) : Affichage niveau -1   ");
    locate(100,4);
    printf("- (-2) : Affichage niveau -2   ");
    locate(100,5);
    printf("- 1 : restaurer une sauvegarde \n");
    locate(100,6);
    printf("- 2 : sauvegarder la partie en cours \n");
    locate(100,7);
    printf("- 3 : ajouter un element \n");
    locate(100,8);
    printf("- 4 : Sortir du jeux \n");
    locate(100,9);

}

void choixElement() {
    //printf("\n");
    locate(100,11);
    printf("Quelle element voulez-vous placer ? \n");
    locate(100,12);
    printf("- 1 : route \n");
    locate(100,13);
    printf("- 2 : terrain vide \n");
    locate(100,14);
    printf("- 3 : centrale electrique \n");
    locate(100,15);
    printf("- 4 : chateau d'eau \n");
    locate(100,16);
}

void route(char** plateau, int choix, int x, int y, DonneesJoueur *joueur, Construction *construction) {
    choix = 1;
    do {
        if(joueur->compteurMonnaie >= construction->cout){
            locate(100,20);
            printf("                                            ");
            locate(100,21);
            printf("                                            ");
            locate(100,22);
            printf("                                            ");
            locate(100,23);
            printf("                                            ");
            locate(100,24);
            printf("                                            ");
            locate(100,25);
            printf("                                            ");
            saisir_coordonnees(&x, &y);
            valid_coordonnees(x, y, plateau, construction, joueur);
            locate(100,23);
            printf("Souhaitez-vous placer une autre route ?\n\r");
            locate(100,24);
            printf("(1) Oui      (2) Non\n\r");
            locate(100,25);
            scanf("%d", &choix);
            locate(100,23);
            printf("                                            ");
            locate(100,24);
            printf("                                            ");
        }
        else{
            locate(100,23);
            printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
        }
    } while (choix == 1);
}

void terrainVague(char** plateau, int x, int y, DonneesJoueur *joueur, Construction *construction) {
    if(joueur->compteurMonnaie >= construction->cout){
        saisir_coordonnees(&x, &y);
        valid_coordonnees(x, y, plateau, construction, joueur);
    }
    else{
        locate(100,23);
        printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
    }
}

void chateauDeau(char** plateau, int x, int y, DonneesJoueur *joueur, Construction *construction) {
    if(joueur->compteurMonnaie >= construction->cout){
        saisir_coordonnees(&x, &y);
        valid_coordonnees(x, y, plateau, construction, joueur);
    }
    else{
        locate(100,23);
        printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
    }
}

void centraleElectrique(char** plateau, int x, int y, DonneesJoueur *joueur, Construction *construction) {
    if(joueur->compteurMonnaie >= construction->cout){
        saisir_coordonnees(&x, &y);
        valid_coordonnees(x, y, plateau, construction, joueur);
    }
    else{
        locate(100,23);
        printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
    }
}

void afficherElement(char** plateau, int choix, int x, int y, DonneesJoueur *joueur, Construction *construction) {
    scanf("%d", &construction->choixBatiment);
    switch (construction->choixBatiment) {
        case 1:{
            route(plateau, choix, x, y, joueur, construction);
            break;
        }
        case 2:{
            terrainVague(plateau, x, y, joueur, construction);
            break;
        }
        case 3:{
            centraleElectrique(plateau, x, y, joueur, construction);
            break;
        }
        case 4:{
            chateauDeau(plateau, x, y, joueur, construction);
            break;
        }
    }
}

void afficherRessource(DonneesJoueur *joueur){
    locate(100,30);
    printf(" Compteur temporel :     ");
    locate(100,31);
    printf(" Monnaie :  %d   ",joueur->compteurMonnaie);
    locate(100,32);
    printf(" Habitants :     ");
    locate(100,33);
    printf(" Capacite electrique :     ");
    locate(100,34);
    printf(" Capacite en eau :     ");
}