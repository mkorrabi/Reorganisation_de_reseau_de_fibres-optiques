#include <stdio.h>
#include <stdlib.h>
#include "Struct_File.h"
#include "Struct_Liste.h"
#include "Reseau.h"
#include "Chaine.h"
#include "Graphe.h"

// Q7.1
Graphe* creerGraphe(Reseau * r){    
    Graphe * g = (Graphe *)malloc(sizeof(Graphe));    
    if(! g){
        printf("Erreur allocation Graphe.\n");
        return NULL;
    }
    g -> nbsom = r -> nbNoeuds;
    g -> gamma = r -> gamma;
    g -> nbcommod = nbCommodites(r);
    
   /* Partie 1 : création de T_som tableau de sommets dans le graphe g */
    Sommet ** tabS = (Sommet **)malloc((g -> nbsom) * sizeof(Sommet*));
   
    if(! tabS ){
        free(g);
        printf("Erreur allocation de T_Som du Graphe.\n");
        return NULL;
    }
    for(int i = 0; i < g -> nbsom; i++){
        tabS[i] = NULL;
    }
    
    CellNoeud *cell = r -> noeuds;
    Noeud * n= NULL;
    CellNoeud *voisins= NULL;
    int numVoisin = 0;
    
    /* chemin la liste chaînée CellNoeud du Reseau */
    while(cell != NULL){
        n = cell -> nd;
        voisins = n -> voisins;
        Sommet * sommet = (Sommet *)malloc(sizeof(Sommet));
        if(!sommet){
            for(int i = 0; i < g -> nbsom; i++){
                if(tabS[i]){
                    free(tabS[i]);
                }
            }
            free(tabS);
            free(g);
            printf("Erreur lors de l'allocation d'un sommet.\n");
            return NULL;
        }
        sommet -> num = n -> num - 1; /* initialisation à -1car l'indice premier du tableau est 0 */
        sommet -> x = n -> x;
        sommet -> y = n -> y;
        
        /* Crée les arêtes du graphe  : en parcourant la liste de voisins des Noeuds du Reseau r */
        Cellule_arete * a= (Cellule_arete *)malloc(sizeof(Cellule_arete));
        sommet -> L_voisin = va;
        while (voisins) {
            numVoisin = voisins -> nd -> num;
            Arete *aNew = NULL;
            
            /* on cherche à savoir si on a déjà croisé le voisin -> comparaison des numéros */
            
             /* cas 1 : jamais vu */
            if(numVoisin <= n -> num){
                aNew = (Arete *)malloc(sizeof(Arete));
                aNew -> u = n -> num - 1;
                aNew -> v = numVoisin - 1;
            /* cas 2 : déjà croisé */
            } else {    
                Sommet * vDejaVu = tabS[numVoisin - 1];  
                Arete * aDejaVu = NULL;
                while(vDejaVu -> L_voisin != NULL){
                    aDejaVu = vDejaVu -> L_voisin -> a;
                    /* l'arete qui a pour numero = le numero du sommet v */
                    if(aDejaVu && (aDejaVu -> v == n -> num - 1)){
                        aNew = aDejaVu;
                        break;
                    }
                    vDejaVu -> L_voisin = vDejaVu -> L_voisin -> suiv;
                }
            }
            /* ajout de a dans la liste des Voisins L_voisins */
            Cellule_arete * a2 = (Cellule_arete *)malloc(sizeof(Cellule_arete));
            a2 -> a = aNew ;
            a2 -> suiv = va;
            a= a2;
            sommet -> L_voisin = va;
            voisins = voisins -> suiv;
        }
        /*ajout du sommet dans la Table de Sommets */
        tabS[sommet -> num] = sommet;
        cell = cell -> suiv;
    }
    
    g -> T_som = tabS;
    
    /* Partie 2 : Création du tableau de Commodités */
    Commod * g_tabCommod = (Commod *)malloc(g -> nbcommod * sizeof(Commod));
    CellCommodite * co = r -> commodites;
    int i = 0;
    while(co != NULL){
        Commod g_co;
        g_co.e1 = co-> extrA -> num;
        g_co.e2 = co -> extrB -> num;
        g_tabCommod[i] = g_co;
        i++;
        co =co -> suiv;
    }
    
    g -> T_commod = g_tabCommod;

    return g;
}


