#include "nouvellePartie.h"

void nouvellePartie(){

    int** sommet = NULL;


    char** plateau = NULL;
    char** niveaueau = NULL;
    char** niveauelec = NULL;
    int choix = 0;
    int choix2 = 0;
    FILE* fichier = NULL;


    Chateaueau listeChateau[20];
    Maison listeMaison[30];
    Centraleelec listeCentraleelec[30];
    Habitat listeHabitat[5];


    clock_t t1, t2;
    t1 = clock();

    DonneesJoueur joueur;
    Construction construction;
    paramclock majclock;

    initialisationJoueur(&joueur);
    initialisationConstruction(&construction);


    AllouerTableau(&plateau);
    AllouerTableau(&niveaueau);
    AllouerTableau(&niveauelec);

    AllouerSommet(&sommet);
    InitialisationSommet(sommet);

    Initialisationmaison(listeMaison);
    initialisationChateaueau(listeChateau);
    initialisationCentraleelec(listeCentraleelec);

    initialisationmajclock(&majclock);

    creerTableau(plateau);
    creerTableau(niveaueau);
    creerTableau(niveauelec);
    afficherPlateau(plateau);
    afficherPlateau(plateau); // bug clion suite à maj windows donc appelle 2 fois de suite la meme fonction

    ChargeHabitat(fichier,listeHabitat);// charge la correspondance type batiment / nbhabitant epuis un fichier

    afficherMenu();
    afficherRessource(&joueur, listeChateau, listeCentraleelec);

    Graphe * g=charge_graphe(&joueur, sommet);
    int s0;
    int *preds2=(int*)malloc(g->ordre*sizeof(int));


    while (choix != '6'){
        check_time_15(&majclock, &joueur);
        if (majclock.majdon == 1){
            majdonnees( &joueur,  plateau, listeMaison, listeChateau, listeCentraleelec,listeHabitat);
            majclock.majdon = 0;
            afficherPlateau(plateau);
            afficherMenu();
        }


        //t1=check_time_15(t1, t2, &joueur);
        fflush (stdout);
        afficherRessource(&joueur, listeChateau, listeCentraleelec);
        if(kbhit())
        {
            choix=getch();
            switch (choix) {
                case '0' :{
                    lire_regle(fichier, "../regles.txt");
                    Sleep(3000);
                    break;
                }
                case '1' :{
                    lire_fichier_grille(fichier, "../grille.txt", plateau);
                    lire_DonneesJoueur("../DonneesJoueur.txt", &joueur);
                    lire_sommet("../ListeSommet.txt", &joueur,sommet);
                    lire_listeChateau("../ListeChateau.txt",&joueur,listeChateau);
                    lire_listeCentraleelec("../listeCentraleelec.txt",&joueur,listeCentraleelec);
                    lire_listeMaison("../listeMaison.txt",&joueur,listeMaison);
                    afficherPlateau(plateau);
                    afficherMenu();
                    afficherRessource(&joueur, listeChateau, listeCentraleelec);
                    break;
                }
                case '2' :{
                    save_grille(fichier, "../grille.txt", plateau);
                    save_DonneesJoueur("../DonneesJoueur.txt", &joueur);
                    save_sommet("../ListeSommet.txt", &joueur,sommet);
                    save_listeChateau("../ListeChateau.txt",&joueur,listeChateau);
                    save_listeCentraleelec("../listeCentraleelec.txt",&joueur,listeCentraleelec);
                    save_listeMaison("../listeMaison.txt",&joueur,listeMaison);
                    afficherPlateau(plateau);
                    afficherMenu();
                    afficherRessource(&joueur, listeChateau, listeCentraleelec);
                    break;
                }
                case '3' :{
                    choixElement();
                    afficherElement(preds2, plateau, choix2, &joueur, &construction, sommet, listeMaison, listeChateau, listeCentraleelec);
                    afficherPlateau(plateau);
                    afficherMenu();
                    afficherRessource(&joueur, listeChateau, listeCentraleelec);
                    break;
                }
                case '4' :{
                    int clavier = 0;
                    majniveaueau(&joueur,niveaueau,sommet,listeMaison,listeChateau);
                    afficherPlateau(niveaueau);
                    checkmanqueeau(&joueur,listeMaison,listeChateau);
                    do{
                        while(1) //vidage du kbhit
                        {
                            if(kbhit())
                            {
                                clavier = 1;
                                break;
                            }
                            else
                            {
                                afficherRessource(&joueur, listeChateau, listeCentraleelec);
                            }
                        }
                    }while (clavier == 0);
                    break;
                }
                case '5' :{
                    int clavier = 0;
                    majniveauelec(&joueur,niveauelec,sommet,listeMaison,listeCentraleelec);
                    afficherPlateau(niveauelec);
                    checkmanqueelec(&joueur, listeMaison);
                    do{
                        while(1) //vidage du kbhit
                        {
                            if(kbhit())
                            {
                                clavier = 1;
                                break;
                            }
                            else
                            {
                                afficherRessource(&joueur, listeChateau, listeCentraleelec);
                            }
                        }
                    }while (clavier == 0);
                    break;
                }
            }
        }
    }
    locate(100,36);
    free_plateau(plateau);
}
