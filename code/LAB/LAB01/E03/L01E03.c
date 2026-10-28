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
int confrontaRecord(const voce_t * voceA, const voce_t * voceB, comando_e key);
int ricercaStazione(voce_t * data, int lenData, char * ricercaStr);

void defineEpoch(voce_t * data);
void stampaRecord(voce_t data[MAX_FILE_LEN], int lenData, FILE * file);
void ordinaRecord(voce_t * data, int lenData, comando_e key);
void ricercaRecord(voce_t * data, int lenData, comando_e key);

comando_e leggiComando(char comandi[][MAX_STR_LEN]) {

    /** @brief Funzione ritorna il comando selezionato dall'utente e stampa a schermo quelli disponibili;
     *  
     * @param comandi[][MAX_STR_LEN] Array di stringe contententi i comandi da stampare a schermo;
     * 
     * @return comando_e Tipo enum corrispondente al comando scelto via cast esplicito;
     * 
    */ 

    char comandoString[MAX_STR_LEN] = "";

    printf("SELEZIONARE UN COMANDO:\n\n");

    for (int i = 0; i < CMD; i++) {

        printf("> %s ", comandi[i] );

    }

    printf("\n\nCOMANDO > ");

    scanf("%s", comandoString);
    printf("\n");

    for (int i = 0; i < CMD; i++) {

        if (strcmp(comandoString, comandi[i]) == 0) {

            return (comando_e) i;

        }

    }

    return (comando_e) -1;
    
}

int initData(voce_t data[MAX_FILE_LEN]) {

    /** @brief Funzione legge i dati dal file di input. Letti i dati vengono memorizzati in opportuna struttura dati;
     *  Oltre a quello la funzione chiama funzioni che operano sui singoli dati per creare parametri di confronto da utilizzare più avanti;
     *  La funzione inizializza il file di output rendendolo vuoto;
     * 
     * @param data[][MAX_FILE_IN] Parametro ricevuto per puntatore é il vettore di dimensione massima MAX_FILE_IN dichiarato nel main;
     * 
     * @return lenData La funzione restituisce il numero di record letti nel file;
     * 
    */

    FILE * fileIn;
    FILE * fileOut;

    int lenData;

    fileIn = fopen(FILE_IN, "r");
    fileOut = fopen(FILE_OUT, "w");

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

    fprintf(fileOut, "");

    fclose(fileIn);
    fclose(fileOut);

    return lenData;

}

void defineEpoch(voce_t * data) {

    /**
     * @brief Funzione riceve una istanza delle struct e ne calcoal un tag per ordinamento temporale;
     * Il tag é creato concatenando i valori di YYYY/MM/GG/HH/MM/SS in un int long long;
     * 
     * @param data Riferisce ad una instanza della struct;
     * 
     * @return void There is no return type;
     * 
    */

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

void stampaRecord(voce_t data[MAX_FILE_LEN], int lenData, FILE * file) {

    /**
     * @brief Funzione utilizzata per la stampa dei record a schermo o su file;
     *
     * @param data[MAX_FILE_LEN] Viene passato il vettore di cui stampare il contenuto;
     * @param lenData Lunghezza del vettore di record;
     * @param file Puntatore a file, nel caso in cui sia NULL si stampa a schemro su stdout altriemnti al file puntato;
     * 
     * @return void There is no return type;
    */

    if (file == NULL) {

        file = stdout;

    }
    
    for (int i = 0; i < lenData; i++) {

        fprintf(file, "%s %s %s %s %s %s %d \n", data[i].codiceTrattaStr, data[i].partenzaStr,
        data[i].destinazioneStr, data[i].dataStr, data[i].oraPartenzaStr, data[i].oraArrivoStr, data[i].ritardo);

    }

    printf("\n");

    return;

}

void ordinaRecord(voce_t * data, int lenData, comando_e key) {

    /**
     * @brief La funzione esegue il BubbleSort tra le entry del vettore;
     * In base al comando decide che confronto passare a confrontaRecord();
     * 
     * @param data Puntatore a vettore di struct;
     * @param lenData Lunghezza del vettore;
     * @param key Comando da eseguire per capire che campi confrontare;
    */

    for (int i = 0; i < lenData - 1; i++) {

        for (int j = 0; j < lenData - 1 - i; j++) {

            if (confrontaRecord(&data[j], &data[j + 1], key) > 0) {

                voce_t tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;

            }

        }

    }

}

int confrontaRecord(const voce_t * voceA, const voce_t * voceB, comando_e key) {

    /**
     * @brief Funzione in base al comando recevuto ed alle due istanze della struct decide il confronto e ritorna un valore corretto;
     * 
     * @param voceA puntatore al primo elemento;
     * @param voceB puntatore al secondo elemento;
     * @param key comando che deve essere eseguito;
     * 
     * @retunr La funzione ritorna un valore positivo o negativo se bisogna eseguire o meno lo swap;
    */

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

        default:
            return 0;
    }

}

