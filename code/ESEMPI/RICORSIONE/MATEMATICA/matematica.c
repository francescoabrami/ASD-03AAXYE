#include <stdio.h>
#include <math.h>

#include "matematica.h"

#define MAX_DIG 1048576

int main(void) {

    int n;
    int numero[MAX_DIG];
    int numCifre;

    printf("INSERIRE IL NUMERO DI CUI SI VUOLE CALCOLARE IL FATTORIALE: ");
    scanf("%d", &n);

    printf("RISULATO: %d \n", factorial_EX(n));

    printf("INSERIRE IL NUMERO DELLA SEQUENZA DI FIBONACCI CHE SI VUOLE TORVARE: ");
    scanf("%d", &n);

    printf("RISULATO: %d \n", fibonacci_EX(n));

    printf("INSERIRE IL NUMERO DI CUI SI VUOLE CALCOLARE IL FATTORIALE ESTESO: ");
    scanf("%d", &n);

    fattorialeLungo_EX(n, numero, &numCifre);

    printf("RISULTATO: \n");

    for (int i = numCifre - 1; i > -1 ; i--) {
        printf("%d",numero[i]);
    }

    printf("\n");

    int x, y;

    printf("INSERIRE X: ");
    scanf("%d", &x);

    printf("INSERIRE Y: ");
    scanf("%d", &y);

    printf("GCD(%d,%d): %d\n\n", x, y, gcdEuclide(x,y));


    printf("INSERIRE X: ");
    scanf("%d", &x);

    printf("INSERIRE Y: ");
    scanf("%d", &y);

    printf("GCD(%d,%d): %d\n\n", x, y, gcdLame(x,y));

    int prod1[] = {1, 3, 5, 6}; // 1356;
    int prod2[] = {2, 4, 1, 0}; // 2410;

    printf("Prodotto: %ld \n \n", prodInt(&prod1, 0, 3, &prod2, 0, 3, 4));

    return 0;

}
