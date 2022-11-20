
#include "affichage.h"


DonneesJoueur initialisationJoueur(DonneesJoueur *joueur) {
    joueur->compteurTemps = 0;
    joueur->compteurMonnaie = 500000;
    joueur->nombreDHabitants = 0;
    joueur->capaciteEau = 0;
    joueur->capaciteElectrique = 0;
    joueur->nb_sommet = 0;
    joueur->mode_jeux = 0; // 0 = mode communiste; 1 = mode capitaliste
    return *joueur;
}

void initialisationConstruction(Construction *construction) {

    construction->cout = 0;

    if (construction->choixBatiment == ROUTE){
        construction->cout = 10;
    }
    else if (construction->choixBatiment == MAISON){
        construction->cout = 1000;
    }
    else if (construction->choixBatiment == ELEC){
        construction->cout = 100000;
    }
    else if (construction->choixBatiment == EAU){
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

void AllouerSommet(int ***sommet) {
    *sommet = malloc(10 * sizeof(int *));//premier test avec 5 sommet
    for (int i = 0; i < 10; i++)
        *(*sommet + i) = malloc(7 * sizeof(int));

}

void InitialisationSommet(int **sommet) {
    int i, j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 7; j++)
        {
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

void saisir_coordonnees(Construction* construction) {
    locate(100,18);
    printf("Saisissez des coordonnees :\n");
    int ret, continuer;
    do{
        continuer = 0;
        locate(100,19);
        printf("x : \n");
        locate(100,20);
        ret = scanf("%d", &construction->x);

        if(ret != 1 || construction->x <= 0 || construction->x > 35)
            continuer = 1;

        while(ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    }while(continuer);

    do{
        continuer = 0;
        locate(100,21);
        printf("y : \n");
        locate(100,22);
        ret = scanf("%d", &construction->y);
        //*y = modifier

        if(ret != 1 || construction->y <= 0 || construction->y > 45)
            continuer = 1;

        while(ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    }while(continuer);

}

void check_adjacent(char **plateau,Construction *construction, DonneesJoueur *joueur, int **sommet) {
    int debugx=0;
    int debugy=0;
    char checkadj;
    debugx = construction->x;
    debugy = construction->y;

    // recherche adjacent horizontaux
    for (int boucle = 0; boucle < joueur->nb_sommet ; boucle++)
    {
        debugx = construction->x;
        debugy = construction->y;
        if (construction->x == sommet[boucle][0])
        {
            debugy = construction->y-1;

            // recherche adjacent gauche
            if (construction->y-1 == sommet[boucle][1])
            {
                for (int boucleadj = 3; boucleadj <6 ; boucleadj++)
                {
                    if (sommet[boucle][boucleadj] == 0)
                    {
                        Sleep(3);
                        sommet[boucle][boucleadj]= joueur->nb_sommet;
                        break;
                    }
                }

            }
            // recherche adjacent droite
            if (construction->y+1 == sommet[boucle][1])
            {
                for (int boucleadj = 3; boucleadj <6 ; boucleadj++)
                {
                    if (sommet[boucle][boucleadj] == 0)
                    {
                        Sleep(3);
                        sommet[boucle][boucleadj]= joueur->nb_sommet;
                        break;
                    }
                }

            }
        }
    }

    // recherche adjacent verticaux

    for (int boucle = 0; boucle < joueur->nb_sommet ; boucle++)
    {
        debugx = construction->x;
        debugy = construction->y;
        if (construction->y == sommet[boucle][1])
        {
            // recherche adjacent inferieur

            if (construction->x-1 == sommet[boucle][0])
            {
                for (int boucleadj = 3; boucleadj <6 ; boucleadj++)
                {
                    if (sommet[boucle][boucleadj] == 0)
                    {
                        Sleep(3);
                        sommet[boucle][boucleadj]= joueur->nb_sommet;
                        break;
                    }
                }

            }
            // recherche adjacent superieur

            if (construction->x+1 == sommet[boucle][0])
            {
                for (int boucleadj = 3; boucleadj <6 ; boucleadj++)
                {
                    if (sommet[boucle][boucleadj] == 0)
                    {
                        Sleep(3);
                        sommet[boucle][boucleadj]= joueur->nb_sommet;
                        break;
                    }
                }

            }
        }
    }
    Sleep(3);
}

void placer_bloc(char **plateau, Construction *construction, DonneesJoueur *joueur, int** sommet) {
    if(construction->choixBatiment == ROUTE){
        plateau[construction->x-1][construction->y-1] = -36;
        argentJoueur(joueur, construction);
        sommet[joueur->nb_sommet][0] = construction->x;
        sommet[joueur->nb_sommet][1] = construction->y;
        sommet[joueur->nb_sommet][2] = joueur->nb_sommet;
        check_adjacent(plateau, construction, joueur, sommet);
        joueur->nb_sommet = joueur->nb_sommet + 1;
    }
    else if(construction->choixBatiment == MAISON){
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                plateau[construction->x-i-1][construction->y+j-1] = 'M';
            }
        }
        argentJoueur(joueur, construction);
        sommet[joueur->nb_sommet][1] = construction->x;
        sommet[joueur->nb_sommet][2] = construction->y-1;
        sommet[joueur->nb_sommet][3] = joueur->nb_sommet;
        joueur->nb_sommet = joueur->nb_sommet + 1;
    }
    else if(construction->choixBatiment == ELEC){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                plateau[construction->x-i-1][construction->y+j-1] = 'U';
            }
        }
        argentJoueur(joueur, construction);
        sommet[joueur->nb_sommet][1] = construction->x;
        sommet[joueur->nb_sommet][2] = construction->y-1;
        sommet[joueur->nb_sommet][2] = joueur->nb_sommet;
        joueur->nb_sommet = joueur->nb_sommet + 1;
    }
    else if(construction->choixBatiment == EAU){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                plateau[construction->x-i-1][construction->y+j-1] = 'C';
            }
        }
        argentJoueur(joueur, construction);
        sommet[joueur->nb_sommet][1] = construction->x;
        sommet[joueur->nb_sommet][2] = construction->y-1;
        sommet[joueur->nb_sommet][2] = joueur->nb_sommet;
        joueur->nb_sommet = joueur->nb_sommet + 1;
    }
}

