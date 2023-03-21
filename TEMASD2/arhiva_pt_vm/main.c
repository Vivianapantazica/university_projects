/* PANTAZICA VIVIANA-STEFANIA, GRUPA 315 CB */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tlg.h"
#include "coada.h"
#include "stiva.h"



int main(int argc, char* argv[]) // extragem argumentele din linia de comanda
{
	FILE* in = fopen(argv[1], "rt");
	FILE* out = fopen(argv[2], "w");
	char * line = NULL;
	size_t len = 0;
	//TH* h = InitializareTH(M); // initializam tabela hash
	if (in == NULL)
		return 0;
	TListaS Tendinte = InitializareL();
	TListaS Documentare = InitializareL();
	TListaS TutorialePentruLimbajC = InitializareL();
	TListaS Top10inRomania = InitializareL(); 

	AQ watch_later = CreareQ();
	ASt history = CreareSt();

	while (getline(&line, &len, in) != -1) {
		char * operatie = strtok(line, " ");//retinem operatia
		if (operatie[strlen(operatie) - 1] == '\n')
			operatie[strlen(operatie) - 1] = '\0';
			while(line[strlen(line)-1]=='\n')
			{
				line[strlen(line)-1]='\0';
			}

		if(strcmp(operatie, "add")==0)/* se realizeaza operatia de adaugare */
		{							  /* a unui serial in baza de date      */
			char * id_str = strtok(NULL, " ");
			if (id_str[strlen(id_str) - 1] == '\n')
					id_str[strlen(id_str) - 1] = '\0';
			int id = atoi(id_str);
			char * nume = strtok(NULL, " ");
			if (nume[strlen(nume) - 1] == '\n')
				nume[strlen(nume) - 1] = '\0';
			char* rating_str = strtok(NULL, " ");
			if (rating_str[strlen(rating_str) - 1] == '\n')
					rating_str[strlen(rating_str) - 1] = '\0';
			float rating = atof(rating_str);
			Serial* s = calloc(1, sizeof(Serial));
			s->ID = id;
			s->nume = calloc(strlen(nume) + 1, sizeof(char));
			strcpy(s->nume, nume);
			s->rating = rating;
			if(id == 1)
				InserareL(&Tendinte, s, fcmp, out);
			if(id == 2)
				InserareL(&Documentare, s, fcmp, out);
			if(id == 3)
				InserareL(&TutorialePentruLimbajC, s, fcmp, out);
			if(id == 4)
				InserareL(&Top10inRomania, s, fcmp, out);
			
		}

		if(strcmp(operatie, "show") == 0)
			{
				char* id_str = strtok(NULL, " \n");
				if (id_str[strlen(id_str) - 1] == '\n')
					id_str[strlen(id_str) - 1] = '\0';
				int id = atoi(id_str);
				
				if(id == 1)
					{
						AfisareLPtINT(&Tendinte, 1, out);
					}
				if(id == 2)
					{
						AfisareLPtINT(&Documentare, 2, out);
					}
				if(id == 3)
				{
					AfisareLPtINT(&TutorialePentruLimbajC, 3, out);
				}
				if(strcmp(id_str, "top10") == 0)
				{
					AfisareLPtCHAR(&Top10inRomania, id_str, out);
				}
				else
				{
					if(strcmp(id_str, "later") == 0)
					{
						AfisareCoada(watch_later, id_str, out);
					}
	
				}
			}
		
		if(strcmp(operatie, "add_sez") == 0)/* se realizeaza operatia 		*/
		{								    /* de adaugare a unui sezon nou */ 
			int i;
			Serial* s = calloc(1, sizeof(Serial));
			//ii retinem numele
			char* nume_str = strtok(NULL, " ");
			if (nume_str[strlen(nume_str) - 1] == '\n')
					nume_str[strlen(nume_str) - 1] = '\0';
			s->nume = calloc(strlen(nume_str)+1,sizeof(char));
			strcpy(s->nume, nume_str);
			//ii retinem nr de episoade
			char* nr_str = strtok(NULL, " ");
				if (nr_str[strlen(nr_str) - 1] == '\n')
					nr_str[strlen(nr_str) - 1] = '\0';
			int nr_episoade = atoi(nr_str);
			
			for(i=1; i<=nr_episoade; i++)
			{
				char* durata_str = strtok(NULL, " \n");
				if (durata_str[strlen(durata_str) - 1] == '\n')
					durata_str[strlen(durata_str) - 1] = '\0';
				int durata_episod = atoi(durata_str);
				
			}
			fprintf(out, "Serialul %s are un sezon nou.\n", nume_str);
		}
		
    }
	fclose(in);

}
