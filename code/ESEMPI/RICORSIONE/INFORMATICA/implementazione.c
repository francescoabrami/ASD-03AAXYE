#include <stdio.h>
#include <math.h>

#include "informatica.h"


int binSearch(int x[], int l, int r, int k) {

    int m;

    // Condizione di terminazione senza successo;

    if (l > r) {

        return -1;

    }

    // Operazione di divide;

    m = (l + r) / 2;

    // Condizione di terminazione con successo;

    if (k == x[m]) {

        return (m);

    } 

    // Operazione di ricorsione: non trovo e cerco ancora nel sotto-vettore corretto;

    if (k < x[m]) {

        return binSearch(x, l, m - 1, k);

    }

    return binSearch(x, m + 1, r, k);

}

void reverseString(char * s) { 

    if (* s == '\0') {

        return;

    }

    reverseString(s + 1);
    putchar(*s);

}

void hanoiTower(int n, int src, int dest) {

    int aux;

    // Terminazione della ricorsione;

    if (n == 1) {

        printf("src %d -> dest %d \n", src, dest);
        return;

    }

    // Operazione di Divide con chiamata ricorsiva;

    aux = 3 - (src + dest);
    hanoiTower(n-1, src, aux);

    printf("src %d -> dest %d \n", src, dest);
    hanoiTower(n-1, aux, dest);

    return;

}

void mark(int m, int h) {

    int i;

    printf("%d \t", m);
    for (i = 0; i < h; i++) {

        printf("*");

    }

    printf("\n");


}

void ruler(int l, int r, int h) {

    int m;

    // Condizone di terminazione;
    
    if (h == 0) {

        return; 

    }

    m = (l + r) / 2;

    // Chiamata ricorsiva e segno le tacche con ma mark();

    ruler(l, m, h - 1);
    mark(m, h);
    ruler(m, r, h - 1);

}




