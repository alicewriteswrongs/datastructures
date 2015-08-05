#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

/* My hashtable implementation. This code is free to use/re-use/whatever */
/* if you find it helpful */
/* :D */

/* This is a hashtable using SHA1 - we use a linked list implementation */
/* I wrote to provide for separate chaining. Every bin in the table */ 
/* is initialized pointing to an empty linked list, if we hash a key */ 
/* that points to that node then we add things to that list (key/value pairs) */
/* then later we can look in that list to find everything hashed to that key! */

// structs
typedef struct node {
    struct node *previous;
    struct node *next;
    char *key;
    char *value;
} node;

typedef struct list {
    node *head;
    node *tail;
} list;

typedef struct hashtable {
    int size;
    list **table;
} hashtable;

// function declarations
unsigned char *hash(unsigned char *key, unsigned char *output);
hashtable *hashinit(int size);
void destroyhash(hashtable *oldtable);
list *listinit();
void destroylist(list *oldlist);
void printlist(list *toprint);
node *nodegen(char *key, char *value);
void listinsert(list *insertlist, node *toinsert);
void listremove(list *removelist, node *toremove);
node *listsearch(list *tosearch, char *key, char *value);

// function definitions
unsigned char *hash(unsigned char *key, unsigned char *output)
{ // get the hash of a key
    size_t len = sizeof(key);
    /* unsigned char output[SHA_DIGEST_LENGTH]; */
    SHA1(key, len, output);
    /* return output; */
}

hashtable *hashinit(int size)
{ // allocates hashtable array, returns pointer to array
    list **hasharray;
    hasharray = malloc(sizeof (list) * size);
    hashtable *hashtab;
    hashtab = malloc(sizeof hashtab);

    int i;
    for (i = 0; i < size; i++) {
        hasharray[i] = listinit();
    }

    hashtab->table = hasharray;
    hashtab->size = size;
    return hashtab;
}

void destroyhash(hashtable *oldtable)
{ // destroy!!
    int i;
    for (i = 0; i < oldtable->size; i++) {
        destroylist(oldtable->table[i]);
    }
    free(oldtable);
}

// list functions
list *listinit()
{
    list *newlist;
    newlist = malloc(sizeof (list));
    node *sentinel;
    sentinel = malloc(sizeof (node));

    sentinel->key = '\0';
    sentinel->value = '\0';
    sentinel->next = sentinel;
    sentinel->previous = sentinel;

    newlist->head = sentinel;
    newlist->tail = sentinel;
    
    return newlist;
}

void destroylist(list *oldlist)
{
    node *sentinel = oldlist->tail;
    node *iternode = oldlist->head;
    node *next;
    while (iternode != sentinel) {
        next = iternode->next;
        free(iternode);
        iternode = next;
    }
    free(sentinel);
    free(oldlist);
}

node *nodegen(char *key, char *value)
{ // make a new node
    node *newnode;
    newnode = malloc(sizeof (node));
    newnode->key = key;
    newnode->value = value;
    return newnode;
}

void listinsert(list *insertlist, node *toinsert)
{ // inserts a new item at the beginning
    toinsert->next = insertlist->head;
    toinsert->previous = insertlist->tail;
    insertlist->head = toinsert;
}

void listremove(list *curlist, node *toremove)
{ // remove a given node (use listsearch to find it)
    if (curlist->head == toremove) {
        curlist->head = toremove->next;
        curlist->head->previous = toremove->previous;
        free(toremove);
    } else {
        toremove->next->previous = toremove->previous;
        toremove->previous->next = toremove->next;
        free(toremove);
    }
}

node *listsearch(list *tosearch, char *key, char *value)
{
    node *iternode = tosearch->head;
    while (iternode != tosearch->tail) {
        if ((strcmp(iternode->key, key) == 0) && (strcmp(iternode->value, value) == 0)) {
            return iternode;
        } else {
            iternode = iternode->next;
        }
    }
    return tosearch->tail;
}


// debugging tools
void printlist(list *toprint)
{
    node *iternode = toprint->head;
    if (iternode == toprint->tail)
        printf("empty list!\n");
    while (iternode != toprint->tail) {
	printf("%s\t", iternode->key);
	printf("%s\n", iternode->value);
	iternode = iternode->next;
    }
}

