/*PANTAZICĂ Viviana-Ștefania 315CB*/

/*-- main.c  */
#include <stdio.h>
#include "tlg.h"
#include "thash.h"
#include <string.h>


int main(int argc, char* argv[]) // extragem argumentele din linia de comanda
{
	int M = atoi(argv[1]);
	FILE* in = fopen(argv[2], "rt");
	FILE* out = fopen(argv[3], "w");
	char * line = NULL;
	size_t len = 0;
	TH* h = InitializareTH(M); // initializam tabela hash
	if (in == NULL)
		return 0;

	while (getline(&line, &len, in) != -1) {
		char * operatie = strtok(line, " ");//retinem operatia
		if (operatie[strlen(operatie) - 1] == '\n')
			operatie[strlen(operatie) - 1] = '\0';
		if(strcmp(operatie, "put")==0)/* se realizeaza operatia PUT */
		{
			char * key = strtok(NULL, " ");
			if (key[strlen(key) - 1] == '\n')
					key[strlen(key) - 1] = '\0';
			char * value = strtok(NULL, " ");
			if (value[strlen(value) - 1] == '\n')
			value[strlen(value) - 1] = '\0';
			
			TAdresa* adresa = calloc(1, sizeof(TAdresa));
			adresa->key = calloc(strlen(key)+1, sizeof(char));
			adresa->value = calloc(strlen(value)+1, sizeof(char));
			strcpy(adresa->key, key);
			strcpy(adresa->value, value);
			InserareTH(h, (void*)adresa, M, CmpDiferit, CmpLexicografic);
		}
		if(strcmp(operatie, "print")==0)/* se realizeaza operatia PRINT */
			AfisareTH(h, out);
		if(strcmp(operatie, "print_bucket")==0)
			{
				char* nr_str = strtok(NULL, " ");
				if (nr_str[strlen(nr_str) - 1] == '\n')
					nr_str[strlen(nr_str) - 1] = '\0';
				int nr = atoi(nr_str);
				PrintBucket(h, nr, out);
			}
		if(strcmp(operatie, "find")==0)/* se realizeaza operatia PRINT_BUCKET */
		{
			char* key_str = strtok(NULL, " ");
			if (key_str[strlen(key_str) - 1] == '\n')
					key_str[strlen(key_str) - 1] = '\0';
			int result = FindTH(h, (void*)key_str, M);
			if(result == 1)
				fprintf(out, "True\n");
			else
				fprintf(out, "False\n");

		}
		if(strcmp(operatie, "get")==0)/* se realizeaza operatia GET */
		{
			char* key_str = strtok(NULL, " ");
			if (key_str[strlen(key_str) - 1] == '\n')
					key_str[strlen(key_str) - 1] = '\0';
			char* value_str = GetTH(h, (void*)key_str, M);
			fprintf(out, "%s\n", value_str);
		}
		if(strcmp(operatie, "remove")==0)
		{
			char* key_str = strtok(NULL, " ");
			if (key_str[strlen(key_str) - 1] == '\n')
					key_str[strlen(key_str) - 1] = '\0';
			RemoveTH(h, (void*)key_str, M);
		}
    }
	fclose(in);

}
