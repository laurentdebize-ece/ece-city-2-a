#include <stdio.h>
#include <stdlib.h>

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
        printf("x : ");
        ret = scanf("%d", x);

        if(ret != 1 || *x <= 0 || *y >= 35)
            continuer = 1;

        while(ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    }while(continuer);

    do{
        continuer = 0;
        printf("y : ");
        ret = scanf("%d", y);
        //*y = modifier

        if(ret != 1 || *y <= 0 || *y >= 45)
            continuer = 1;

        while(ret != '\n' && ret != EOF)  // vide le buffer
            ret = getchar();

    }while(continuer);

    do{
        continuer = 0;
        printf("element : ");
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
    //plateau[x-1][y-1] = element;
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



int main(){

    char ** plateau=NULL;
    int x = 0, y = 0;
    char element = -36;

    AllouerTableau(&plateau);
    //printf("%c", -36); servira à créer la route

    creerTableau(plateau);

    saisir_coordonnees(&x,&y,&element);
    placer_bloc(plateau, element,x,y);

    //plateau[5][6] = 'M';
    //plateau[6][6] = -36;
    afficherPlateau(plateau);
    free_plateau(plateau);
    return 0;

}