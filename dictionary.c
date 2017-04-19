/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "dictionary.h"

typedef struct node{
    bool is_word;
    struct node* next[27];
}node;

void init_node(node** ptr){ 
    *ptr=(node*)malloc(sizeof(node));
    int i;
    (*ptr)->is_word=false;
    for(i=0;i<27;i++){
        (*ptr)->next[i]=NULL;
    }
}

node *root, *trav, *prev;
int no_of_words=0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word_copy){
    char *word=(char*) malloc(50);
    int i;
    trav=root;
    strcpy(word,word_copy);
    int len=strlen(word_copy);
    word[len]='\0';
    int key;
    for (i=0;i<len;i++){
        word[i]=toupper(word[i]);
    }
    for (i=0; i<len; i++, key=0){
        if (isalpha(word[i])){
            key=(int) word[i]-65;
        }
        else key=26;
        
        if (trav->next[key]==NULL){
            return false;
        }
        trav=trav->next[key];
    }
    
    free (word);
    return trav->is_word;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary){
    init_node(&root);
    FILE *infile=fopen(dictionary,"r");
    if (infile==NULL){
        return false;
    }
    char* word=malloc(100);
    int i,len,key;
    while(!(feof(infile))){
        trav=root;
        fgets(word, 100, infile);
        len=strlen(word);
        for(i=0;i<len;i++){
            if(isalpha(word[i])){
                word[i]=toupper(word[i]);
                key=word[i]-65;
            }
            else key=26;
            if (trav->next[key]==NULL){
                init_node(&(trav->next[key]));
            }
            trav=trav->next[key];
        }
        trav->is_word=true;
        no_of_words++;
    }
    fclose(infile);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void){
    return no_of_words;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
 

void free_node(node* trav){
    int i;
    for(i=0;i<28;i++){
        if(trav->next[i]!=NULL){
            free_node(trav->next[i]);
        }
    }
    free(trav);
}


bool unload(void){
    free_node(root);
    return true;
}
