#include <stdio.h>

void plateau(int ligne, int colonne){
    for (int i = 0; i < colonne; i++) {
        printf("__");
    }
    printf("_");
    printf("\n");
    for (int i = 0; i < ligne; i++) {
        //printf("| ");
        for (int j = 0; j < colonne; j++) {
            printf("|_");
        }
        printf("|");
        printf("\n");
    }
}

int main() {
    int ligne = 35;
    int colonne = 45;

    plateau(ligne, colonne);

    return 0;
}