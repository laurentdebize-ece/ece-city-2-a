#include "affichage.h"
#include "graphe.h"
#include "compteur.h"


_Noreturn void compteurTemps() {
    int h = 0, m = 0, s = 0, ms = 0;
    while (TRUE) //or we can write 1 instead of TRUE
    {
        printf("       \r %2d : %2d : %2d ", h, m, s);//here \r is used to update the value in a single line
        ms++;
        Sleep(10);//it is approximately 1 millisecond
        if (ms == 99) {
            s++;
            ms = 0;
        }
        if (s == 59) {
            m++;
            s = 0;
            ms = 0;
        }
        if (m == 59) {
            h++;
            m = 0;
            s = 0;
            ms = 0;
        }
        if (h == 24) {
            h = 0;
            m = 0;
            s = 0;
            ms = 0;
        }
    }
}

int main(){
    //Affichage console en mode pleine ecran
    keybd_event(VK_MENU,0x38,0,0); //Appuie sur ALT
    keybd_event(VK_RETURN,0x1c,0,0); //Appuie ENTREE
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0); // Relache ENTREE
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0); //Relache ALT
    //Fin Affichage console en mode pleine ecran


    int** sommet = NULL;
    char** plateau = NULL;
    int choix = 0;
    int choix2 = 0;
    FILE* fichier = NULL;

    Graphe* g;
    int *preds=(int*)malloc(g->ordre*sizeof(int));

    DonneesJoueur joueur;
    Construction construction;

    initialisationJoueur(&joueur);
    initialisationConstruction(&construction);

    AllouerTableau(&plateau);
    AllouerSommet(&sommet);
    InitialisationSommet(sommet);

    creerTableau(plateau);
    afficherPlateau(plateau);
    afficherPlateau(plateau); // bug clion suite à maj windows donc appelle 2 fois de suite la meme fonction

    afficherMenu();
    afficherRessource(&joueur);


    while (choix != '4'){
        fflush (stdout);
        if(kbhit())
        {
            choix=getch();
            switch (choix) {
                case '1' :{
                    lire_fichier_grille(fichier, "grille.txt", plateau);
                    lire_DonneesJoueur("DonneesJoueur.txt", &joueur);
                    afficherPlateau(plateau);
                    afficherMenu();
                    afficherRessource(&joueur);
                    break;
                }
                case '2' :{
                    save_grille(fichier, "grille.txt", plateau);
                    save_DonneesJoueur("DonneesJoueur.txt", &joueur);
                    afficherPlateau(plateau);
                    afficherMenu();
                    afficherRessource(&joueur);
                    break;
                }
                case '3' :{
                    choixElement();
                    afficherElement(plateau, choix2, &joueur, &construction, sommet);
                    afficherPlateau(plateau);
                    afficherMenu();
                    afficherRessource(&joueur);
                    break;
                }
                case '5' :{
                    printf("\n\n\n\n ADJACENCE : \n") ;
                    for (int boucle2 = 0; boucle2 < 10; boucle2++) {
                        printf("x = %d :: " ,sommet[boucle2][0]);
                        printf("y = %d :: " ,sommet[boucle2][1]);
                        printf("numsommet = %d :: " ,sommet[boucle2][2]);
                        printf("Adj1 = %d :: " ,sommet[boucle2][3]);
                        printf("Adj2 = %d :: " ,sommet[boucle2][4]);
                        printf("Adj3 = %d :: " ,sommet[boucle2][5]);
                        printf("Adj4 = %d \n" ,sommet[boucle2][6]);
                    }
                    g=charge_graphe(&joueur, sommet);
                    int s0;
                    printf("choisissez le sommet initial\n");
                    do {
                        scanf("%d", &s0);
                    } while (s0 < 0 || s0 > g->ordre);


                    printf("\nBFS\n\n");
                    BFS(g,preds,s0);
                    affichage(preds,s0,g);
                    break;
                }
            }
        }
    }
    locate(100,36);
    free_plateau(plateau);

    return 0;
}