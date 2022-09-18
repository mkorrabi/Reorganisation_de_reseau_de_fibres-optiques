#include <math.h>
#include <stdlib.h>
#include "Reseau.h"
#include "Chaine.h"
#include "SVGwriter.h"

#define NBDOR (sqrt(5)-1)/2
  ///////////////////////////////////////////////////////////////////////
 ////////////////////FONCTIONS DE GESTION DU RESEAU/////////////////////
///////////////////////////////////////////////////////////////////////

/*fonction annexe : libere la liste de Noeuds*/
void libere_CellNoeud_Chaines(CellNoeud *cell){
    CellNoeud *tmp = NULL;
    while(cell){
        tmp = cell;
        cell = cell->suiv;
        free(tmp);
    }
}

/*fonction annexe : libère un noeud*/
void libere_CellNoeud(CellNoeud *n){
    if(n == NULL ) { return; }// si c'est vide alors on sort 

    if(n->suiv != NULL ){//on va jusqu'a la fin pour liberer en apelle recursive 
        libere_CellNoeud(n->suiv);
    }
    libere_CellNoeud_Chaines(n->nd->voisins);  // on libere les voisins 
    free(n->nd);// on libere le noeud 
    free(n);// on libere la cell 
}

/*fonction annexe libère la liste de commodités : CellCommodite */
void libere_Commodite(CellCommodite *co){
    if( co == NULL) {return; }// si c'est vide alors on sort 
    
    if (co->suiv != NULL ){
        libere_Commodite(co->suiv);
    }
    free(co);
}

/*fonction annexe : libération de tout le Réseau r */
void libere_Reseau(Reseau *r){// facile 
    
    libere_Commodite(r->commodites);
    libere_CellNoeud(r->noeuds);
    free(r);
}

/*fonction annexe : ajout un noeud dans la liste CellNoeud*/
CellNoeud* creerCellNoeud(Noeud* n, CellNoeud* cell){
    CellNoeud* res = (CellNoeud*) calloc(1, sizeof(CellNoeud));
    res->nd = n;//facile 
    res->suiv = cell;
    return res;
}

/*fonction annexe : créer une CellCommodite */
CellCommodite* creerCellCommodite(Noeud* extrA, Noeud* extrB, CellCommodite* suiv){
    CellCommodite* res = (CellCommodite*) calloc(1, sizeof(CellCommodite));
    res->extrA = extrA; //facile
    res->extrB = extrB;
    res->suiv = suiv;
    return res;
}

/* fonction annexe : ajout d'un Noeud dans la liste de noeuds Voisins à ce noeud */
Noeud* ajouterVoisin(Noeud* prev, Noeud* next){
   
    if(!next) return NULL;

    /* cas 1 : les deux sont deja voisins -> on renvoie Noeud next directement */
    CellNoeud* tmp = prev->voisins;//on parcours la liste des voisins pour savoir 
    while(tmp){
        if(tmp->nd == next){
            return next;
        }
        tmp = tmp->suiv;
    }

    /* cas 2 : on crée CellNoeud correspondants et tisse les liens */
    CellNoeud* cellN = creerCellNoeud(next, prev->voisins);// si non on cree cellnoeud qui contient next et et les voisin de prev
    prev->voisins = cellN;//et les voisin de prev seron la cell cree 
    next->voisins = creerCellNoeud(prev, next->voisins); // enfin on cree une cell avec prev et les voisin de next 

    return next;
}

/* fcontion annexe : création d'un noeud */
Noeud* creerNoeud(int num, double x, double y){
    Noeud* res = (Noeud*) calloc(1, sizeof(Noeud));
    res->num = num;
    res->x = x;
    res->y = y;
    return res;
}


  /////////////////////////////////////////////////////////////////////////
 ////////////////////////////// EXERCICE 2 ///////////////////////////////
/////////////////////////////////////////////////////////////////////////


//Q2.1
Noeud *rechercheCreeNoeudListe(Reseau *R, double x, double y){
    CellNoeud *cell = R->noeuds;
    //verifier si le noeud existe déjà dans le réseau R
    while( cell ){// on fait exactement ce qui a etait demander chercher x et y dans le noeud de celnoeaud de R
        if((cell->nd->x == x) && (cell->nd->y == y)){
            return cell->nd;
        }        
        cell = cell->suiv;
    }
    //sinon on ajoute le noeud 
    Noeud *n = (Noeud *)malloc(sizeof(Noeud));//on cree un noaud qu'on va mettre dans cellnoeuds
    CellNoeud *tmp = (CellNoeud*)malloc(sizeof(CellNoeud));//on cree cellnoeud qu'on va mettre dans le reseau R
    //on inialise le noaud 
    n->num = R->nbNoeuds + 1;
    n->x = x;
    n->y = y;
    n->voisins = NULL;

    tmp->nd = n;  // ensuite le noaud on le met dans cellnoaud 
    tmp->suiv = R->noeuds;  //on fait l'astuce d'ajout en tete d'un nv element son suivant ca sera toute la structure 
    R->noeuds = tmp;//et la structure sera le noeud 
    R->nbNoeuds += 1;
    return n;// et on renvoie le nv noeud 
}


// fonction annexe  : fonction à utiliser pour  Q 2.2
CellNoeud *inserer_Noeud(CellNoeud *cell, Noeud *n){
    CellNoeud * tmp = cell;

    while(tmp && tmp->nd != n){// on verfie si le noeud n'existe pas dans la structure
        tmp = tmp->suiv ;
    }
    if(tmp == NULL){ // et on l'ajoute en tete
        CellNoeud *tmp2  = malloc(sizeof(CellNoeud)); 
        tmp2->nd = n;
        tmp2->suiv = cell;
        cell = tmp2;
    }
    return cell; 
}

