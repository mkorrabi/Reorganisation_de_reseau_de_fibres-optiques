#include <stdio.h>
#include <stdlib.h>
#include "ArbreQuat.h"
#include "Chaine.h"
#include "Reseau.h"
#include <math.h>

//Q 5.1
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax) {

  CellChaine *c = C->chaines;
  
  /* initialisation : prend les valeurs des premiers points */
  *xmin = c->points->x;
  *xmax = c->points->x;
  *ymin = c->points->y;
  *ymax = c->points->y;
  
  /* parcours CellChaine de Chaines */
  while(c ) {
    CellPoint *p = c->points;

    /*parcours de la liste de points dans CellChaine */	
    while(p ) {
    /*comparaisons des valeurs des coordonnées du milieu comme ca ete dit dans le sujet  */ 
      if (*xmin > p->x){ // on cherchre la valeur la plus petit de x
      	*xmin = p->x;
      }
      
      if (*xmax < p->x){// on cherche le x le plus grand 
      	*xmax = p->x;
      }
      
      if (*ymin > p->y){ // on cherche le y le plus petit dans les coordoneés de la chaine 
      	*ymin = p->y;
      }
      
      if (*ymax < p->y){// on cherche le y le plus grand 
      	*ymax = p->y;
      }
      
      p = p->suiv;
    }
    c = c->suiv;
  }
}




//Q 5.2
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY) {

        ArbreQuat* a = (ArbreQuat*) malloc(sizeof(ArbreQuat)) ;

        a->xc = xc ;
        a->yc = yc ;
        a->coteX = coteX ;
        a->coteY = coteY ;
        a->noeud = NULL ;
        a->so = NULL ;
        a->se = NULL ;
        a->ne = NULL ;
        a->no = NULL ;

        return a ;
}

    
//Q 5.3 
void insererNoeudArbre(Noeud *n, ArbreQuat **a, ArbreQuat *parent) {
  //premiere condition demander 
  if (*a == NULL) { 
    double coteX = parent->coteX / 2 ;
    double coteY = parent->coteY / 2;
    double xc, yc;
    
    if(n->x < parent->xc) {// on verifie ou se situe le noeud en fonction de ca on peut calculer le centre
      if(n->y < parent->yc) {
        xc = parent->xc - (coteX / 2);
        yc = parent->yc - (coteY / 2);
      }else{
        xc = parent->xc - (coteX / 2);
        yc = parent->yc + (coteY / 2);
      }
    }else if(n->y < parent->yc) {
      xc = parent->xc + (coteX / 2);
      yc = parent->yc - (coteY / 2);
    }else{
      xc = parent->xc + (coteX / 2);
      yc = parent->yc + (coteY / 2);
    }
    *a = creerArbreQuat(xc, yc, coteX, coteY);// comme demander si le l'arbre est vide on le recree comme le petit carre (le carre choisi depend ou se situe le point )de l'arbre de la page 10 )ainsi son centre sera le bord du grand carre et ca longuer de chaque coté sera la moitié du grand carre 
    (*a)->noeud = n;
    return ;
  }
  // deuxieme condition si le noeud a n'est pas vide 

  if ((*a)->noeud != NULL) { 
    if((*a)->noeud->x < (*a)->xc) {// ici on cree un nouveau carre pour le noeud qui existe a l'interieur 
	if ((*a)->noeud->y < (*a)->yc) {
		insererNoeudArbre((*a)->noeud, &(*a)->so, *a);//on le place en bas a gauche 
	}
      	else{ 
      	insererNoeudArbre((*a)->noeud, &(*a)->no, *a);//on le place en haut a gauche 
      	}
    } 
    else if((*a)->noeud->y < (*a)->yc) {
    	insererNoeudArbre((*a)->noeud, &(*a)->se, *a);// on le place en bas a droite 
    }
    else{ 
    	insererNoeudArbre((*a)->noeud, &(*a)->ne, *a);// on le place en haut a droite 
    }
    (*a)->noeud = NULL;// ensuite on s'occupe du noeud qu'on veut ajouter 
    if(n->x < (*a)->xc) {
      if(n->y < (*a)->yc) { 
      	insererNoeudArbre(n, &(*a)->so, *a);//on le place en bas a gauche 
      }
      else{
      	insererNoeudArbre(n, &(*a)->no, *a);//on le place en haut a gauche
      }
    }
    else if(n->y < (*a)->yc) {
    	insererNoeudArbre(n, &(*a)->se, *a);// on le place en bas a droite 
    } 
    else {
    	insererNoeudArbre(n, &(*a)->ne, *a);// on le place en haut a droite
    }
    return ;//on sort 
  }
  //troisieme choix  
  if (n->x < (*a)->xc) {// si non on sera dans le cas de  ((*a)->noeud == NULL))
  	if (n->y < (*a)->yc) {
    		insererNoeudArbre(n, &(*a)->so, *a);// ainsi on fait comme avant 
   	 }
    	else{ 
    	insererNoeudArbre(n, &(*a)->no, *a); 
 	}
  }
  else if (n->y < (*a)->yc) { 
  	insererNoeudArbre(n, &(*a)->se, *a);
  }
  else {
  	insererNoeudArbre(n, &(*a)->ne, *a);
  }

}



