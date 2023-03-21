/* PANTAZICA VIVIANA-STEFANIA, GRUPA 315 CB */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "coada.h"
#include "tlg.h"

//Creare coada vida
AQ CreareQ()
{
    AQ q = (AQ)malloc(sizeof(TCoada));
    q->ic = q->sc = NULL;
    return q;
}

//Inserare in coada: CONDITIE COADA VIDA - a->ic == NULL && a->sc == NULL

int InsQ(AQ c, TListaS* aL, FILE* out)
{
    // Creeaza un nou nod
    ACelC aux = (ACelC)malloc(sizeof(TCelC));
    if(!aux)
        return 0;
    aux->urm = NULL;
    
    aux->info = malloc(sizeof(Serial));
    if(!aux->info) 
        return 0;
    memcpy(aux->info, (void*)aL, sizeof(Serial));
    strcpy(((Serial*)aux->info)->nume, ((Serial*)((*aL)->info))->nume);
    ((Serial*)aux->info)->rating = ((Serial*)((*aL)->info))->rating;
    ((Serial*)aux->info)->ID = ((Serial*)((*aL)->info))->ID;
    TListaS s = *aL;
    // Daca coada este vida, atunci nodul aux va fi si IC si SC pentru c
    if (SC(c) == NULL && IC(c)== NULL) {
       
        IC(c) = aux;;
        SC(c) = aux;
        fprintf(out, "Serialul %s", ((Serial*)(s->info))->nume);
		fprintf(out, " se afla in coada de asteptare pe pozitia 1.\n");
        return 1;
    }
    // Adaugam noul nod la finalul cozii si schimbam SC
    SC(c)->urm = aux;
    SC(c) = aux;
    int pozitie = 1 + (SC(c) - IC(c))/sizeof(TCelC);
    fprintf(out, "Serialul %s", ((Serial*)(s->info))->nume);
    fprintf(out, "se afla in coada de asteptare pe pozitia %d.\n", pozitie);
    return 1;
}

void AfisareCoada(AQ q, char* nume, FILE* out)
{
    
    if(q->ic == NULL && q->sc == NULL) {
        fprintf(out, "Categoria %s: [].\n", nume);
        return;
    }
    AQ p = q;
    
    fprintf(out, "Categoria %s: [", nume);
    for( ; IC(p) != NULL; IC(p) = IC(p)->urm)
    {
        ACelC aux = IC(p);
        if(!aux) 
            return;
        //memcpy(aux->info, (void*)IC(p), sizeof(Serial));    
        strcpy(((Serial*)aux->info)->nume, ((Serial*)((IC(p))->info))->nume);
        ((Serial*)aux->info)->rating = ((Serial*)((IC(p))->info))->rating;
        ((Serial*)aux->info)->ID = ((Serial*)((IC(p))->info))->ID;
       
        char* nume1 = ((Serial*)aux->info)->nume;
        float rating1 = ((Serial*)aux->info)->rating;
        fprintf(out, "(%s, %.1f)", nume1, rating1);
        if(IC(p)->urm != NULL)
		    fprintf(out, ", ");
    }
    fprintf(out, "].\n");
}

