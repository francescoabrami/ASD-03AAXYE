#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 1000

typedef enum {false, true} bool;

char * cercaRegExp(char * src, char * regExp);
void initPorgram(char * src, char * regExp);
void stampaRisultato(char * location, char * regExp, int charSpecial);

void initProgram(char * src, char * regExp) {

    // Inserisco i vlaori nei vettori di src e regExp;

    printf("INSERIRE LA STRINGA SU CUI SI EFFETTUA LA RICERCA:\n\nSTRINGA > ");
    scanf("%s", src);
    printf("\n");
    
    printf("INSERIRE LA REGEXP:\n\nREGEXP > ");
    scanf("%s", regExp);      
    printf("\n");  

    return;

}

void stampaRisultato(char * location, char * regExp, int charSpecial) {

    // Funzione cicla su risultato e stampa solo la lunghezza della regExp a partire dal valore di fine ricerca;
    // Tiene conto dei vlaori speciali delle regExp che non devono essere contati;

    int lenRegExp = strlen(regExp) - charSpecial;

    for (int i = 0; i < lenRegExp; i++) {

        printf("%c", * (location++ - lenRegExp) );
              
    }

    printf("\n\n");

    return;

}

char * cercaRegExp(char * src, char * regExp) {

    // Inizializzo i valori dei vettori stringa;

    initProgram(src, regExp);

    char * location = NULL;

    int lenRegExp = strlen(regExp);

    int i; // Posizione iniziale della ricerca totale in src;
    int k; // Posizione nella regExp;
    int j; // Posizione nella src ad ogni parziale;


    // Ciclo esterno su tutte le possibilità della mia ricerca dove poi verifico la regExp;

    for (int i = 0; src[i] != '\0'; i ++) { 

        // Parto dalla condizione che la soluzione sia trovata;
   
        bool trovato = true;

        int charSpecial = 0;
        
        int j = i; // Posizione corrente in src per la ricerca;
        int k = 0; // Posizione corrente della regExp;

        // Continuo fino alla fine o della regExp o della src;

        while (src[j] != '\0' && regExp[k] != '\0') {

            // Se trovo un punto va bene qualsiasi valore, accetto, aumento e passo oltre;

            if (regExp[k] == '.') {

                j++;
                k++;

            } 

            // Controllo ora se incontro una parentesi aperta '[' e agisco conseguenza;

            else if (regExp[k] == '[') {

                bool negato = false;
                bool presente = false;

                // Memorizzo la posizione della parentesi aperta;

                int apertura = k;

                k++;

                // Controllo la presenza di '^';

                if (regExp[k] == '^') {

                    negato = true;
                    k++;

                }

                // Verifico che il gruppo non sia vuoto;

                if (regExp[k] == ']' || regExp[k] == '\0') {

                    trovato = false;
                    break;

                }

                // Cerco il carattere tra quelli nelle parentesi;

                while (regExp[k] != ']' && regExp[k] != '\0') {

                    if (src[j] == regExp[k]) {

                        presente = true;

                    }

                    k++;

                }

                // Verifico che la parentesi sia stata chiusa;

                if (regExp[k] == '\0') {

                    trovato = false;
                    break;

                }

                // Valuto la corrispondenza tenendo conto dell'eventuale negazione;

                if (negato == true) {

                    if (presente == true) {

                        trovato = false;
                        break;

                    }

                } else {

                    if (presente == false) {

                        trovato = false;
                        break;

                    }

                }

                // Conto i caratteri della regexp che non orrispondono a caratteri aggiuntivi in src;

                charSpecial += k - apertura;

                // Salto la parentesi chiusa ed avanzo di un solo carattere nella sorgente;

                k++;
                j++;

            }

            // Contorllo ora se incontro una '\' e agisco di conseguenza;

            else if (regExp[k] == '\\') {

                // Avanzo sulla stringa di regExp, esludo '\';

                k++;

                // Controllo ora se c'é il match con la sola lettera miuscola o maiuscola;

                // Condizione non valida non é minuscola;

                if (regExp[k] == 'a' && (src[j] < 'a' || src[j] > 'z')) {

                    trovato = 0;
                    break;

                }

                // Condizione non valida non é maiuscola;

                else if (regExp[k] == 'A' && (src[j] < 'A' || src[j] > 'Z')) {

                    trovato = 0;
                    break;

                }

                // Non viene messa una terza via, si suppone un carattere valido;

                // Aumento i vlaori di entrambi come fatto in precedenza;

                j++;
                k++;
                charSpecial++;

            }

            // In ultima isntanza controllo che ci sia il match tra caratteri normali dunque ALPHANUM;
            
            else {

                if (src[j] != regExp[k]) {

                    trovato = false;
                    break;

                }

                k++;
                j++;

            }

            location = &src[j];

        }   

        // Controllo se ho trovato una regExp completa se si ritorno ed aggiorno la location;
        // Se non trovo un risultato utile avviso utente e ritorno puntatore a 0x00;

        if (trovato == true && regExp[k] == '\0') {

            stampaRisultato(location, regExp, charSpecial);
            return location;

        }

    }

    printf("Nessun risultato trovato!\n\n");

    return NULL;

}

int main(void) {

    char src[MAX_STR_LEN + 1];
    char regExp[MAX_STR_LEN + 1];

    char * risultato;
    
    cercaRegExp(src, regExp);

    return 0;

}

