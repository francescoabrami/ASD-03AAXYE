#include "matematica.h"

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
    moltiplica_EX(numero, numCifre, n);

    return;

}

void moltiplica_EX(int numero[], int *numCifre, int moltiplicatore) {

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

    return;
}