void verif_chevauchement(char** plateau, Construction *construction, DonneesJoueur *joueur, int** sommet) {

    int verif = 0;

    int tailleX, tailleY = 0;

    switch (construction->choixBatiment) {
        case ROUTE :{
            tailleX = 1;
            tailleY = 1;
            break;
        }
        case MAISON :{
            tailleX = 3;
            tailleY = 3;
            break;
        }
        case ELEC :{
            tailleX = 4;
            tailleY = 6;
            break;
        }
        case EAU :{
            tailleX = 4;
            tailleY = 6;
            break;
        }
    }
    for (int i = 0; i < tailleX; i++) {
        for (int j = 0; j < tailleY; j++) {
            if(plateau[construction->x-i-1][construction->y+j-1] != '.'){
                verif = 1;
            }
        }
    }
    if(verif == 1){
        saisir_coordonnees(construction);
        verif_chevauchement(plateau,  construction, joueur, sommet);
    }
    else{
        placer_bloc(plateau, construction, joueur, sommet);
    }
}

void valid_coordonnees(char** plateau, Construction *construction, DonneesJoueur *joueur, int** sommet) {

    int verif = 0;

    while (verif != 1){
        if(((construction->choixBatiment == 2) && (construction->x < 3 || construction->y > 43))){
            saisir_coordonnees(construction);
        }
        else if((construction->choixBatiment == 3 || construction->choixBatiment == 4) && (construction->x < 4 || construction->y > 40)){
            saisir_coordonnees(construction);
        }
        else{
            verif = 1;
            verif_chevauchement(plateau, construction, joueur, sommet);
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

void lire_DonneesJoueur(char* save, DonneesJoueur *joueur) {
    FILE* fichier = NULL;
    fichier = fopen(save, "r");

    if (fichier != NULL)
    {
        fscanf(fichier,"%d %d %d %d %d %d %d", &joueur->compteurTemps, &joueur->compteurMonnaie, &joueur->mode_jeux, &joueur->nombreDHabitants, &joueur->capaciteEau, &joueur->capaciteElectrique, &joueur->nb_sommet);
    }
    fclose(fichier);
}

void save_DonneesJoueur(char* save, DonneesJoueur *joueur) {
    FILE* fichier = NULL;
    fichier = fopen(save, "w");

    if(fichier != NULL){

        fprintf(fichier, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n", joueur->compteurTemps, joueur->compteurMonnaie, joueur->mode_jeux, joueur->nombreDHabitants, joueur->capaciteEau, joueur->capaciteElectrique, joueur->nb_sommet );

        fclose(fichier);
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

void route(char** plateau, int choix, DonneesJoueur *joueur, Construction *construction, int** sommet) {
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
            saisir_coordonnees(construction);
            valid_coordonnees(plateau, construction, joueur, sommet);
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

void terrainVague(char** plateau, DonneesJoueur *joueur, Construction *construction, int** sommet) {
    if(joueur->compteurMonnaie >= construction->cout){
        saisir_coordonnees(construction);
        valid_coordonnees(plateau, construction, joueur, sommet);
    }
    else{
        locate(100,23);
        printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
    }
}

void chateauDeau(char** plateau, DonneesJoueur *joueur, Construction *construction, int** sommet) {
    if(joueur->compteurMonnaie >= construction->cout){
        saisir_coordonnees(construction);
        valid_coordonnees(plateau, construction, joueur, sommet);
    }
    else{
        locate(100,23);
        printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
    }
}

void centraleElectrique(char** plateau, DonneesJoueur *joueur, Construction *construction, int** sommet) {
    if(joueur->compteurMonnaie >= construction->cout){
        saisir_coordonnees(construction);
        valid_coordonnees(plateau, construction, joueur, sommet);
    }
    else{
        locate(100,23);
        printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire une route !\n\r");
    }
}

void afficherElement(char** plateau, int choix, DonneesJoueur *joueur, Construction *construction, int** sommet) {
    scanf("%d", &construction->choixBatiment);
    switch (construction->choixBatiment) {
        case 1:{
            route(plateau, choix, joueur, construction, sommet);
            break;
        }
        case 2:{
            terrainVague(plateau, joueur, construction, sommet);
            break;
        }
        case 3:{
            centraleElectrique(plateau,  joueur, construction, sommet);
            break;
        }
        case 4:{
            chateauDeau(plateau,  joueur, construction, sommet);
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
