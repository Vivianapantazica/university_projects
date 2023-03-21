/* PANTAZICA VIVIANA-STEFANIA, GRUPA 315 CB */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _STIVA_IMPLEMENTATA_CU_LISTE_GENERICE_
#define _STIVA_IMPLEMENTATA_CU_LISTE_GENERICE_

#define VF(a) (((ASt)(a))->vf)
#define DIME(a) (((ASt)(a))->dime)

typedef struct celst
{ struct celst *urm; /* adr.urmatoarei celule */
void* info; /* adresa informatie */
} TCelSt, *ACelSt;


typedef struct stiva
{ size_t dime; /* dim.element */
ACelSt vf; /* adresa celulei din varf */
} TStiva, *ASt;

ASt CreareSt();
void* InitS(size_t d);
int Push(void* s, void* ae);
void ResetS(void* s);
void DistrS(void** s);
void AfisareStiva(ASt st, char* nume, FILE* out);

#endif