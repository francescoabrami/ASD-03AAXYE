#include <stdio.h>
#include <string.h>

#define ORD             4
#define CMD             7
#define MAX_STR_LEN     30
#define MAX_FILE_LEN    1000

#define FILE_IN "corse.txt"
#define FILE_OUT "out.txt"

typedef enum {oData, oCodice, oArrivo, oPartenza, cFine, sStampas, sStampaAll} comando_e;
typedef enum {false, true} bool;

typedef struct {

    int aa;
    int mm;
    int gg;


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

} voce_t;

int initData(voce_t * data);
int confrontaData(const voce_t * voceA, const voce_t * voceB, comando_e key);

void defineEpoch(voce_t * data);
void stampaRecord(voce_t * data, voce_t * sortData[][ORD], comando_e comandoLast, int lenData);
void ordinaRecord(voce_t * data, voce_t * sortRecord[][ORD], comando_e comando, int lenData);
void initSortData(voce_t * data, voce_t * sortRecord[][ORD], int lenData);

comando_e selezionaComando(char comandi[][MAX_STR_LEN]);


int initData(voce_t * data) {

    int lenData;

    FILE * fileIn;
    fileIn = fopen(FILE_IN, "r");

    fscanf(fileIn, "%d", &lenData);

    for (int i = 0; i < lenData; i++) {

        fscanf(fileIn, "%s %s %s %s %s %s %d\n", 
            data[i].codiceTrattaStr, data[i].partenzaStr,
            data[i].destinazioneStr, data[i].dataStr,
            data[i].oraPartenzaStr, data[i].oraArrivoStr, &data[i].ritardo);
        
        sscanf(data[i].dataStr, "%d/%d/%d", &data[i].data.aa, &data[i].data.mm, &data[i].data.gg);
        sscanf(data[i].oraPartenzaStr, "%d:%d:%d", &data[i].partenza.hh, &data[i].partenza.mm, &data[i].partenza.ss);
        sscanf(data[i].oraArrivoStr, "%d:%d:%d", &data[i].arrivo.hh, &data[i].arrivo.mm, &data[i].arrivo.ss);

        defineEpoch(&data[i]);

    }

    return lenData;

}

void defineEpoch(voce_t * data) {

    data->epochPartenza = data->data.aa;

    data->epochPartenza  = data->epochPartenza  * 100 + data->data.mm;
    data->epochPartenza  = data->epochPartenza  * 100 + data->data.gg;

    data->epochPartenza  = data->epochPartenza  * 100 + data->partenza.hh;
    data->epochPartenza  = data->epochPartenza  * 100 + data->partenza.mm;
    data->epochPartenza  = data->epochPartenza  * 100 + data->partenza.ss;

    data->epochArrivo = data->data.aa;

    data->epochArrivo = data->epochArrivo * 100 + data->data.mm;
    data->epochArrivo = data->epochArrivo  * 100 + data->data.gg;

    data->epochArrivo = data->epochArrivo  * 100 + data->arrivo.hh;
    data->epochArrivo = data->epochArrivo * 100 + data->arrivo.mm;
    data->epochArrivo = data->epochArrivo  * 100 + data->arrivo.ss;

    return;

}

comando_e selezionaComando(char comandi[][MAX_STR_LEN]) {

    char comandoString[MAX_STR_LEN] = "";

    printf("\n\nSELEZIONARE UN COMANDO:\n\n");

    for (int i = 0; i < CMD; i++) {

        printf("> %s ", comandi[i] );

    }

    printf("\n\nCOMANDO > ");

    scanf("%s", comandoString);
    printf("\n");

    for (int i = 0; i < CMD; i++) {

        if ( strcmp(comandi[i],comandoString) == 0) {

            return (comando_e) i;

        }

    }

    return (comando_e) -1;

}

void stampaData(voce_t * data, voce_t * sortData[][ORD], comando_e cmd, int lenData) {

    for (int i = 0; i < lenData; i++) {

        printf("%-5s %-12s %-15s %s %s %s %d \n", sortData[i][(int) cmd]->codiceTrattaStr, 
            sortData[i][(int) cmd]->partenzaStr, sortData[i][(int) cmd]->destinazioneStr, 
            sortData[i][(int) cmd]->dataStr, sortData[i][(int) cmd]->oraPartenzaStr, 
            sortData[i][(int) cmd]->oraArrivoStr, sortData[i][(int) cmd]->ritardo);

    }

    return;

}

void ordinaData(voce_t * data, voce_t * sortRecord[][ORD], comando_e comando, int lenData) {

    for (int i = 0; i < lenData - 1; i++) {

        for (int j = 0; j < lenData - 1 - i; j++) {

            if (confrontaData(sortRecord[j][comando], sortRecord[j + 1][comando], comando) > 0) {

                voce_t * tmp = sortRecord[j][(int) comando];
                sortRecord[j][(int) comando] = sortRecord[j + 1][(int) comando];
                sortRecord[j + 1][(int) comando] = tmp;

            }

        }

    }

    return;

}

int confrontaData(const voce_t * voceA, const voce_t * voceB, comando_e key) {

    switch (key) {

        case oData: {

            return (voceA->epochPartenza > voceB->epochPartenza) - (voceA->epochPartenza < voceB->epochPartenza);

        } break;

        case oCodice: {

            return strcmp(voceA->codiceTrattaStr, voceB->codiceTrattaStr);

        } break;

        case oArrivo: {

            return strcmp(voceA->destinazioneStr, voceB->destinazioneStr);

        } break;

        case oPartenza: {

            return strcmp(voceA->partenzaStr, voceB->partenzaStr);

        } break;

    }

    return 0;

}

void initSortData(voce_t * data, voce_t * sortRecord[][ORD], int lenData) {

    for (int j = 0; j < lenData; j++) {

        for (int i = 0; i < ORD; i++) {

            sortRecord[j][i] = & data[j];

        }
    }
}

int main(void) {

    bool exit = false;
    bool wrongCommand;

    comando_e comandoLast = oData;

    voce_t data [MAX_FILE_LEN];

    voce_t * sortData[MAX_FILE_LEN][ORD];

    char comandi[][MAX_STR_LEN] = {"odata", "ocodice", "oarrivo", "opartenza", "fine", "stampas", "stampall"};

    int lenData = initData(data);

    initSortData(data, sortData, lenData);

    do {

        comando_e comando = selezionaComando(comandi);
        wrongCommand = false;

        switch (comando) {

            case sStampas: {

                stampaData(data, sortData, comandoLast, lenData);

            } break;

            case sStampaAll: {

                for (int i = 0; i < ORD; i++) {

                    printf("\nORDINAMENTO PER %s\n\n", comandi[i]);
                    stampaData(data, sortData, (comando_e) i, lenData);

                }

                printf("\nSe l'ordinamento non é corretto chiamare il relativo comando!\n\n");


            } break;

            case oData: {

                ordinaData(data, sortData, comando, lenData);

            } break;

            case oCodice: {

                ordinaData(data, sortData, comando, lenData);

            } break;

            case oArrivo: {

                ordinaData(data, sortData, comando, lenData);

            } break;
            
            case oPartenza: {

                ordinaData(data, sortData, comando, lenData);

            } break;

            case cFine: {
                
                exit = true;

            } break;

            default: {

                printf("Comando errato!\n\n");
                wrongCommand = true;

            } break;

        }

        if (comando != sStampas && comando != sStampaAll && !wrongCommand) {

            comandoLast = comando;

        }

    } while (!exit);


    return 0;

}