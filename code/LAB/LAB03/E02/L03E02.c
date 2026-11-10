#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD         7
#define REC_LEN     7
#define MAX_STR_LEN 15
#define MAX_LEN     50

typedef enum {false, true} bool;

typedef enum {iTastiera, iFile, rCodice, cDato, cDati, sStampa, cFine} comando_e;

typedef struct date_t {

    int dd;
    int mm;
    int yy;

} date_t;

typedef struct node_t {

    int codice;
    char codiceCompleto[MAX_LEN];
    char nome[MAX_LEN];
    char cognome[MAX_LEN];

    date_t nascita;
    
    long long epoch;

    char via[MAX_LEN];
    char citta[MAX_LEN];

    char cap[MAX_LEN];

    struct node_t * next;

} node_t;

typedef node_t * link;

comando_e getComando(char comandiList[][MAX_STR_LEN]);
void ricercaCodice(link anagraficaHead);
void inserimentoOrdinato(link * head, link p);

void inserimentoLista(link * anagraficaHead, comando_e cmd);

void eliminaDato(link * anagraficaHead);
void eliminaDati(link * anagraficaHead);

comando_e getComando(char comandiList[][MAX_STR_LEN]) {

    char comando[MAX_STR_LEN];

    printf("SELEZIONARE UN COMANDO \n\n");

    for (int i = 0; i < CMD; i++) {

        printf("%s > ", comandiList[i]);

    }

    printf("\n\nCOMANDO > ");
    scanf("%s", comando);
    printf("\n");

    for (int i = 0; i < CMD; i++) {

        if ( strcmp(comandiList[i], comando) == 0) {

            return (comando_e) i;

        }

    }

    return (comando_e) -1;

}

bool isCodice(link anagraficaHead, int codice) {

    link p;

    for (p = anagraficaHead; p != NULL; p = p->next) {

        if (codice == p->codice) {

            return true;

        }

    }

    return false;

}

void ricercaCodice(link anagraficaHead) {

    int codice;
    char codiceCompletoRicerca[MAX_LEN];


    printf("INSERIRE CODICE DA CERCARE:\n\nCODICE > ");
    scanf("%24s", codiceCompletoRicerca);
    printf("\n");

    codice = atoi(codiceCompletoRicerca + 1);

    if (codiceCompletoRicerca[0] == 'A' && codice != 0) {

        link p;

        for (p = anagraficaHead; p != NULL; p = p -> next) {

            if (codice == p->codice) {

                printf("ELEMENTO TROVATO!\n\n");

                printf("%-5s %-15s %-10s ", p->codiceCompleto, p->nome, p->cognome);

                if (p->nascita.dd < 10) {

                    printf("0%d/", p->nascita.dd);

                } 

                else {

                    printf("%2d/", p->nascita.dd);

                }

                if (p->nascita.mm < 10) {

                    printf("0%d/", p->nascita.mm);

                } 

                else {

                    printf("%2d/", p->nascita.mm);

                }

                printf("%d %-20s %-15s %-10s \n",p->nascita.yy, p->via, p->citta, p->cap);  

                return;

            }

        }

        printf("ELEMENTO NON TROVATO!\n\n");

    }

    else {

        printf("FORMATO CODICE ERRATO!\n\n");

    }

    return;

}

void inserimentoOrdinato(link * head, link p) {

    link * pp;

    for (pp = head; *pp != NULL && (*pp)->epoch < p->epoch; pp = &((*pp)->next));

    p->next = *pp;
    *pp = p;

    return;

}

void inserimentoLista(link * anagraficaHead, comando_e cmd) {

    FILE * fileIn = NULL;

    bool fileCorrect = false;

    char fileInName[MAX_LEN];

    char codiceCompleto[MAX_LEN];
    char dataCompleta[MAX_LEN];
    char nome[MAX_LEN], cognome[MAX_LEN];
    char via[MAX_LEN], citta[MAX_LEN], cap[MAX_LEN];

    link p;

    if (cmd == iFile) {

        do {

            printf("INSERIRE IL NOME DEL FILE\n\nFILE > ");
            scanf("%24s", fileInName);
            printf("\n");

            fileIn = fopen(fileInName, "r");

            if (fileIn != NULL) {

                fileCorrect = true;
                
            }

        } while (!fileCorrect);

        while (fscanf(fileIn, "%49s %49s %49s %49s %49s %49s %49s", codiceCompleto, nome, cognome, dataCompleta, via, citta, cap) == REC_LEN) {

            p = malloc(sizeof(*p));

            p->codice = atoi(codiceCompleto + 1);
            
            strcpy(p->codiceCompleto, codiceCompleto);
            strcpy(p->nome, nome);
            strcpy(p->cognome, cognome);
            strcpy(p->via, via);
            strcpy(p->citta, citta);
            strcpy(p->cap, cap);

            sscanf(dataCompleta, "%d/%d/%d", &p->nascita.dd, &p->nascita.mm, &p->nascita.yy);

            p->epoch = p->nascita.yy;
            p->epoch = p->epoch * 100 + p->nascita.mm;
            p->epoch = p->epoch * 100 + p->nascita.dd;

            if (!isCodice(*anagraficaHead, p->codice)) {

                inserimentoOrdinato(anagraficaHead, p);

            } 
            else {

                free(p);

            }

        }

    }

    if (cmd == iTastiera) {

        fileIn = stdin;

        p = malloc(sizeof(*p));

        printf("INSERIRE CODICE\n\nCODICE > ");
        scanf("%49s", p->codiceCompleto);
        printf("\n");

        p->codice = atoi(p->codiceCompleto + 1);

        printf("INSERIRE NOME\n\nNOME > ");
        scanf("%s", p->nome);
        printf("\n");

        printf("INSERIRE COGNOME\n\nCOGNOME > ");
        scanf("%s", p->cognome);
        printf("\n");

        printf("INSERIRE DATA DI NASCITA\n\nDATA DD/MM/YY > ");
        scanf("%s", dataCompleta);
        printf("\n");

        sscanf(dataCompleta, "%d/%d/%d", &p->nascita.dd, &p->nascita.mm, &p->nascita.yy);

        p->epoch = p->nascita.yy;
        p->epoch = p->epoch * 100 + p->nascita.mm;
        p->epoch = p->epoch * 100 + p->nascita.dd;

        printf("INSERIRE VIA \n\nVIA > ");
        scanf("%s", p->via);
        printf("\n");

        printf("INSERIRE CITTÀ \n\nCITTÀ > ");
        scanf("%s", p->citta);
        printf("\n");

        printf("INSERIRE CAP \n\nCAP > ");
        scanf("%s", p->cap);
        printf("\n");

        if (!isCodice(*anagraficaHead, p->codice)) {

            inserimentoOrdinato(anagraficaHead, p);

        }
        else {

            printf("CODICE GIA' PRESENTE!\n\n");
            free(p);

        }

    }

    return;

}

