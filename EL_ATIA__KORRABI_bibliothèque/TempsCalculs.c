#include "Reseau.h"
#include "Chaine.h"
#include "SVGwriter.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
   printf("\033[0;93m");
  printf("\n| Bonjour et Bienvenue, Partie du Projet de Nadia EL ATIA  et Madjid KORRABI.");
  
  printf("\033[1;35m");
  printf(" \n\n| Veuillez entrer une valeur entre 1 et 3 \n\n| la valeur 1 correspond a la question 6.1 le temps de calculs se fera sur les l' instance proposée à savoir  00014_burma.cha  \n\n| la valeur 2 correspond à la question 6.3 (PARTIE : graphe arbre et table de hachage ) \n\n| la valeur 3 correspond à la question 6.3 (PARTIE : graphe liste chaînée ). \n|");
  printf("\n|\n|- Enfin Pour quitter le programme tapez 0\n|");
  printf("\n");
   printf("\033[1;36m");
  printf("| Veuillez entrer votre choix: ");
   printf("\033[0m");
}

double generateRandomDouble(int maximum){
    int nb = rand()%(maximum*100);
    return (nb * 1.0) / 100.0;
}
//Q 6.2 
Chaines* generationAleatoire(int nbChaines, int nbPointsChaine, int xmax, int ymax){

    CellChaine *cellC ;  /* CellChaine de Chaines */

    /* étape 1 : créer les nbChaines de chaines de Chaines */
    for (int i = 0; i < nbChaines; i++) {

        CellChaine *newCellChaine = calloc(1, sizeof(CellChaine));
        newCellChaine->numero = i;

        /* création des CellPoint de CellChaine */
        CellPoint *cellP ;

        /* étape 2 : crée les nbPointsChaines pour chaque CellChaine */
        for (int j = 0; j < nbPointsChaine; j++) {
            
            CellPoint *newCellPoint = calloc(1,sizeof(CellPoint));

            /*attribution des points entre 0 et xmax,ymax (noncompris)*/
            newCellPoint->x = generateRandomDouble(xmax);
            newCellPoint->y = generateRandomDouble(ymax);

           
            newCellPoint->suiv = cellP;// on lajoute en tete de cellp
            cellP = newCellPoint;
        }

        //insertions des points dans la CellChaine, puis de la CellChaine dans la tete de cellC
        newCellChaine->points = cellP;// on inialise la liste des point d'une chaine
        newCellChaine->suiv = cellC;// on met en tete la cellchaine 
        cellC = newCellChaine;
    }

    /* Création de la chaîne */
    Chaines *c = calloc(1, sizeof(Chaines));// on cree la chaine 
    c->gamma = 1;
    c->nbChaines = nbChaines;
    c->chaines = cellC;

    return c;
}


// test de  la fonction 6.1 et 6.3

int main(){
    int sortie = 0 ;

    do{
      
      menu(); 
      int rep;
      scanf("%d",&rep) ;
      switch (rep){
      case 0:;
          printf("\nMerci et au revoir :)\n");
          sortie=1;
          break;
      case 1:;
            printf("\nQuestion 6.1 : \n");
            clock_t temps_debut, temps_fin;
            double temps;

            FILE *f1 = fopen("00014_burma.cha","r")  ;
            Chaines *c = lectureChaines(f1);
            fclose(f1);

            printf("\nReseau Liste -> ");
            temps_debut = clock();
            reconstitueReseauListe(c);
            temps_fin = clock();
            FILE* f2 = fopen("6.1_Liste.txt ", "w");
            temps = ((double)(temps_fin - temps_debut)) / CLOCKS_PER_SEC;
            fprintf(f2, "%lf\n", temps);
            printf("-> Done \n");
            fclose(f2);
                     
            FILE* f3 = fopen("6.1_Hachage.txt", "w");
            printf("Reseau Hachage->");
            for(int i = 5; i <= 30; i+=5){
                
                temps_debut = clock();
                reconstitueReseauHachage(c, i);
                temps_fin = clock();
                temps = ((double)(temps_fin - temps_debut)) / CLOCKS_PER_SEC;
                fprintf(f3, "%d %lf\n", i, temps);
                
            }
            printf("-> Done \n");
            fclose(f3);
            

            printf("Reseau Arbre");
            temps_debut = clock();
            reconstitueReseauArbre(c);
            temps_fin = clock();
            f2 = fopen("6.1_ArbreQuat.txt ", "w");
            temps = ((double)(temps_fin - temps_debut)) / CLOCKS_PER_SEC;
            fprintf(f2, "%lf\n", temps);
            printf("-> Done \n");
            fclose(f2);

            liberer_Chaines(c);
  
            break;
      case 2 : ;
            printf("\nQuestion 6.3 Partie 1 \n");
            clock_t temps_debut2, temps_fin2;
            double tempsH, tempsA;
            FILE *f = fopen("donneesGrapheHachageArbre.txt", "w");
            Chaines *c2 ;
            for (int i = 500; i <= 5000; i += 500) {
                printf("%d\n ...",i);

                c2 = generationAleatoire(i, 100, 5000, 5000);

                temps_debut2 = clock();
                reconstitueReseauHachage(c2, (int)(i/50) );
                temps_fin2 = clock();
                tempsH = ((double)(temps_fin2 - temps_debut2)) / CLOCKS_PER_SEC;

                temps_debut2 = clock();
                reconstitueReseauArbre(c2);
                temps_fin2 = clock();
                tempsA = ((double)(temps_fin2 - temps_debut2)) / CLOCKS_PER_SEC;

                fprintf(f, "%d %lf %lf\n", i, tempsH, tempsA);
                
                liberer_Chaines(c2);
            }
            fclose(f);

            break ; 

      case 3 : ;
            printf("\n\nuestion 6.3 Partie 2 \n\n");
            clock_t temps_debut3, temps_fin3;
            double tempsL;
            FILE *f4 = fopen("donneesGrapheListe.txt", "w");
            Chaines *c3 ;
            for (int i = 500; i < 2000; i += 500) {
                printf("%d\n ...",i);

                c3 = generationAleatoire(i, 100, 5000, 5000);

                temps_debut3 = clock();
                reconstitueReseauListe(c3);
                temps_fin3 = clock();

                tempsL = ((double)(temps_fin3 - temps_debut3)) / CLOCKS_PER_SEC;

                fprintf(f4, "%d %lf\n", i, tempsL);

                liberer_Chaines(c3);
            }
            fclose(f4);
 
          break ;
      
      default:
          printf("Veuillez relancer le programme\n");
          sortie=1;
          break;
      }

      if (sortie==1){ 
      	break;
      }
      printf("\n\n");
      
    }while(1);


    return 0 ; 
      

}
