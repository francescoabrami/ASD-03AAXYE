#include <stdio.h>
#include <stdlib.h>

#define LEN 25

typedef enum {false, true} bool;

typedef int Item;

typedef struct node {

    Item val;
    struct node *next;

} node_t;

typedef node_t *link;

void stampaListaOrdinata(link head);
void riempiLista(link * head);

void freeLista(link head);

void stampaListaOrdinata(link head) {

    link p;

    for (p = head; p != NULL; p = p->next) {

        printf("VALORE: %d \n", p->val);

    }

    printf("\n\n");

    return;

}

void riempiListaTesta(link *head) {

    link p;

    bool exit = false;

    int val;

    do {

        printf("INSERIRE IL VALORE DI UN NODO:\n\nVALORE > ");
        scanf("%d", &val);
        printf("\n");

        if (val == 0) {

            exit = true;
            break;

        }

        p = malloc( sizeof(*p) );

        if (p == NULL) {

            exit = true;

        }

        p->val = val;
        p->next = *head;
        *head = p;


    } while (!exit);



}

void freeLista(link head) {

    link p;

    while (head != NULL) {

        p = head;
        head = head->next;

        free(p);

    }

    return;

}

int main(void) {

    link head = NULL;
    
    riempiListaTesta(&head);

    stampaListaOrdinata(head);

    freeLista(head);
    
    return 0;

} 