//Q2.2
Reseau *reconstitueReseauListe(Chaines *C){

     /* création de la Structure Reseau */
    Reseau *r = (Reseau *)malloc(sizeof(Reseau));
    r->gamma = C->gamma;
    r->nbNoeuds = 0 ;
    r->noeuds = NULL;
    r->commodites = NULL;
   
    CellChaine *cell = C->chaines;
    CellCommodite *co = NULL;

    for(int i = 0 ;  i < C->nbChaines ; i++){// ici c'est l'astuce pour savoir si on a deja ajouter un noeud a un reseau 
        CellPoint *p = cell->points;
        Noeud *a =NULL, *b = NULL;

        while( p ){
            Noeud *n = rechercheCreeNoeudListe(r,p->x,p->y);

            if(a ==NULL){ //ici a est inialiser une fois pour prendre juste le premier extrA
            	a = n; 
            }

            if(b != NULL){// le premier tour b sera null donc il y a que au deuxieme tour quz cela s'executera qu'au deuxieme tour 
                b->voisins = inserer_Noeud(b->voisins,n);// n sera un voisin de b 
                n->voisins = inserer_Noeud(n->voisins , b);// b sera un voisin de n
            }
            b = n;// b est le noeud precedent ainsi n est voisin avec le noeud precendent et reciproquement 
            p = p->suiv;
           
        }
        CellCommodite *tmp_co = malloc(sizeof(CellCommodite));// tjr l'astuce d'ajout en tete d'un nv element
        tmp_co->extrA = a ;   
        tmp_co->extrB = b ; // sera l'extremité vu que il prendra un nouveau n a chaque tour de boucle 
        tmp_co->suiv = co;
        co = tmp_co;
        cell =cell->suiv;
    } 
    r->commodites = co;
    
    return r ;
}


  /////////////////////////////////////////////////////////////////////////
 ////////////////////////////// EXERCICE 3 ///////////////////////////////
/////////////////////////////////////////////////////////////////////////


//Q 3.1
int nbCommodites(Reseau *R){// on parcours les comodité ppour calculer le nb comodité 
    CellCommodite *c = R->commodites; 
    int res = 0;
    while( c ){
        res++ ;
        c = c->suiv;
    }
    printf("\n\nIl y a %d commodités \n", res) ;
    return res;
}


int nbLiaisons(Reseau *R){
	int res = 0 ;          /* nombre total de liaisons */
	CellNoeud *c = R -> noeuds ;     /* cellule noeud courant */
	Noeud *n;         /* noeud courant */
	CellNoeud *v;     /* voisin du noeud courant */

	
	/* parcourt des CellNoeud */
	while (c){
		n = c-> nd;
		v =n -> voisins;
		/* on parcourt les voisins de n  */
		while (v){
			/* si on n'est pas encore passé sur v, on compte une liaison de plus.
			   on sait qu'on est deja passe sur v si le numero de son noeud est supérieur à celui du noeud_courant*/
			if (v -> nd -> num < n -> num){// ca s'explique avec un shema avec 4 noeuds
				res++;
			}
			v = v -> suiv;
		}
    		c= c-> suiv;
	}
	
	printf("\n\nIl y a %d Liaisons \n", res) ;
	return res;
}


//Q 3.2
void ecrireReseau(Reseau *R, FILE *f){
    int nbL = nbLiaisons(R);
    int nbC = nbCommodites(R);
    
    fprintf(f,"NbNoeuds :  %d\nNbLiaisons :  %d\nNbcommodites :  %d\nGamma :  %d\n\n", R->nbNoeuds , nbL ,nbC, R->gamma);
    
    CellNoeud *c= R->noeuds;
    
    /* "v" représente les noeuds du réseau */
    for(int  i = 0 ; i< R->nbNoeuds ; i++){// on fait un tour de cellnoeud de reseau et on ecrit les coordonneés de cahque noeud saus format demander 
        fprintf(f,"v %d %f %f \n", c->nd->num, c->nd->x, c->nd->y);
        c = c->suiv;
    }
    
    fprintf(f, "\n"); /* correspond au saut de ligne de la ligne 18 du fichier 00014_burma.res */
    
    /* "l" représente les liaisons */
    c = R->noeuds;
    CellNoeud *tmp = NULL;

    for(int j = 0 ; j < nbL ;){// un boucle sur noeud 
        tmp = c->nd->voisins;
        
        while( tmp ){// une boucle sur les voisins 
            if( tmp->nd->num < c->nd->num){//un noeud ila deux voisin et on verifie comme avant si on est pas passer par ce noeud 
                fprintf(f,"l %d %d \n ", tmp->nd->num, c->nd->num );
                j++;
            }
            
            tmp = tmp->suiv;
        }
        c = c->suiv;
         
    }
    
    fprintf(f, "\n"); /* correspond au saut de ligne de la ligne 34 du fichier 00014_burma.res */
    
    /* "k" correspond aux commodités */
    CellCommodite *co = R->commodites;

    for(int k = 0 ; k < nbC ; k++){//et enfin un tour de boucle des comodité 
        fprintf(f, "k %d %d \n", co->extrA->num,co->extrB->num);
        co = co->suiv;
    }
}

 