void ricercaRecord(voce_t * data, int lenData, comando_e key) {

    /**
     * @brief Funzione che ricerca tutti i record con il codice tratta cercato;
     * 
     * @param data Puntatore alla struct di record;
     * @param lenData Intro che indica la lunghezza dei dati;
     * @param key Comando che si intende eseguire;
     * 
     * @return The function does not return anything;
    */

    switch (key) {

        case rCodice: {

            char ricercaStr[MAX_STR_LEN];
            printf("Inserire la tratta desiderata:\n\nCODICE > ");

            scanf("%s", ricercaStr);
            printf("\n");

            for (int i = 0; i < lenData; i++) {

                if( strcmp(ricercaStr, data[i].codiceTrattaStr) == 0) {

                    printf("%s %s %s %s %s %s %d \n", data[i].codiceTrattaStr, data[i].partenzaStr,
                        data[i].destinazioneStr, data[i].dataStr, data[i].oraPartenzaStr, 
                        data[i].oraArrivoStr, data[i].ritardo);
                }

            }

            printf("\n");

        } break;

        case rStazione: {

            char ricercaStr[MAX_STR_LEN];
            printf("Inserire la stazione di partenza desiderata:\n\nNOME STAZIONE > ");

            scanf("%s", ricercaStr);
            printf("\n");

            ricercaStazione(data, lenData, ricercaStr);


        } break;

    }

    return;

}

int ricercaStazione(voce_t * data, int lenData, char * ricercaStr) {

    /**
     * @brief Funzione che cicla sui nomi delle stazioni di partenza, se trova una corrispoindenza
     * con un valore ache parziale (dal primo char) con la stringa di ricerca stampa il record;
     * 
     * @param data Puntatore al vettore di struct record;
     * @param lenData Lunghezza del vettore;
     * @param ricercaStr Puntatore a stringa di ricerca;
     * 
     * @return La funzione ritorna 1 se trova una corrispondenza e zero se non la trova;
    */

    bool corrispondenza;

    for (int i = 0; i < lenData; i++) {

        corrispondenza = true;

        for (int j = 0; j < strlen(ricercaStr); j++) {

            char a = ricercaStr[j];
            char b = data[i].partenzaStr[j];

            if (ricercaStr[j] != data[i].partenzaStr[j]) {

                corrispondenza = false;
                break;

            } 

        }

        if (corrispondenza == true) {

            printf("%s %s %s %s %s %s %d \n", data[i].codiceTrattaStr, data[i].partenzaStr,
                    data[i].destinazioneStr, data[i].dataStr, data[i].oraPartenzaStr, 
                    data[i].oraArrivoStr, data[i].ritardo);

        }
        
    }

    printf("\n");

    return 0;

}

int main(void) {

    bool exit = false;
    voce_t data[MAX_FILE_LEN];

    char comandi[][MAX_STR_LEN] = {"stampas", "stampaf", "odata", "ocodice", "oarrivo", "opartenza", "rcodice", "rstazione", "fine"};

    int lenData = initData(data);
    
    do {

        comando_e comando = leggiComando(comandi);

        switch (comando) {

            case sStampas: {
                
                // Stampa i record a schermo;

                stampaRecord(data, lenData, NULL);

            } break;

            case sStampaf: {

                // Stampa i record sul file di output;
                
                FILE * fileOut = fopen(FILE_OUT, "w");
                stampaRecord(data, lenData, fileOut);
                fclose(fileOut);

            }   break;

            case oData: {

                // Ordina i dati per momento di partenza;

                ordinaRecord(data, lenData, comando);

            } break;

            case oCodice: {

                // Ordina i dati per codice della tratta;

                ordinaRecord(data, lenData, comando);

            } break;
            
            case oArrivo: {

                // Ordina i dati per stazione di arrivo della tratta;

                ordinaRecord(data, lenData, comando);

            } break; 

            case oPartenza: {

                // Ordina i dati per stazione di partenza della tratta;

                ordinaRecord(data, lenData, comando);


            } break;

            case rCodice: {

                // Ricerca delle corse per un dato codice tratta;

                ricercaRecord(data, lenData, comando);

            } break;

            case rStazione: {

                // Ricerca delle corse per un dato codice tratta;

                ricercaRecord(data, lenData, comando);

            } break;

            case cFine: {

                // Sequenza di uscita;

                exit = true;

            } break;

            default: {

                // Output di default che indica un comando non trovato;

                printf("COMANDO ERRATO!\n\n");

            } break;

        }

    } while (!exit);

    return 0;

}  