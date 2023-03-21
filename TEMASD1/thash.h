/*PANTAZICĂ Viviana-Ștefania 315CB*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlg.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*, FILE*);     /* functie afisare/eliberare un element */
typedef int (*TFHash)(void*);

typedef struct // structura tabelei hash
{
    size_t M;
    TFHash fh;
    TL2 *v;
} TH;

/* functii tabela hash */
TH* InitializareTH(int M);
int codHash(void * element, int M);
void AfisareTH(TH* ah, FILE *out);
int FindTH(TH* h, void* key, int M);
void DistrugeTH(TH** ah, TF fe);
void PrintBucket(TH* ah, int nr, FILE *out);
int FindTH(TH* h, void* key, int M);
void* GetTH(TH* h, void* key, int M);
int InserareTH(TH* a, void* ae, int M, TFCmp f, TFCmp f2);
void RemoveTH(TH* h, void* ae, int M);

#endif
