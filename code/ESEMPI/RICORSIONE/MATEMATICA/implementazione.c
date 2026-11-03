#include <stdio.h>
#include <math.h>

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

int gcdEuclide(int x, int y) {

    if (x == y) {

        return x;

    }

    if (x > y) {

        return gcdEuclide(x - y, y);

    }

    return gcdEuclide(x, y - x);

}

int gcdLame(int x, int y) {

    if (y == 0) {

        return x;

    }

    return gcdLame(y, x % y);

}

long prodInt(int * x, int lx, int rx, int * y, int ly, int ry, int n) {

    long t1, t2, t3;
    int m = n /2;

    // Condizione di termnazione e ritorno il prodotto tra due cifre;

    if (n == 1) {

        return (x[lx] * y[ly]);

    }

    t1 = prodInt(x, lx, (lx + rx) / 2, y, ly, (ly + ry) / 2, n / 2);
    t2 = prodInt(x, lx, (lx + rx) / 2, y, ly + n / 2, ry, n / 2) + prodInt(x, lx + n / 2, rx, y, ly, (ly + ry) / 2, n / 2); 
    t3 = prodInt(x, lx + n / 2, rx, y, ly + n / 2, ry, n / 2);

    return t1 * pow(10, n) + t2 * pow(10, n/2) + t3;

}