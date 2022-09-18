#ifndef __GRAPHE_H__
#define __GRAPHE_H__
#include<stdlib.h>
#include<stdio.h>
#include "Struct_Liste.h"

typedef struct{
  int u,v;        /* Numeros des sommets extremité */
} Arete;


typedef struct cellule_arete{
  Arete *a;     /* pointeur sur l'arete */
  struct cellule_arete *suiv;
} Cellule_arete;


typedef struct {
  int num;                 /* Numero du sommet (le meme que dans T_som) */
  double x, y;
  Cellule_arete* L_voisin;  /* Liste chainee des voisins */
} Sommet;


typedef struct{
  int e1,e2;    /* Les deux extremites de la commodite */
} Commod;


typedef struct{
  int nbsom;        /* Nombre de sommets */
  Sommet* *T_som;    /* Tableau de pointeurs sur sommets */
  int gamma;     
  int nbcommod;     /* Nombre de commodites */
  Commod *T_commod; /* Tableau des commodites */
} Graphe;


/* Q7.1 Création du graphe */
Graphe * creerGraphe(Reseau * r);

/*Q 7.2 retourne le plus petit nombre d'arêtes d'une chaine entre 2 sommets u et v*/
int plusPetitCheminUV(Graphe * G, int u, int v);

/* Q 7.3 stocke l'arborescence des chaines issus de u */
ListeEntier arborescence(Graphe * g, int u , int  v) ;

/* Q 7.4 Nous créons le graphe, pour chaque commodité nous cherchons sa plus courte chaîne et nous regardons si le nombre gamma est verifiee*/
int reorganiseReseau(Reseau * r);

/* fonction annexe Q7.4 desalloue la matrice 2D */
desalloue_matrice(int ** matrice, int taille) ;

#endif
