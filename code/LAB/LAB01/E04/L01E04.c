#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 30
#define MAX_FILE_LEN 1000
#define CMD 6

#define FILE_IN "corse.txt"
#define FILE_OUT "out.txt"

typedef enum {sStampas, oData, oCodice, oArrivo, oPartenza, cFine} comando_e;
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
void defineEpoch(voce_t * data);
comando_e selezionaComando(char comandi[][MAX_STR_LEN]);
void stampaRecord(voce_t * data, int lenData);
void ordinaRecord(voce_t * data, voce_t * refData[], int lenData);

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

    printf("SELEZIONARE UN COMANDO:\n\n");

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

void stampaRecord(voce_t * data, int lenData) {

    for (int i = 0; i < lenData; i++) {

        printf("%-5s %-12s %-15s %s %s %s %d \n", data[i].codiceTrattaStr, data[i].partenzaStr,
            data[i].destinazioneStr, data[i].dataStr, data[i].oraPartenzaStr, data[i].oraArrivoStr, data[i].ritardo);

    }


    printf("\n\n");

    return;

}

void ordinaRecord(voce_t * data, voce_t * refData[], int lenData) {






    return;

}

int main(void) {

    bool exit = false;
    voce_t data [MAX_FILE_LEN];

    voce_t * sortData[MAX_FILE_LEN];
    voce_t * sortCodice[MAX_FILE_LEN];
    voce_t * sortArrivo[MAX_FILE_LEN];
    voce_t * sortPartenza[MAX_FILE_LEN];

    char comandi[][MAX_STR_LEN] = {"stampas", "odata", "ocodice", "oarrivo", "opartenza", "fine"};

    int lenData = initData(data);


    do {

        comando_e comando = selezionaComando(comandi);

        switch (comando) {

            case sStampas: {

                stampaRecord(data, lenData);

            } break;

            case oData: {

                

            } break;

            case oCodice: {


            } break;

            case oArrivo: {


            }

            case oPartenza: {


            } break;

            case cFine: {
                
                exit = true;

            } break;

            default: {

                printf("Comando errato!\n\n");

            } break;

        }

    } while (!exit);

    return 0;

}