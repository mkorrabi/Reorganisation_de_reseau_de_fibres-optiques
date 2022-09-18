#include "Chaine.h"
#include "SVGwriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



//Q1.1


/*pour initialiser une chaine :
on a gamma et nbchaine et cellchaine 
    -gamam et nbchaine c'est les deux premeirs lignes ensuite cellchaine on doit l'initialser avec une boucle grace a nbchaine
          -cellchaine pour l'inialiser :
             on a numero et nbpoint et cellpoint a inialiser a chaque tour de la grande boucle 
             -pour inialiser cellpoint on fait une boucle ou on inialiser x y a chaque fois */
Chaines* lectureChaines(FILE *f){

    Chaines *c = malloc(sizeof(Chaines));
    char buffer[256];
    int Nbchain, Gamma ;

    fgets(buffer, 256,f);
    sscanf(buffer,"NbChain: %d", &Nbchain);

    fgets(buffer, 256,f);
    sscanf(buffer,"Gamma: %d" , &Gamma);

    c->nbChaines =Nbchain;
    c->gamma=Gamma;
    CellChaine *cell = NULL;

/*parcours de tous les CellChaines de Chaines */
    for(int j =  0 ;  j < c->nbChaines ; j++){
        CellChaine *tmp_cell = malloc(sizeof(CellChaine));
        int numero, nbPoints ;
        fscanf(f,"%d %d ", &numero , &nbPoints);// on lit le numero et nb point 
        printf("\nnumero = %d, nbPoints = %d \n", numero , nbPoints);
        tmp_cell->numero = numero ;
        CellPoint *p = NULL;

	/*pour le meme tour de boucle on récupère les valeurs des coordonnées x et y grace a nbpoints */
        for(int i = 0 ; i < nbPoints; i++){
            CellPoint *tmp_p = malloc(sizeof(CellPoint));
            float x, y;
            fscanf(f,"%f %f ", &x , &y );
            printf("x=%.2f y=%.2f \n", x , y );
            tmp_p->x=x;
            tmp_p->y = y;
            tmp_p->suiv = p; //on garde p au premier tour pour que au deuxieme tour le suiv de tmp_p ca sera le p d'avant 
            p=tmp_p; //ici p prend tout (tmp_p qui contient le p d'avant)
            
        }
        //ici on inialise cell qui contient une liste de point p qu'on a inialiser dans la boucle interieure d'avant
        tmp_cell->points = p;
        tmp_cell->suiv = cell; //ici on fait la meme chose qu'avec les points on les p ici au 2 eme tour le suiv de tmp_cell ca sera cell d'avant 
        cell = tmp_cell;


    }
    c->chaines = cell;// on inialise la cellchaien de c qui est une liste qui contient toute les lignes 
    return c;
}



//Q1.2
void ecrireChaines(Chaines *C, FILE *f){
    fprintf(f,"NbChain : %d \nGamma : %d\n",C->nbChaines,C->gamma);
    CellChaine *cell = C->chaines;

    for(int i = 0 ; i <C->nbChaines ; i++){//on fait une boucle pour parcourir toutes les cell//
        int nb_points = 0; 
        CellPoint *p = cell->points;

        while( p ){// une boucle pour compté le nombres de points dans chaque cell
            nb_points++ ;
            p = p->suiv ;//on passe au point suivant 
        }
        fprintf(f,"%d %d ",cell->numero, nb_points);// on ecrit le num nbpoint de chaque cell
        p = cell->points;

        while( p ){// une deuxieme boucle pour parcourir les points de chaque cell et les ecrire 
            fprintf(f, "%.2f %.2f ",p->x,p->y);//.2 juste deux points apres la virgule 
            p = p->suiv;//on passe au point suivant 
        }
        
        fprintf(f,"\n");
        cell = cell->suiv;//on passe a la cell suivante 
    }
}

//Q1.4
double longueurChaine(CellChaine *c){
    double res = 0;
    CellPoint *p = c->points;
    CellPoint *p_suiv = p->suiv;

    while( p_suiv ){
        res +=sqrt(pow(p_suiv->y - p->y,2)+pow(p_suiv->x - p->x, 2));
        p = p_suiv;
        p_suiv = p_suiv->suiv;
    }
    return res;
}


double longueurTotale(Chaines* C)  {
    double res = 0;
    CellChaine *cell = C->chaines;
    
    while( cell ){
        res+=longueurChaine( cell );
        cell = cell->suiv;
    }
    //   printf("la longeure de cette chaine est : %.2f\n",res);

    return res;
}

//Q1.5
int comptePointsTotal(Chaines* C){
    int nb_points = 0;
    CellChaine *cell = C->chaines;

    while( cell ){
        CellPoint *p = cell->points;
        
        while( p ){
            nb_points+=1;
            p = p->suiv;
        }
        cell = cell->suiv;
    }
     // printf("le nombre de points to: %.2d\n",nb_points);
    return nb_points;
}