//Q 5.4
Noeud *rechercheCreeNoeudArbre(Reseau *R, ArbreQuat **a, ArbreQuat *parent, double x, double y){
    if ((*a)==NULL){// premier cas si l'arbre est vide le noeud on l'insere dans un reseau avec cellnoeud et dans l'arbre 
        //insertion  du noeud dans le reseau
        R->nbNoeuds++;
        CellNoeud *new = (CellNoeud*) calloc(1, sizeof(CellNoeud));
        new->nd = creerNoeud(R->nbNoeuds, x, y);
        new->suiv = R->noeuds;
        R->noeuds = new;

        //insertion dans l'arbre
        insererNoeudArbre(new->nd, a, parent);// on l'insere dans l'arbre avec la fonction demander 
        return new->nd;
    }

    else{// la on est dansq le cas 2 ( ((a->noeud != NULL)),)
        if ((*a)->noeud != NULL){
            if (fabs((*a)->noeud->x - x) < 0.000001 && fabs((*a)->noeud->y - y) < 0.000001){
                // le fonction renvoie la valeur absolue de la diffrence 
                //Le noeud existe dans l'arbre et donc dans le réseau, on retourne le noeud
                return (*a)->noeud;
            }
            else{// si on trouve les corddonne alors le noeud il n'existe pas alors il faut l'ajouter et le renvoyer 
                //Le noeud n'existe pas dans l'arbre car on est arrivé a une feuille et le if n'est pas vérifié.
                //On ajoute au réseau
                R->nbNoeuds++;
                CellNoeud *new = (CellNoeud*) calloc(1,sizeof(CellNoeud));
                new->nd = creerNoeud(R->nbNoeuds, x, y);
                new->suiv = R->noeuds;
                R->noeuds = new;
                //On ajoute dans l'arbre
                insererNoeudArbre(new->nd, a, parent);
                return new->nd;
            }
        }
        else{// et la on est dans le cas 3 ,,((*a != NULL)&& ((*a)->noeud == NULL)
            //On continue de chercher jusqu'a ce qu'on arrive a une feuille ou place libre
            //On doit déterminer dans lequel des enfants on doit chercher

            //cas sud-ouest
            if (x < (*a)->xc && y < (*a)->yc)
            {
                return rechercheCreeNoeudArbre(R, &((*a)->so), *a, x, y);
            }

            //cas sud-est
            if (x >= (*a)->xc && y < (*a)->yc){
               return rechercheCreeNoeudArbre(R, &((*a)->se), *a, x, y);
            }

            //cas nord-ouest
            if (x < (*a)->xc && y >= (*a)->yc){
                return rechercheCreeNoeudArbre(R, &((*a)->no), *a, x, y);
            }

            //cas nord-est
            if(x >= (*a)->xc && y >= (*a)->yc){
                return rechercheCreeNoeudArbre(R, &((*a)->ne), *a, x, y);
            }
        }
    }

    return NULL;// si non on retourne rien 
}

