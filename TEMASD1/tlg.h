/*PANTAZICĂ Viviana-Ștefania 315CB*/

/*-- tlg.h --- LISTA DUBLU INLANTUITA CIRCULARA SI GENERICA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_


typedef struct { // tipul structurii
	char* key;
	char* value;
} TAdresa;

typedef struct celula2
{
  void* info;           // adresa informatie 
  struct celula2 *urm;  //   adresa urmatoarei celule
  struct celula2 *pre;  //   adresa celulei anterioare 
} TCelula2, *TL2;       //   tipurile celula, lista

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*, FILE*);     /* functie afisare/eliberare un element */

/* functii lista generica */
TL2* InitializareLDIC();
void DistrugeLDIC(TL2* aL);
size_t LungimeLDIC(TL2* a);
void afisareLDIC(TL2* aL, FILE* out);
int InserareDupa(TL2* a, void* x, TFCmp f);
int CmpDiferit(void* element1, void* element2);
int CmpLexicografic(void* x, void* y);
#endif
