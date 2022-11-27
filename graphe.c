#include "graphe.h"

/*Ajouter l'arete entre les sommets s1 et s2 du graphe*/
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

/*Creer le graphe*/
Graphe* CreerGraphe(int ordre) {
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

    graphe=CreerGraphe(ordre); // creer le graphe d'ordre sommets
    taille=0;
    for (int ligne=0; ligne<ordre; ++ligne)
    {
        for (int boucleadj = 3; boucleadj <6 ; boucleadj++)
        {
            if (sommet[ligne][boucleadj] != 0)
            {
                graphe->pSommet=CreerArete(graphe->pSommet, sommet[ligne][2], sommet[ligne][boucleadj]);
                graphe->pSommet=CreerArete(graphe->pSommet, sommet[ligne][boucleadj], sommet[ligne][2]);
                taille++;
            }
        }
    }


    orientation = 0;

    graphe->orientation=orientation;
    graphe->ordre=ordre;


    return graphe;
}


void enfiler(t_file *f,int num){
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

int defiler(t_file *f){

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

/*  -Procédure qui crée le graphe pour le calcul de la connectivité
 *  -Récupère la distance la plus longue et la plus courte entre le sommet initial et les autres sommets connectés*/
void checkconnexionmaisonelec(int* preds,DonneesJoueur *joueur, int s0, int** sommet, Maison listeMaison[],int numelec,Centraleelec listeCentraleelec[]){
    check_maison_elec(s0,joueur,sommet,listeMaison,1,numelec,listeCentraleelec);
    //Graphe * graphe=recharge_graphe(joueur, sommet);
    Graphe * graphe=charge_graphe(joueur, sommet);
    BFS(graphe,preds,s0);
    int num=0;
    int min_arrete = 99;
    int max_arrete = 0;
    int count=0;
    for(int i=0;i<graphe->ordre;i++) {// Boucle de recherche du plus gand nombre arrete
        num=i;
        while (num!=-1 && preds[num]!=-1) {
            if (i == s0) {
                num = -1;
            } else {
                if (preds[num] == s0) {
                    count=count+1;
                    num = -1;
                }
                else if(preds[num]==i){
                    num=-1;
                    count=count+1;
                }
                else {
                    num = preds[num];
                    count=count+1;

                }
            }
        }
        if (count < min_arrete && count != 0) min_arrete = count;
        if (count > max_arrete ) max_arrete = count;
        count=0;
    }
    printf("\n\n");
    //Boucle recherche Maison
    while (min_arrete <= max_arrete){        // Boucle de recherche de maison du
        for(int i=0;i<graphe->ordre;i++) {   // plus petit au plus grand nombre arrete
            num=i;
            while (num!=-1 && preds[num]!=-1) {
                if (i == s0) {
                    num = -1;
                } else {
                    //printf("<--");
                    if (preds[num] == s0) {
                        count=count+1;
                        num = -1;
                    }
                    else if(preds[num]==i){
                        num=-1;
                        count=count+1;
                    }
                    else {
                        num = preds[num];
                        count=count+1;
                    }
                }
            }
            if (count == min_arrete) {
                check_maison_elec(i,joueur,sommet,listeMaison,count+1,numelec,listeCentraleelec);
            }
            count=0;
        }
        min_arrete = min_arrete + 1;
    }
    printf("\n\n");
}


/*  -Procédure qui crée le graphe pour le calcul de la connectivité
 *  -Récupère la distance la plus longue et la plus courte entre le sommet initial et les autres sommets connectés*/
void checkconnexionmaison(int* preds,DonneesJoueur *joueur, int s0, int** sommet, Maison listeMaison[],int numchateau, Chateaueau listeChateau[]){
    check_maison(s0,joueur,sommet,listeMaison,1,numchateau,listeChateau);
    //Graphe * graphe=recharge_graphe(joueur, sommet);
    Graphe * graphe=charge_graphe(joueur, sommet);
    BFS(graphe,preds,s0);
    int num=0;
    int min_arrete = 99;
    int max_arrete = 0;
    int count=0;
    for(int i=0;i<graphe->ordre;i++) {// Boucle de recherche du plus gand nombre arrete
        num=i;
        while (num!=-1 && preds[num]!=-1) {
            if (i == s0) {
                num = -1;
            } else {
                if (preds[num] == s0) {
                    count=count+1;
                    num = -1;
                }
                else if(preds[num]==i){
                    num=-1;
                    count=count+1;
                }
                else {
                    num = preds[num];
                    count=count+1;

                }
            }
        }
        if (count < min_arrete && count != 0) min_arrete = count;
        if (count > max_arrete ) max_arrete = count;
        count=0;
    }
    printf("\n\n");
    //Boucle recherche Maison
    while (min_arrete <= max_arrete){        // Boucle de recherche de maison du
        for(int i=0;i<graphe->ordre;i++) {   // plus petit au plus grand nombre arrete
            num=i;
            while (num!=-1 && preds[num]!=-1) {
                if (i == s0) {
                    num = -1;
                } else {
                    if (preds[num] == s0) {
                        count=count+1;
                        num = -1;
                    }
                    else if(preds[num]==i){
                        num=-1;
                        count=count+1;
                    }
                    else {
                        num = preds[num];
                        count=count+1;
                    }
                }
            }
            if (count == min_arrete) {
                check_maison(i,joueur,sommet,listeMaison,count+1,numchateau,listeChateau);
            }
            count=0;
        }
        min_arrete = min_arrete + 1;
    }
}


/*Pour chaque maison de "listemaison", si le sommet initial touche la maison, on ajoute alors la maison dans la
 * structure château d'eau correspondant ainsi que la distance correspondante.
 * On change la maison correspondante pour inscrire le numéro de château d'eau ainsi que la distance*/
void check_maison(int s0,DonneesJoueur *joueur,int** sommet, Maison listeMaison[],int nb_arrete,int numchateau, Chateaueau listeChateau[]) {
    int ajoutmaison = 1;
    int maison;
    for(int nummaison=0;nummaison<joueur->nb_maison;nummaison++)
    {

        for (int i=0 ; i <30 ; i++) // check si maison deja presente dans la centrale elec
        {
            if (listeChateau[numchateau].listeMaisonconnecteau[i].nummaison == nummaison){
                ajoutmaison = 0;
                maison=i;
            }
        }
        //check sommet a droite
        for (int checkx = 0; checkx <=2 ; checkx++)
        {
            if (listeMaison[nummaison].x-checkx == sommet[s0][0] && listeMaison[nummaison].y-1 == sommet[s0][1])
            {
                if (ajoutmaison == 1)
                {
                    listeChateau[numchateau].listeMaisonconnecteau[listeChateau[numchateau].nextmaison].nummaison = nummaison;
                    listeChateau[numchateau].listeMaisonconnecteau[listeChateau[numchateau].nextmaison].distance = nb_arrete;
                    if (listeMaison[nummaison].eau1 == 99) {
                        listeMaison[nummaison].eau1=numchateau;
                        listeMaison[nummaison].disteau1=nb_arrete;
                    }
                    else
                    {if (listeMaison[nummaison].eau2 == 99) {
                            // check si nouveau chateau est plus proche que eau 1 , on switch le chateau 1 et 2
                            //if (listeMaison[nummaison].disteau1=nb_arrete > nb_arrete){
                            if (listeMaison[nummaison].disteau1>nb_arrete){
                                listeMaison[nummaison].eau2=listeMaison[nummaison].eau1;
                                listeMaison[nummaison].disteau2=listeMaison[nummaison].disteau1;
                                listeMaison[nummaison].capaeau1use=listeMaison[nummaison].capaeau2use;
                                listeMaison[nummaison].eau1=numchateau;
                                listeMaison[nummaison].disteau1=nb_arrete;
                                listeMaison[nummaison].capaeau1use=0;
                            }
                            else{
                                listeMaison[nummaison].eau2=numchateau;
                                listeMaison[nummaison].disteau2=nb_arrete;
                            }

                        }

                        else{//si les 2 chateaux sont remplis , on regarde si celui qu'on essaye d'ajouter est plus proche


                            //!!!!!!!!!!!! A ECRIRE !!!!!!!!!!!!!!!


                            /*if listeMaison[nummaison].disteau1=nb_arrete > nb_arrete{
                                eauchat1=listeMaison[nummaison].nbhab;
                                listeChateau[numchateau].
                                listeMaison[nummaison].eau1=
                                listeMaison[nummaison].eau2=listeMaison[nummaison].eau1;
                                listeMaison[nummaison].disteau2=listeMaison[nummaison].disteau1;
                                listeMaison[nummaison].eau1=numchateau;
                                listeMaison[nummaison].disteau1=nb_arrete;
                                }
                             else{

                             } */

                        }
                    }
                    listeChateau[numchateau].nextmaison=listeChateau[numchateau].nextmaison+1;

                }
                else{

                }
            }

        }
        //check sommet a gauche
        for (int checkx = 0; checkx <=2 ; checkx++)
        {
            if (listeMaison[nummaison].x-checkx == sommet[s0][0] && listeMaison[nummaison].y+3 == sommet[s0][1])
            {
                if (ajoutmaison == 1)
                {
                    listeChateau[numchateau].listeMaisonconnecteau[listeChateau[numchateau].nextmaison].nummaison = nummaison;
                    listeChateau[numchateau].listeMaisonconnecteau[listeChateau[numchateau].nextmaison].distance = nb_arrete;
                    if (listeMaison[nummaison].eau1 == 99) {
                        listeMaison[nummaison].eau1=numchateau;
                        listeMaison[nummaison].disteau1=nb_arrete;
                    }
                    else if (listeMaison[nummaison].eau2 == 99) {
                        listeMaison[nummaison].eau2=numchateau;
                        listeMaison[nummaison].disteau2=nb_arrete;
                    }
                    listeChateau[numchateau].nextmaison=listeChateau[numchateau].nextmaison+1;
                }
            }
            else{
            }
        }

        //check sommet en bas
        for (int checky = 0; checky <=2 ; checky++)
        {
            if (listeMaison[nummaison].x+1 == sommet[s0][0] && listeMaison[nummaison].y+checky == sommet[s0][1])
            {
                if (ajoutmaison == 1)
                {
                    listeChateau[numchateau].listeMaisonconnecteau[listeChateau[numchateau].nextmaison].nummaison = nummaison;
                    listeChateau[numchateau].listeMaisonconnecteau[listeChateau[numchateau].nextmaison].distance = nb_arrete;
                    if (listeMaison[nummaison].eau1 == 99) {
                        listeMaison[nummaison].eau1=numchateau;
                        listeMaison[nummaison].disteau1=nb_arrete;
                    }
                    else if (listeMaison[nummaison].eau2 == 99) {
                        listeMaison[nummaison].eau2=numchateau;
                        listeMaison[nummaison].disteau2=nb_arrete;
                    }
                    listeChateau[numchateau].nextmaison=listeChateau[numchateau].nextmaison+1;
                }
            }
            else{
            }
        }
        //check sommet en dessus
        for (int checky = 0; checky <=2 ; checky++)
        {
            if (listeMaison[nummaison].x-3 == sommet[s0][0] && listeMaison[nummaison].y+checky == sommet[s0][1])
            {
                if (ajoutmaison == 1)
                {
                    listeChateau[numchateau].listeMaisonconnecteau[listeChateau[numchateau].nextmaison].nummaison = nummaison;
                    listeChateau[numchateau].listeMaisonconnecteau[listeChateau[numchateau].nextmaison].distance = nb_arrete;
                    if (listeMaison[nummaison].eau1 == 99) {
                        listeMaison[nummaison].eau1=numchateau;
                        listeMaison[nummaison].disteau1=nb_arrete;
                    }
                    else if (listeMaison[nummaison].eau2 == 99) {
                        listeMaison[nummaison].eau2=numchateau;
                        listeMaison[nummaison].disteau2=nb_arrete;
                    }
                    listeChateau[numchateau].nextmaison=listeChateau[numchateau].nextmaison+1;
                }
            }
            else{
            }
        }
        ajoutmaison = 1;

    }
}


/*Pour chaque maison de "listemaison", si le sommet initial touche la maison on ajoute alors la maison dans la structure
 * de la centrale électrique et on change le numéro de la maison pour inscrire le numéro de la centrale*/
void check_maison_elec(int s0,DonneesJoueur *joueur,int** sommet, Maison listeMaison[],int nb_arrete,int numelec, Centraleelec listeCentraleelec[]){
    //printf("check_maison\n\n");
    int ajoutmaison = 1;
    int maison;
    for(int nummaison=0;nummaison < joueur->nb_maison;nummaison++)
    {

        for (int i=0 ; i <30 ; i++) // check si maison deja presente dans la centrale elec
        {
            if (listeCentraleelec[numelec].listeMaisonconnectelec[i].nummaison == nummaison){
                ajoutmaison = 0;
                maison=i;
            }
        }

        //check sommet a droite
        for (int checkx = 0; checkx <=2 ; checkx++)
        {
            if (listeMaison[nummaison].x-checkx == sommet[s0][0] && listeMaison[nummaison].y-1 == sommet[s0][1])
            {
                if (ajoutmaison == 1)
                {
                    listeCentraleelec[numelec].listeMaisonconnectelec[listeCentraleelec[numelec].nextmaison].nummaison = nummaison;
                    listeCentraleelec[numelec].listeMaisonconnectelec[listeCentraleelec[numelec].nextmaison].distance = nb_arrete;
                    listeMaison[nummaison].elec=numelec;
                    listeCentraleelec[numelec].nextmaison=listeCentraleelec[numelec].nextmaison+1;
                }
                else{
                    // si distance inferieur , on modifi la valeur
                    if (listeCentraleelec[numelec].listeMaisonconnectelec[maison].distance > nb_arrete)
                        listeCentraleelec[numelec].listeMaisonconnectelec[maison].distance = nb_arrete;
                }
            }
            else{
            }
        }
        //check sommet a gauche
        for (int checkx = 0; checkx <=2 ; checkx++)
        {
            if (listeMaison[nummaison].x-checkx == sommet[s0][0] && listeMaison[nummaison].y+3 == sommet[s0][1])
            {
                if (ajoutmaison == 1)
                {
                    listeCentraleelec[numelec].listeMaisonconnectelec[listeCentraleelec[numelec].nextmaison].nummaison = nummaison;
                    listeCentraleelec[numelec].listeMaisonconnectelec[listeCentraleelec[numelec].nextmaison].distance = nb_arrete;
                    listeMaison[nummaison].elec=numelec;
                    listeCentraleelec[numelec].nextmaison=listeCentraleelec[numelec].nextmaison+1;
                }
                else{
                    // si distance inferieur , on modifi la valeur
                    if (listeCentraleelec[numelec].listeMaisonconnectelec[maison].distance > nb_arrete)
                        listeCentraleelec[numelec].listeMaisonconnectelec[maison].distance = nb_arrete;
                }
            }
            else{
            }
        }

        //check sommet en bas
        for (int checky = 0; checky <=2 ; checky++)
        {
            if (listeMaison[nummaison].x+1 == sommet[s0][0] && listeMaison[nummaison].y+checky == sommet[s0][1])
            {
                if (ajoutmaison == 1)
                {
                    listeCentraleelec[numelec].listeMaisonconnectelec[listeCentraleelec[numelec].nextmaison].nummaison = nummaison;
                    listeCentraleelec[numelec].listeMaisonconnectelec[listeCentraleelec[numelec].nextmaison].distance = nb_arrete;
                    listeMaison[nummaison].elec=numelec;
                    listeCentraleelec[numelec].nextmaison=listeCentraleelec[numelec].nextmaison+1;
                }
                else{
                    // si distance inferieur , on modifi la valeur
                    if (listeCentraleelec[numelec].listeMaisonconnectelec[maison].distance > nb_arrete)
                        listeCentraleelec[numelec].listeMaisonconnectelec[maison].distance = nb_arrete;
                }
            }
            else{
            }
        }
        //check sommet en dessus
        for (int checky = 0; checky <=2 ; checky++) {
            if (listeMaison[nummaison].x-3 == sommet[s0][0] && listeMaison[nummaison].y+checky == sommet[s0][1])
            {
                if (ajoutmaison == 1)
                {
                    listeCentraleelec[numelec].listeMaisonconnectelec[listeCentraleelec[numelec].nextmaison].nummaison = nummaison;
                    listeCentraleelec[numelec].listeMaisonconnectelec[listeCentraleelec[numelec].nextmaison].distance = nb_arrete;
                    listeMaison[nummaison].elec=numelec;
                    listeCentraleelec[numelec].nextmaison=listeCentraleelec[numelec].nextmaison+1;
                }
                else{
                    // si distance inferieur , on modifi la valeur
                    if (listeCentraleelec[numelec].listeMaisonconnectelec[maison].distance > nb_arrete)
                        listeCentraleelec[numelec].listeMaisonconnectelec[maison].distance = nb_arrete;
                }
            }
            else{
            }
        }
        ajoutmaison = 1;

    }
}


/*Pour chaque centrale électrique, la fonction regarde si on a une route qui touche */
void checkelecmaison(int* preds, char **plateau,DonneesJoueur *joueur, int** sommet,Maison listeMaison[],Centraleelec listeCentraleelec[]) {

    int s0;
    for(int numelec=0;numelec<joueur->nb_centraleelec;numelec++)
    {
        //check sommet a gauche
        for (int checkx = 0; checkx <=5 ; checkx++)
        {
            if (plateau[listeCentraleelec[numelec].x-checkx-1][listeCentraleelec[numelec].y-2] == -36)
            {
                s0=checksommet(joueur,listeCentraleelec[numelec].x-checkx,listeCentraleelec[numelec].y-1,sommet);
                checkconnexionmaisonelec(preds,joueur,s0,sommet,listeMaison,numelec,listeCentraleelec);
            }
            else{

            }

        }
        //check sommet a droite
        for (int checkx = 0; checkx <=5 ; checkx++)
        {
            if (plateau[listeCentraleelec[numelec].x-checkx-1][listeCentraleelec[numelec].y+3] == -36)
            {
                s0=checksommet(joueur,listeCentraleelec[numelec].x-checkx,listeCentraleelec[numelec].y+4,sommet);
                checkconnexionmaisonelec(preds,joueur,s0,sommet,listeMaison,numelec,listeCentraleelec);
            }
            else{

            }

        }

        //check sommet en haut
        if (listeCentraleelec[numelec].x > 6)// on regarde si on est pas en limite haute
        {
            for (int checky = 0; checky <=3 ; checky++)
            {
                if (plateau[listeCentraleelec[numelec].x-7][listeCentraleelec[numelec].y+checky-1] == -36)
                {
                    s0=checksommet(joueur,listeCentraleelec[numelec].x-6,listeCentraleelec[numelec].y+checky,sommet);
                    checkconnexionmaisonelec(preds,joueur,s0,sommet,listeMaison,numelec,listeCentraleelec);
                }
                else{

                }

            }

        }
        //check sommet en bas
        if (listeCentraleelec[numelec].x < 35)// on regarde si on est pas en limite basse
        {
            for (int checky = 0; checky <=3 ; checky++)
            {
                if (plateau[listeCentraleelec[numelec].x][listeCentraleelec[numelec].y+checky-1] == -36)
                {
                    s0=checksommet(joueur,listeCentraleelec[numelec].x+1,listeCentraleelec[numelec].y+checky,sommet);
                    checkconnexionmaisonelec(preds,joueur,s0,sommet,listeMaison,numelec,listeCentraleelec);
                }
                else{

                }

            }
        }
    }
}


/*Pour chaque château d'eau, la fonction regarde si on a une route qui touche*/
void checkchateaumaison(int* preds, char **plateau,DonneesJoueur *joueur, int** sommet,Maison listeMaison[],Chateaueau listeChateau[]) {

    int s0;
    for(int numchateau=0;numchateau<joueur->nb_chateaueau;numchateau++)
    {
        //check sommet a gauche
        for (int checkx = 0; checkx <=5 ; checkx++)
        {
            if (plateau[listeChateau[numchateau].x-checkx-1][listeChateau[numchateau].y-2] == -36)
            {
                s0=checksommet(joueur,listeChateau[numchateau].x-checkx,listeChateau[numchateau].y-1,sommet);
                checkconnexionmaison(preds,joueur,s0,sommet,listeMaison,numchateau,listeChateau);
            }
            else{

            }

        }
        //check sommet a droite
        for (int checkx = 0; checkx <=5 ; checkx++)
        {
            if (plateau[listeChateau[numchateau].x-checkx-1][listeChateau[numchateau].y+3] == -36)
            {
                s0=checksommet(joueur,listeChateau[numchateau].x-checkx,listeChateau[numchateau].y+4,sommet);
                checkconnexionmaison(preds,joueur,s0,sommet,listeMaison,numchateau,listeChateau);
            }
            else{

            }

        }


        //check sommet en haut
        if (listeChateau[numchateau].x > 6)// on regarde si on est pas en limite haute
        {
            for (int checky = 0; checky <=3 ; checky++)
            {
                if (plateau[listeChateau[numchateau].x-7][listeChateau[numchateau].y+checky-1] == -36)
                {
                    s0=checksommet(joueur,listeChateau[numchateau].x-6,listeChateau[numchateau].y+checky,sommet);
                    checkconnexionmaison(preds,joueur,s0,sommet,listeMaison,numchateau,listeChateau);
                }
                else{

                }

            }
        }


        //check sommet en bas
        if (listeChateau[numchateau].x <35)// on regarde si on est pas en limite basse
        {
            for (int checky = 0; checky <=3 ; checky++)
            {
                if (plateau[listeChateau[numchateau].x][listeChateau[numchateau].y+checky-1] == -36)
                {
                    s0=checksommet(joueur,listeChateau[numchateau].x+1,listeChateau[numchateau].y+checky,sommet);
                    checkconnexionmaison(preds,joueur,s0,sommet,listeMaison,numchateau,listeChateau);
                }
                else{

                }
            }
        }
    }
}
