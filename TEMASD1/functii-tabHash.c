/*PANTAZICĂ Viviana-Ștefania 315CB*/

/*  functii-tabHash.c - functii tabela hash */

#include "thash.h"
#include "tlg.h"
#include <stdio.h>
#include <stdlib.h>

TH* InitializareTH(int M) // initializare tabela hash
{
    TH* h = (TH *) calloc(1, sizeof(TH));

    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TL2 *) calloc(M, sizeof(TL2));
    if(!h->v) {
        printf("eroare alocare vector de pointeri TL2 in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    int i;
    for(i=0; i<M; i++)
        h->v[i] = NULL;

    return h;
}

int codHash(void * element, int M) // functia hash
{
	char * key = element;
	int i, sum = 0;
	for(i = 0; i < strlen(key); i++)
	{
		sum = sum + key[i] - '\0';
	}
	return sum % M;
}

void DistrugeTH(TH** ah, TF fe)
{
    TL2 * p, el, aux;

    //parcurgere cu pointeri
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
        //daca exista elemente corespunzatoare acestui hash
        //eliberam info din celula si apoi eliberam celula
        for(el = *p; el != NULL; ) {
            aux = el;
            el = el->urm;
            free(aux->info);
            free(aux);
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}

void AfisareTH(TH* ah, FILE *out) // print
{
    TL2 p;
    int i;
    for(i = 0; i < ah->M; i++) {
        p = ah->v[i];
        if(p) {
            fprintf(out, "%d: ", i);
            TAdresa* adresa = (TAdresa*)(p->info);

	        TL2 prim = p;
            fprintf(out, "%s ", adresa->value);
	        TL2 el = p->urm;
	        for(; el != prim; el = el->urm) 
            {
		        fprintf(out, "%s ", ((TAdresa*)el->info)->value);
            }
	        fprintf(out, "\n");
        }
    }
}


void PrintBucket(TH* ah, int nr, FILE* out) //printeaza doar valorile din lista cu indicele nr
{
    TL2 p;
    int i;
    if (nr >= ah->M)
        return;

    p = ah->v[nr];
    if (p) {
        TAdresa* adresa = (TAdresa*)(p->info);

        TL2 prim = p;
        fprintf(out, "%s ", adresa->value);
        TL2 el = p->urm;
        for(; el != prim; el = el->urm) 
        {
            fprintf(out, "%s ", ((TAdresa*)el->info)->value);
        }
        fprintf(out, "\n");
    }
    else {
        fprintf(out, "VIDA\n");
    }
}

int FindTH(TH* h, void* key, int M)// returneaza 1/0 daca elem cu cheia key exista/nu exista in tabela
{
    int cod = codHash(key, M);
    TL2 element = h->v[cod];
    if(!element)
    {
        return 0;
    }
    
    TL2 prim = element;
	
	if(prim)
	{
        if(strcmp((char*)((TAdresa*)(element->info))->key, (char*)key) == 0)
        {
            return 1;
        }

        element = element->urm;
		for(; element!=prim; element=element->urm)
		{
			if(strcmp((char*)((TAdresa*)(element->info))->key, (char*)key) == 0)
			{
				return 1;
			}
		}
    }
    
    return 0;
}

int CmpDiferit(void* element1, void* element2)
{
    TAdresa* el1 = (TAdresa* )element1;
    TAdresa* el2 = (TAdresa* )element2;

    if(strcmp(el1->key, el2->key)!=0)
    {
        return 0;
    }
    return 1;
}

int CmpLexicografic(void* x, void* y)
{
    TAdresa* el1 = (TAdresa* )x;
    TAdresa* el2 = (TAdresa* )y;
    if(strcmp(el1->key, el2->key)<0)
    {
        return 0;
    }
    return 1;
}

  

int InserareTH(TH* a, void* ae, int M, TFCmp f, TFCmp f2)// put- insereaza un element in tabela, 
{                                                   // ordonat lexicografic in fct de cheie
    int cod = codHash((char*)((TAdresa*)ae)->key, M);
    int rez;
    TL2 element;
    if(a->v[cod])//cautam elem in lista specifica hash-ului
    {
        if(f(a->v[cod]->info, ae) == 1) // returnam 0 daca acesta exista deja
        {
            return 0;
        }
        else
        {
            for(element = a->v[cod]->urm; element != a->v[cod]; element = element->urm)
            {
                if(f(element->info, ae) == 1)
                    return 0;
            }
        }
    }

    rez = InserareDupa(&(a->v[cod]), ae, f2); // altfel, il inseram
    return rez;
}



void* GetTH(TH* h, void* key, int M) // intoarce valoarea value a elementului cu cheia key
{
	int cod = codHash(key, M);
    TL2 element = h->v[cod];
    if(!element)
    {
        return "NULL";
    }
    
    TL2 prim = element;
	
	if(prim)
	{
        if(strcmp((char*)((TAdresa*)(element->info))->key, (char*)key) == 0)
        {
            return (void*)((TAdresa*)(element->info))->value;
        }

        element = element->urm;
		for(; element!=prim; element=element->urm)
		{
			if(strcmp((char*)((TAdresa*)(element->info))->key, (char*)key) == 0)
			{
				return (void*)((TAdresa*)(element->info))->value;
			}
		}
    }
    
    return "NULL";
}

void RemoveTH(TH* h, void* key, int M)
{
    int cod = codHash((char*)key, M);
    TL2 element = h->v[cod];
    if(!element)
    {
        return;
    }
    
    TL2 prim = element;
	if(prim)
	{
        if(strcmp((char*)((TAdresa*)(element->info))->key, (char*)key) == 0)
        {
            if (element->urm == element) {
                h->v[cod] = NULL;
                free(element->info);
                free(element);
            }
            else {
                h->v[cod] = element->urm;
                element->pre->urm = element->urm;
                element->urm->pre = element->pre;
                free(element->info);
                free(element);
            }
            return;
        }

        element = element->urm;
		for(; element!=prim; element=element->urm)
		{
			if(strcmp((char*)((TAdresa*)(element->info))->key, (char*)key) == 0)
			{
				element->pre->urm = element->urm;
                element->urm->pre = element->pre;
    
			}
		}
    }

}
