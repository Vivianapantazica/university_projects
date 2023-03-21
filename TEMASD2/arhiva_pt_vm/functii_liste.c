/* PANTAZICA VIVIANA-STEFANIA, GRUPA 315 CB */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tlg.h"

/* initializare lista de seriale */
TListaS InitializareL()//initializez o lista vida
{
	
	TListaS aL = calloc(1, sizeof(TListaS));
	if(aL == NULL)
	{
		printf("Eroare alocare memorie\n");
		exit(-1);
	}
	aL = NULL;
	return aL;

}

/* functie de comparatie auxiliara pentru sortarea listei */
int fcmp(void* a, void* b)
{
	/*
		fcmp(x, y) intoarce:
		- 0 daca x == y
		- valoare pozitiva daca x > y
		- valoare negativa daca x < y
	 */
	
	Serial* serialA = a;
	Serial* serialB = b;
	if(serialA->rating == serialB->rating)
		return -strcmp(serialA->nume, serialB->nume);
	return (serialA->rating > serialB->rating ? 1 : -1);
}

/* functie care insereaza in lista de seriale un serial
ordonat descrescator dupa rating; rating egal -> crescator dupa nume */

void InserareL(TListaS *aL, void* serial, int fcmp(void*, void*), FILE* out)
{
	TListaS elem = NULL;
	TListaS aux = *aL;
	TListaS prim = *aL;
	Serial* s = serial;
	int pozitie = 1;
	
	if(prim != NULL) //daca lista nu e vida
	{
		do
		{
			if(strcmp((char*)((Serial*)(aux->info))->nume, s->nume) == 0)
				return; // verific daca elementul exista deja in lista, caz in care ies din functie
			aux = aux->urm;
		}
		while(aux != NULL);
	
	}

	//daca elementul nu este in lista, atunci il inserez
	elem = calloc(1, sizeof(TSerial));
	elem->urm = NULL;
	//copiez informatia in aux->info
	elem->info = malloc(sizeof(Serial));
	memcpy(elem->info, serial, sizeof(TSerial));
	((Serial*)elem->info)->rating = s->rating;

	if(prim == NULL) //lista vida
	{
		*aL = elem;
		fprintf(out, "Serialul %s a fost adaugat la pozitia 1.\n", s->nume);
		return;
	}
	
	
	
	if(prim->urm == NULL)
	{
		if(fcmp(prim->info, serial) <= 0)
		{
			elem->urm = *aL;
			*aL = elem;
			fprintf(out, "Serialul %s a fost adaugat la pozitia 1.\n", s->nume);
			return;
				
		} else {
			prim->urm = elem;
			fprintf(out, "Serialul %s a fost adaugat la pozitia 2.\n", s->nume);
			return;
		}
	}
	else {
		//parcurgem lista
		if (fcmp(prim->info, serial) <= 0) {
			*aL = elem;
			elem->urm = prim;
			fprintf(out, "Serialul %s a fost adaugat la pozitia 1.\n", s->nume);
			return;
		}

		while(prim->urm != NULL)
		{	
			pozitie++;
			//pentru a face inserarea in ordine descrescatoare dupa rating facem acest test:
			if(fcmp(prim->urm->info, serial) <= 0)
			{
				//inserare ordonata: inserez dupa elem p
				elem->urm = prim->urm;
				prim->urm = elem;
				fprintf(out, "Serialul %s a fost adaugat la pozitia %d.\n", s->nume, pozitie);
				return;
			}
			
			prim = prim->urm;
		}
		pozitie++;
		prim->urm = elem;
		fprintf(out, "Serialul %s a fost adaugat la pozitia %d.\n", s->nume, pozitie);
		return;
	}
}




/* functie care sterge un element din interiorul listei, 
primind ca parametru adresa predecesorului */

void StergereElementInterior(TListaS predecesor)
{
    // salvam referinta la elementul de sters
    TListaS deSters = predecesor->urm;

    // scurcircuitam elementul
    predecesor->urm = predecesor->urm->urm;

    // si il stergem
    free(deSters); 
}


