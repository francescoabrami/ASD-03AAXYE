#include <stdio.h>

int funzione1 (int x);
int funzione2 (int x);


int funzione1 (int x) {

    int ris;

    printf("f1: chiamo f2(%d)\n", x);

    ris = funzione2(x);

    printf("f1: f2 ha restituito %d\n", ris);

    return ris;

}

int funzione2 (int x) {

    int ris;

    ris = x + 1;

    printf("f2: restituisco %d\n", ris);

    return ris;

}



int main(void) {

    int ris, a = 10;

    printf("main: chiamo f1(%d)\n", a);
    
    ris = funzione1(a);

    printf("main: f1 ha restituito %d", ris);

    return 0;

}