#include "GrilleDeJeu.h"
#include "BoiteAOutils.h"

int main() {

    DonneesJoueur joueur;
    joueur.compteurMonnaie = 0;
    Construction construction[nbCases]; //Faire une allocation dynamique ?
    int ordreDeConstruction = 0;
    char **plateau = NULL;
    int x = 0, y = 0, i = 0;

    int choix = 0;

    joueur = initialisationJoueur(joueur);
    initialisationConstruction(*construction);

    AllouerTableau(&plateau);

    creerTableau(plateau);

    afficherBoite(joueur, construction, &i, plateau);

    //afficherPlateau(plateau);

    /*while (choix != 1) {
        saisir_coordonnees(&x, &y, &element);
        valid_coordonnees(x, y, element, plateau);
        afficherPlateau(plateau);
        printf("Veux-tu placer un autre element ? (0 : oui, 1 : non)\n");
        scanf("%d", &choix);
    }*/


    /*
    Graphe * g=lire_graphe("graphe1_TP2.txt");  // AJOUTER LE BON FICHIER TXT
    int s0;
    int *preds=(int*)malloc(g->ordre*sizeof(int));
    viabilite(g,preds,s0);
     */

    free_plateau(plateau);

    compteur();  // PERMET D'AFFICHER LE TEMPS QUE DURE LE PROGRAMME. A MODIFIER POUR LES CYCLES!!!!

    return 0;

}