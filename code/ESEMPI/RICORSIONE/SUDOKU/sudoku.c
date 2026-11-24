
#include <stdio.h>
#include <stdlib.h>

#define N 9
#define BOX 3
#define EMPTY 0

#define FULL_MASK 0x3FEu

typedef struct {

    int cell[N][N];

    unsigned int rowMask[N];
    unsigned int colMask[N];
    unsigned int boxMask[N];

} sudoku_t;

int getBox(int row, int col) {

    return (row / BOX) * BOX + (col / BOX);
}

void printSudoku(const sudoku_t *s) {

    for (int i = 0; i < N; i++) {

        if (i % BOX == 0 && i != 0)
            printf("------+-------+------\n");

        for (int j = 0; j < N; j++) {

            if (j % BOX == 0 && j != 0)
                printf("| ");

            printf("%d ", s->cell[i][j]);
        }

        printf("\n");
    }
}

int initSudoku(sudoku_t *s) {

    for (int i = 0; i < N; i++) {

        s->rowMask[i] = 0;
        s->colMask[i] = 0;
        s->boxMask[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            int value = s->cell[i][j];

            if (value == EMPTY)
                continue;

            if (value < 1 || value > 9)
                return 0;

            unsigned int bit = 1u << value;

            int box = getBox(i, j);

            if ((s->rowMask[i] & bit) ||
                (s->colMask[j] & bit) ||
                (s->boxMask[box] & bit)) {

                return 0;
            }

            s->rowMask[i] |= bit;
            s->colMask[j] |= bit;
            s->boxMask[box] |= bit;
        }
    }

    return 1;
}


unsigned int getCandidates(const sudoku_t *s,
                           int row,
                           int col) {

    int box = getBox(row, col);

    unsigned int used =
        s->rowMask[row] |
        s->colMask[col] |
        s->boxMask[box];

    return FULL_MASK & ~used;
}


int countBits(unsigned int mask) {

    int count = 0;

    while (mask != 0) {

        mask &= mask - 1;

        count++;
    }

    return count;
}


int findBestCell(const sudoku_t *s,
                 int *bestRow,
                 int *bestCol,
                 unsigned int *bestCandidates) {

    int minCandidates = 10;

    *bestRow = -1;
    *bestCol = -1;
    *bestCandidates = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            if (s->cell[i][j] != EMPTY)
                continue;

            unsigned int candidates =
                getCandidates(s, i, j);

            int count = countBits(candidates);

            if (count == 0)
                return -1;

            if (count < minCandidates) {

                minCandidates = count;

                *bestRow = i;
                *bestCol = j;

                *bestCandidates = candidates;
            }

            if (minCandidates == 1)
                return 1;
        }
    }

    if (*bestRow == -1)
        return 0;

    return 1;
}

void solveSudokuAll(sudoku_t *s,
                    unsigned long long *solutionCount) {

    int row, col;

    unsigned int candidates = 0;

    int status = findBestCell(
        s,
        &row,
        &col,
        &candidates
    );

    if (status == -1)
        return;

    if (status == 0) {

        (*solutionCount)++;

        printf("\nSOLUTION #%llu\n", *solutionCount);
        printSudoku(s);

        return;
    }

    int box = getBox(row, col);

    while (candidates != 0) {

        unsigned int bit =
            candidates & (~candidates + 1u);

        candidates &= candidates - 1u;

        int value = 1;

        while ((1u << value) != bit)
            value++;


        s->cell[row][col] = value;

        s->rowMask[row] |= bit;
        s->colMask[col] |= bit;
        s->boxMask[box] |= bit;

        solveSudokuAll(s, solutionCount);

        s->cell[row][col] = EMPTY;

        s->rowMask[row] &= ~bit;
        s->colMask[col] &= ~bit;
        s->boxMask[box] &= ~bit;
    }
}


int main(void) {

    sudoku_t sudoku = {
        .cell = {

            {7,2,6,0,0,0,8,4,0},
            {0,0,0,0,0,6,1,7,9},
            {0,9,0,7,0,0,0,0,6},
            {2,5,0,6,8,0,0,0,0},
            {0,0,0,2,0,0,5,0,0},
            {0,0,0,0,9,3,0,1,0},
            {5,4,0,0,0,9,0,8,1},
            {8,6,7,1,0,0,0,0,0},
            {0,1,0,8,4,7,0,2,5}

        }
    };

    unsigned long long solutionCount = 0;

    if (!initSudoku(&sudoku)) {
        printf("Invalid Sudoku configuration!\n");
        return EXIT_FAILURE;
    }

    printf("INITIAL SUDOKU:\n\n");
    printSudoku(&sudoku);

    printf("\nSearching for all possible solutions...\n");

    solveSudokuAll(&sudoku, &solutionCount);

    printf("\n================================\n");
    printf("TOTAL SOLUTIONS: %llu\n", solutionCount);
    printf("================================\n");

    return EXIT_SUCCESS;

}   