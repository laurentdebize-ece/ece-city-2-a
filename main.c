#include "graphe.h"
#include "affichage.h"
#include "compteur.h"

int main() {
    //Affichage console en mode pleine ecran
    keybd_event(VK_MENU, 0x38, 0, 0); //Appuie sur ALT
    keybd_event(VK_RETURN, 0x1c, 0, 0); //Appuie ENTREE
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0); // Relache ENTREE
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); //Relache ALT
    //Fin Affichage console en mode pleine ecran

    color(15,0); //Couleur de fond et de police du texte

    //Déclaration de variables
    int **sommet = NULL;
    int **maison = NULL;
    //int** chateaueau = NULL;
    int **centraleelec = NULL;

    char **plateau = NULL;
    int choix = 0;
    int choix2 = 0;
    FILE *fichier = NULL;

    struct Chateaueau listeChateau[20];
    struct Maisonconnect listeMaisonconnecteau[30];
    struct Maisonconnect listeMaisonconnectelec[30];
    struct Maison listeMaison[30];
    struct Centraleelec listeCentraleelec[30];
    struct Habitat listeHabitat[5];

    clock_t t1, t2;
    t1 = clock();

    DonneesJoueur joueur;
    Construction construction;
    paramclock majclock;

    //Initialisation des données joueur et constructions
    initialisationJoueur(&joueur);
    initialisationConstruction(&construction);

    //Allocation de la grille
    AllouerTableau(&plateau);

    //Allocation et initialisation des sommets pour la théorie des graphes
    AllouerSommet(&sommet);
    InitialisationSommet(sommet);

    //Initialisation de chaque type de construction
    Initialisationmaison(listeMaison);
    initialisationChateaueau(listeChateau);
    initialisationCentraleelec(listeCentraleelec);

    //Initialisation compteur temps du jeu
    initialisationmajclock(&majclock);

    //Création de la grille et son affichage
    creerTableau(plateau);
    afficherPlateau(plateau);
    afficherPlateau(plateau);
    afficherPlateau(plateau); // bug clion suite à maj windows donc appelle 3 fois de suite la meme fonction

    ChargeHabitat(fichier, listeHabitat);// charge la correspondance type batiment / nbhabitant depuis un fichier

    //Affichage des actions du joueur et des données
    afficherMenu();
    afficherRessource(&joueur, listeChateau, listeCentraleelec);

    //Création et chargement du graphe
    Graphe *g = charge_graphe(&joueur, sommet);
    int s0;
    int *preds2 = (int *) malloc(g->ordre * sizeof(int));

    while (choix != '4') {
        check_time_15(&majclock, &joueur);
        if (majclock.majdon == 1) {
            majdonnees(&joueur, plateau, listeMaison, listeChateau, listeCentraleelec, listeHabitat);
            majclock.majdon = 0;
            afficherPlateau(plateau);
            afficherMenu();
        }

        fflush(stdout);
        afficherRessource(&joueur, listeChateau, listeCentraleelec);
        if (kbhit()) {
            choix = getch();
            switch (choix) {
                case '1' : {
                    lire_fichier_grille(fichier, "grille.txt", plateau);
                    lire_DonneesJoueur("DonneesJoueur.txt", &joueur);
                    afficherPlateau(plateau);
                    afficherMenu();
                    afficherRessource(&joueur, listeChateau, listeCentraleelec);
                    break;
                }
                case '2' : {
                    save_grille(fichier, "grille.txt", plateau);
                    save_DonneesJoueur("DonneesJoueur.txt", &joueur);
                    afficherPlateau(plateau);
                    afficherMenu();
                    afficherRessource(&joueur, listeChateau, listeCentraleelec);
                    break;
                }
                case '3' : {
                    choixElement();
                    afficherElement(preds2, plateau, choix2, &joueur, &construction, sommet, listeMaison, listeChateau, listeCentraleelec);
                    afficherPlateau(plateau);
                    afficherMenu();
                    afficherRessource(&joueur, listeChateau, listeCentraleelec);
                    break;
                }
                case '5' : {
                    Graphe *g = charge_graphe(&joueur, sommet);
                    int s0 = 3;
                    int s1 = 0;
                    printf("choisissez le sommet initial\n");
                    do {
                        scanf("%d", &s0);
                    } while (s0 < 0 || s0 > g->ordre);
                    break;
                }
                case '6' : {
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            printf("\n\n=========");
                            printf("numchateau %d : ", listeChateau[i].numchateau);
                            printf("x %d : ", listeChateau[i].x);
                            printf("y %d : ", listeChateau[i].y);
                            printf("capa %d : ", listeChateau[i].capa);
                            printf("con1nummaison : %d", listeChateau[i].listeMaisonconnecteau[j].nummaison);
                            printf("dist : %d", listeChateau[i].listeMaisonconnecteau[j].distance);
                            printf("\n\n=========");
                        }
                    }
                    Sleep(10000);
                }
                case '7' : {
                    printf("\n\n");
                    for (int i = 0; i < 4; i++) {
                        printf("nummaison : %d ,", listeMaison[i].nummaison);
                        printf("type : %c ,: ", listeMaison[i].type);
                        printf("x : %d ,", listeMaison[i].x);
                        printf("y : %d ,", listeMaison[i].y);
                        printf("eau1 : %d ,", listeMaison[i].eau1);
                        printf("eau2 : %d ,", listeMaison[i].eau2);
                        printf("elec : %d ,", listeMaison[i].elec);
                        printf("nbhabmax : %d ,", listeMaison[i].nbhabmax);
                        printf("nbhab : %d ,", listeMaison[i].nbhab);
                        printf("\n\n=========");
                    }
                    Sleep(3000);
                }
                case '8' : {
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 4; j++) {
                            printf("\n\n=========");
                            printf("numcentrale %d : ", listeCentraleelec[i].numcentrale);
                            printf("x %d : ", listeCentraleelec[i].x);
                            printf("y %d : ", listeCentraleelec[i].y);
                            printf("capa %d : ", listeCentraleelec[i].capa);
                            printf("con1nummaison : %d", listeCentraleelec[i].listeMaisonconnectelec[j].nummaison);
                            printf("dist : %d", listeCentraleelec[i].listeMaisonconnectelec[j].distance);
                            printf("\n\n=========");
                        }
                    }
                    Sleep(10000);
                }
            }
        }
    }
    locate(100, 36);
    free_plateau(plateau);

    return 0;
}
