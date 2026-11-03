#include <stdio.h>

#define TEST_LEN 20

void showRecThree(int x[], int l, int );
int showMax(int x[], int l, int r);


void showRecThree(int x[], int l, int r) {

    int i, m;

    // Condizione di terminazione;

    if (l >= r) {
        
        return;

    }

    // Operazione di divisione o di Divide;

    m = (r + l) / 2;

    // Stampo la prima parte del vettore, ovvero SX;

    printf("xs = ");

    for (int i = l; i <= m; i++) {

        printf("%d", x[i]);

    }

    printf("\n");

    // Ora chiamo la funzione ricorsivamente;

    showRecThree(x, l, m);

    // Ripeto il tutto per la parte destra del vettore, ovvero DX;

    printf("xd = ");

    for (int i = m + 1; i <= r; i++) {

        printf("%d", x[i]);

    }
    
    printf("\n");

    // Ora chiamo la funzione ricorsivamente;

    showRecThree(x, m + 1, r);

    return; 


}

int showMax(int x[], int l, int r) {

    int lMax, rMax, m;

    // Condizione di terminazione, identica al caso di vettore degenere;

    if (l == r) {

        return x[l];

    }

    // Divide, divido il problema in due;

    m = (l + r) / 2;

    // Ricorro al vettore SX e DX per trovare massimo e minimo sui due lati;

    lMax = showMax(x, l, m);
    rMax = showMax(x, m + 1, r);

    return (lMax > rMax) ? lMax : rMax;

}

int main(void) {

    int vettore[] = {1, 4, 5, 4, 1, 9, 8, 3, 4, 1, 4, 6, 3, 7, 8, 9, 8, 0, 1, 2};

    int l = 0;
    int r = TEST_LEN - 1;

    showRecThree(vettore, l, r);

    printf("\nValore massimo = %d\n\n", showMax(vettore, l, r));

    return 0;

}