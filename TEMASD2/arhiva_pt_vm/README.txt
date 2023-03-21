/* PANTAZICA VIVIANA-STEFANIA, GRUPA 315 CB */

README


Structurile folosite sunt:

typedef struct serial /* lista de seriale */
{
    void* info; /* info care va fi castata la tipul Serial */
    struct serial* urm;
} TSerial, *TListaS;

typedef struct episod /* dimensiune variabila */
{   struct episod * urm;
    int info; /* durata in minute */
} TEpisod, *TListaE;

typedef struct sezon /* coada de episoade */
{   int nr_episoade; /* dim. sezon */
    TListaE ic_episod, sc_episod; /* adr.prima, ultima celula */
} TSezon, *TLSezoane;

typedef struct tip_serial /* coada de sezoane */
{
    int ID;
    char* nume;
    float rating;
    int nr_sezoane;
	int nr_ordine;
	TLSezoane ic_sezon, sc_sezon;
} Serial, *TLSeriale;

Am gandit legaturile dintre structuri astfel:

TSerial         Serial          TSezon          TEpisod
    |               |               |               |
    v               v               v               v
TListaS ->     TLSeriale ->     TLSezoane ->    TListaE

Pentru manipularea listelor, functiile se gasesc in functii_liste.c, iar antetele, in tlg.h.

1. TListaS InitializareL();
    -initializeaza o lista vida;

2. void StergereElementInterior(TListaS predecesor);
    -primeste adresa unui element dintr-o lista si sterge elementul care ii este succesor;

3. int fcmp(void* a, void* b);
    -functie de comparatie care ne ajuta la inserarea ordonata;
    -retinem ca s-a cerut ordonarea serialelor in lista descrescator dupa rating, iar in caz de
rating egal, crescator dupa nume;
    -fcmp returneaza astfel:
        - 0 daca x == y
		- valoare pozitiva daca x > y
		- valoare negativa daca x < y

4. void InserareL(TListaS *aL, void* serial, int fcmp(void*, void*), FILE* out);
    -functia de inserare ordonata a unui element in lista simplu inlantuita are in vedere urmatoarele
cazuri:
    * lista este vida;
    * lista are un singur element;
    * serialul trebuie inserat la inceput;
    * serialul trebuie inserat la final.

5. int EliminareL(TListaS* aL, char* serial);
    - folosindu-se de functia StergereElementInterior, functia EliminareL elimina un element dintr-o 
lista simplu inlantuita;

6. void AfisareLPtINT(TListaS* aL, int id, FILE* out);
    - functie de afisare a elementelor dintr- o lista simplu inlantuita;
    - are ca paramentru un int care reprezinta id-ul categoriei listei de seriale care trebuie afisata.

7. void AfisareLPtCHAR(TListaS* aL, char* id, FILE* out);
    - functie de afisare a elementelor dintr- o lista simplu inlantuita;
    - are ca paramentru un char* care reprezinta numele categoriei listei de seriale care trebuie afisata.

8. TListaS CautareSerial(TListaS* aL, char* nume_str);
    - returneaza adresa serialului cu numele nume_str primit ca parametru din lista aL;
    - in cazul in care acesta nu se afla in lista, functia returneaza NULL.

9. void InserareTop10(TListaS *aL, void* serial);
    - functie de inserare la final intr- o lista simplu inlantuita;
    - insereaza serialele primite ca parametru in categoria top10.

Pentru manipularea cozilor, functiile se gasesc in functii_coada.c, iar antetele, in coada.h.
1.AQ CreareQ();
    - creeaza o lista vida;
2.int InsQ(AQ c, TListaS* ae, FILE* out);
    - insereaza un element in coada;
    - sunt luate in considerare cazurile de coada vida si coada nevida.
3.void AfisareCoada(AQ q, char* nume, FILE* out);
    - afiseaza elementele unei cozi de la inceput la final.

Pentru manipularea stivelor, functiile se gasesc in functii_stiva.c, iar antetele, in stiva.h.
1.ASt CreareSt();
    - creeaza o stiva vida.
2.void AfisareStiva(ASt st, char* nume, FILE* out);
    -  - afiseaza elementele unei stive.