/* functie de eliminare a unui serial dintr-o lista */

int EliminareL(TListaS* aL, char* serial)
{

// daca lista e vida returam 0
if (*aL == NULL)
 return 0;

//Serial* s = serial;
char* nume = serial;

// daca este primul element, atunci
// il stergem si mutam capul
if (strcmp(((Serial*)(*aL)->info)->nume, nume) == 0)
 {
 TListaS aux = *aL;
 *aL = (*aL)->urm;
 free(aux);
 return 1;
 }

// cautam predecesorul
TListaS elem = *aL, ant = NULL;
while ((elem->urm != NULL) && (strcmp(((Serial*)elem->info)->nume, nume) != 0))
{
	ant = elem;
	elem = elem->urm;	
}

// daca a fost gasit, atunci il stergem
StergereElementInterior(ant);

return 1;
}

/* functie de afisare a listei */

void AfisareLPtINT(TListaS* aL, int id, FILE* out)
{
	if(!*aL) {
        fprintf(out, "Categoria %d: [].\n", id);
        return;
    }
	TListaS p = *aL;
	fprintf(out, "Categoria %d: [", id);
	for(; p != NULL; p = p->urm) {
		Serial * s = (Serial *)(p->info);
		fprintf(out, "(%s, %.1f)", s->nume, s->rating);
		if(p->urm != NULL)
			fprintf(out, ", ");
		
    }
	fprintf(out, "].\n");
}

void AfisareLPtCHAR(TListaS* aL, char* id, FILE* out)
{
	if(!*aL) {
        fprintf(out, "Categoria %s: [].\n", id);
        return;
    }
	TListaS p = *aL;
	fprintf(out, "Categoria %s: [", id);
	for(; p != NULL; p = p->urm) {
		Serial * s = (Serial *)(p->info);
		fprintf(out, "(%s, %.1f)", s->nume, s->rating);
		if(p->urm != NULL)
			fprintf(out, ", ");
		
    }
	fprintf(out, "].\n");
}

/*TSerial* CautarePozitie(TSerial* elem, int pozitie)
{
	int curent = 0;
	while(elem != NULL && i<pozitie)
	{
		elem = elem->urm;
		i++;
	}
	if(i == pozitie)
		return elem;
	else
		return NULL;
}*/

/*functie care parcurge o lista, cautand un serial cu numele nume_str primit ca parametru*/
TListaS CautareSerial(TListaS* aL, char* nume_str)
{
	if(*aL == NULL)
		return NULL;
	TListaS elem = *aL;
	//((Serial*)elem->info)->nume = calloc(strlen(((Serial*)elem->info)->nume)+1, sizeof(char));
	//strcpy(((Serial*)elem->info)->nume, ((Serial*)((*aL)->info))->nume);
	
	while (elem != NULL) 
	{
		if(strcmp(((Serial*)elem->info)->nume, nume_str) != 0)
		{
			return elem;
		}
		elem = elem->urm;	
	}
	
	return NULL;
	
}

// Inserare element la sfarsitul unei
// liste simplu inlantuite
void InserareTop10(TListaS *aL, void* serial)
{
	
TListaS elem = NULL;
Serial* s = serial;

// Alocare si initializare nod
elem = calloc(1, sizeof(TSerial));
elem->urm = NULL;

//copiez informatia in aux->info
elem->info = malloc(sizeof(Serial));
memcpy(elem->info, serial, sizeof(TSerial));
strcpy(((Serial*)elem->info)->nume, s->nume);
((Serial*)elem->info)->rating = s->rating;

// daca avem lista vida
if ( *aL == NULL)
 	{// doar modificam capul listei
	*aL = elem;
	return;
	}
else
	{
	// parcurgem lista pana la ultimul nod
	TListaS aux = *aL;
	while (aux->urm != NULL)
		aux = aux->urm;
	// adaugam elementul nou in lista
	aux->urm = elem;
	//((Serial*)(*aL)->info)->nr_ordine ++;
	}
}