// Q 7.2 
int plusPetitCheminUV(Graphe* g, int u , int v){

    if (u == v){   /* 1 er cas u et v identitque */
        return 0 ;
    }
    
    int visit[g->nbsom-1]; /*création d'un tableau pour vérifier si un noeud est deja visite ou non -1 car indice du 1er élément est 0  et num est de 1  */

    memset(visit, 0 , sizeof(int) * g->nbsom-1); /* prends un espace memoire  de taille sizeof(int) * g->nbsom */

    int distance[g->nbsom-1];
    for(int i = 0 ; i < g->nbsom-1 ; i++){
        distance[i] = 0; /*initialisation  du tableau  */
    }

    S_file *F  = (S_file*) malloc(sizeof(S_file));
    Init_file(F);
    visit[u-1] = 1;
    enfile(F,u);


    while(!(estFileVide(F))){
        int present = defile(F); 
        if(present == v){
            return distance[v-1];
        }

        Cellule_arete * cour = g->T_som[present -1]->L_voisin;
        while (cour != NULL)
        {
            int voisin = (present == cour->a->u) ?cour->a->v : cour->a->u;
            if(visit[voisin -1] == 0){
                visit[voisin -1] =  1 ;
                enfile(F,voisin);
                distance[voisin -1] = distance[present -1] +1;

            }
            cour = cour->suiv;
        }       
    }
    
    return -1 ; /* aucun chemin de u à v */

}


//Q7.3 
ListeEntier arborescence(Graphe * g, int u , int  v){

     if (u == v){
        return 0 ; 
    }
    int visit[g->nbsom -1]; /* vérifier si un noeud est deja visite ou non */

    memset(visit, 0 , sizeof(int) * g->nbsom);

    int distance[g->nbsom -1 ];
    for(int i = 0 ; i < g->nbsom-1  ; i++){
        distance[i] = 0; /* distance entre 2 sommets  */
    }

    int prev[g->nbsom]; /* sommet precedent de chaque sommet*/
    for(int i = 0 ; i < g->nbsom ; i++){
        prev[i] = -1;
    }

    S_file *F  = (S_file*) malloc(sizeof(S_file));
    Init_file(F);
    visit[u-1] = 1;
    enfile(F,u);


    while(!(estFileVide(F))){
        int present = defile(F); 
       
        Cellule_arete * cour = g->T_som[present -1]->L_voisin;
        while (cour != NULL)
        {
            int voisin =  (present == cour->a->u) ?cour->a->v : cour->a->u;
            if(visit[voisin -1] == 0){
                visit[voisin -1] =  1 ;
                enfile(F,voisin);
                distance[voisin -1] = distance[present -1] +1;
                prev[voisin - 1] = present;

            }
            cour = cour->suiv;
        }
        

        
    }
    ListeEntier chaine; 
    Init_Liste(&chaine);

    if(prev[v-1] == -1){
        return chaine; 
    }
    int tmp = v; 

    while (tmp != u){
        ajoute_en_tete(&chaine , tmp);
        tmp = prev[tmp -1];
    }
    ajoute_en_tete(&chaine, u);
    liberer_file(F);

    return chaine;
}



// Q 7.4.

int reorganiseReseau(Reseau * r){
  /*etape1 : création du graphe */
    Graphe* g = creerGraphe(r);
   
  /* étape 2 création de la matrice comptant le nombre de chaînes pour chaque arêtes */
    int ** mat = (int **)malloc((g -> nbsom) * sizeof(int*));
    if(mat == NULL){ 
        return  -1 ;
    }
    for (int i = 0; i < g -> nbsom + 1; i++){
        mat[i] = (int *)malloc((g -> nbsom) * sizeof(int));
        if(mat[i] == NULL){
            for(int j = 0; j < i; i++){
                free(mat[j]);   
            }
            free(mat);
            return -1;
        }
    }

    /* initialisation des éléments de la matrice à 0 */
    for(int j = 0; j < g -> nbsom; j++){
        for(int k = 0; k < g -> nbsom; k++){
            mat[j][k] = 0;
        }
    }
    
    
    /*étape 3 :  calcul la plus courte chaîne pour chaque commodité */
    Commod * tabCommod = g -> T_commod;
    Commod k;
    for(int l = 0; l < g -> nbcommod; l++){
        k = tabCommod[l];
        /*la plus courte chaine qui relie les deux extremites de la commodite */
        ListeEntier * lE = plusCourteChaineUV(g, k.e1, k.e2);
        ListeEntier * chemin = lE;
        //ajout des arêtes dans la matrice
        while((*chemin) -> suiv != NULL){
            mat[(*chemin) -> u][(*chemin) -> suiv -> u]++;
            *chemin = (*chemin) -> suiv;
        }
        desalloue(lE);
    }
    
    /* compte le nombre de chaînes passant par chaque arêtes -> couple (u,v) */
    int aretes = 0;
    for (int m = 0; m < g -> nbsom; m++){
        for(int n = m; n < g -> nbsom; n++){
            aretes = mat[m][n] + mat[n][m];
            if(aretes > g -> gamma){
                freeMAT(matArete, (g -> nbsom) + 1); /*si le nombre est supérieur à gamma */
                libererGraphe(g);
                return 0;
            }
        }
    }
    
    desalloue_matrice(mat, g -> nbsom + 1);
    return 1;
    
}

//fonction annexe 
void desalloue_matrice(int ** matrice, int taille){
    for(int i = 0; i < taille; i++){
        free(matrice[i]);
    }
    free(matrice);
}

