#include <stdio.h>

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


    return 0;

}

unsigned long factorial_EX(int n) {

    if (( n == 0) || (n == 1))
        return 1;
    return n * factorial_EX(n - 1);
}

unsigned long fibonacci_EX(int n) {

    if (( n == 0) || (n == 1))
        return n;
    return (fibonacci_EX(n - 1) + fibonacci_EX(n - 2));

}

void fattorialeLungo_EX(int n, int numero[], int *numCifre) {

    if (n == 0) {
        numero[0] = 1;
        *numCifre = 1;
        return;
    }

    fattorialeLungo_EX(n - 1, numero, numCifre);
    moltiplica(numero, numCifre, n);

}

void moltiplica(int numero[], int *numCifre, int moltiplicatore) {

    int carry = 0;

    for (int i = 0; i < *numCifre; i++) {

        int prodotto = numero[i] * moltiplicatore + carry;

        numero[i] = prodotto % 10;
        carry = prodotto / 10;
    }

    while (carry > 0) {

        numero[*numCifre] = carry % 10;
        carry /= 10;
        (*numCifre)++;

    }
}
