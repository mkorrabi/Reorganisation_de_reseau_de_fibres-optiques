#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"


//fonction annexe 
void libere_Hachage(TableHachage *H){
    
    if( H == NULL) {
    	return ;
    }

    for (int i = 0; i < H->taille; i++){
        libere_CellNoeud_Chaines(H->tab[i]);
    }
    free(H->tab);
    free(H);
}

//Q 4.2
int cleH( double x ,double y ){// la premier fonction qui donne la clef 
  return (int) y + (( x+y ) * ( x+y+1 )) / 2 ; 
}

//Q 4.3
int fonctionHachage(int cle, int m){// ensuite on hache la clef pour trouver la case 
    float a = (sqrt(5)-1)/2; /* nombre d'or */
    return (int)(m*(cle*a - (int)(cle*a)));
}


//Q 4.4
Noeud *rechercheCreeNoeudHachage(Reseau *R, TableHachage *H, double x, double y){

    int pos = fonctionHachage( cleH(x,y) , H->taille ); /* position théorique du point dans le tableau de hachage */
    CellNoeud *tmp = H->tab[pos];

    while(tmp && tmp->nd->x!=x && tmp->nd->y !=y ){   /*recherche du Noeud ayant les mêmes coordonnées dans la liste chaine dans cette case  */
    	tmp = tmp->suiv; 
    } 
    
    if(tmp!= NULL){ // si on sort et qu'on arrive pas a la fin et qu'on a le trouver le point alors on le renvoie 
    	return tmp->nd; 
    } 

    /* création du noeud car n'existe pas dans la table de hachage */
    Noeud *n = malloc(sizeof(Noeud));
    n->x = x;
    n->y = y;
    n->num = R->nbNoeuds + 1 ;
    n->voisins = NULL;

    /* ajout en tete  de ce noeud dans le Reseau R */
    CellNoeud *res = malloc(sizeof(CellNoeud));
    res->nd = n ;
    res->suiv = R->noeuds;
    R->noeuds = res;
    R->nbNoeuds++;

    /* ajout en tete de ce noeud dans la table H */
    CellNoeud *resH = malloc(sizeof(CellNoeud));// on cree la cell qu'on a ajoute a la case des liste chaine de la table de hachage 
    resH->nd = n ;
    resH->suiv = H->tab[pos];// son suiv ca sera la liste dans cette case 
    H->nE++; // ainsi le nb element dans la table s'incremente 
    H->tab[pos] = resH;// et la liste de cette case predra tout 

    return n ;
}


/* fonction annexe 4.5 : création de la table de hachage */
TableHachage* creerTableHachage(int taille){
    TableHachage* res = (TableHachage*) calloc(1, sizeof(TableHachage));// on aloue pour 1 objet (sizeof(TableHachage)octet )
    
    res->taille = taille;
    res->tab = calloc(taille, sizeof(CellNoeud*));// ca evite de faire la boucle avec le malloc pour chaque case 
    return res;
}



//Q 4.5
Reseau* reconstitueReseauHachage(Chaines *C, int M){
    
    Reseau* R = (Reseau*) calloc(1, sizeof(Reseau));// on cree un reseau 
    R->gamma = C->gamma;//on inialise gamma de reseau 
    TableHachage* H = creerTableHachage(M);// on cree une table hachage comme demander on ajoute des noeud  petit a petit ce qui va nous permettre de dire si un noeud on l'a deja ajouter ou pas 
    Noeud* noeudPrev = NULL;
    Noeud* n = NULL;
    Noeud* noeudTete = NULL;
    CellChaine* cellC = C->chaines;
    CellPoint* cellp = NULL;
    CellPoint* pointPrev = NULL;
    CellPoint* pointTete = NULL; 
    CellCommodite* co = NULL;

    /*  parcours des chaines de Chaines*/
    int i;
    for ( i = 0; i < C->nbChaines; i++, cellC = cellC->suiv){  // on fait une boucle pour parcourir toute les chaine       
    
        pointTete = cellC->points;
        cellp = pointTete ;
        noeudTete = rechercheCreeNoeudHachage(R, H, cellp->x, cellp->y);// ici l'astuce ppour savo rsi un noeud a ete deja ajouter 
        noeudPrev = noeudTete;
        pointPrev = cellp;
        cellp = cellp->suiv;


        while(cellp){// on parcours tout les points 
            n = rechercheCreeNoeudHachage(R, H, cellp->x, cellp->y);  /* // ici l'astuce ppour savo rsi un noeud a ete deja ajouter    on cree un noeud avec chaque point */
            noeudPrev = ajouterVoisin(noeudPrev, n); /* mise à jour , on ajoute le noeud d'avant au voisin de n et reciproquemnt */
            pointPrev = cellp;// le point prec devient celui en cors 
            cellp = cellp->suiv;// et le point en cours avance 
        }
        
       
        co = creerCellCommodite(noeudTete, n, co);// on cree une commodité avec avec le prmier noeud et le drenier de chaque tour de boucle 
    }
    R->commodites = co;// on inialise la commodite du reseau 
    libere_Hachage(H);// pas compris 
    return R;
}

/*
Test main : fonction cle (x,y) en faisiant 2 boucle for allant de 1 à 10 pour x et y 
res = 4
res = 8
res = 13
res = 19
res = 26
res = 34
res = 43
res = 53
res = 64
res = 76
res = 7
res = 12
res = 18
res = 25
res = 33
res = 42
res = 52
res = 63
res = 75
res = 88
res = 11
res = 17
res = 24
res = 32
res = 41
res = 51
res = 62
res = 74
res = 87
res = 101
res = 16
res = 23
res = 31
res = 40
res = 50
res = 61
res = 73
res = 86
res = 100
res = 115
res = 22
res = 30
res = 39
res = 49
res = 60
res = 72
res = 85
res = 99
res = 114
res = 130
res = 29
res = 38
res = 48
res = 59
res = 71
res = 84
res = 98
res = 113
res = 129
res = 146
res = 37
res = 47
res = 58
res = 70
res = 83
res = 97
res = 112
res = 128
res = 145
res = 163
res = 46
res = 57
res = 69
res = 82
res = 96
res = 111
res = 127
res = 144
res = 162
res = 181
res = 56
res = 68
res = 81
res = 95
res = 110
res = 126
res = 143
res = 161
res = 180
res = 200
res = 67
res = 80
res = 94
res = 109
res = 125
res = 142
res = 160
res = 179
res = 199
res = 220

 */

