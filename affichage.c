#include "affichage.h"

//Initialisation des données du joueur
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


//Initialisation du compteur temps
paramclock initialisationmajclock(paramclock *majclock) {
    majclock->majdon = 0;
    return *majclock;
}


//Initialisation des constructions
void initialisationConstruction(Construction *construction) {

    construction->cout = 0;

    if (construction->choixBatiment == ROUTE){
        construction->cout = 10;
        construction->nb_x = 1;
        construction->nb_y = 1;
    }
    else if (construction->choixBatiment == MAISON){
        construction->cout = 1000;
        construction->nb_x = 3;
        construction->nb_y = 3;
    }
    else if (construction->choixBatiment == ELEC||construction->choixBatiment == EAU){
        construction->cout = 100000;
        construction->nb_x = 6;
        construction->nb_y = 4;
    }
}



void initialisationChateaueau(Chateaueau listeChateau[]){
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 30 ; j++){
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



void initialisationCentraleelec(Centraleelec listeCentraleelec[]){
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 30 ; j++){
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


// Charge la liste de type d'habitation depuis le fichier listehabitat.txt
void ChargeHabitat(FILE* fichier,Habitat listeHabitat[]) {

    int i = 0;
    char type[2];
    int nbhabitant;
    fichier = fopen("../listehabitat.txt", "r");
    if (fichier != NULL)
    {
        for (i = 0; i < 5; i++){
            fscanf(fichier, "Type : %s nbhab : %d\n", &type, &nbhabitant);
            listeHabitat[i].type = type[0];
            listeHabitat[i].nbhabitant = nbhabitant;
        }
        fclose(fichier);
    }

}



void Initialisationmaison(Maison listeMaison[]) {
    int i;
    for (i = 0; i < 30; i++)
    {
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
        listeMaison[i].nbhabmax = 0;
        listeMaison[i].nbhab = 0;

    }
}


//Fonction qui met à jour l'argent du joueur
int argentJoueur(DonneesJoueur *joueur, Construction *construction) {
    return joueur->compteurMonnaie = joueur->compteurMonnaie - construction->cout;
}


//Fonction qui permet de localiser sur l'écran en console le texte
//C'est-à-dire que l'on peut afficher notre grille de jeu à gauche et la boîte à outils et les données du joueur à droite
void locate(int x,int y)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD C;
    C.X=x;
    C.Y=y;
    SetConsoleCursorPosition(H,C);
}


//Allocation de la grille dynamiquement
void AllouerTableau(char ***plateau) {
    *plateau = malloc(nbLignes * sizeof(char *));
    for (int i = 0; i < nbLignes; i++)
        *(*plateau + i) = malloc(nbColonnes * sizeof(char));

}


//Allocation des sommets pour la théorie des graphes
void AllouerSommet(int ***sommet) {

    *sommet = malloc(1225 * sizeof(int *));

    for (int i = 0; i < 1225; i++) {
        *(*sommet + i) = malloc(7 * sizeof(int));
    }
}


//Initialisation des sommets
void InitialisationSommet(int **sommet) {
    int i, j;
    for (i = 0; i < 1225; i++)
    {
        for (j = 0; j < 7; j++)
        {
            sommet[i][j] = 0;
        }
    }
}


//Création des cases de la grille qui sont des points
void creerTableau(char **plateau) {
    int i, j;

    for (i = 0; i < nbLignes; i++) {
        for (j = 0; j < nbColonnes; j++) {
            plateau[i][j] = '.';
        }
    }
}


//Fonction qui permet la saisie des coordonnées de nos constructions et routes
void saisir_coordonnees(Construction* construction) {
    locate(100,18); // Localisation du texte sur l'écran
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

        if(ret != 1 || construction->y <= 0 || construction->y > 45)
            continuer = 1;

        while(ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    }while(continuer);

}


//Fonction de recherche de sommets adajacens pour la viabilité
void check_adjacent(char **plateau,Construction *construction, DonneesJoueur *joueur, int **sommet) {

    char checkadj;

    // recherche adjacent horizontaux
    for (int boucle = 0; boucle < joueur->nb_sommet ; boucle++)
    {
        if (construction->x == sommet[boucle][0])
        {

            // recherche adjacent gauche
            if (construction->y-1 == sommet[boucle][1])
            {
                for (int boucleadj = 3; boucleadj <6 ; boucleadj++)
                {
                    if (sommet[boucle][boucleadj] == 0)
                    {

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
        if (construction->y == sommet[boucle][1])
        {
            // recherche adjacent inferieur

            if (construction->x-1 == sommet[boucle][0])
            {
                for (int boucleadj = 3; boucleadj <6 ; boucleadj++)
                {
                    if (sommet[boucle][boucleadj] == 0)
                    {

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

                        sommet[boucle][boucleadj]= joueur->nb_sommet;
                        break;
                    }
                }

            }
        }
    }
}


//Fonction qui place la construction ou la route sur la grille
void placer_bloc(int* preds,char **plateau, Construction *construction, DonneesJoueur *joueur, int** sommet, Maison listeMaison[], Chateaueau listeChateau[],Centraleelec listeCentraleelec[]) {
    if(construction->choixBatiment == ROUTE){
        plateau[construction->x-1][construction->y-1] = -36; // Attribution du caractère de la route à la case correspondante dans le tableau de la grille
        argentJoueur(joueur, construction); // Mise à jour de l'argent du joueur
        sommet[joueur->nb_sommet][0] = construction->x;
        sommet[joueur->nb_sommet][1] = construction->y;
        sommet[joueur->nb_sommet][2] = joueur->nb_sommet;
        check_adjacent(plateau, construction, joueur, sommet); // Vérification de l'adjacence
        joueur->nb_sommet = joueur->nb_sommet + 1;
    }
    else if(construction->choixBatiment == MAISON){
        for (int i = 0; i < construction->nb_x; i++) {
            for (int j = 0; j < construction->nb_y; j++) {
                plateau[construction->x-i-1][construction->y+j-1] = 'T'; // Attribution du T représentant le terrain vague au neux cases nécessaires du tableau de la grille
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

        joueur->nb_maison = joueur->nb_maison+1;
    }
    else if(construction->choixBatiment == ELEC ){
        for (int i = 0; i < construction->nb_x; i++) {
            for (int j = 0; j < construction->nb_y; j++) {
                plateau[construction->x-i-1][construction->y+j-1] = 'U'; // Attribution du U représentant la centrale électrique au 24 cases nécessaires du tableau de la grille
            }
        }
        argentJoueur(joueur, construction);
        listeCentraleelec[joueur->nb_centraleelec].numcentrale = joueur->nb_centraleelec;
        listeCentraleelec[joueur->nb_centraleelec].x = construction->x;
        listeCentraleelec[joueur->nb_centraleelec].y = construction->y;
        listeCentraleelec[joueur->nb_centraleelec].capa = 5000;
        joueur->nb_centraleelec = joueur->nb_centraleelec+1;
        joueur->capaciteElectrique  = joueur->capaciteElectrique+5000; // Electricite totale de la ville qui augmente
    }
    else if(construction->choixBatiment == EAU){
        for (int i = 0; i < construction->nb_x; i++) {
            for (int j = 0; j < construction->nb_y; j++) {
                plateau[construction->x-i-1][construction->y+j-1] = 'E'; // Attribution du E représentant le château d'eau au 24 cases nécessaires du tableau de la grille
            }
        }
        argentJoueur(joueur, construction);
        listeChateau[joueur->nb_chateaueau].numchateau = joueur->nb_chateaueau;
        listeChateau[joueur->nb_chateaueau].x = construction->x;
        listeChateau[joueur->nb_chateaueau].y = construction->y;
        listeChateau[joueur->nb_chateaueau].capa = 5000; // Eau totale de la ville qui augmente
        joueur->nb_chateaueau = joueur->nb_chateaueau+1;
    }
    checkelecmaison(preds,plateau,joueur,sommet,listeMaison,listeCentraleelec); // Vérification de la connexion de l'habitation avec une centrale électrique
    checkchateaumaison(preds,plateau,joueur,sommet,listeMaison,listeChateau); // Vérification de la connexion de l'habitation avec un château d'eau
}


//Fonction qui vérifie s'il n'y a pas déja une construction ou une route placée à l'endroit où l'on souhaite rajouter notre construction ou route
void verif_chevauchement(int* preds, char** plateau, Construction *construction, DonneesJoueur *joueur, int** sommet, Maison listeMaison[], Chateaueau listeChateau[],Centraleelec listeCentraleelec[]) {

    int verif = 0;

    int tailleX, tailleY = 0;
    //initialisationConstruction(construction);

    for (int i = 0; i < construction->nb_x; i++) {
        for (int j = 0; j < construction->nb_y; j++) {
            if(plateau[construction->x-i-1][construction->y+j-1] != '.'){ // Si les cases nécessaires à notre construction ne sont pas occupées par des points
                verif = 1;
            }
        }
    }
    if(verif == 1){ // Alors on ressaisit de nouvelles coordonnées et on vérifie une nouvelle fois le chevauchement
        saisir_coordonnees(construction);
        verif_chevauchement(preds, plateau,  construction, joueur, sommet, listeMaison, listeChateau, listeCentraleelec);
    }
    else{ // Sinon on place la construction
        placer_bloc(preds, plateau, construction, joueur, sommet, listeMaison, listeChateau, listeCentraleelec);
    }
}


//Fonction qui vérifie que la construction sera bien placée dans la grille et que des cases ne se retrouvent pas à l'extérieur
void valid_coordonnees(int* preds, char** plateau, Construction *construction, DonneesJoueur *joueur, int** sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {

    int verif = 0;

    while (verif != 1){
        if(((construction->choixBatiment == 2 || construction->choixBatiment == 3 || construction->choixBatiment == 4) && (construction->x < construction->nb_x || construction->y > 46-construction->nb_y))){
            // Si la construction dépasse, on ressaisit de nouvelles coordonnées
            saisir_coordonnees(construction);
        }
        else{ // Sinon on peut vérifier le chevauchement
            verif = 1;
            verif_chevauchement(preds, plateau, construction, joueur, sommet, listeMaison, listeChateau, listeCentraleelec);
        }
    }
}


//Affichage de la grille de jeu
void afficherPlateau(char **plateau) {
    int i, j;
    printf("\n");
    system("cls");
    locate(1,1);
    //color(5, 0);
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


//Libération du tableau de la grille
void free_plateau(char **plateau) {
    for (int i = 0; i < nbLignes; i++)
        free(plateau[i]);
    free(plateau);

}


//Sauvegarde de la grille
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
    }

}


//Sauvegarde des données du joueur
void save_DonneesJoueur(char* save, DonneesJoueur *joueur) {
    FILE* fichier = NULL;
    fichier = fopen(save, "w");

    if(fichier != NULL){
        fprintf(fichier, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", joueur->compteurMonnaie, joueur->nombreDHabitants, joueur->capaciteEau, joueur->capaciteElectrique, joueur->nb_sommet, joueur->mode_jeux,joueur->nb_maison,joueur->nb_chateaueau,joueur->nb_centraleelec );
        fclose(fichier);
    }
}

void save_sommet(char* save, DonneesJoueur *joueur, int** sommet) {
    FILE* fichier = NULL;
    fichier = fopen(save, "w");
    if(fichier != NULL){
        for (int numsommet = 0; numsommet < joueur->nb_sommet ; numsommet++)
        {
            fprintf(fichier, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n", sommet[numsommet][0],sommet[numsommet][1], sommet[numsommet][2], sommet[numsommet][3], sommet[numsommet][4], sommet[numsommet][5], sommet[numsommet][6]);
        }
        fclose(fichier);
    }
}

void save_listeChateau(char* save, DonneesJoueur *joueur,Chateaueau listeChateau[]) {
    FILE* fichier = NULL;
    fichier = fopen(save, "w");
    if(fichier != NULL){
        for (int numchateau = 0; numchateau < joueur->nb_chateaueau ; numchateau++)
        {
            fprintf(fichier, "%d\n%d\n%d\n%d\n%d\n", listeChateau[numchateau].numchateau , listeChateau[numchateau].x, listeChateau[numchateau].y, listeChateau[numchateau].capa, listeChateau[numchateau].nextmaison );
            for (int listemaison = 0; listemaison < listeChateau[numchateau].nextmaison ; listemaison++)
                fprintf(fichier, "%d\n%d\n",listeChateau[numchateau].listeMaisonconnecteau[listemaison].nummaison,listeChateau[numchateau].listeMaisonconnecteau[listemaison].distance);
        }

        fclose(fichier);
    }
}

void save_listeCentraleelec(char* save, DonneesJoueur *joueur,Centraleelec listeCentraleelec[]) {
    FILE* fichier = NULL;
    fichier = fopen(save, "w");
    if(fichier != NULL){
        for (int numcentrale = 0; numcentrale < joueur->nb_centraleelec ; numcentrale++)
        {
            fprintf(fichier, "%d\n%d\n%d\n%d\n%d\n", listeCentraleelec[numcentrale].numcentrale , listeCentraleelec[numcentrale].x, listeCentraleelec[numcentrale].y, listeCentraleelec[numcentrale].capa, listeCentraleelec[numcentrale].nextmaison );
            for (int listemaison = 0; listemaison < listeCentraleelec[numcentrale].nextmaison ; listemaison++)
                fprintf(fichier, "%d\n%d\n",listeCentraleelec[numcentrale].listeMaisonconnectelec[listemaison].nummaison,listeCentraleelec[numcentrale].listeMaisonconnectelec[listemaison].distance);
        }

        fclose(fichier);
    }
}
void save_listeMaison(char* save, DonneesJoueur *joueur,Maison listeMaison[]) {
    FILE* fichier = NULL;
    fichier = fopen(save, "w");

    if(fichier != NULL){
        for (int maison = 0; maison < joueur->nb_maison ; maison++)
            fprintf(fichier, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", listeMaison[maison].nummaison,listeMaison[maison].type,listeMaison[maison].x,listeMaison[maison].y,listeMaison[maison].eau1,listeMaison[maison].disteau1,listeMaison[maison].capaeau1use,listeMaison[maison].eau2,listeMaison[maison].disteau2,listeMaison[maison].capaeau2use,listeMaison[maison].elec,listeMaison[maison].nbhabmax,listeMaison[maison].nbhab );
        fclose(fichier);
    }
}


//Lecture du fichier de la grille
void lire_fichier_grille(FILE* fichier, char* save, char** plateau) {

    int i = 0, j = 0;
    char element;

    fichier = fopen(save, "r");

    if (fichier != NULL)
    {
        // Boucle de lecture des caracteres un a un
        do
        {

            if(j < (nbColonnes)){
                element = fgetc(fichier); // On lit le caractere vide entre chaque valeur
                element = fgetc(fichier); // On lit le caractere
                plateau[i][j] = element;
                j++;
            }
            else{
                element = fgetc(fichier); // On lit le caractere vide apres le saut de ligne
                j = 0;
                i++;
            }
        } while (element != EOF); // On continue tant que fgetc n'a pas retourne EOF (fin de fichier)

        fclose(fichier);

    }
}


//Lecture du fichier des données du joueur
void lire_DonneesJoueur(char* save, DonneesJoueur *joueur) {
    FILE* fichier = NULL;
    fichier = fopen(save, "r");
    if (fichier != NULL)
    {
        fscanf(fichier,"%d %d %d %d %d %d %d %d %d", &joueur->compteurMonnaie, &joueur->nombreDHabitants, &joueur->capaciteEau, &joueur->capaciteElectrique, &joueur->nb_sommet, &joueur->mode_jeux,&joueur->nb_maison,&joueur->nb_chateaueau,&joueur->nb_centraleelec);
    }
    fclose(fichier);
}

void lire_sommet(char* save, DonneesJoueur *joueur, int** sommet) {
    FILE* fichier = NULL;
    fichier = fopen(save, "r");
    if(fichier != NULL){
        for (int numsommet = 0; numsommet < joueur->nb_sommet ; numsommet++)
        {
            fscanf(fichier,"%d %d %d %d %d %d %d", &sommet[numsommet][0],&sommet[numsommet][1], &sommet[numsommet][2], &sommet[numsommet][3], &sommet[numsommet][4], &sommet[numsommet][5], &sommet[numsommet][6]);
        }
        fclose(fichier);
    }
}
void lire_listeChateau(char* save, DonneesJoueur *joueur,Chateaueau listeChateau[]) {
    FILE* fichier = NULL;
    fichier = fopen(save, "r");
    if (fichier != NULL)
    {
        for (int numchateau = 0; numchateau < joueur->nb_chateaueau ; numchateau++)
        {
            printf ("resto du chateau n %d :\n",numchateau);
            printf ("listeChateau[numchateau].nextmaison : %d \n",listeChateau[numchateau].nextmaison);
            fscanf(fichier, "%d %d %d %d %d", &listeChateau[numchateau].numchateau , &listeChateau[numchateau].x, &listeChateau[numchateau].y, &listeChateau[numchateau].capa, &listeChateau[numchateau].nextmaison );
            for (int listemaison = 0; listemaison < listeChateau[numchateau].nextmaison ; listemaison++)
                fscanf(fichier, "%d %d",&listeChateau[numchateau].listeMaisonconnecteau[listemaison].nummaison,&listeChateau[numchateau].listeMaisonconnecteau[listemaison].distance);
        }
        fclose(fichier);
    }

}

void lire_listeCentraleelec(char* save, DonneesJoueur *joueur,Centraleelec listeCentraleelec[]) {
    FILE* fichier = NULL;
    fichier = fopen(save, "r");
    if (fichier != NULL)
    {
        for (int numcentrale = 0; numcentrale < joueur->nb_centraleelec ; numcentrale++)
        {
            fscanf(fichier, "%d %d %d %d %d", &listeCentraleelec[numcentrale].numcentrale , &listeCentraleelec[numcentrale].x, &listeCentraleelec[numcentrale].y, &listeCentraleelec[numcentrale].capa, &listeCentraleelec[numcentrale].nextmaison );
            for (int listemaison = 0; listemaison < listeCentraleelec[numcentrale].nextmaison ; listemaison++)
                fscanf(fichier, "%d %d",&listeCentraleelec[numcentrale].listeMaisonconnectelec[listemaison].nummaison,&listeCentraleelec[numcentrale].listeMaisonconnectelec[listemaison].distance);
        }
        close(fichier);
    }
}

void lire_listeMaison(char* save, DonneesJoueur *joueur,Maison listeMaison[]) {
    FILE* fichier = NULL;
    fichier = fopen(save, "r");
    if(fichier != NULL){
        for (int maison = 0; maison < joueur->nb_maison ; maison++)
            fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &listeMaison[maison].nummaison,&listeMaison[maison].type,&listeMaison[maison].x,&listeMaison[maison].y,&listeMaison[maison].eau1,&listeMaison[maison].disteau1,&listeMaison[maison].capaeau1use,&listeMaison[maison].eau2,&listeMaison[maison].disteau2,&listeMaison[maison].capaeau2use,&listeMaison[maison].elec,&listeMaison[maison].nbhabmax,&listeMaison[maison].nbhab );
        fclose(fichier);
    }
}


//Affichage de la boîte à outils
void afficherMenu() {
    int i, j;
    locate(100,1);
    printf("Boite a outils : \n");
    locate(100,2);
    printf("- 0 : lire la notice \n");
    locate(100,3);
    printf("- 1 : restaurer une sauvegarde \n");
    locate(100,4);
    printf("- 2 : sauvegarder la partie en cours \n");
    locate(100,5);
    printf("- 3 : ajouter un element \n");
    locate(100,6);
    printf("- 4 : visualiser le niveau -1 (eau) \n");
    locate(100,7);
    printf("- 5 : visualiser le niveau -2 (elec) \n");
    locate(100,8);
    printf("- 6 : Sortir du jeux \n");
    locate(100,9);

}


//Affichage des différents éléments que le joueur peut placer
void choixElement() {
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


//Fonction pour la route
void route(int* preds, char** plateau, int choix, DonneesJoueur *joueur, Construction *construction, int** sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
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
            valid_coordonnees(preds, plateau, construction, joueur, sommet, listeMaison, listeChateau, listeCentraleelec);
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
            Sleep(2000);
            choix = 2;// on sort du while si plus assez de ECEflouz
        }
    } while (choix == 1); // Tant que le joueur veut placer des routes
}


//Fonction pour le terrain vague
void terrainVague(int* preds, char** plateau, DonneesJoueur *joueur, Construction *construction, int** sommet,Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
    if(joueur->compteurMonnaie >= construction->cout){
        saisir_coordonnees(construction);
        valid_coordonnees(preds, plateau, construction, joueur, sommet, listeMaison, listeChateau, listeCentraleelec);
    }
    else{ // S'il n'a pas l'argent
        locate(100,23);
        printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire un terrain vague !\n\r");
        Sleep(2000);
    }
}


//Fonction pour le château d'eau
void chateauDeau(int* preds, char** plateau, DonneesJoueur *joueur, Construction *construction, int** sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
    if(joueur->compteurMonnaie >= construction->cout){
        saisir_coordonnees(construction);
        valid_coordonnees(preds,plateau, construction, joueur, sommet, listeMaison, listeChateau, listeCentraleelec);
    }
    else{
        locate(100,23);
        printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire un chateau d'eau !\n\r");
        Sleep(2000);
    }
}


//Fonction pour la centrale électrique
void centraleElectrique(int* preds, char** plateau, DonneesJoueur *joueur, Construction *construction, int** sommet,Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
    if(joueur->compteurMonnaie >= construction->cout){
        saisir_coordonnees(construction);
        valid_coordonnees(preds,plateau, construction, joueur, sommet, listeMaison, listeChateau, listeCentraleelec);
    }
    else{
        locate(100,23);
        printf("Desole ! Vous n'avez pas assez d'ECEflouz pour construire une centrale electrique !\n\r");
        Sleep(2000);
    }
}


//Fonction qui lance la fonction qui place une certaine construction en fonction du choix du joueur
void afficherElement(int* preds, char** plateau, int choix, DonneesJoueur *joueur, Construction *construction, int** sommet, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[]) {
    scanf("%d", &construction->choixBatiment);
    initialisationConstruction(construction);
    switch (construction->choixBatiment) {
        case 1:{
            route(preds, plateau, choix, joueur, construction, sommet, listeMaison, listeChateau, listeCentraleelec);
            break;
        }
        case 2:{
            terrainVague(preds,plateau, joueur, construction, sommet, listeMaison, listeChateau, listeCentraleelec);
            break;
        }
        case 3:{

            centraleElectrique(preds,plateau,  joueur, construction, sommet, listeMaison, listeChateau, listeCentraleelec);
            break;
        }
        case 4:{
            chateauDeau(preds,plateau,  joueur, construction, sommet, listeMaison, listeChateau, listeCentraleelec);
            break;
        }
    }
}


//Fonction qui affiche en continue les données du joueur qui se situent en bas à droite de l'écran
void afficherRessource(DonneesJoueur *joueur, Chateaueau listeChateau[], Centraleelec listeCentraleelec[]){
    locate(92,30);
    printf(" Compteur temporel :  %ld s   ",joueur->compteurTemps);
    locate(92,31);
    printf(" Monnaie :  %d   ",joueur->compteurMonnaie);
    locate(92,32);
    printf(" Nb Habitants : %d ",joueur->nombreDHabitants);
    locate(92,33);
    printf(" Capacite electrique : %d ",joueur->capaciteElectrique);
    locate(92,34);
    printf(" Capacite eau :");
    locate(107,34);
    for (int i = 0; i < joueur->nb_chateaueau; i++){
        printf(" n%d %d/5000 :",i+1,listeChateau[i].capa);
    }
}


/*Récupère le numéro de sommet à partir des coordonnées x et y*/
int checksommet(DonneesJoueur *joueur, int x,int y, int** sommet) {
    for (int i = 0; i<=joueur->nb_sommet;i++){
        if (sommet[i][0]==x && sommet[i][1]==y){
            return i;
        }
    }

}



void majdonnees(DonneesJoueur *joueur, char** plateau, Maison listeMaison[], Chateaueau listeChateau[], Centraleelec listeCentraleelec[],Habitat listeHabitat[]){
    int eaudispo1=0;
    int eaudispo2=0;
    int elecdispo=0;
    int sommeeau = 0;
    int nexthab,actuhab,nexteau,actueau1use,actueau2use,actuelec,nextelec,resthab;
    char predtype,checktype,typeactu,nexttype;
    //char typepred = 'Z';
    joueur->compteurMonnaie = joueur->compteurMonnaie + (10 * joueur->nombreDHabitants);
    for (int nummaison = 0; nummaison < joueur->nb_maison; nummaison++) {
        typeactu=listeMaison[nummaison].type;
        actuhab=listeMaison[nummaison].nbhab;

        if (typeactu != 'G' && listeMaison[nummaison].eau1 != 99)
        {
            for (int i = 0; i < 5; i++){
                if (listeHabitat[i].type == typeactu)
                {
                    nexttype = listeHabitat[i+1].type;
                    actuelec = listeHabitat[i].nbhabitant;

                    nexthab = listeHabitat[i+1].nbhabitant;
                    nexteau = nexthab;
                    nextelec = nexthab;
                }
            }
            // on regarde la dispo en eau et electricite
            if (listeMaison[nummaison].eau1 != 99) eaudispo1=listeChateau[listeMaison[nummaison].eau1].capa;
            if (listeMaison[nummaison].eau2 != 99) eaudispo2=listeChateau[listeMaison[nummaison].eau1].capa;
            if (listeMaison[nummaison].elec != 99) elecdispo=joueur->capaciteElectrique;
            //si il y a un peu d'eau et l'equivalent d'electricitenecessaire , on peut chnager le type
            if ((eaudispo1 + eaudispo2) > 0 && elecdispo >= nextelec-actuelec)
            {

                //if (listeMaison[nummaison].eau1 != 99 && listeMaison[nummaison].elec != 99){
                //eaudispo1=listeChateau[listeMaison[nummaison].eau1].capa;
                actueau1use=listeMaison[nummaison].capaeau1use;
                if (nexteau <= eaudispo1-actuhab)
                {
                    listeMaison[nummaison].type=nexttype;
                    listeMaison[nummaison].nbhabmax=nexthab;
                    listeMaison[nummaison].nbhab=nexthab;
                    listeMaison[nummaison].capaeau1use=listeMaison[nummaison].capaeau1use+nexthab-actueau1use;
                    listeChateau[listeMaison[nummaison].eau1].capa=listeChateau[listeMaison[nummaison].eau1].capa-listeMaison[nummaison].capaeau1use+actueau1use;
                    joueur->capaciteElectrique = joueur->capaciteElectrique - nexthab + actuelec;
                    joueur->nombreDHabitants = joueur->nombreDHabitants + nexthab - actuhab;
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            plateau[listeMaison[nummaison].x-i-1][listeMaison[nummaison].y+j-1] = listeMaison[nummaison].type;

                        }
                    }
                }
                else
                {
                    if (eaudispo1 > 0)
                        // on alimente partiellement avec le chateau 1
                    {
                        listeMaison[nummaison].type=nexttype;
                        listeMaison[nummaison].nbhabmax=nexthab;
                        listeMaison[nummaison].nbhab=listeMaison[nummaison].nbhab+eaudispo1;
                        resthab=nexthab-eaudispo1+actuhab;
                        listeMaison[nummaison].capaeau1use=listeMaison[nummaison].capaeau1use+eaudispo1;
                        listeChateau[listeMaison[nummaison].eau1].capa=listeChateau[listeMaison[nummaison].eau1].capa-listeMaison[nummaison].capaeau1use+actueau1use;
                        joueur->capaciteElectrique = joueur->capaciteElectrique - nexthab + actuelec;
                        joueur->nombreDHabitants = joueur->nombreDHabitants + eaudispo1;
                        for (int i = 0; i < 3; i++) {
                            for (int j = 0; j < 3; j++) {
                                plateau[listeMaison[nummaison].x-i-1][listeMaison[nummaison].y+j-1] = listeMaison[nummaison].type;

                            }
                        }
                    }
                    if (eaudispo2 > 0 && listeMaison[nummaison].eau2 != 99)
                    {
                        // on alimente partiellement le reste avec le chateau 2
                        if(eaudispo2 >= resthab)
                        {
                            listeMaison[nummaison].nbhab=listeMaison[nummaison].nbhab+resthab;
                            listeMaison[nummaison].capaeau2use=listeMaison[nummaison].capaeau2use+resthab;
                            listeChateau[listeMaison[nummaison].eau2].capa=listeChateau[listeMaison[nummaison].eau2].capa-listeMaison[nummaison].capaeau2use+resthab;
                            joueur->nombreDHabitants = joueur->nombreDHabitants + resthab;
                        }
                        else
                        {
                            listeMaison[nummaison].nbhab=listeMaison[nummaison].nbhab+eaudispo2;
                            listeMaison[nummaison].capaeau2use=listeMaison[nummaison].capaeau2use+eaudispo2;
                            listeChateau[listeMaison[nummaison].eau2].capa=listeChateau[listeMaison[nummaison].eau2].capa-listeMaison[nummaison].capaeau2use+eaudispo2;
                            joueur->nombreDHabitants = joueur->nombreDHabitants + eaudispo2;
                        }
                    }
                }
            }
            else{
                // On est dans le cas ouon peut pas faire evoluer le type
                // on regarde si on peut reiquilibrer l'eau
                // si l'on a de l'eau  de dispo et que l'elec est connetee
                if ((eaudispo1 + eaudispo2) > 0 && elecdispo >= 0)
                {
                    //On fait la somme de l'eau des types inferieurs ou egales
                    checktype=listeMaison[nummaison].type;
                    while (checktype != 'T'){
                        for (int nummaisoneau = 0; nummaisoneau < joueur->nb_maison; nummaisoneau++) {
                            if (listeMaison[nummaisoneau].type==checktype){
                                if (listeMaison[nummaisoneau].eau1 == listeMaison[nummaison].eau1 || listeMaison[nummaisoneau].eau1 == listeMaison[nummaison].eau2)
                                    sommeeau = listeMaison[nummaisoneau].capaeau1use + sommeeau;
                                if ((listeMaison[nummaisoneau].eau2 == listeMaison[nummaison].eau1 || listeMaison[nummaisoneau].eau2 == listeMaison[nummaison].eau2)&&listeMaison[nummaisoneau].eau2 !=99)
                                    sommeeau = listeMaison[nummaisoneau].capaeau2use + sommeeau;
                            }
                        }
                        for (int i = 0; i < 5; i++)
                        {
                            if (listeHabitat[i].type == checktype)
                                //{
                                /*if (listeHabitat[i].type != 'T')*/
                                predtype=listeHabitat[i-1].type;
                            //}
                        }
                        checktype=predtype;
                    }
                    //if (checktype != 'T')
                    //checktype=predtype;
                }
                if (sommeeau + eaudispo1 + eaudispo2 >= nexteau)
                {
                    // On peut reiquilibrer
                    int eauarecup;
                    eauarecup=nexteau-eaudispo1-eaudispo2-listeMaison[nummaison].capaeau1use-listeMaison[nummaison].capaeau2use;
                    listeMaison[nummaison].nbhab=listeMaison[nummaison].nbhab+eaudispo1;
                    joueur->nombreDHabitants = joueur->nombreDHabitants + eaudispo1;
                    joueur->capaciteElectrique = joueur->capaciteElectrique - eaudispo1;
                    listeChateau[listeMaison[nummaison].eau1].capa=0;
                    listeMaison[nummaison].nbhab=listeMaison[nummaison].nbhab+eaudispo2;
                    joueur->capaciteElectrique = joueur->capaciteElectrique - eaudispo2;
                    joueur->nombreDHabitants = joueur->nombreDHabitants + eaudispo2;
                    listeChateau[listeMaison[nummaison].eau1].capa=0;
                    checktype=listeMaison[nummaison].type;
                    while (checktype != 'T'){
                        for (int nummaisoneau = 0; nummaisoneau < joueur->nb_maison; nummaisoneau++) {
                            // Je regarde deja si la maison est pas celle que j'essaye de faire evoluer
                            //int eauarecup;
                            //eauarecup=nexteau-eaudispo1-eaudispo2;
                            if (listeMaison[nummaisoneau].nummaison != listeMaison[nummaison].nummaison)
                            {
                                if (listeMaison[nummaisoneau].type==checktype){
                                    // on bascule les habitants et l'eau
                                    //   nexteau
                                    //  actuhab //idem eau actuelle
                                    if (listeMaison[nummaisoneau].eau2 == listeMaison[nummaison].eau1)
                                    {
                                        if (listeMaison[nummaisoneau].capaeau2use <= eauarecup)
                                        {// Si l'on prend totalement l'eau
                                            listeMaison[nummaison].capaeau1use=listeMaison[nummaison].capaeau1use+listeMaison[nummaisoneau].capaeau2use;
                                            listeMaison[nummaison].nbhab = listeMaison[nummaison].nbhab + listeMaison[nummaisoneau].capaeau2use;
                                            listeMaison[nummaisoneau].nbhab = listeMaison[nummaisoneau].nbhab - listeMaison[nummaisoneau].capaeau2use;
                                            listeChateau[listeMaison[nummaisoneau].eau2].listeMaisonconnecteau[nummaisoneau].nummaison = 99;
                                            listeChateau[listeMaison[nummaisoneau].eau2].listeMaisonconnecteau[nummaisoneau].distance = 99;
                                            eauarecup=eauarecup-listeMaison[nummaisoneau].capaeau2use;
                                            listeMaison[nummaisoneau].capaeau2use=0;
                                            listeMaison[nummaisoneau].disteau2 = 0;
                                            listeMaison[nummaisoneau].eau2 = 99;
                                        }
                                        else{// Si l'on prend partiellment l'eau
                                            listeMaison[nummaison].capaeau1use=listeMaison[nummaison].capaeau1use+eauarecup;
                                            listeMaison[nummaison].nbhab = listeMaison[nummaison].nbhab + eauarecup;
                                            listeMaison[nummaisoneau].nbhab = listeMaison[nummaisoneau].nbhab - eauarecup;
                                            listeMaison[nummaisoneau].capaeau2use=listeMaison[nummaisoneau].capaeau2use-eauarecup;
                                            eauarecup=0;
                                            //ajout du reste des chateau a voir
                                        }
                                    }
                                    if (eauarecup!=0 && listeMaison[nummaisoneau].eau2 == listeMaison[nummaison].eau2 && listeMaison[nummaison].eau2 != 99)
                                    {
                                        if (listeMaison[nummaisoneau].capaeau2use <= eauarecup)
                                        {// Si l'on prend totalement l'eau
                                            listeMaison[nummaison].capaeau2use=listeMaison[nummaison].capaeau2use+listeMaison[nummaisoneau].capaeau2use;
                                            listeMaison[nummaison].nbhab = listeMaison[nummaison].nbhab + listeMaison[nummaisoneau].capaeau2use;
                                            listeMaison[nummaisoneau].nbhab = listeMaison[nummaisoneau].nbhab - listeMaison[nummaisoneau].capaeau2use;
                                            //listeChateau[listeMaison[nummaisoneau].eau2].listeMaisonconnecteau[nummaisoneau].nummaison = 99;
                                            //listeChateau[listeMaison[nummaisoneau].eau2].listeMaisonconnecteau[nummaisoneau].distance = 99;
                                            eauarecup=eauarecup-listeMaison[nummaisoneau].capaeau2use;
                                            listeMaison[nummaisoneau].capaeau2use=0;
                                            listeMaison[nummaisoneau].disteau2 = 0;
                                            listeMaison[nummaisoneau].eau2 = 99;
                                        }
                                        else{// Si l'on prend partiellment l'eau
                                            listeMaison[nummaison].capaeau2use=listeMaison[nummaison].capaeau2use+eauarecup;
                                            listeMaison[nummaison].nbhab = listeMaison[nummaison].nbhab + eauarecup;
                                            listeMaison[nummaisoneau].nbhab = listeMaison[nummaisoneau].nbhab - eauarecup;
                                            listeMaison[nummaisoneau].capaeau2use=listeMaison[nummaisoneau].capaeau2use-eauarecup;
                                            eauarecup=0;
                                            //ajout du reste des chateau a voir
                                        }

                                    }
                                    if (eauarecup!=0 && listeMaison[nummaisoneau].eau1 == listeMaison[nummaison].eau1 )
                                    {

                                        if (listeMaison[nummaisoneau].capaeau1use <= eauarecup)
                                        {// Si l'on prend totalement l'eau
                                            listeMaison[nummaison].capaeau1use=listeMaison[nummaison].capaeau1use+listeMaison[nummaisoneau].capaeau1use;
                                            listeMaison[nummaison].nbhab = listeMaison[nummaison].nbhab + listeMaison[nummaisoneau].capaeau1use;
                                            listeMaison[nummaisoneau].nbhab = listeMaison[nummaisoneau].nbhab - listeMaison[nummaisoneau].capaeau1use;
                                            //listeChateau[listeMaison[nummaisoneau].eau1].listeMaisonconnecteau[nummaisoneau].nummaison = 99;
                                            //listeChateau[listeMaison[nummaisoneau].eau1].listeMaisonconnecteau[nummaisoneau].distance = 99;
                                            eauarecup=eauarecup-listeMaison[nummaisoneau].capaeau1use;
                                            listeMaison[nummaisoneau].capaeau1use=0;
                                            listeMaison[nummaisoneau].disteau1 = 0;
                                            listeMaison[nummaisoneau].eau1 = 99;
                                        }
                                        else{// Si l'on prend partiellment l'eau
                                            Sleep(3000);
                                            listeMaison[nummaison].capaeau1use=listeMaison[nummaison].capaeau1use+eauarecup;
                                            listeMaison[nummaison].nbhab = listeMaison[nummaison].nbhab + eauarecup;
                                            listeMaison[nummaisoneau].nbhab = listeMaison[nummaisoneau].nbhab - eauarecup;
                                            listeMaison[nummaisoneau].capaeau1use=listeMaison[nummaisoneau].capaeau1use-eauarecup;
                                            eauarecup=0;
                                            //ajout du reste des chateau a voir
                                        }
                                    }
                                    if (eauarecup!=0 && listeMaison[nummaisoneau].eau1 == listeMaison[nummaison].eau2)
                                    {
                                        if (listeMaison[nummaisoneau].capaeau1use <= eauarecup)
                                        {// Si l'on prend totalement l'eau
                                            listeMaison[nummaison].capaeau2use=listeMaison[nummaison].capaeau2use+listeMaison[nummaisoneau].capaeau1use;
                                            listeMaison[nummaison].nbhab = listeMaison[nummaison].nbhab + listeMaison[nummaisoneau].capaeau1use;
                                            listeMaison[nummaisoneau].nbhab = listeMaison[nummaisoneau].nbhab - listeMaison[nummaisoneau].capaeau1use;
                                            //listeChateau[listeMaison[nummaisoneau].eau1].listeMaisonconnecteau[nummaisoneau].nummaison = 99;
                                            //listeChateau[listeMaison[nummaisoneau].eau1].listeMaisonconnecteau[nummaisoneau].distance = 99;
                                            eauarecup=eauarecup-listeMaison[nummaisoneau].capaeau1use;
                                            listeMaison[nummaisoneau].capaeau1use=0;
                                            listeMaison[nummaisoneau].disteau1 = 0;
                                            listeMaison[nummaisoneau].eau1 = 99;
                                        }
                                        else{// Si l'on prend partiellment l'eau
                                            listeMaison[nummaison].capaeau1use=listeMaison[nummaison].capaeau1use+eauarecup;
                                            listeMaison[nummaison].nbhab = listeMaison[nummaison].nbhab + eauarecup;
                                            listeMaison[nummaisoneau].nbhab = listeMaison[nummaisoneau].nbhab - eauarecup;
                                            listeMaison[nummaisoneau].capaeau1use=listeMaison[nummaisoneau].capaeau1use-eauarecup;
                                            eauarecup=0;
                                            //ajout du reste des chateau a voir
                                        }

                                    }



                                }
                            }
                            if (listeMaison[nummaisoneau].capaeau1use + listeMaison[nummaisoneau].capaeau2use == 0)
                            {
                                listeMaison[nummaisoneau].nbhabmax=0;
                                listeMaison[nummaisoneau].type='T';
                                for (int i = 0; i < 3; i++) {
                                    for (int j = 0; j < 3; j++) {
                                        plateau[listeMaison[nummaisoneau].x-i-1][listeMaison[nummaisoneau].y+j-1] = listeMaison[nummaisoneau].type;

                                    }
                                }

                            }
                        }
                        for (int i = 0; i < 5; i++)
                        {
                            if (listeHabitat[i].type == checktype)
                                //{
                                /*if (listeHabitat[i].type != 'T')*/
                                predtype=listeHabitat[i-1].type;
                            //}
                        }
                        checktype=predtype;
                    }
                    listeMaison[nummaison].type=nexttype;
                    listeMaison[nummaison].nbhabmax=nexteau;
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            plateau[listeMaison[nummaison].x-i-1][listeMaison[nummaison].y+j-1] = listeMaison[nummaison].type;

                        }
                    }
                    Sleep(3000);
                }
            }

        }
    }
}


//Fonction qui permet de lire les règles à partir d'un fichier texte
void lire_regle(FILE* fichier, char* save) {
    fichier = fopen(save, "r");
    if(fichier != NULL){
        char texte[1000];
        while (fgets(texte, 1000, fichier) != NULL){
            printf("%s", texte);
        }
    }
    else{
        printf("Erreur ! Ouverture du fichier des regles impossibles.");
    }
}


/* Procedure de mise a jour du niveau -1 avec liste des chateaux d'eau et des maisons*/
void majniveaueau(DonneesJoueur *joueur, char** niveaueau, int** sommet,  Maison listeMaison[], Chateaueau listeChateau[]) {
    // Mise a jour des routes
    for (int i = 0; i<joueur->nb_sommet;i++){
        niveaueau[sommet[i][0]-1][sommet[i][1]-1] = -36;
    }
    // Mise a jour dea Chateaux d'eau
    for (int numchateau = 0; numchateau < joueur->nb_chateaueau ;numchateau++){
        for (int x = 0; x < 6; x++) {
            for (int j = 0; j < 4; j++) {
                //niveaueau[construction->x-i-1][construction->y+j-1] = 'E';
                niveaueau[listeChateau[numchateau].x-1-x][listeChateau[numchateau].y+j-1] = 'E';
            }
        }
    }
    for (int nummaison = 0; nummaison<joueur->nb_maison;nummaison++){
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                //niveaueau[construction->x-i-1][construction->y+j-1] = 'E';
                niveaueau[listeMaison[nummaison].x-1-i][listeMaison[nummaison].y+j-1] = listeMaison[nummaison].type;
            }
        }
    }
}


/* Procedure de mise a jour du niveau -1 pour faire aparaitre le manque d'eau*/
void checkmanqueeau(DonneesJoueur *joueur, Maison listeMaison[], Chateaueau listeChateau[]) {
    int capa1,capa2;
    for (int nummaison = 0; nummaison<joueur->nb_maison;nummaison++){
        // On regarde si la maison est connect�e au reseau d'eau
        if (listeMaison[nummaison].eau1 == 99){
            //si pas connectee , on la place en rouge
            //color(6, 0);//orange
            color(4, 0);//rouge
            locate(listeMaison[nummaison].y*2+3,listeMaison[nummaison].x);
            printf("%c ", listeMaison[nummaison].type);
        }
        else
        {
            //on regarde si connectee mais occupee partiellement on la place en orange
            if (listeMaison[nummaison].nbhab <  listeMaison[nummaison].nbhabmax){
                color(6, 0);//orange
                locate(listeMaison[nummaison].y*2+3,listeMaison[nummaison].x);
                printf("%c ", listeMaison[nummaison].type);
            }
            // on regarde si la maison peut pas passer sur le prochain type
            if (listeMaison[nummaison].type != 'G'){
                capa1 = listeChateau[listeMaison[nummaison].eau1].capa;
                if (listeMaison[nummaison].eau2 !=99) capa2=listeChateau[listeMaison[nummaison].eau2].capa;
                if (capa1+capa2 == 0){
                    color(6, 0);//orange
                    locate(listeMaison[nummaison].y*2+3,listeMaison[nummaison].x);
                    printf("%c ", listeMaison[nummaison].type);
                }
            }

        }
    }






    color(15, 0);//Blanc
}


/*  Procedure de mise a jour du niveau -2 pour faire aparaitre le manque d'elec*/
void checkmanqueelec(DonneesJoueur *joueur, Maison listeMaison[]) {
    for (int nummaison = 0; nummaison<joueur->nb_maison;nummaison++){
        // On regarde si la maison est connect�e au reseau d'eau
        if (listeMaison[nummaison].elec == 99){
            //si pas connectee , on la place en rouge
            //color(6, 0);//orange
            color(4, 0);//rouge
            locate(listeMaison[nummaison].y*2+3,listeMaison[nummaison].x);
            printf("%c", listeMaison[nummaison].type);
        }
    }
    color(15, 0);//Blanc
}


/* Procedure de mise a jour du niveau -2 avec liste des centrales elec et des maisons*/
void majniveauelec(DonneesJoueur *joueur, char** niveauelec, int** sommet,  Maison listeMaison[], Centraleelec listeCentraleelec[]) {
    // Mise a jour des routes
    for (int i = 0; i<joueur->nb_sommet;i++){
        niveauelec[sommet[i][0]-1][sommet[i][1]-1] = -36;
    }
    // Mise a jour dea Chateaux d'eau
    for (int numcentrale = 0; numcentrale < joueur->nb_centraleelec ;numcentrale++){
        for (int x = 0; x < 6; x++) {
            for (int j = 0; j < 4; j++) {
                //niveauelec[construction->x-i-1][construction->y+j-1] = 'U';
                niveauelec[listeCentraleelec[numcentrale].x-1-x][listeCentraleelec[numcentrale].y+j-1] = 'E';
            }
        }
    }
    for (int nummaison = 0; nummaison<joueur->nb_maison;nummaison++){
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                //niveaueau[construction->x-i-1][construction->y+j-1] = 'U';
                niveauelec[listeMaison[nummaison].x-1-i][listeMaison[nummaison].y+j-1] = listeMaison[nummaison].type;
            }
        }
    }
}


//Fonction pour la couleur des polices (réutilisation du code venant du projet monopoly)
void color(int couleurDuTexte, int couleurDeFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}