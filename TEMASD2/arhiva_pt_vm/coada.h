/* PANTAZICA VIVIANA-STEFANIA, GRUPA 315 CB */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tlg.h"

#ifndef _COADA_IMPLEMENTATA_CU_LISTE_GENERICE_
#define _COADA_IMPLEMENTATA_CU_LISTE_GENERICE_


#define IC(a) (((AQ)(a))->ic)
#define SC(a) (((AQ)(a))->sc)
#define DIM(a) (((AQ)(a))->dime)

typedef struct celc { /* dimensiune variabila */
    struct celc * urm;
    void* info;
} TCelC, *ACelC;

typedef struct coada { 
    size_t dime;  /* dim.element */
    ACelC ic, sc; /* adr.prima, ultima celula */
} TCoada, *AQ;


AQ CreareQ();
int InsQ(AQ c, TListaS* ae, FILE* out);
int Extragere(void* a, void* ae);
void AfisareCoada(AQ q, char* nume, FILE* out);

#endif
