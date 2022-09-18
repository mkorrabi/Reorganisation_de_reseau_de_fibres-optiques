#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include "Reseau.h"
#include "Chaine.h"
#include "SVGwriter.h"
#include "Hachage.h"
#include "ArbreQuat.h"

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


void menu() { 
  printf("\n\n Bonjour et Bienvenue !\nVoici le projet de Nadia EL ATIA et Madjid KORRABI\n\n");
 
}

// 1 : Réseau Liste
// 2 : Réseau Hachage
// 3 : Réseau Arbre


int main (int argc, char** argv){
    if (argc != 3) {
        printf("Usage : %s <nameFile.cha> <value> \n", argv[0]) ;
		exit(1);
    }
    
    menu();
    
    int rep = atoi(argv[2]);  //convertit le caractère argv[2] en entier

    FILE *f = fopen("00014_burma.cha","r") ;
    Chaines *c = lectureChaines(f);

    switch (rep)
    {
    case 1 : ;
    	printf("Vous avez choisi la valeur 1 : Reconstitution du Reseau par liste\n ");
        Reseau *r1 = reconstitueReseauListe(c);  /* test question 2.2 */ 
        nbCommodites(r1);
        nbLiaisons(r1);
        afficheReseauSVG(r1 ,"AffichageReseauListe");
        FILE *f1 = fopen("fileReseauListe.res", "w");      /*test de la question 3.2 */
        ecrireReseau(r1,f1);
        fclose(f1); 
        printf("Veuillez trouver les fichier AffichageReseauListe.html et fileReseauListe \n\n"); 
        libere_Reseau(r1) ;
        break;
    case 2 : ;
        printf("Vous avez choisi la valeur 2 : Reconstitution du Reseau par Hachage\n ");
        Reseau *r2 = reconstitueReseauHachage(c, 50);
        afficheReseauSVG(r2, "AffichageReseauHachage");
        
        FILE *f2= fopen("fileReseauHachage", "w");
        ecrireReseau(r2,f2);
        fclose(f2);
        printf("Veuillez trouver les fichier AffichageReseauHachage.html et fileReseauHachage \n\n");        
        libere_Reseau(r2) ;
        break ; 

    case 3 : 
           printf("Vous avez choisi la valeur 3 : Reconstitution du Reseau par Arbre Quaternaire\n");
          Reseau *r3 = reconstitueReseauArbre(c);
          afficheReseauSVG(r3, "AffichageReseauArbre");

          FILE *f3 = fopen("fileReseauArbre", "w");
          ecrireReseau(r3, f3);
          fclose(f3); 
           printf("Veuillez trouver les fichier AffichageReseauArbre.html et fileReseauArbre \n\n");
          libere_Reseau(r3) ;
       
          break ;
          
    default:
        printf("\nveuillez entrez une valeur :) \n");
        break;
    }
    fclose( f ) ;
    
  
    liberer_Chaines(c);

    return 0;

}


