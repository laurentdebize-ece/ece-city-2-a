
#include "menuPrincipal.h"

void menuPrincipal(){
    FILE *fichier = NULL;
    int choixMenu = 0;

    locate(100, 20);
    printf("ECE CITY");
    getch();
    locate(90, 10);
    printf("QUE VOULEZ VOUS FAIRE ?");
    locate(74, 14);
    printf("1.MODE COMMUNISTE");
    locate(110, 14);
    printf("2.MODE CAPITALISTE");
    locate(92, 20);
    printf("3.REGLES DU JEU");
    printf("\n");
    locate(92, 22);
    fflush(stdout);
    scanf("%d", &choixMenu);
    //getch();

    switch (choixMenu) {
        case 1 :{
            locate(91, 25);
            printf("JEU EN MODE COMMUNISTE\n");
            getch();
            nouvellePartie();
            break;
        }
        case 2 :{
            locate(91, 25);
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
