#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;


void majority(int * vettoreA, int N);
void leggiVettore(int ** vettoreA, int N);

int majorityR(int * vettoreA, int N);
int countOccurrences(int * vettoreA, int N, int x);

void leggiVettore(int ** vettoreA, int N) {

    *vettoreA = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {

        printf("INSERIRE ELEMENTO # %d > ", i + 1);
        scanf("%d", &(*vettoreA)[i]);
    }

    printf("\n");

    return;

}

int majorityR(int * vettoreA, int N) {

    if (N == 1) {

        return vettoreA[0];

    }

    int left = majorityR(vettoreA, N / 2);
    int right = majorityR(vettoreA + N / 2, N - (N / 2));

    if (left != -1) {

        if (countOccurrences(vettoreA, N, left) > N / 2) {

            return left;

        }
            
    } 

    if (right != -1 && right != left) {

        if (countOccurrences(vettoreA, N, right) > N / 2) {

            return right;

        }
         
    }

    return -1;
    
}

int countOccurrences(int * vettoreA, int N, int x) {

    int count = 0;

    for (int i = 0; i < N; i++) {

        if (vettoreA[i] == x) {

            count++;

        }

    }

    return count;
}

void majority(int * vettoreA, int N) {

    int major = majorityR(vettoreA, N);

    if (major != -1) {

        printf("ELEMENTO MAGGIORITARIO > %d\n\n", major);

    } 

    else {

        printf("ELEMENTO MAGGIORITARIO NON TROVATO!\n\n");

    }

    free(vettoreA);

}



int main(void) {

    bool exit = false;

    int N;

    int * vettoreA;

    do {

        printf("INSERIRE IL NUMERO DI ELEMENTI DEL VETTORE\n\nELEMENTI > ");
        scanf("%d", &N);
        printf("\n");

        if(N <= 0) {

            exit = true;
            break;

        }

        leggiVettore(&vettoreA, N);

        majority(vettoreA, N);
        

    } while (!exit);


    return 0;

}