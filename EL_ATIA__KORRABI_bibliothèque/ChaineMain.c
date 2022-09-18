#include<stdio.h>
#include<stdlib.h>
#include "Chaine.h"
#include "SVGwriter.h"

/* fonction annexe 
ajout de la fonction liberer_Chaines pour éviter les fuites mémoire 
et pour libérér la Chaines créée lors dans le fichier ChaineMain.c */

void liberer_Chaines(Chaines* c){
    CellChaine *tmp = c->chaines;

    while( tmp ){
        CellPoint *p = tmp->points;

        while( p ){
            CellPoint *p_suiv = p->suiv;
            free( p );
            p = p_suiv;
        }

        CellChaine *tmp2 = tmp->suiv;
        free( tmp );
        tmp = tmp2 ;
    }
    free(c);
}


int main(int argc, char* argv[]){

    if (argc <2  ){// le nombre d'argument doit etre egale a 1 avec le nom de l'xecutable ca fait 2
    printf("Usage : ./%s <nameFile> \n", argv[0]) ;
    return -1 ;
    }

    //test de la fonction LectureChaine(FILE *f)
    FILE *f= fopen(argv[1],"r") ;
    Chaines*  c = lectureChaines(f); 

    //test de la fonction ecrireChaine(Chaines *FILE *f)
    FILE *f2=fopen("fileChaines.cha","w") ;
    ecrireChaines(c , f2) ;
    
    //Affichage du Reseau 
   /* afficheChainesSVG(c,"AffichageChaineExo1");
    
    //test de la fonction  longueurTotale(Chaines* C) 
    double k = longueurTotale(c) ;
    printf("\n \nLa longueur totale de la Chaine est de %f \n", k) ;
    
    // test de la fonction comptePointsTotal(Chaines* C)
    int i = comptePointsTotal(c);
    printf("La nombre total de points de la Chaine est de %d\n", i) ;
    
    
    */
    liberer_Chaines(c);
    fclose(f2); 
    fclose(f);


    return 0 ;
}
