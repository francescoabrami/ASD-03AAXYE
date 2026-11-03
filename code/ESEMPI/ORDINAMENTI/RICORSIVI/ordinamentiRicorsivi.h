#ifndef ORDINAMENTI_R_H
#define ORDINAMENTI_R_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_KEY 263845
#define RAND_MAX 10000

typedef int Item;
typedef enum {false, true} bool;

Item ITEMscan(void);
bool ITEMeq(Item A, Item B);
bool ITEMneq(Item A, Item B);
bool ITEMlt(Item A, Item B);
bool ITEMgt(Item A, Item B);
void ITEMshow(Item A);
Item ITEMrand(void);

void mergeSort(Item A[], Item B[], int N);
void mergeSortRic(Item A[], Item B[], int l, int r);
void merge(Item A[], Item B[], int l, int q, int r);

void quickSort(Item A[], int N);
void quickSortRic(Item A[], int l, int r);
int partition(Item A[], int l, int r);
void swap(Item * v, int n1, int n2);

#endif
