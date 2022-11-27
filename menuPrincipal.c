#include "menuPrincipal.h"

void menuPrincipal() {
    FILE *fichier = NULL;
    int choixMenu = 0;

    locate(70, 5);
    //color(15, 12);
    printf("ECE CITY");
    //getch();
    //color(12, 0);
    locate(64, 10);
    printf("QUE VOULEZ VOUS FAIRE ?");
    locate(52, 15);
    printf("1.MODE COMMUNISTE");
    locate(80, 15);
    printf("2.MODE CAPITALISTE");
    locate(67, 20);
    printf("3.REGLES DU JEU");
    //printf("\n");
    locate(92, 22);
    //color(15, 0);
    fflush(stdout);
    scanf("%d", &choixMenu);
    //getch();

    switch (choixMenu) {
        case 1 : {
            locate(90, 32);
            printf("JEU EN MODE COMMUNISTE\n");
            nouvellePartie();
            break;
        }
        case 2 : {
            locate(90, 32);
            printf("JEU EN MODE CAPITALISTE\n");
            nouvellePartie();
            break;
        }
        case 3 : {
            lire_regle(fichier, "../regles.txt");
            menuPrincipal();
            break;
        }

        default: {
            printf("\t\t\t\t\t\tCe que vous avez entre ne correspond pas aux options proposees. Veuillez entrer un numero correspondant a une option.\n");
            printf("\n");
            menuPrincipal();
        }
    }
}
