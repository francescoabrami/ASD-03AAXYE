#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ORD             4
#define CMD             8
#define MAX_STR_LEN     30

typedef enum {false, true} bool;
typedef enum {oData, oCodice, oArrivo, oPartenza, cFine, iFile, sStampas, sStampaAll} comando_e;

typedef struct {

    int yy;
    int mm;
    int dd;

} date_t;

typedef struct {

    int hh;
    int mm;
    int ss;

} time_t;

typedef struct {

    char codiceTrattaStr[MAX_STR_LEN];
    char partenzaStr[MAX_STR_LEN];
    char destinazioneStr[MAX_STR_LEN];
    char dataStr[MAX_STR_LEN];
    char oraPartenzaStr[MAX_STR_LEN];
    char oraArrivoStr[MAX_STR_LEN];

    int ritardo;

    long long epochPartenza;
    long long epochArrivo;

    date_t data;
    time_t partenza, arrivo;

} record_t;

comando_e getComando(char (*comandiList)[MAX_STR_LEN]);

record_t * readFile(record_t * recordSet, int * recordSize);
record_t * readData(record_t * recordSet, int * recordSize, FILE * fileIn);
void stampaRecord(record_t *** sortData, comando_e comando, int * recordSize);
void initData(record_t * recordSet, record_t **** sortData, int * recordSize);

void sortRecord(record_t *** sortData, int * recordSize, comando_e cmd);

int confrontaData(record_t * a, record_t * b, comando_e cmd);


void setEpoch(record_t * record);

comando_e getComando(char (*comandiList)[MAX_STR_LEN]) {

    char comando[MAX_STR_LEN];

    for (int i = 0; i < CMD; i++) {

        printf("%s > ", comandiList[i]);

    }

    printf("\n\nCOMANDO > ");
    scanf("%29s", comando);
    printf("\n");

    for (int i = 0; i < CMD; i++) {

        if ( strcmp(comando, comandiList[i]) == 0) {

            return (comando_e) i;

        }

    }

    return (comando_e) -1;

}

record_t * readFile(record_t * recordSet, int * recordSize) {

    FILE * fileIn = NULL;

    char fileName[MAX_STR_LEN];

    do {

        printf("INSERIRE IL NOME DEL FILE\n\nFILE > ");
        scanf("%29s", fileName);
        printf("\n");

        fileIn = fopen(fileName, "r");

    } while (fileIn == NULL);

    fscanf(fileIn, "%d ", recordSize);

    return readData(recordSet, recordSize, fileIn);

}

record_t * readData(record_t * recordSet, int * recordSize, FILE * fileIn) {

    free(recordSet);

    recordSet = malloc(*recordSize * sizeof(record_t));

    for (int i = 0; i < *recordSize; i++) {

        fscanf(fileIn, "%s %s %s %s %s %s %d\n", recordSet[i].codiceTrattaStr, 
            recordSet[i].partenzaStr, recordSet[i].destinazioneStr, recordSet[i].dataStr,
            recordSet[i].oraPartenzaStr, recordSet[i].oraArrivoStr, &recordSet[i].ritardo);


        sscanf(recordSet[i].dataStr, "%d/%d/%d", &recordSet[i].data.yy, &recordSet[i].data.mm, &recordSet[i].data.dd);
        sscanf(recordSet[i].oraPartenzaStr, "%d:%d:%d", &recordSet[i].partenza.hh, &recordSet[i].partenza.mm, &recordSet[i].partenza.ss);
        sscanf(recordSet[i].oraArrivoStr, "%d:%d:%d", &recordSet[i].arrivo.hh, &recordSet[i].arrivo.mm, &recordSet[i].arrivo.ss);

        setEpoch(&recordSet[i]);

    }

    fclose(fileIn);

    return recordSet;

}

void setEpoch(record_t * data) {

    data->epochPartenza = data->data.yy;

    data->epochPartenza = data->epochPartenza * 100 + data->data.mm;
    data->epochPartenza = data->epochPartenza * 100 + data->data.dd;

    data->epochPartenza = data->epochPartenza * 100 + data->partenza.hh;
    data->epochPartenza = data->epochPartenza * 100 + data->partenza.mm;
    data->epochPartenza = data->epochPartenza * 100 + data->partenza.ss;

    data->epochArrivo = data->data.yy;

    data->epochArrivo = data->epochArrivo * 100 + data->data.mm;
    data->epochArrivo = data->epochArrivo * 100 + data->data.dd;

    data->epochArrivo = data->epochArrivo * 100 + data->arrivo.hh;
    data->epochArrivo = data->epochArrivo * 100 + data->arrivo.mm;
    data->epochArrivo = data->epochArrivo * 100 + data->arrivo.ss;

    return;

}

