/*PANTAZICĂ Viviana-Ștefania 315CB*/

/*-- tlg.h --- LISTA SIMPLU INLANTUITA GENERICA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct serial
{
    void* info;
    struct serial* urm;
} TSerial, *TListaS;

typedef struct episod /* dimensiune variabila */
{   struct episod * urm;
    int info; //durata in minute
} TEpisod, *TListaE;

typedef struct sezon
{   int nr_episoade; /* dim. sezon */
    TListaE ic_episod, sc_episod; /* adr.prima, ultima celula */
} TSezon, *TLSezoane;

typedef struct tip_serial
{
    int ID;
    char* nume;
    float rating;
    int nr_sezoane;
	int nr_ordine;
	TLSezoane ic_sezon, sc_sezon;
} Serial, *TLSeriale;

TListaS InitializareL();
void StergereElementInterior(TListaS predecesor);
int fcmp(void* a, void* b);
int EliminareL(TListaS* aL, char* serial);
void AfisareLPtINT(TListaS* aL, int id, FILE* out);
void AfisareLPtCHAR(TListaS* aL, char* id, FILE* out);
void InserareL(TListaS *aL, void* serial, int fcmp(void*, void*), FILE* out);
TListaS CautareSerial(TListaS* aL, char* nume_str);
void InserareTop10(TListaS *aL, void* serial);
#endif
