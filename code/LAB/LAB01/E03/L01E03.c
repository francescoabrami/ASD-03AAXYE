#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 30
#define MAX_FILE_LEN 1000
#define CMD 9

#define FILE_IN "corse.txt"
#define FILE_OUT "out.txt"

typedef enum {sStampas, sStampaf, oData, oCodice, oArrivo, oPartenza, rCodice, rStazione, cFine} comando_e;
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

comando_e leggiComando(char comandi[][MAX_STR_LEN]);

int initData(voce_t data[MAX_FILE_LEN]);

void stampaComandi(char comandi[][MAX_STR_LEN]);
void selezionaDati(comando_e comando, voce_t data[MAX_FILE_LEN], int lenData);
void stampaRecordSchermo(voce_t data[MAX_FILE_LEN], int lenData, bool screen);
void ordinaRecord(voce_t data[MAX_FILE_LEN], int lenData, comando_e key);

void defineEpoch(voce_t * data);

void stampaComandi(char comandi[][MAX_STR_LEN]){

     printf("SELEZIONARE UN COMANDO:\n\n");

    for (int i = 0; i < CMD; i++) {

        printf("> %s ", comandi[i] );

    }

    printf("\n\n");

    return;

}

comando_e leggiComando(char comandi[][MAX_STR_LEN]) {

    char comandoString[MAX_STR_LEN] = "";

    printf("COMANDO > ");

    scanf("%s", comandoString);
    printf("\n");

    for (int i = 0; i < CMD; i++) {

        if (strcmp(comandoString, comandi[i]) == 0) {

            return (comando_e) i;

        }

    }

    return (comando_e) -1;
    
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

int initData(voce_t data[MAX_FILE_LEN]) {

    FILE * fileIn;

    int lenData;

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

    fclose(fileIn);

    return lenData;

}

void stampaRecord(voce_t data[MAX_FILE_LEN], int lenData, FILE * file) {

    if (file == NULL) {

        file = stdout;

    }
    
    for (int i = 0; i < lenData; i++) {

        fprintf(file, "%s %s %s %s %s %s %d \n", data[i].codiceTrattaStr, data[i].partenzaStr,
        data[i].destinazioneStr, data[i].dataStr, data[i].oraPartenzaStr, data[i].oraArrivoStr, data[i].ritardo);

    }

    return;

}

void ordinaRecord(voce_t data[MAX_FILE_LEN], int lenData, comando_e key) {





}

void selezionaDati(comando_e comando, voce_t data[MAX_FILE_LEN], int lenData) {



    return;


}



int main(void) {

    comando_e comando;

    bool exit = false;

    char comandi[][MAX_STR_LEN] = {"stampas", "stampaf", "data", "ocodice", "arrivo", "partenza", "rcodice", "stazione", "fine"};

    voce_t data[MAX_FILE_LEN];

    int lenData = initData(data);
    
    do {

        stampaComandi(comandi);
        comando = leggiComando(comandi);

        switch (comando) {

            case sStampas: 

                stampaRecord(data, lenData, NULL);

                break;

            case sStampaf:

                FILE * fileOut = fopen(FILE_OUT, "w");
                stampaRecord(data, lenData, fileOut);
                fclose(fileOut);

                break;

            case oData:

                break;
            
            case oArrivo:

                break;

            case oPartenza:

                break;

            case rCodice:

                break;


            case rStazione:
            
                break;

            case cFine:

                exit = true;
                break;

            default: 

                printf("COMANDO ERRATO!\n\n");
                break;

        }

    } while (!exit);


    return 0;

}  



