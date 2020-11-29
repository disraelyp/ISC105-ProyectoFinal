#include "header.h"

int verificar_char_to_int (char frase[]) {
    int contA;
    for ( contA = 0; frase[contA] != '\0'; contA++ ){
        if (frase[contA]!= '1' && frase[contA]!= '2' && frase[contA]!= '3' && frase[contA]!= '4' && frase[contA]!= '5' && frase[contA]!= '6' && frase[contA]!= '7' && frase[contA]!= '8' && frase[contA]!= '9' && frase[contA]!= '0') {
            return 0;
        }
    }
    return 1;
}
int captura_int(int limiteA, int limiteB) {
    int contB;

    char contA[limiteB-limiteA];
    do {
        scanf("%s", &contA);
        if (verificar_char_to_int(contA)==0){
            printf("\n\tERORR: ENTRADA INVALIDA, INTENTELO NUEVAMENTE. NOTA: NO INGRESE LETRAS NI SIMBOLOS, SOLO NUMEROS\n");
            printf("\t->");
        } else{
            contB=char_to_int(contA);
        }
    } while(verificar_char_to_int(contA)==0);

    if (contB < limiteA || contB>limiteB){
        do {
            printf("\n\tERORR: ENTRADA INVALIDA, INTENTELO NUEVAMENTE. NOTA: INGRESE UN NUMERO DENTRO DEL RANGO (%d-%d)\n", limiteA, limiteB);
            printf("\t->");

            do {
                scanf("%s", &contA);
                if (verificar_char_to_int(contA)==0){
                    printf("\n\tERORR: ENTRADA INVALIDA, INTENTELO NUEVAMENTE. NOTA: NO INGRESE LETRAS NI SIMBOLOS, SOLO NUMEROS\n", limiteA, limiteB);
                    printf("\t->");
                } else{
                    contB=char_to_int(contA);
                }
            } while(verificar_char_to_int(contA)==0);


        } while(contB<limiteA || contB>limiteB);
    }
    return contB;
}
int char_to_int (char frase[]) {
    int contA=0, contB, contC;
    for ( contB = 0; frase[contB] != '\0'; contB++ ){
        if (frase[contB]== '1' || frase[contB]== '2' || frase[contB]== '3' || frase[contB]== '4' || frase[contB]== '5' || frase[contB]== '6' || frase[contB]== '7' || frase[contB]== '8' || frase[contB]== '9' || frase[contB]== '0') {
            contC=frase[contB];
            contA=+(contA*10)+(contC-'0');
        }
    }
    return contA;
}
int verificar_frase(char *frase){
    if (strlen(frase)==6 && *(frase)=='p' && *(frase+1)>=97 && *(frase+1)<=104 && *(frase+2)>=49 && *(frase+2)<=56 && *(frase+3)==' '&& *(frase+4)>=97 && *(frase+4)<=104 && *(frase+5)>=49 && *(frase+5)<=56){
        return 1;
    }
    return 0;
}