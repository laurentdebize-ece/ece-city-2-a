#include "GrilleDeJeu.h"

int main(){

    char ** plateau=NULL;
    int x = 0, y = 0;
    int choix = 0;
    int choix2 = 0;
    FILE* fichier = NULL;

    DonneesJoueur joueur;
    Construction construction[nbCases];
    int i = 0;
    joueur.compteurMonnaie = 0;
    initialisationJoueur(joueur);

    AllouerTableau(&plateau);

    creerTableau(plateau);
    afficherPlateau(plateau);
    afficherMenu();

    while (choix != '4'){
        fflush (stdout);
        if(kbhit())
        {
            choix=getch();
            switch (choix) {
                case '1' :{
                    printf("choix 1 : restaurer une sauvegarde\n");
                    lire_fichier_grille(fichier, "save.txt", plateau);
                    afficherPlateau(plateau);
                    afficherMenu();
                    break;
                }
                case '2' :{
                    printf("choix 2 : sauvegarder la partie en cours \n");
                    save_grille(fichier, "save.txt", plateau);
                    afficherPlateau(plateau);
                    afficherMenu();
                    break;
                }
                case '3' :{
                    printf("choix 3 : ajouter un element \n");
                    choixElement();
                    afficherElement(plateau, choix2, x, y, joueur, construction, &i);
                    afficherPlateau(plateau);
                    afficherMenu();
                }
            }
        }
    }

    free_plateau(plateau);

    return 0;
}