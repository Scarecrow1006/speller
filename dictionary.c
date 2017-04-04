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
    char right_word[100];
    struct node* next[28];
}node;

void init_node(node** ptr){
    *ptr=malloc(sizeof(node));
    int i;
    for(i=0;i<28;i++){
        (*ptr)->next[i]=NULL;
    }
}

node *root, *trav, *prev;
int no_of_words=0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word){
    trav=root;
    int key;
    int i;
    for(i=0;word[i]!='\0';i++){
        if(isalpha(word[i])){
            tolower(word[i]);
            key=word[i]-96;
        }
        else{
            key=27;
        }
        trav=trav->next[key];
    }
    if(!strcmp(trav->right_word,word)){
        return true;
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary){
    init_node(&root);
    FILE *infile=fopen(dictionary,"r");
    char* word=malloc(100);
    //node* trav;
    int key;
    int i;
    while(true){
        trav=root;
        fgets(word,100,infile);
        if(feof(infile)){
            break;
        }
        no_of_words++;
        for(i=0;word[i]!='\0';i++){
            if(isalpha(word[i])){
                toupper(word[i]);
                key=word[i]-96;
            }
            else{
                key=27;
            }
            if(trav->next[key]==NULL){
                init_node(&(trav->next[key]));
            }
            trav=trav->next[key];
        }
        strcpy(trav->right_word,word);
    }
    free(word);
    if(feof(infile)){
        return true;
    }
    return false;
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
 

void unload_ptr(node* prev, node* trav){
    int i;
    for(i=0;i<28;i++){
        if(trav->next[i]!=NULL){
            prev=trav;
            trav=trav->next[i];
            unload_ptr(prev,trav);
        }
    }
    free(trav);
}


bool unload(void){
    int i;
    for(i=0;i<28;i++){
        if(trav->next[i]!=NULL){
            prev=trav;
            trav=trav->next[i];
            unload_ptr(prev,trav);
        }
    }
    return false;
}
