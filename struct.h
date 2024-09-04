/*MARINICA ALEXANDRA RALUCA - GRUPA 315CB*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct structuranecesara {
	unsigned char red, green, blue;
} Tinfo;

typedef struct nod {
	unsigned char type;
	Tinfo info;
	struct nod *stang1, *drept1, *stang2, *drept2;
} TNod, *TArb;

typedef struct celula {
	TArb eleme;
	struct celula *urm;
} TCelula, *TLista;

typedef struct coada {
	TLista inc, sf;
} TCoada;

typedef struct celula2 {
	unsigned char type;
	Tinfo pixel;
	struct celula2 *urm;
} TCelula2, *TLista2;

typedef struct coada2 {
	TLista2 inc, sf;
} TCoada2;

int val_red (Tinfo **mat, unsigned int x, unsigned int y, unsigned int size);
int val_green (Tinfo **mat, unsigned int x, unsigned int y, unsigned int size);
int val_blue (Tinfo **mat, unsigned int x, unsigned int y, unsigned int size);
long long val_mean (Tinfo **mat, unsigned int x, unsigned int y, unsigned int size);
TArb ConstrFr(int x, int y, int z);
TArb makeArb (unsigned int x, unsigned int y, unsigned int size, Tinfo **mat, int factor);
int NrNiv (TArb r);
int nrFrunze (TArb arb);
int dimLatura (TArb arb, int nivel);
int val_max(int x, int y, int z, int t);


TCoada* InitQ ();
int IntrQ(TCoada *c, TArb arb);
TArb ExtrQ (TCoada *c, TArb arbsalvat);


TCoada2* InitQ2 ();
int IntrQ2(TCoada2 *c, int x, int y, int z, int tip);
void AfisareQ2(TCoada2 *c);
Tinfo ExtrQ2 (TCoada2 *c, Tinfo pixelsalvat);
int ExtrTipPixelDinCoada (TCoada2 *c);
TArb constrArbore(TCoada2 *c, TArb arb);
void CreareMatrice (TArb arb, Tinfo **matImag,int size, int x, int y);
void AfisareMatrice (Tinfo **mat, unsigned int size, FILE *out);

void AfisareArbor ( TArb arb );