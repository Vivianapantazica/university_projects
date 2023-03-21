#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "trie.h"


// Returns new trie node (initialized to NULLs)
TTrie* createNode()
{
    struct Trie* pNode = (struct Trie*)malloc(sizeof(struct Trie));
    if(pNode == NULL)
        return NULL;

    int i;
  
    for (i = 0; i < ALPHABET_SIZE; i++)
        pNode->key[i] = NULL;
  
    pNode->isLeaf = 0;
    pNode->info = NULL;

    return pNode;
}

// Iterative function to insert a string into a Trie
void insert(struct Trie *head, char* str, void* info, char alphabet_array[])
{
    // start from the root node
    struct Trie* curr = head;
    int i;
   
    for( ; *str; str++)
    {
        for(i = 0; i < ALPHABET_SIZE; i++)
        {
            
            if(*str == alphabet_array[i])
            {
                // create a new node if the path doesn't exist
                if (curr->key[i] == NULL)
                    curr->key[i] = createNode();
                
                // go to the next node
                curr = curr->key[i];
            }
        }

    }

    curr->info = info;
    
    // mark the current node as a leaf
    curr->isLeaf = 1;
}

 
// Iterative function to search a string in a Trie. It returns 1
// if the string is found in the Trie; otherwise, it returns 0.
int search(struct Trie* head, char* str, char alphabet_array[], FILE* out)
{
    
    char* titlu= (char*)calloc(strlen(str) + 1, sizeof(char));
    strcpy(titlu, str);

    // return 0 if Trie is empty
    if (head == NULL) {
        return 0;
    }
    
    int i;
    struct Trie* curr = head;
    while (*str)
    {
        // go to the next node
        for( i = 0; i < ALPHABET_SIZE; i++)
        {
            if(*str == alphabet_array[i])
                curr = curr->key[i];

            
            // if the string is invalid (reached end of a path in the Trie)
            if (curr == NULL) 
                {
                    if (titlu[strlen(titlu) - 1] == '\n')
                        titlu[strlen(titlu) - 1] = '\0';
                    fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", titlu);
                    return 0;
                }
            
        }
        // move to the next character
        str++;
    }

    if(curr->info == NULL)
        fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", titlu);
    
    if(curr->info != NULL)
        fprintf(out, "Informatii recomandare: %s, %s, %d, %d\n", ((TCarte*)curr->info)->titlu, 
        ((TCarte*)curr->info)->autor, ((TCarte*)curr->info)->rating, 
        ((TCarte*)curr->info)->nr_pag);
   
    // return 1 if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}


// Iterative function to search a string in a Trie. It returns 1
// if the string is found in the Trie; otherwise, it returns 0.
int list_author(struct Trie* head, char* str, char alphabet_array[], char* output_string, FILE* out)
{
    
    char* autor= (char*)calloc(strlen(str) + 1, sizeof(char));
    strcpy(autor, str);
    
    // return 0 if Trie is empty
    if (head == NULL) {
        return 0;
    }
    
    int i;
    struct Trie* curr = head;
    while (*str)
    {
        // go to the next node
        for( i = 0; i < ALPHABET_SIZE; i++)
        {
            if(*str == alphabet_array[i])
                curr = curr->key[i];

            // if the string is invalid (reached end of a path in the Trie)
            if (curr == NULL) 
                return 0;
            
        }
        // move to the next character
        str++;
    }
    display(curr->info, output_string, 0, alphabet_array, out);
    
    // return 1 if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}


// Iterative function to search a string in a Trie. It returns 1
// if the string is found in the Trie; otherwise, it returns 0.
int search_by_author(struct Trie* head, char* str1, char* str2, char alphabet_array[], FILE* out)
{
    char* autor= (char*)calloc(strlen(str1) + 1, sizeof(char));
    strcpy(autor, str1);
   
    // return 0 if Trie is empty
    if (head == NULL) {
        return 0;
    }
    
    int i;
    struct Trie* curr = head;
    
    while (*str1)
    {
        // go to the next node
        for( i = 0; i < ALPHABET_SIZE; i++)
        {
            if(*str1 == alphabet_array[i])
                {
                    curr = curr->key[i];
                }

            // if the string is invalid (reached end of a path in the Trie)
            if (curr == NULL) 
            {   
                fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n", autor);
                return 0;
            }
            
        }
        // move to the next character
        str1++;
    }

    search(curr->info, str2, alphabet_array, out);
 
    return curr->isLeaf;
}

// Iterative function to search a string in a Trie. It returns 1
// if the string is found in the Trie; otherwise, it returns 0.
int search_by_author_prefixed(struct Trie* head, char* str, char alphabet_array[], char* output_string, FILE* out)
{
    
    char* autor= (char*)calloc(strlen(str) + 1, sizeof(char));
    strcpy(autor, str);

    // return 0 if Trie is empty
    if (head == NULL) {
        return 0;
    }
    
    int i;
    struct Trie* curr = head;
    while (*str)
    {
        // go to the next node
        for( i = 0; i < ALPHABET_SIZE; i++)
        {
            if(*str == alphabet_array[i])
                curr = curr->key[i];

            // if the string is invalid (reached end of a path in the Trie)
            if (curr == NULL) 
                {
                    fprintf(out, "Niciun autor gasit.\n");
                    return 0;
                }
        }
        // move to the next character
        str++;
    }
    
    if(curr->info == NULL)
      {
          fprintf(out, "Niciun autor gasit.\n");
      }
   
    if(curr->info != NULL)
        {
            fprintf(out, "Informatii recomandare: %s, %s, %d, %d\n", ((TCarte*)curr->info)->titlu, 
            ((TCarte*)curr->info)->autor, ((TCarte*)curr->info)->rating, 
            ((TCarte*)curr->info)->nr_pag);
        }
       
    // return 1 if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}


void insertT2(struct Trie *head, char* str, char* arb, void* info, char alphabet_array[])
{
    // start from the root node
    struct Trie* curr = head;
    int i;
   
    for( ; *str; str++)
    {
        for(i = 0; i < ALPHABET_SIZE; i++)
        {
            
            if(*str == alphabet_array[i])
            {
                // create a new node if the path doesn't exist
                if (curr->key[i] == NULL) 
                    curr->key[i] = createNode();
                
                // go to the next node
                curr = curr->key[i];
            }
        }

    }
    
    if (curr->info == NULL)
        curr->info = createNode();

    insert(curr->info, arb, info, alphabet_array);
    // mark the current node as a leaf
    curr->isLeaf = 1;
}

void display(struct Trie* root, char str[], int level, char alphabet_array[], FILE* out)
{
    if(root == NULL)
        return;
    
    // If node is leaf node, it indicates end of string, so a null character is added
    // and string is displayed
    if (root->isLeaf == 1) 
    {
        str[level] = 0;
        fprintf(out, "%s\n", str);
        //printf("%s\n", str);
    }
    int i;
    //printf("%s\n", str);
    for (i = 0; i < ALPHABET_SIZE; ++i) 
    {
        if (root->key[i] != NULL) 
        {
            str[level] = alphabet_array[i];
            display(root->key[i], str, level + 1, alphabet_array, out);
        }
    }
}
