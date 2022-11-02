#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graphe.h"

#define nbLignes 35
#define nbColonnes 45


void AllouerTableau(char ***plateau)
{
    *plateau = malloc(nbLignes * sizeof(char*));
    for(int i=0 ; i<nbLignes ; i++)
        *(*plateau+i) = malloc(nbColonnes * sizeof(char));

}

void creerTableau(char **plateau){
    int i, j;

    for (i = 0; i < nbLignes; i++) {
        for (j = 0; j < nbColonnes; j++) {
            plateau[i][j] = '.';
        }
    }
}

void saisir_coordonnees(int *x, int *y,char* element)
{
    printf("Saisissez des coordonnees :\n");
    int ret, continuer;
    do{
        continuer = 0;
        printf("x : \n");
        ret = scanf("%d", x);

        if(ret != 1 || *x <= 0 || *x >= 35)
            continuer = 1;

        while(ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    }while(continuer);

    do{
        continuer = 0;
        printf("y : \n");
        ret = scanf("%d", y);
        //*y = modifier

        if(ret != 1 || *y <= 0 || *y >= 45)
            continuer = 1;

        while(ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    }while(continuer);

    do{
        continuer = 0;
        printf("element : \n");
        ret = scanf("%c", element);

        if(ret != 1)
            continuer = 1;

        while(ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    }while(continuer);

}

void placer_bloc(char **plateau, char element, int x, int y){
    if(element == 'r' || element == 'R'){
        plateau[x-1][y-1] = -36;
    }
    else if(element == 'm' || element == 'M'){
        plateau[x-1][y-1] = 'M', plateau[x-1][y] = 'M', plateau[x-1][y+1] = 'M',
        plateau[x-2][y-1] = 'M', plateau[x-2][y] = 'M', plateau[x-2][y+1] = 'M',
        plateau[x-3][y-1] = 'M' ,plateau[x-3][y] = 'M', plateau[x-3][y+1] = 'M';
    }
    else if(element == 'c' || element == 'C'){
        plateau[x-1][y-1] = 'C', plateau[x-1][y] = 'C', plateau[x-1][y+1] = 'C', plateau[x-1][y+2] = 'C', plateau[x-1][y+3] = 'C', plateau[x-1][y+4] = 'C',
        plateau[x-2][y-1] = 'C', plateau[x-2][y] = 'C', plateau[x-2][y+1] = 'C', plateau[x-2][y+2] = 'C', plateau[x-2][y+3] = 'C', plateau[x-2][y+4] = 'C',
        plateau[x-3][y-1] = 'C' ,plateau[x-3][y] = 'C', plateau[x-3][y+1] = 'C', plateau[x-3][y+2] = 'C', plateau[x-3][y+3] = 'C', plateau[x-3][y+4] = 'C',
        plateau[x-4][y-1] = 'C' ,plateau[x-4][y] = 'C', plateau[x-4][y+1] = 'C', plateau[x-4][y+2] = 'C', plateau[x-4][y+3] = 'C', plateau[x-4][y+4] = 'C';
    }
    //plateau[x-1][y-1] = element;
}

void valid_coordonnees(int x, int y, char element, char** plateau){

    int verif = 0;

    while (verif != 1){
        if((element == 'm' || element == 'M') && x < 3){
            saisir_coordonnees(&x,&y,&element);
            //placer_bloc(plateau, element, x, y);
        }
        else if((element == 'c' || element == 'C') && x < 4){
            saisir_coordonnees(&x,&y,&element);
            //placer_bloc(plateau, element, x, y);
        }
        else{
            placer_bloc(plateau, element, x, y);
            verif = 1;
        }
    }
}

void afficherPlateau(char **plateau){
    int i, j;
    printf("\n");
    printf("           5         10        15        20        25        30        35        40        45\n");
    for(i = 0; i < nbLignes; i++)
    {
        if(i+1<10){
            printf("%d  ",i+1);
        }
        else{
            printf("%d ",i+1);
        }

        for(j = 0; j < nbColonnes; j++){
            printf("%c ", plateau[i][j]);
            //printf("%c ", '.');
        }
        printf("\n");
    }
}

void free_plateau(char **plateau)
{
    for(int i=0 ; i<nbLignes ; i++)
        free(plateau[i]);
    free(plateau);

}


void compteur(){     // A MODIFIER POUR LES CYCLES
    clock_t temps;
    srand(time(NULL));
    temps = clock();
    printf("%f", (double)temps/CLOCKS_PER_SEC);
}


int main(){

    char ** plateau=NULL;
    int x = 0, y = 0;
    char element;

    AllouerTableau(&plateau);
    //printf("%c", -36); servira à créer la route

    creerTableau(plateau);

    saisir_coordonnees(&x,&y,&element);
    valid_coordonnees(x, y, element, plateau);


    /*
    Graphe * g=lire_graphe("graphe1_TP2.txt");  // AJOUTER LE BON FICHIER TXT
    int s0;
    int *preds=(int*)malloc(g->ordre*sizeof(int));
    viabilite(g,preds,s0);
     */



    afficherPlateau(plateau);
    free_plateau(plateau);

    compteur();  // PERMET D'AFFICHER LE TEMPS QUE DURE LE PROGRAMME. A MODIFIER POUR LES CYCLES!!!!

    return 0;

}