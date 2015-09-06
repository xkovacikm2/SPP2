/* 
 * File:   main.c
 * Author: kovko
 *
 * Created on Streda, 2014, októbra 22, 17:56
 */

#include <stdio.h>
#include <stdlib.h>

//#define LADENIE

typedef struct item {
    int value;
    struct item *parent;
    struct item *left;
    struct item *right;
}ITEM;

typedef struct list {
    int number;
    ITEM *first;
}LIST;

/**
 * allocates memory for list
 * @return pointer to empty list
 */
LIST *listCreate();

/**
 * allocates memory for item
 * @param value for item to store
 * @return pointer to empty item
 */
ITEM *itemCreate(int value);

/**
 * adds item to list, if already stored, skips adding
 * @param list
 * @param add
 * @return int depth in list, where item is stored
 */
int listAddItem(LIST *list, ITEM *add);

int main() {
    int buf;
    LIST *list=listCreate();
    while(scanf("%d", &buf)>0)
        printf("%d\n", listAddItem(list, itemCreate(buf)));
    return 0;
}

LIST *listCreate(){
    LIST *list;
    list = (LIST*)malloc(sizeof(LIST));
    list->first=NULL;
    list->number=0;
    return list;
}

ITEM *itemCreate(int value){
    ITEM *item;
    item = (ITEM*)malloc(sizeof(ITEM));
    item->left = item->parent = item->right = NULL;
    item->value = value;
    return item;
}

int listAddItem(LIST *list, ITEM *add){
    ITEM *haystack = list->first;
    int depth = 0;
    //ak pridavam prvu vec
    if (haystack == NULL){
        list->first = add;
        list->number++;
        return depth;
    }
    //podmienka ma zatial nenapadla, breaknem sa ked bude treba
    while(1){
        //kontrolny vypis
#ifdef LADENIE
        printf("control value: %d\n", haystack->value);
#endif
        //kukam sa dolava
        if(add->value < haystack->value){
            //ak sa mam kam posunut vlavo
            if(haystack->left != NULL){
                //tak sa posuniem vlavo
                haystack=haystack->left;
                //a naiterujem si hlbku
                depth++;
                continue;
            }
            //ak sa nemam kam posunut, tak som nasiel miesto
            else{
                //nastavim novemu prvku rodica
                add->parent=haystack;
                //nastavim novy prvok do lavej vetvy stromu
                haystack->left=add;
                list->number++;
                depth++;
                return depth;
            }
        }
        //kukam sa doprava
        if(haystack->value < add->value){
            //ak sa mam kam posunut vpravo
            if(haystack->right != NULL){
                //tak sa posuniem
                haystack = haystack->right;
                //a naiterujem si hlbku
                depth++;
                continue;
            }
            //ak sa nemam kam posunut, tak som nasiel miesto
            else{
                //nastavim novemu prvku rodica
                add->parent = haystack;
                //nastavim novy prvok ako pravu vetvu rodica
                haystack->right = add;
                list->number++;
                depth++;
                return depth;
            }
        }
        //ak mam zhodu
        if(haystack->value == add->value){
            //add mozem vyhodit z pamati
            free(add);
            //vratim dlzku
            return depth;
        }
    }
}
