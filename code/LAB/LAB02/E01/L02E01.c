#include <stdio.h>

typedef enum {false, true} bool;

int gcd(int * a, int * b);

void swap(int * a, int * b);

bool isEven(int * num);
bool returnCondition(int *a, int *b);

bool isEven(int * num) {

    if (* num % 2 == 0) {

        return true;

    } else {

        return false;

    }

}

void swap(int *a, int *b) {

    if (*b > *a) {

        int tmp = *a;
        *a = *b;
        *b = tmp;

    }

    return;

}

bool returnCondition(int *a, int *b) {

    if (*b == 0 || *a == *b) {

        return true;

    }

    return false;

}

int gcd(int *a, int *b) {

    int x, y;

    swap(a, b);

    if (returnCondition(a, b)) {

        return *a;

    }

    if (isEven(a) && isEven(b)) {

        x = *a / 2;
        y = *b / 2;

    }

    else if (isEven(a)) {

        x = *a / 2;
        y = *b;

    }

    else if (isEven(b)) {

        x = *a;
        y = *b / 2;

    }

    else {

        x = (*a - *b) / 2;
        y = *b;

    }

    return gcd(&x, &y);

}

int main(void) {

    bool exit = false;

    int a, b;
    
    do {

        printf("\nINSERIRE IL PRIMO NUMERO:\n\nA > ");
        scanf("%d", &a);
        printf("\nINSERIRE IL SECONDO NUMERO:\n\nB > ");
        scanf("%d", &b);

        if (a < 0 || b < 0) {

            exit = true;
            break;

        }

        printf("\nIL gcd(a,b) É: %d\n\n", gcd(&a, &b));


    } while(!exit);

    return 0;

}