#include <stdio.h>
#include <stdlib.h>

#define MAX 20

struct stud {

    char nome[MAX];
    char cognome[MAX];
    int matr;

} ;


int main(void) {

    struct stud *s;
    struct stud *v;
    int n = 5;

    printf("LA DIMENSIONE DI struct stud É DI %d BYTE \n", sizeof(*s));
    printf("LA DIMENSIONE DI struct stud É DI %d BYTE \n\n", sizeof(struct stud));

    // Alloco con cast implicito;

    s = malloc(sizeof(struct stud));
    s = malloc(sizeof(*s));

    // Alloco con cast esplicito;

    s = (struct stud *) malloc(sizeof(struct stud));
    s = (struct stud *) malloc(sizeof(*s));

    // Allocazione con cast implicito di un vettore dinamico di struct;

    v = malloc(n * sizeof(struct stud));
    v = malloc(n * sizeof(*s));

    // Allocazione con cast implicito di un vettore dinamico di struct;

    v = (struct stud *) malloc(n * sizeof(struct stud));
    v = (struct stud *) malloc(n * sizeof(*v)); 


    return 0;

}