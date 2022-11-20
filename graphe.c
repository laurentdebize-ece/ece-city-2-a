#include "graphe.h"

void afficher_successeurs(pSommet * sommet, int num) {

    printf(" sommet %d :\n",num);

    pArc arc=sommet[num]->arc;

    while(arc!=NULL)
    {
        printf("%d ",arc->sommet);
        arc=arc->arc_suivant;
    }

}

// Ajouter l'arete entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2) {
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
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
        Newarc->arc_suivant=NULL;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            temp->sommet=s2;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

// creer le graphe
Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
    }
    return Newgraphe;
}

Graphe* charge_graphe(DonneesJoueur *joueur, int **sommet) {
    Graphe* graphe;
    int taille, orientation, ordre, s1, s2;

    ordre=joueur->nb_sommet;
    printf("ordre joueur :%d \n",ordre);

    graphe=CreerGraphe(ordre); // creer le graphe d'ordre sommets
    taille=0;
    for (int ligne=0; ligne<ordre; ++ligne)
    {
        for (int boucleadj = 3; boucleadj <6 ; boucleadj++)
        {
            if (sommet[ligne][boucleadj] != 0)
            {
                printf("s1 : %d --> s2 : %d \n",sommet[ligne][2],sommet[ligne][boucleadj]);
                graphe->pSommet=CreerArete(graphe->pSommet, sommet[ligne][2], sommet[ligne][boucleadj]);
                graphe->pSommet=CreerArete(graphe->pSommet, sommet[ligne][boucleadj], sommet[ligne][2]);
                taille++;
                //break;
            }
        }
    }
    printf("taille :%d \n",taille);

    sleep(5);

    orientation = 0;

    graphe->orientation=orientation;
    graphe->ordre=ordre;

    // creer les aretes du graphe
    /*  for (int i=0; i<taille; ++i)
      {
          fscanf(ifs,"%d%d",&s1,&s2);
          graphe->pSommet=CreerArete(graphe->pSommet, s1, s2);

          if(!orientation)
              graphe->pSommet=CreerArete(graphe->pSommet, s2, s1);
      }*/

    return graphe;
}

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe)
{
    printf("graphe\n");

    if(graphe->orientation)
        printf("oriente\n");
    else
        printf("non oriente\n");

    printf("ordre = %d\n",graphe->ordre);

    printf("listes d'adjacence :\n");

    for (int i=0; i<graphe->ordre; i++)
    {
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }

}

void enfiler(t_file *f,int num) {
    t_maillon* tmp= malloc(sizeof(t_maillon));
    tmp->num=num;
    tmp->suiv=NULL;

    if(f->tete==NULL){
        f->tete=tmp;
        f->fin=tmp;
    }
    else{
        f->fin->suiv=tmp;
        f->fin=tmp;

    }

}

int defiler(t_file *f) {

    t_maillon* tmp=f->tete;
    if(f->tete == f->fin){
        f->fin=NULL;
        f->tete=NULL;
    }
    else {
        f->tete = f->tete->suiv;
    }
    int num= tmp->num;
    free(tmp);

    return num;
}

int BFS(Graphe* graphe,int *preds,int s0) {
    t_file f;
    f.tete = f.fin = NULL;

    for (int i = 0; i < graphe->ordre; i++) {
        graphe->pSommet[i]->couleur = 0;
    }


    for (int i = 0; i < graphe->ordre; i++) {
        preds[i] = -1;
    }



    enfiler(&f, s0);

    graphe->pSommet[s0]->couleur = 1;

    while (f.tete != NULL) {
        int num = defiler(&f);

        struct Arc *temp = graphe->pSommet[num]->arc;
        while (temp != NULL) {
            //on récupère le numéro du sommet
            // vers lequel conduit l'arc
            int num2 = temp->sommet;
            //si ce sommet n'est pas marqué
            if (graphe->pSommet[num2]->couleur == 0) {
                //− on l'enfile
                enfiler(&f, num2);
                //− on le marque
                graphe->pSommet[num2]->couleur = 1;
                //− on note que son prédécesseur est le sommet défilé
                preds[num2] = num;
            }
            temp = temp->arc_suivant;
        }
    }

    return s0;
}


void affichage(int* preds,int s0,Graphe * graphe) {
    int num=0;
    for(int i=0;i<graphe->ordre;i++) {
        num=i;
        printf("%d", i);
        while (num!=-1 && preds[num]!=-1) {
            if (i == s0) {
                num = -1;

            } else {
                printf("<--");
                if (preds[num] == s0) {
                    printf("%d", s0);
                    num = -1;
                }
                else if(preds[num]==i){
                    num=-1;
                }
                else {
                    printf("%d", preds[num]);
                    num = preds[num];

                }
            }
        }

        printf("\n");
    }
    printf("\n\n");
}