/*fonction annexe : On va utiliser cette fonction pour trouver ou faut t'il continuer de cherche à partir de la racine du tout debut */
Noeud *lancerRecherche(Reseau *R, ArbreQuat *pere, double x, double y){

    //cas sud-ouest
    if (x < pere->xc && y < pere->yc)
    {
        return rechercheCreeNoeudArbre(R, &(pere->so), pere, x, y);
    }

    //cas sud-est
    if (x >= pere->xc && y < pere->yc){
        return rechercheCreeNoeudArbre(R, &(pere->se), pere, x, y);
    }

    //cas nord-ouest
    if (x < pere->xc && y >= pere->yc){
        return rechercheCreeNoeudArbre(R, &(pere->no), pere, x, y);
    }

    //cas nord-est
    if(x >= pere->xc && y >= pere->yc){
        return rechercheCreeNoeudArbre(R, &(pere->ne), pere, x, y);
    }

    //jamais verifié
    return NULL;
}

// Q 5.5
Reseau *reconstitueReseauArbre(Chaines *C){

    //Determiner et creer la racine 
    double xmin, ymin, xmax, ymax;
    chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);
    ArbreQuat *pere = creerArbreQuat(xmin + (xmax - xmin) / 2.0/*xc:le cote le plus a gauche plus la loguere X/2 */, ymin + (ymax - ymin) / 2.0, xmax - xmin/*coteX*/, ymax - ymin/*coteY*/);

    //Creation du reseau
    Reseau *R = (Reseau*) calloc(1, sizeof(Reseau));
    R->gamma = C->gamma;
    R->nbNoeuds = 0;

    //On va parcourir les chaines de C
    CellChaine *tmpChaines = C->chaines;
    for (int i = 0; i < C->nbChaines; i++){
        
        //On regarde chaque point individuel de la chaine
        CellPoint *tmpPoints = tmpChaines->points;

        //On stocke les extremites pour creer la commodité
        Noeud *extremite1 = NULL;
        Noeud *extremite2 = NULL;

        //Pour le premier noeud de l'arbre:
        extremite1 = lancerRecherche(R, pere, tmpPoints->x, tmpPoints->y);// renvoie le premier noeud recontré 
        tmpPoints = tmpPoints->suiv;// 

        //On stocke le noeud d'avant pour ajouter les ajouter comme voisins
        Noeud *prev = extremite1;

        //Parcours de tous les points (sauf le premier qui est deja fait avant) de la chaine
        while(tmpPoints){// on parcours tout les points de la chaine 
            Noeud *n = NULL;
            if (tmpPoints->suiv == NULL)
            {
                //On sauvegarde le dernier point car ca represente la deuxieme extremite de la commodité
                extremite2 = lancerRecherche(R, pere, tmpPoints->x, tmpPoints->y);// on l'ajoute et on le garde a chaque fois 
                n = extremite2;
            }
            else{// si non on l'ajoute normalement 
                //Ici on est dans les points du milieu
                n = lancerRecherche(R, pere, tmpPoints->x, tmpPoints->y);
            }

            //On ajoute les points dans les voisins les uns des autres, puis on change prev
            ajouterVoisin(prev, n);
            prev = n;// on met a jour prev 

            tmpPoints = tmpPoints->suiv;// on avance 
        }

        //ajout de la commodité dans le reseau// une fois qu'on a les deux extrimité 
        R->commodites = creerCellCommodite(extremite1, extremite2, R->commodites);

        //Incremente pour parcourir toutes les chaines
        tmpChaines = tmpChaines->suiv;// on avance dans la chaine 
    }
    //liberation de l'arbre avec la fonction d'en dessous ne marche pas, a verifier
    liberation_arbreQuat(pere);// une fois on atout ajouter au resea on a plus interet de garde l'arbre 

    return R;
}


/* fonction annexe : fonction récursive */
void liberation_arbreQuat(ArbreQuat *a){
    if(a){
        if(a->se){
            liberation_arbreQuat(a->se);
        }

        if(a->so){
            liberation_arbreQuat(a->so);
        }

        if(a->ne){
            liberation_arbreQuat(a->ne);
        }

        if(a->no){
            liberation_arbreQuat(a->no);
        }  
        free(a);
    }
}



