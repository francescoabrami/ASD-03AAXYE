#include "ordinamentiRicorsivi.h"

bool ITEMeq(Item A, Item B) {

    return (bool) (A == B);

}

bool ITEMneq(Item A, Item B) {

    return (bool) (A != B);

}

bool ITEMlt(Item A, Item B) {


    return (bool) (A < B);

}

bool ITEMgt(Item A, Item B) {

    return (bool) (A > B);

}

void ITEMshow(Item A) {

    printf("%-6d \n", A);

}

Item ITEMscan(void) {

    Item A;

    printf("Inserire un ITEM\n\nITEM > ");
    scanf("%d", &A);
    
    return (Item) A;

}

Item ITEMrand(void) {

    Item A;
    
    A = MAX_KEY * ( (double) rand() / RAND_MAX);

    return A;

}

void mergeSort(Item A[], Item B[], int N) {

    int l = 0;
    int r = N - 1;

    mergeSortRic(A, B, l, r);

}

void mergeSortRic(Item A[], Item B[], int l, int r) {

    int q;
    
    // Condizione di terminazione;

    if (l >= r) {

        return;

    }

    q = (l + r) / 2;

    // Chiamate ricorsive a SX e DX;

    mergeSortRic(A, B, l, q);
    mergeSortRic(A, B, q + 1, r);

    // Funzione con cui ricombino;

    merge(A, B, l, q, r);

}

void merge(Item A[], Item B[], int l, int q, int r) {

    int i, j, k;
    
    i = l;
    j = q + 1;

    for (k = l; k <= r; k++) {

        if (i > q) {

            B[k] = A[j++];

        } 
        else if (j > r) {

            B[k] = A[i++];

        }
        else if ( ITEMlt(A[i], A[j]) || ITEMeq(A[i], A[j]) ) {

            B[k] = A[i++];

        }
        else {

            B[k] = A[j++];

        }

    }

    for (k = l; k <= r; k++) {

        A[k] = B[k];

    }


}

void quickSort(Item A[], int N) {

    int l = 0;
    int r = N - 1;

    quickSortRic(A, l, r);

    return;

}

void quickSortRic(Item A[], int l, int r) {

    int q;

    // Condizione di terminazione;

    if (l >= r) {

        return;

    }

    // Partiziono, ovvero divido il problema;

    q = partition(A, l, r);

    // Chiamata ricorsiva;

    quickSortRic(A, l, q - 1);
    quickSortRic(A, q + 1, r);

    return;

}

int partition(Item A[], int l, int r) {

    int i = l - 1;
    int j = r;

    Item x = A[r];

    for ( ; ; ) {

        while ( ITEMlt( A[++i], x) );
        while ( j > l && ITEMgt( A[--j], x ) );

        if (i >= j) {

            break;

        }

        swap(A, i, j);        

    }

    swap(A, i, r);

    return i;

}

void swap(Item * v, int n1, int n2) {

    Item tmp;

    tmp = v[n1];
    v[n1] = v[n2];
    v[n2] = tmp;

    return;

}




