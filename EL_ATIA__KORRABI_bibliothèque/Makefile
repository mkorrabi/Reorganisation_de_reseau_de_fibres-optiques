EX = ChaineMain ReconstitueReseau TempsCalculs
CFLAGS = -g -Wall -Wextra -pedantic -ggdb
all : $(EX)

ChaineMain: ChaineMain.o Chaine.o SVGwriter.o
	gcc Chaine.o ChaineMain.o SVGwriter.o -o ChaineMain -Wall -g -lm

Chaine.o : Chaine.c Chaine.h SVGwriter.o
	gcc -c Chaine.c  -Wall -g -lm 

ChaineMain.o : ChaineMain.c
	gcc -c ChaineMain.c -Wall -g -lm 

SVGwriter.o: SVGwriter.c
	gcc -c SVGwriter.c $(CFLAGS)

ReconstitueReseau.o : ReconstitueReseau.c SVGwriter.o Hachage.o ArbreQuat.o 
	gcc -c ReconstitueReseau.c $(CFLAGS)

ReconstitueReseau : ReconstitueReseau.o Reseau.o SVGwriter.o Hachage.o ArbreQuat.o 
	gcc SVGwriter.o Reseau.o Chaine.o Hachage.o ArbreQuat.o  ReconstitueReseau.o -o ReconstitueReseau $(CFLAGS) -lm

Reseau.o : Reseau.c SVGwriter.o 
	gcc -c Reseau.c $(CFLAGS)

Hachage.o : Hachage.c Hachage.h SVGwriter.o 
	gcc -c Hachage.c $(CFLAGS)

ArbreQuat.o : ArbreQuat.c ArbreQuat.h SVGwriter.o 
	gcc -c ArbreQuat.c $(CFLAGS)
 
TempsCalculs.o : TempsCalculs.c SVGwriter.o Hachage.o ArbreQuat.o
	gcc -c TempsCalculs.c $(CFLAGS)

TempsCalculs : TempsCalculs.o Reseau.o SVGwriter.o Hachage.o ArbreQuat.o
	gcc SVGwriter.o Reseau.o Chaine.o Hachage.o ArbreQuat.o TempsCalculs.o -o TempsCalculs $(CFLAGS) -lm
 
clean: 
	rm  -f *.o