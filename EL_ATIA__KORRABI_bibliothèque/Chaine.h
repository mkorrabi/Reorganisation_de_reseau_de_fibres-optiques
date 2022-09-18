#ifndef __CHAINE_H__
#define __CHAINE_H__	
#include<stdio.h>

/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;



/*retourne une instance de Chaines à partir d'un fichier */
Chaines* lectureChaines(FILE *f);

/*ecrit dans un fichier f le contenu de Chaines C */
void ecrireChaines(Chaines *C, FILE *f);

/*renvoie la longueur d'une chaine */
double longueurChaine(CellChaine *c) ;

/*renvoie la longueur physique totale des chaine de Chaines */ 
double longueurTotale(Chaines *C);

/*compte le nombre totale de points de Chaines */
int comptePointsTotal(Chaines *C);


#endif	
