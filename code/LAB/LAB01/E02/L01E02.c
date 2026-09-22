#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define MAXL 1000
#define CMD 6
#define STR 31
#define FILE_IN "corse.txt"

typedef enum {r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine} comando_e;
typedef enum {false, true} bool;

typedef struct {

    int aa;
    int mm;
    int gg;

} data_t;

typedef struct {

    int hh;
    int mm;
    int ss;

} ora_t;

typedef struct {

    char codiceTrattaStr[STR];
    char partenzaStr[STR];
    char destinazioneStr[STR];
    char dataStr[STR];
    char oraPartenzaStr[STR];
    char oraArrivoStr[STR];
    int ritardo;
    data_t data;
    ora_t partenza, arrivo;

} voce_t;

typedef struct {

    int nRecord;
    voce_t elenco[MAXL];

} record_t;

record_t leggiRecord(void);
comando_e leggiComando(char comandi[][STR]);
void stampaComandi(char comandi[][STR]);
void selezionaDati(record_t record, comando_e comando);
int confrontaDate(data_t d1, data_t d2);
int dataStrToInt(data_t d);
void stampaRecord(record_t record, int i);


record_t leggiRecord(void) {

    record_t record;

    FILE *fileIn = fopen(FILE_IN, "r");

    if (fileIn == NULL) {

        exit(-1);

    }

    fscanf(fileIn, "%d", &record.nRecord);

    for (int i = 0; i < record.nRecord; i++ ) {

        fscanf(fileIn, "%s %s %s %s %s %s %d\n",
            record.elenco[i].codiceTrattaStr, record.elenco[i].partenzaStr,
            record.elenco[i].destinazioneStr, record.elenco[i].dataStr,
            record.elenco[i].oraPartenzaStr, record.elenco[i].oraArrivoStr, &record.elenco[i].ritardo);

        sscanf(record.elenco[i].dataStr, "%d/%d/%d", &record.elenco[i].data.aa, &record.elenco[i].data.mm, &record.elenco[i].data.gg);
        sscanf(record.elenco[i].oraPartenzaStr, "%d:%d:%d", &record.elenco[i].partenza.hh, &record.elenco[i].partenza.mm, &record.elenco[i].partenza.ss);
        sscanf(record.elenco[i].oraArrivoStr, "%d:%d:%d", &record.elenco[i].arrivo.hh, &record.elenco[i].arrivo.mm, &record.elenco[i].arrivo.ss);
    }

    fclose(fileIn);
    return record;

}

void stampaComandi(char comandi[][STR]) {
    printf("\nSELEZIONARE UN COMANDO:\n\n");
    for (int i = 0; i < CMD; i++ ) {
        printf("> %s ", comandi[i] );
    }
    printf("\n");
}

comando_e leggiComando(char comandi[][STR]) {

    char cmd[STR];
    printf("\nCOMANDO > ");
    scanf("%s", cmd);

    for (int i = 0; i < CMD; i++ ) {
        if (strcmp(cmd, comandi[i]) == 0) {
            return (comando_e) i;
        }
    }

    return (comando_e) -1;

}

void selezionaDati(record_t record, comando_e comando) {

    data_t d1, d2;
    char target[STR];
    int ritatdo_tot = 0;

    if (comando == r_date) {

        printf("\nINSERIRE LA PRIMA DATA (AAAA/MM/GG):\n DATA > ");
        scanf("%d/%d/%d", &d1.aa, &d1.mm, &d1.gg);
        printf("\nINSERIRE LA SECONDA DATA (AAAA/MM/GG):\n DATA > ");
        scanf("%d/%d/%d", &d2.aa, &d2.mm, &d2.gg);

    } else if (comando == r_partenza) {

        printf("\nINSERIRE LA FERMATA: \n FERMATA > ");
        scanf("%s", &target);

    } else if (comando == r_capolinea) {

        printf("\nINSERIRE IL CAPOLINEA: \n CAPOLINEA > ");
        scanf("%s", &target);

    } else if (comando == r_ritardo) {

        printf("\nINSERIRE LA PRIMA DATA (AAAA/MM/GG):\n DATA > ");
        scanf("%d/%d/%d", &d1.aa, &d1.mm, &d1.gg);
        printf("\nINSERIRE LA SECONDA DATA (AAAA/MM/GG):\n DATA > ");
        scanf("%d/%d/%d", &d2.aa, &d2.mm, &d2.gg);

    } else if (comando == r_ritardo_tot) {

        printf("\nINSERIRE IL CODICE TRATTA: \n CODICE > ");
        scanf("%s", &target);

    }

    printf("\nRECORD TROVATI: \n");

    for (int i = 0; i < record.nRecord; i++) {

        switch (comando) {

            case r_date: {

                if (confrontaDate(d1, record.elenco[i].data) <= 0 && confrontaDate(record.elenco[i].data, d2) <= 0) {
                    stampaRecord(record, i);
                }

            } break;

            case r_partenza: {

                if (strcmp(target, record.elenco[i].partenzaStr) == 0) {
                    stampaRecord(record, i);
                }

            } break;

            case r_capolinea: {

                if (strcmp(target, record.elenco[i].destinazioneStr) == 0) {
                    stampaRecord(record, i);
                }

            } break;

            case r_ritardo: {
                if (confrontaDate(record.elenco[i].data, d1) == 1 && confrontaDate(record.elenco[i].data, d2) == -1
                    && record.elenco[i].ritardo > 0) {
                    stampaRecord(record, i);
                }

            }  break;

            case r_ritardo_tot: {

                if (!strcmp(target, record.elenco[i].codiceTrattaStr)) {
                    ritatdo_tot = ritatdo_tot + record.elenco[i].ritardo;

                }

            } break;
        }

    }

    if (comando == r_ritardo_tot) {
        printf("\nRITARDO TOTALE: %d\n", ritatdo_tot);
    }

    return;

}

int confrontaDate(data_t d1, data_t d2) {

    int dI1, dI2;
    dI1 = dataStrToInt(d1);
    dI2 = dataStrToInt(d2);

    if (dI1 < dI2)
        return -1;
    if (dI1 > dI2)
        return 1;
    return 0;
}

int dataStrToInt(data_t d){

    return d.gg + d.mm * 30 + d.aa * 365;

}

void stampaRecord(record_t record, int i) {

    printf("%s %s %s %s %s %s %d \n",record.elenco[i].codiceTrattaStr, record.elenco[i].partenzaStr,
        record.elenco[i].destinazioneStr, record.elenco[i].dataStr, record.elenco[i].oraPartenzaStr,
        record.elenco[i].oraArrivoStr, record.elenco[i].ritardo);

    return;
}

int main() {

    bool exit = false;
    char comandi[][STR] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};

    record_t record = leggiRecord();
    comando_e comando;

    do {

        stampaComandi(comandi);
        comando = leggiComando(comandi);

        switch (comando) {

            case r_date:
                selezionaDati(record, comando);
                break;

            case r_partenza:
                selezionaDati(record, comando);
                break;

            case r_capolinea:
                selezionaDati(record, comando);
                break;

            case r_ritardo:
                selezionaDati(record, comando);
                break;

            case r_ritardo_tot:
                selezionaDati(record, comando);
                break;

            case r_fine:
                exit = true;
                break;

            default:
                printf("COMANDO ERRATO! \n ");
                break;
        }

    } while (!exit);

    return 0;

}