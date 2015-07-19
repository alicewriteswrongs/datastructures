#include <stdio.h>
#include <stdlib.h>

// nodes in our list
typedef struct node {
    struct node *cdr;
    char *data;
} node;

// pointer to the first element
typedef struct list {
    node *car;
    node *tail;
} list;

// function declarations
list *listinit();
int insert(node *after, node *new);
node *nodegen(char *data);
void deletenext(node *after);
int insertstart(list *list, node *insert);
void deletebeginning(list *list);
void printlist(list *list);

// list operation functions

void printlist(list *list)
{
    node *first = list->car;
    node *temp;

    while (first != list->tail) {
        printf("%s\n", first->data);
        temp = first;
        first = temp->cdr;
    }
}

list *listinit() 
{ // initialize a list with a sentinel node

    list *newlist;
    newlist = malloc(sizeof *newlist);
    node *sentinel;
    sentinel = malloc(sizeof *sentinel);
    if (sentinel == NULL)
        return 0; 

    sentinel->data = '\0';
    sentinel->cdr = sentinel;
    newlist->car = sentinel;
    newlist->tail = sentinel;

    return newlist;
}

int insert(node *after, node *new)
{ // insert 'new' following 'after'
    new->cdr = after->cdr;
    after->cdr = new;
    return 0;
}

int insertstart(list *list, node *insert)
{
    insert->cdr = list->car;
    list->car = insert;
    return 0;
}

node *nodegen(char *input)
{ // make a new node, returns ptr
    node *newnode;
    newnode = malloc(sizeof *newnode);
    newnode->data = input;
    return newnode;
}

void deletenext(node *after)
{ // delete the node following
    node *toremove = after->cdr;
    after->cdr = toremove->cdr;
    free(toremove);
}

void deletebeginning(list *list)
{ //delete the node at the beginning
    node *toremove = list->car;
    list->car = toremove->cdr;
    free(toremove);
}


