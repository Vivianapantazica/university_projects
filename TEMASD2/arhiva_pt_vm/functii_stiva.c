/* PANTAZICA VIVIANA-STEFANIA, GRUPA 315 CB */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stiva.h"
#include "tlg.h"


//functie de creare stiva
ASt CreareSt()
{
    ASt st = (ASt)malloc(sizeof(TStiva));
    st->vf = NULL;
    return st;
}

// Inserare w in stiva = inserare la inceput de lista
// Stiva in care se face inserarea este void* s;
int Push(void* s, void* ae)
{
ACelSt aux;
aux = (ACelSt)malloc(sizeof(TCelSt));
if(!aux) return 0;
//alocare aux->info + testare
memcpy(aux->info, ae, ((ASt)s)->dime);
aux->urm = ((ASt)s)->vf; //aux->urm = VF(s)
((ASt)s)->vf = aux;
return 1;
}

int Pop(void* s, void* ae)
{
ACelSt aux = VF(s); //varful stivei
if(aux == NULL) return 0;
memcpy(ae, aux->info, ((ASt)s)->dime);
VF(s) = aux->urm;
free(aux);
return 1;
}

void ResetS(void* s)
{
    ACelSt aux;
    ACelSt p;
    aux = (ACelSt)malloc(sizeof(TCelSt));
    if(!aux) return;    

    //distrugere lista VF(s);
    aux = VF(s);
    while(aux)
    {
        p = aux;
        aux = aux->urm;
        free(p->info);
        free(p);
    }
    VF(s) = NULL;
}

void DistrS(void** s)
{
    ResetS(*s);
    free(*s);
    *s = NULL;
}

void AfisareStiva(ASt st, char* nume, FILE* out)
{
    if(!st) {
        fprintf(out, "Categoria %s: [].\n", nume);
        return;
    }
    ASt p = st;
    ACelSt aux = (ACelSt)malloc(sizeof(TCelSt));
    if(!aux)    
        return;
    aux = VF(p);
    fprintf(out, "Categoria %s: [", nume);
    for( ; VF(p) != NULL; aux = aux->urm)
    {
        fprintf(out, "(%s, %.1f)", ((TLSeriale)aux->info)->nume, ((TLSeriale)aux->info)->rating);
        if(aux->urm != NULL)
			fprintf(out, ", ");
    }
    fprintf(out, "].\n");
}