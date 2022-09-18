#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "Reseau.h"
#include "Chaine.h"

  /////////////////////////////////////////////////////////////////////////
 ////////////////////////////// EXERCICE 4 ///////////////////////////////
/////////////////////////////////////////////////////////////////////////

//Q 4.1
typedef struct table {
    int nE;             /*nombre d'éléments dans le tableau tab   */
    int taille;        /* taille maximale de la table de hachage */
    CellNoeud* *tab ; /* tableau de CellNoeud                   */
}TableHachage;


/* fonction annexe : libération de la table de hachage */ 
void libere_Hachage(TableHachage *H);

/* fonction annexe : crée une table de Hachage */
TableHachage* creerTableHachage(int taille);

/* Q 4.2 fonction de clé renvoie un entier a partir de 2 valeurs  x et y */
int cleH( double x ,double y );

/* Q 4.3 fonction de hachage */
int fonctionHachage(int cle, int m);

/* Q 4.4 retourne le noeud du Reseau correspondant au point x et y dans la table de hachage */
Noeud *rechercheCreeNoeudHachage(Reseau *R, TableHachage *H, double x, double y);

/* Q 4.5 reconstitue le Reseau à partir de Chaines et une table de hachage  de taille M */ 
Reseau *reconstitueReseauHachage(Chaines *C, int M);


#endif