void stampaLista(link anagraficaHead) {

    link p;

    if (anagraficaHead == NULL) {

        printf("LISTA VUOTA!\n\n");
        return;

    }

    for (p = anagraficaHead; p != NULL; p = p -> next) {

        printf("%-5s %-15s %-10s ", p->codiceCompleto, p->nome, p->cognome);

            if (p->nascita.dd < 10) {

                printf("0%d/", p->nascita.dd);

            } 

            else {

                printf("%2d/", p->nascita.dd);

            }

            if (p->nascita.mm < 10) {

                printf("0%d/", p->nascita.mm);

            } 

            else {

                printf("%2d/", p->nascita.mm);

            }

        printf("%d %-20s %-15s %-10s \n",p->nascita.yy, p->via, p->citta, p->cap);   

    }

    printf("\n");

    return;
    
}

void eliminaDato(link * anagraficaHead) {

    char codiceDelete[MAX_LEN];
    int codice;

    link p;
    link * pp;

    printf("INSERIRE UN CODICE VALIDO\n\nCODICE > ");
    scanf("%s", codiceDelete);
    printf("\n");

    codice = atoi(codiceDelete + 1);

    for (pp = anagraficaHead; *pp != NULL && (*pp)->codice != codice; pp = &((*pp)->next));

    p = * pp;
    *pp = p->next;

    free(p);
    
    return;

}

void eliminaDati(link * anagraficaHead) {

    link p;
    link * pp;

    char dataInizio[MAX_LEN];
    char dataFine[MAX_LEN];

    date_t data1, data2;

    long long dataI, dataF;

    printf("INSERIRE PRIMA DATA\n\nDATA DD/MM/YYYY > ");
    scanf("%49s",dataInizio);
    printf("\n");

    printf("INSERIRE SECONDA DATA\n\nDATA DD/MM/YYYY > ");
    scanf("%49s",dataFine);
    printf("\n");

    sscanf(dataInizio, "%d/%d/%d", &data1.dd, &data1.mm, &data1.yy);
    sscanf(dataFine, "%d/%d/%d", &data2.dd, &data2.mm, &data2.yy);

    dataI = data1.yy * 10000LL + data1.mm * 100 + data1.dd;
    dataF = data2.yy * 10000LL + data2.mm * 100 + data2.dd;

    pp = anagraficaHead;

    while (*pp != NULL && (*pp)->epoch <= dataF) {

        if ((*pp)->epoch >= dataI) {

            p = *pp;
            *pp = p->next;
            free(p);

        } else {


            pp = &((*pp)->next);

        }

    }

    return;

}

int main(void) {

    bool exit = false;

    char comandiList [][MAX_STR_LEN] = {"itastiera", "ifile", "rcodice", "cdato", "cdati", "stampa", "cfine"};

    link anagraficaHead = NULL;

    do {

        comando_e comando = getComando(comandiList);

        switch (comando) {

            case iTastiera: {

                inserimentoLista(&anagraficaHead, iTastiera);

            } break;

            case iFile: {

                inserimentoLista(&anagraficaHead, iFile);

            } break;

            case rCodice: {

                ricercaCodice(anagraficaHead);

            } break;

            case cDato: {

                eliminaDato(&anagraficaHead);

            } break;

            case cDati: {

                eliminaDati(&anagraficaHead);

            } break;

            case sStampa: {

                stampaLista(anagraficaHead);

            } break;

            case cFine: {

                exit = true;

            } break;

            default: {

                printf("COMANDO ERRATO!\n\n");

            }

        }

    } while (!exit);

    return 0;

}