#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

int main(int argc, char* argv[]) // extragem argumentele din linia de comanda
{
    FILE* in = fopen(argv[1], "rt");
    FILE* out = fopen(argv[2], "w");
    char * line = NULL;
    size_t len = 0;
    
    char alphabet_array[68] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! "};
    
    if (in == NULL)
        return 0;

    struct Trie* T1 = createNode();
    struct Trie* T2 = createNode();
    while (getline(&line, &len, in) != -1) 
    {
        char * operatie = strtok(line, " ");
        if (operatie[strlen(operatie) - 1] == '\n')
            operatie[strlen(operatie) - 1] = '\0';
       
        if(strcmp(operatie, "add_book")==0) /* se realizeaza operatia de adaugare */
            {                               /* a unei carti in baza de date       */
                char* titlu = strtok(NULL, ":");
                char* autor = strtok(NULL, ":");
                char* rating = strtok(NULL, ":");
                int rat = atoi(rating);
                char* numar_pag = strtok(NULL, ":");
                if (numar_pag[strlen(numar_pag) - 1] == '\n')
                    numar_pag[strlen(numar_pag) - 1] = '\0';
                int nr = atoi(numar_pag);

                TLista book = calloc(1, sizeof(TCarte));
              
                book->rating = rat;
                book->nr_pag = nr;
                book->titlu = (char*)calloc(strlen(titlu)+1, sizeof(char));
                strcpy(book->titlu, titlu);
                book->autor = (char*)calloc(strlen(autor)+1, sizeof(char));
                strcpy(book->autor, autor);
                
                insert(T1, titlu, (void*)book, alphabet_array);
                insertT2(T2, autor, titlu, (void*)book, alphabet_array);
                
            }
    
            if(strcmp(operatie, "search_book")==0)  /* se realizeaza operatia de cautare */
            {                                        /* a unei carti in baza de date      */
                char* titlu = strtok(NULL, ":");
                if (titlu[strlen(titlu) - 1] == '\n')
                    titlu[strlen(titlu) - 1] = '\0';

                if (strstr(titlu, "~") == NULL)
                {
                    search(T1, titlu, alphabet_array, out);
                }

            }
          
           if(strcmp(operatie, "list_author")==0)  /* se realizeaza operatia de cautare */
           {                                       /* a unui autor in baza de date      */

                char* autor = strtok(NULL, ":");
                if (autor[strlen(autor) - 1] == '\n')
                    autor[strlen(autor) - 1] = '\0';

                char* output_string = (char*)calloc(CHAR_SIZE, sizeof(char));
              
                if (strstr(autor, "~") == NULL)
                {
                    int result = list_author(T2, autor, alphabet_array, output_string, out);
            
                    if(result == 0)
                        fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n", autor);

                }

           }
           if(strcmp(operatie, "search_by_author")==0)  /* se realizeaza operatia de cautare a unui        */
           {                                            /* autor si a unei carti specifice in baza de date */
                char* autor = strtok(NULL, ":");
                if (autor[strlen(autor) - 1] == '\n')
                    autor[strlen(autor) - 1] = '\0';

                if (strstr(autor, "~") == NULL)
                {
                    char* titlu = strtok(NULL, ":");
                    if (titlu[strlen(autor) - 1] == '\n')
                        titlu[strlen(autor) - 1] = '\0';

                    if (strstr(titlu, "~") == NULL)
                        search_by_author(T2, autor, titlu, alphabet_array, out);
                }
                
            }
           
    }

    fclose(in);
}