void stampaRecord(record_t *** sortData, comando_e comando, int * recordSize) {

    for (int i = 0; i < *recordSize; i++) {

        record_t * record = sortData[i][comando];

        printf("%-6s %-15s %-15s %s %s %s %d\n", record->codiceTrattaStr, record->partenzaStr,
            record->destinazioneStr, record->dataStr, record->oraPartenzaStr, 
            record->oraArrivoStr, record->ritardo);

    }

    printf("\n");
}

void initData(record_t * recordSet, record_t **** sortData, int * recordSize) {

    * sortData = malloc(*recordSize * sizeof(record_t **));

    for (int i = 0; i < *recordSize; i++) {

        (*sortData) [i] = malloc(ORD * sizeof(record_t *));

    }

    for (int i = 0; i < *recordSize; i++) {

        for (int j = 0; j < ORD; j++) {

            (*sortData) [i][j] = &recordSet[i];

        }
    }
}

void sortRecord(record_t *** sortData, int * recordSize, comando_e cmd) {

    record_t * tmp;

    for (int i = 0; i < *recordSize - 1; i++) {

        for (int j = 0; j < *recordSize - i - 1; j++) {

            if (confrontaData( sortData[j][cmd], sortData[j + 1][cmd], cmd) > 0) {

                tmp = sortData[j][cmd];

                sortData[j][cmd] = sortData[j + 1][cmd];

                sortData[j + 1][cmd] = tmp;

            }
        }
    }

    return;

}

int confrontaData(record_t * a, record_t * b, comando_e cmd) {

    switch (cmd) {

        case oCodice: {

            return strcmp(a->codiceTrattaStr, b->codiceTrattaStr);

        }
            
        case oArrivo: {

            return strcmp(a->destinazioneStr, b->destinazioneStr);

        }

        case oPartenza: {

            return strcmp(a->partenzaStr, b->partenzaStr);

        }

        case oData: {

            return (a->epochPartenza > b->epochPartenza) - (b->epochPartenza > a->epochPartenza);

        }

        default: {

            return 0;

        }

    }

}

int main(void) {

    char comandiList [][MAX_STR_LEN] = {"odata", "ocodice", "oarrivo", "opartenza", "cfine", "ifile", "stampa", "stampall"}; 

    record_t * recordSet = NULL;
    record_t *** sortData = NULL;
    
    int recordSize = 0;

    bool exit = false;
    bool readyFile = false;
    comando_e lastComando = oData;

    do {

        comando_e comando = getComando(comandiList);

        switch (comando) {

            case oData: {

                sortRecord(sortData, &recordSize, comando);

            } break;

            case oCodice: {

                sortRecord(sortData, &recordSize, comando);

            } break;

            case oPartenza: {

                sortRecord(sortData, &recordSize, comando);

            } break;

            case oArrivo: {

                sortRecord(sortData, &recordSize, comando);

            } break;

            case sStampas: {

                    if (readyFile) {

                        stampaRecord(sortData, lastComando, &recordSize);

                    } 
                    
                    else {

                        printf("CARICARE PRIMA UN FILE!\n\n");
                        
                    }

            } break;

            case sStampaAll: {

                if (readyFile) {

                    for (int i = 0; i < ORD; i++) {

                        printf("ORDINAMENTO PER %s\n\n", comandiList[i]);

                        stampaRecord(sortData, (comando_e) i, &recordSize);

                    }

                } 
                
                else {

                    printf("CARICARE PRIMA UN FILE!\n\n");
                        
                }

            } break;

            case cFine: {

                free(sortData);
                free(recordSet);
                exit = true;

            } break;

            case iFile: {

                recordSet = readFile(recordSet, &recordSize);

                initData(recordSet, &sortData, &recordSize);

                readyFile = true;

            } break;

            default: {

                printf("COMANDO ERRATO!\n\n");

            } break;

        }

        if (comando >= oData && comando <= oPartenza) {
            
            lastComando = comando;
        }

    } while (!exit);

    return 0;

}
