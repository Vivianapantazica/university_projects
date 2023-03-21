/*PANTAZICĂ Viviana-Ștefania 315CB*/

/*--- functiiLG.c -- operatii de baza pentru lista dublu inlantuita circulara si generica---*/
#include "tlg.h"
#include "thash.h"

TL2* InitializareLDIC()//initializez o lista vida
{
	TL2* aL = calloc(1, sizeof(TL2));
	if(aL == NULL)
	{
		printf("Eroare alocare memorie\n");
		exit(-1);
	}
	return aL;

}

void InserareLDIC(TL2* aL, void* ae) //insereaza un element in lista, care contine cheia ae
{
	TL2 aux = *aL;
	TL2 prim = *aL;
	TL2 ultim;
	TAdresa* adresa = ae;
	if(prim) //daca lista nu e vida
	{
		do
		{
			if(strcmp(((char*)((TAdresa*)(aux->info))->key), adresa->key) == 0)
				return; // verific daca elementul exista deja in lista, caz in care ies din functie
			aux = aux->urm;
		}while(aux != prim);
	
	}
	//daca elementul nu este in lista, atunci il inserez
	aux = calloc(1, sizeof(TCelula2));
	aux->urm = NULL;
	//copiez informatia in aux->info
	aux->info = malloc(sizeof(TCelula2));
	memcpy(aux->info, ae, sizeof(TCelula2));

	if(prim)
	{
		ultim = (*aL)->pre;
		TL2 p = prim->urm;
		for(; p != prim; p=p->urm)
		{
			//pentru a face inserarea in ordine lexicografica facem acest test
			if(strcmp(((char*)((TAdresa*)p->info)->key), adresa->key) > 0) //inserare ordonata: inserez dupa elem p
			{
				aux->pre = p;
				aux->urm = p->urm;
				p->urm->pre = aux;
				p->urm = aux;
			}
		}
	
	}
	
	if(prim == NULL) // inserez element la inceput, lista fiind vida
		{
			prim = aux;
			ultim = aux;
			aux->pre = ultim;
			aux->urm = prim;

			*aL = aux;
		}

}


void DistrugeLDIC(TL2* aL) /* distruge lista */
{
	while(*aL != NULL)
    {
        TL2 aux = *aL; 
		TL2 prim = *aL;
		TL2 ultim = (*aL)->pre;    
        if (!aux)
            return;
		while(prim != ultim)
		{
			aux = prim;
			prim = prim->urm;
			free(((TAdresa*)(aux->info))->key);
			free(((TAdresa*)(aux->info))->value);
			free(aux->info);
			free(aux);
		}
		aux = prim;
        free(((TAdresa*)(aux->info))->key);
		free(((TAdresa*)(aux->info))->value);
		free(aux->info);
		free(aux); 
        free(*aL);
    }
}

size_t LungimeLDIC(TL2* a)/* numarul de elemente din lista */  
{
	size_t lg = 0;
	TL2 prim = *a;
	
	if (!prim)
		return 0;

	TL2 p = (*a)->urm;

     /* parcurge lista, numarand celulele */
	for (; p != prim; p = p->urm)
        lg++;

	return lg;
}

void afisareLDIC(TL2* aL, FILE* out) // afisarea valorilor dintr-o lista
{
	if(!*aL) {
        printf("Lista vida\n");
        return;
    }
	
	TL2 prim = *aL;
	TL2 p = (*aL)->urm;
	for(; p != prim; p = p->urm) {
		TAdresa * adresa = (TAdresa *)(p->info);
		fprintf(out, "%s ", (char*)adresa->value);
		
    }
	fprintf(out, "\n");
}

int InserareDupa(TL2* a, void* x, TFCmp f)
{
    TL2 aux = (TL2)malloc(sizeof(TCelula2));
    TL2 el, p;
    if(!aux)
        return 0;
    aux->info = x;
    if(*a == NULL) //daca trebuie inserat la inceputul listei
    {
        aux->urm = aux;
        aux->pre = aux;
        *a = aux;
    }
    else 
    {
        if(f(x, (*a)->info)==0)//daca exista deja in lista
        { 
            aux->urm = *a;
            aux->pre = (*a)->pre;
            (*a)->pre->urm = aux;
            (*a)->pre = aux;
            *a = aux;
        }
        else //daca nu exista in lista
        {
            p = (*a)->urm;
            while(p != (*a) && f(x, p->info))
                p = p->urm;
            aux->pre = p->pre;
            aux->urm = p;
            p->pre->urm = aux;
            p->pre = aux;
        }
    }
    return 1; //inserarea a reusit
}




