#include "GrilleDeJeu.h"

int main(){
    //Affichage console en mode pleine ecran
    keybd_event(VK_MENU,0x38,0,0); //Appuie sur ALT
    keybd_event(VK_RETURN,0x1c,0,0); //Appuie ENTREE
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0); // Relache ENTREE
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0); //Relache ALT
    //Fin Affichage console en mode pleine ecran

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
    afficherPlateau(plateau); // bug clion suite à maj windows donc appelle 2 fois de suite la meme fonction

    afficherMenu();
    afficherRessource(joueur);

    while (choix != '4'){
        fflush (stdout);
        if(kbhit())
        {
            choix=getch();
            switch (choix) {
                case '1' :{
                    lire_fichier_grille(fichier, "grille.txt", plateau);
                    afficherPlateau(plateau);
                    afficherMenu();
                    afficherRessource(joueur);
                    break;
                }
                case '2' :{
                    save_grille(fichier, "grille.txt", plateau);
                    afficherPlateau(plateau);
                    afficherMenu();
                    afficherRessource(joueur);
                    break;
                }
                case '3' :{
                    choixElement();
                    afficherElement(plateau, choix2, x, y, joueur, construction, &i);
                    afficherPlateau(plateau);
                    afficherMenu();
                    afficherRessource(joueur);
                }
            }
        }
    }
    locate(100,36);
    free_plateau(plateau);

    return 0;
}