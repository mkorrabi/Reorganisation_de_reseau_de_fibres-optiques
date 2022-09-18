
#ifndef __RESEAU_H__
#define __RESEAU_H__
#include "Chaine.h"


  /////////////////////////////////////////////////////////////////////////
 //////////////////////DEFINITION DE STRUCTURES///////////////////////////
/////////////////////////////////////////////////////////////////////////

typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
typedef struct cellnoeud {
    Noeud *nd;               /* Pointeur vers le noeud stock\'e */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud*/
   CellNoeud *voisins;             /* Liste des voisins du noeud */
};

/* Liste chainee de commodites */
typedef struct cellCommodite {
    Noeud *extrA, *extrB;       /* Noeuds aux extremites de la commodite */
    struct cellCommodite *suiv;     /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                      /* Nombre maximal de fibres par cable */
    CellNoeud *noeuds;              /* Liste des noeuds du reseau */
    CellCommodite *commodites;      /* Liste des commodites a relier */
} Reseau;


  /////////////////////////////////////////////////////////////////////////
 //////////////////FONCTIONS DE GESTIONS DU RESEAU ///////////////////////
/////////////////////////////////////////////////////////////////////////

/*fonction annexe : libère un noeud*/
void libere_CellNoeud(CellNoeud *n);

/*fonction annexe : libere la liste de Noeuds*/
void libere_CellNoeud_Chaines(CellNoeud *cell);

/*fonction annexe libère la liste de commodités : CellCommodite */
void libere_Commodite(CellCommodite *co);

/*fonction annexe : libération de tout le Réseau r */
void libere_Reseau(Reseau *r);

/*crée un noeud dans la liste de Noeuds */
CellNoeud* creerCellNoeud(Noeud* n, CellNoeud* cell) ;

/*ajout d'une CellCommodite à la liste de CellComodite */
CellCommodite* creerCellCommodite(Noeud* extrA, Noeud* extrB, CellCommodite* suiv) ;

/* ajout d'un voisins dans la liste de noeuds Voisins à ce noeud   */
Noeud* ajouterVoisin(Noeud* prev, Noeud* next) ;

/*fonction annexe : créer un noeud de coordonnées x et y */
Noeud* creerNoeud(int num, double x, double y) ;

/* foncion annexe Q2.2 : insertion d'un noeud en tete de La liste CellNoeud */
CellNoeud *inserer_Noeud(CellNoeud *cell, Noeud *n) ;

  /////////////////////////////////////////////////////////////////////////
 ////////////////////////////// EXERCICE 2 ///////////////////////////////
/////////////////////////////////////////////////////////////////////////

/* Q2.1 retourne un Noeud de R sinon le crée et l'ajoute dans R */
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);

/* Q2.2 reconstitue le réseau R à partir de Chaines */
Reseau* reconstitueReseauListe(Chaines *C);



  /////////////////////////////////////////////////////////////////////////
 ////////////////////////////// EXERCICE 3 ///////////////////////////////
/////////////////////////////////////////////////////////////////////////

/* Q3.1 compte le nombre de liaisons dans le réseau */ 
int nbLiaisons(Reseau *R);

/* Q3.1 compte le nombre de commodités dans le réseau */ 
int nbCommodites(Reseau *R);

/* Q3.2 écrit dans un fichier le contenu d'un réseau */
void ecrireReseau(Reseau *R, FILE *f);



 
#endif


