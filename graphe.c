#include "graphe.h"

pSommet *CreerArete(pSommet *sommet, int s1, int s2, int distance) {
    if (sommet[s1]->arc == NULL) {
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->distance = distance;
        Newarc->arc_suivant = NULL;
        sommet[s1]->arc = Newarc;
        return sommet;
    } else {
        pArc temp = sommet[s1]->arc;
        while (temp->arc_suivant != NULL) {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->distance = distance;
        Newarc->arc_suivant = NULL;

        if (temp->sommet > s2) {
            Newarc->arc_suivant = temp->arc_suivant;
            Newarc->sommet = temp->sommet;
            Newarc->distance = temp->distance;
            temp->sommet = s2;
            temp->distance = distance;
            temp->arc_suivant = Newarc;
            return sommet;
        }

        temp->arc_suivant = Newarc;
        return sommet;
    }
}

Graphe *CreerGraphe(int ordre, FILE *ifs) {
    char *lettre;
    Graphe *Newgraphe = (Graphe *) malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet *) malloc(ordre * sizeof(pSommet));


    for (int i = 0; i < ordre; i++) {

        fscanf(ifs, "%s", lettre);


        Newgraphe->pSommet[i] = (pSommet) malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur = i;
        Newgraphe->pSommet[i]->arc = NULL;
    }
    return Newgraphe;
}

Graphe *lire_graphe(char *nomFichier) {
    Graphe *graphe;
    FILE *ifs = fopen(nomFichier, "r");
    int ordre, s1, s2, poids;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &ordre);

    graphe = CreerGraphe(ordre, ifs); // creer le graphe d'ordre sommets
    graphe->ordre = ordre;

    for (int j = 0; j < ordre; j++) {
        for (int i = 0; i < ordre; ++i) {
            fscanf(ifs, "%d", &poids);
            s1 = j;
            s2 = i;
            if (poids != 0) {
                graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, poids);
            }
        }
    }
    return graphe;
}

void parcoursDFS(Graphe *graphe, int sommet, int s0, int *preds) {

    int fin = 0;
    while (fin != 1) {
        if (graphe->pSommet[sommet]->couleur != 2 && graphe->pSommet[sommet]->couleur != 1) {

            graphe->pSommet[sommet]->couleur = 1;
            graphe->pSommet[sommet]->debut = graphe->date;
            graphe->date++;


            struct Arc *temp = graphe->pSommet[sommet]->arc;
            while (temp != NULL) {

                if (graphe->pSommet[temp->sommet]->couleur != 2 && graphe->pSommet[temp->sommet]->couleur != 1) {
                    preds[temp->sommet] = sommet;
                    parcoursDFS(graphe, temp->sommet, s0, preds);
                }
                temp = temp->arc_suivant;
            }

            graphe->pSommet[sommet]->couleur = 2;
            graphe->pSommet[sommet]->finxplo = graphe->date;
            graphe->date++;
        }
        fin = 1;
    }
}

void DFS(Graphe *graphe, int *preds, int s0) {

    int sommet;

    sommet = s0;
    graphe->date = 0;

    parcoursDFS(graphe, sommet, s0, preds);
}

void eulerien(Graphe *g, int nb) {
    int degimpair = 0;
    int k;

    for (int i = 0; i < g->ordre; i++) {
        if (g->pSommet[i]->connexe == nb) {
            k = 0;
            struct Arc *temp = g->pSommet[i]->arc;
            while (temp != NULL) {
                if (g->pSommet[i]->connexe == nb) {
                    k = k + 1;
                }
                temp = temp->arc_suivant;
            }
            if (k % 2 != 0) {
                degimpair++;
            }
        }
    }

    if (degimpair == 0 || degimpair == 2) {
        printf("chaine %d eulerienne\n\n", nb);
    } else {
        printf("chaine %d pas chaine eulerienne\n\n", nb);
    }
}

void viabilite(Graphe *graphe, int *preds, int s0) {

    int *BFSafaire = (int *) malloc(graphe->ordre * sizeof(int));
    int j = 0;
    int nbconnexe = 1;
    int l = 1;

    printf("connexité :");
    for (int i = 0; i < graphe->ordre; i++) {
        if (preds[i] == -1 && i != s0) {
            BFSafaire[j] = i;
            j++;
        } else {
            printf(" %d", i);
            graphe->pSommet[i]->connexe = 1;

        }
    }
    printf("\n");
    for (int i = 2; i < j + 2; i++) {
        if (graphe->pSommet[BFSafaire[i]]->couleur == 0) {
            DFS(graphe, preds, BFSafaire[i]);
            printf("connexité :");
            for (int k = 0; k < graphe->ordre; k++) {
                if ((preds[k] != -1 || k == BFSafaire[i]) && graphe->pSommet[k]->connexe == -1) {
                    printf(" %d", k);
                    graphe->pSommet[k]->connexe = i;
                    if (l != i) {
                        nbconnexe++;
                        l = i;
                    }
                }
            }
            printf("\n");
        }
    }
    printf("\n");
    for (int i = 1; i <= nbconnexe; i++) {
        eulerien(graphe, i);
    }

    printf("\n\n");

    printf("\n");

}



