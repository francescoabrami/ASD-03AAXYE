#include <stdio.h>
#include <math.h>
#include <string.h>

#include "informatica.h"

#define MAX 25

int main(void) {

    int vettore[MAX] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 24};

    char stringa[] = "Hello World!";

    printf("INDICE DELLA CHIAVE 9: %d \n \n", binSearch(vettore, 0, 24, 9));
    printf("INDICE DELLA CHIAVE 30: %d \n \n", binSearch(vettore, 0, 24, 30));

    printf("Contrario di \"%s\" é ", stringa);

    reverseString(stringa);
    printf("\n\n");

    hanoiTower(4,0,1);

    printf("\n\nRIGHELLO:\n\n");

    ruler(0,32,3);
    

    return 0;
    
}