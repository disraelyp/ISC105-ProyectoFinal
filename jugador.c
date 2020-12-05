#include "header.h"

jugador creacion_jugador(int representacion){
    jugador contenedor;
    printf("\n");
    if(representacion == 1){
        contenedor.representacion=blancas;
    } else {
        contenedor.representacion=negras;
    }
    printf("Indique el nombre del jugador de las "); imprimir_color(contenedor.representacion); printf("\t->"); gets(contenedor.nombre);
    return contenedor;
}
void creacion_jugadores (jugador *pJugadorA, jugador *pJugadorB){
    (*pJugadorA)=creacion_jugador(0);
    (*pJugadorB)=creacion_jugador(1);
}
void imprimir_color(color representacion){
    if (representacion == blancas){
        printf("BLANCAS");
    } else {
        printf("NEGRAS");
    };
}
int turno(jugador *pJugador){
    printf("");
}
void nueva_partida(){
    jugador a, b;
    creacion_jugadores(&a, &b);
    tablero cont=generar_tablero(&a, &b);
    int op;
    do {

    } while (1==1);

}
int verificar_char_to_int (char *frase) {
    int contA;
    for (contA = 0; *(frase+contA)!= '\0'; contA++ ){
        if (*(frase+contA)!= '1' && *(frase+contA)!= '2' && *(frase+contA)!= '3' && *(frase+contA)!= '4' && *(frase+contA)!= '5' && *(frase+contA)!= '6' && *(frase+contA)!= '7' && *(frase+contA)!= '8' && *(frase+contA)!= '9' && *(frase+contA)!= '0') {
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
int char_to_int (char *frase) {
    int contA=0, contB, contC;
    for ( contB = 0; *(frase+contB)!= '\0'; contB++ ){
        if (*(frase+contB)== '1' || *(frase+contB)== '2' || *(frase+contB)== '3' || *(frase+contB)== '4' || *(frase+contB)== '5' || *(frase+contB)== '6' || *(frase+contB)== '7' || *(frase+contB)== '8' || *(frase+contB)== '9' || *(frase+contB)== '0') {
            contC=*(frase+contB);
            contA+=(contA*10)+(contC-'0');
        }
    }
    return contA;
}
int verificar_frase(char *frase){
    if (strlen(frase)==6 && *(frase+1)>=97 && *(frase+1)<=104 && *(frase+2)>=49 && *(frase+2)<=56 && *(frase+3)==' '&& *(frase+4)>=97 && *(frase+4)<=104 && *(frase+5)>=49 && *(frase+5)<=56){
        if ((*frase)=='p' || (*frase)=='P'){
            return 1;
        }
    }
    return 0;
}
posiciones posiciones_char(char *posicion) {
    posiciones lista_enum[64] = {a8, b8, c8, d8, e8, f8, g8, h8, a7, b7, c7, d7, e7, f7, g7, h7, a6, b6, c6, d6, e6, f6, g6, h6, a5, b5, c5, d5, e5, f5, g5, h5, a4, b4, c4, d4, e4, f4, g4, h4, a3, b3, c3, d3, e3, f3, g3, h3, a2, b2, c2, d2, e2, f2, g2, h2, a1, b1, c1, d1, e1, f1, g1, h1};
    char lista_char[][64] = {"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"};
    int i;
    for (i = 0; strcmp(lista_char[i], posicion); i++);
    return lista_enum[i];
}