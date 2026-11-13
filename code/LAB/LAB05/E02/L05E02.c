#include <stdio.h>
#include <stdlib.h>

#define FILE_BOARD "board.txt"
#define FILE_TILES "tiles.txt"

typedef struct {

    int valH, valV; 

    char colorH, colorV;

} tile_t;

typedef struct {

    int id;
    int rot;

} cell_t;

void leggiFile(int * nR, int * nC,  tile_t ** tiles, int * nTiles, cell_t *** board, int ** used);

void leggiFile(int * nR, int * nC,  tile_t ** tiles, int * nTiles, cell_t *** board, int ** used) {

    FILE * fileInTiles;
    FILE * fileInBoard;

    fileInTiles = fopen(FILE_TILES, "r");
    fileInBoard = fopen(FILE_BOARD, "r");

    fscanf(fileInTiles, "%d", nTiles);

    fscanf(fileInBoard, "%d %d", nR, nC);

    *tiles = malloc( (*nTiles) * sizeof(tile_t) );

        tile_t * pointer = * tiles;

    for (int i = 0; i < *nTiles; i++, pointer++) {

        fscanf(fileInTiles, " %c %d %c %d", 

            &pointer->colorH, 
            &pointer->valH, 
            &pointer->colorV, 
            &pointer->valV

        );

    }

    *board = malloc( (*nR) * sizeof(cell_t *) );

    for (int i = 0; i < *nR; i++) {

        (*board)[i] = malloc( (*nC) * sizeof(cell_t) );

    }

    for (int i = 0; i < *nR; i++) {

        for (int j = 0; j < *nC; j++) {

            fscanf(fileInBoard, "%d/%d", 

                &(*board)[i][j].id, 
                &(*board)[i][j].rot

            );

        }

    }

    *used = calloc(*nTiles, sizeof(int));

    for (int i = 0; i < *nR; i++) {

        for (int j = 0; j < *nC; j++) {

            if ( (*board)[i][j].id != -1) {

                (*used)[(*board)[i][j].id] = 1;

            }

        }

    }

    fclose(fileInTiles);
    fclose(fileInBoard);
    
    return;

}

int main(void) {

    int nR, nC;
    int nTiles;

    tile_t * tiles;
    cell_t ** board;

    int * used;

    leggiFile(&nR, &nC, &tiles, &nTiles, &board, &used);








    





    return 0;

}