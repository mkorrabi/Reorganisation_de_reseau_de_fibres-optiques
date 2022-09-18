#ifndef __ARBRE_QUAT_H__
#define __ARBRE_QUAT_H__
#include "Reseau.h"
#include "Chaine.h"

   /////////////////////////////////////////////////////////////////////////
  ////////////////////////////// EXERCICE 5 ///////////////////////////////
 /////////////////////////////////////////////////////////////////////////


/* Arbre quaternaire contenant les noeuds du réseau */
typedef struct arbreQuat{
    double xc, yc;          /* Coordonnees du centre de la cellule */	
    double coteX;           /* Longueur de la cellule */
    double coteY;           /* Hauteur de la cellule */
    Noeud* noeud;           /* Pointeur vers le noeud du reseau */
    struct arbreQuat *so;   /* Sous-arbre sud-ouest, pour x < xc et y < yc */
    struct arbreQuat *se;   /* Sous-arbre sud-est, pour x >= xc et y < yc */
    struct arbreQuat *no;   /* Sous-arbre nord-ouest, pour x < xc et y >= yc */
    struct arbreQuat *ne;   /* Sous-arbre nord-est, pour x >= xc et y >= yc */
} ArbreQuat;



/* Q5.1 renvoie les coordonnées minimales et maximales de la Chaines C*/ 
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax) ;

/* Q5.2 création de l'arbre quaternaire */
ArbreQuat *creerArbreQuat(double xc, double yc, double coteX,double coteY) ;
 
/* Q5.3 insère un noeud du réseau dans un arbre quaternaire */
void insererNoeudArbre(Noeud *n, ArbreQuat** a, ArbreQuat* parent) ;


Noeud *rechercheCreeNoeudArbre(Reseau *R, ArbreQuat **a, ArbreQuat *parent,double x, double y);
/* Q 5.5 Reconstitution du Reseau en utilisant Chaines C et l'arbre quaternaire */
Reseau *reconstitueReseauArbre(Chaines *C);

/* fonction annexe : libère l'arbre Quaternaire */
void liberation_arbreQuat(ArbreQuat *a) ;

#endif
