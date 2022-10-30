//
// Created by cleme on 30/10/2022.
//

#include "graphe.h"

pSommet* CreerArete(pSommet* sommet,int s1,int s2,int distance)
{
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->distance=distance;
        Newarc->arc_suivant=NULL;
        sommet[s1]->arc=Newarc;
        return sommet;
    }

    else
    {
        pArc temp=sommet[s1]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->distance=distance;
        Newarc->arc_suivant=NULL;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            Newarc->distance=temp->distance;
            temp->sommet=s2;
            temp->distance=distance;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

Graphe* CreerGraphe(int ordre,FILE * ifs)
{
    char* lettre;
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));


    for(int i=0; i<ordre; i++)
    {

        fscanf(ifs,"%s",lettre);


        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
    }
    return Newgraphe;
}

Graphe * lire_graphe(char * nomFichier) {
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

    for (int j = 0; j<ordre;j++) {
        for (int i = 0; i < ordre; ++i) {
            fscanf(ifs, "%d",&poids);
            s1=j;
            s2=i;
            if(poids !=0) {
                graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, poids);
            }
        }
    }
    return graphe;
}