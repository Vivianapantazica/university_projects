#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Define the character size
#define CHAR_SIZE 500
#define ALPHABET_SIZE 69
 
 
typedef struct carte
{
    char* titlu;
    char* autor;
    int rating;
    int nr_pag;
} TCarte, *TLista;


typedef struct carti{
    char* autor;
    char* titlu;
}TNod;


// Data structure to store a Trie node
typedef struct Trie
{
    int isLeaf;
    void* info;            
    struct Trie* key[ALPHABET_SIZE];
} TTrie;



#ifndef _TRIE_
#define _TRIE_

struct Trie* createNode();
struct Trie* getNewTrieNode();
void insert(struct Trie *head, char* str, void* info, char v[]);
void insertT2(struct Trie *head, char* str, char *arb, void* info, char v[]);
int search(struct Trie* head, char* str, char v[], FILE* out);
int list_author(struct Trie* head, char* str, char alphabet_array[], char* string, FILE* out);
int search_by_author(struct Trie* head, char* str1, char* str2, char alphabet_array[], FILE* out);
int search_by_author_prefixed(struct Trie* head, char* str, char alphabet_array[], char* output_string, FILE* out);
int list_author_prefixed(struct Trie* head, char* str, char alphabet_array[], char* output_string, FILE* out);
void display(struct Trie* root, char str[], int level, char alphabet_array[], FILE* out);
int isLeafNode(struct Trie* root);
#endif
