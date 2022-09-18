#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SVGwriter.h"

void afficheChainesSVG(Chaines *C, char* nomInstance){
    //int i;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}


void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}

void SVGinit(SVGwriter *svg, char *nom, int sizeX, int sizeY) {
  char filename[100];

  strcpy(filename,nom);
  strcat(filename,".html");
  
  svg->file=fopen(filename, "w");

  if (svg->file==NULL) {
    printf("Unable to create %s\n",nom);
    exit(1);
  }
  
  strcpy(svg->lineColor, Red);
  strcpy(svg->pointColor, Black);

  svg->sizeX=sizeX;
  svg->sizeY=sizeY;

  svg->gencol[0]='0';svg->gencol[1]='1';svg->gencol[2]='2';svg->gencol[3]='3';
  svg->gencol[4]='4';svg->gencol[5]='5';svg->gencol[6]='6';svg->gencol[7]='7';
  svg->gencol[8]='8';svg->gencol[9]='9';svg->gencol[10]='A';svg->gencol[11]='B';
  svg->gencol[12]='C';svg->gencol[13]='D';svg->gencol[14]='E';svg->gencol[15]='F';

  fprintf(svg->file,"<html><body><svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\"");
  fprintf(svg->file, " width=\"100%%\" height=\"100%%\"");
  fprintf(svg->file, " viewBox=\"%lf %lf %lf %lf\"", -2.0, -2.0, sizeX+7.0, sizeY+7.0);
  fprintf(svg->file, " preserveAspectRatio=\"yes\">\n");
  fprintf(svg->file, "<g >\n\n");

   svg->lineColor[0]='#';
}


void SVGlineColor(SVGwriter *svg, char *col) {
  strcpy(svg->lineColor,col);
}

void SVGlineRandColor(SVGwriter *svg){
  int i;
  for (i=1;i<=6;i++) svg->lineColor[i]=svg->gencol[rand()%16];

}

void SVGpointColor(SVGwriter *svg, char *col) {
  strcpy(svg->pointColor,col);
}

void SVGpoint(SVGwriter *svg, double x, double y) {
  fprintf(svg->file,"<circle cx=\"%lf\" cy=\"%lf\" r=\"2\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\" />\n",x,y,svg->pointColor,svg->pointColor);
}


void SVGline(SVGwriter *svg,double xa,double ya,double xb,double yb) {
  fprintf(svg->file, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" ", xa, ya, xb, yb);
  fprintf(svg->file, " style=\"stroke:%s;stroke-width:2\"/>\n", svg->lineColor);    
}


void SVGfinalize(SVGwriter *svg) {
  fprintf(svg->file, "\n\n</g></svg></body></html>\n");
  fclose(svg->file);
  svg->file=NULL;
}
