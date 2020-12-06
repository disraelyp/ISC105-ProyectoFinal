#include "header.h"

jugador captura_jugador(const int representacion){
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
    (*pJugadorA)= captura_jugador(0);
    (*pJugadorB)= captura_jugador(1);
}
int verificar_char_int (const char *frase) {
    int contA;
    for (contA = 0; *(frase+contA)!= '\0'; contA++ ){
        if (*(frase+contA)!= '1' && *(frase+contA)!= '2' && *(frase+contA)!= '3' && *(frase+contA)!= '4' && *(frase+contA)!= '5' && *(frase+contA)!= '6' && *(frase+contA)!= '7' && *(frase+contA)!= '8' && *(frase+contA)!= '9' && *(frase+contA)!= '0') {
            return 0;
        }
    }
    return 1;
}
int captura_int(const int limiteA, const int limiteB) {
    int contB;
    char contA[limiteB-limiteA];
    do {
        scanf("%s", &contA);
        if (verificar_char_int(contA) == 0){
            printf("\n\tERORR: ENTRADA INVALIDA, INTENTELO NUEVAMENTE. NOTA: NO INGRESE LETRAS NI SIMBOLOS, SOLO NUMEROS\n");
            printf("\t->");
        } else{
            contB= char_int(contA);
        }
    } while(verificar_char_int(contA) == 0);

    if (contB < limiteA || contB>limiteB){
        do {
            printf("\n\tERORR: ENTRADA INVALIDA, INTENTELO NUEVAMENTE. NOTA: INGRESE UN NUMERO DENTRO DEL RANGO (%d-%d)\n", limiteA, limiteB);
            printf("\t->");

            do {
                scanf("%s", &contA);
                if (verificar_char_int(contA) == 0){
                    printf("\n\tERORR: ENTRADA INVALIDA, INTENTELO NUEVAMENTE. NOTA: NO INGRESE LETRAS NI SIMBOLOS, SOLO NUMEROS\n", limiteA, limiteB);
                    printf("\t->");
                } else{
                    contB= char_int(contA);
                }
            } while(verificar_char_int(contA) == 0);


        } while(contB<limiteA || contB>limiteB);
    }
    return contB;
}
int char_int (const char *frase) {
    int contA=0, contB, contC;
    for ( contB = 0; *(frase+contB)!= '\0'; contB++ ){
        if (*(frase+contB)== '1' || *(frase+contB)== '2' || *(frase+contB)== '3' || *(frase+contB)== '4' || *(frase+contB)== '5' || *(frase+contB)== '6' || *(frase+contB)== '7' || *(frase+contB)== '8' || *(frase+contB)== '9' || *(frase+contB)== '0') {
            contC=*(frase+contB);
            contA+=(contA*10)+(contC-'0');
        }
    }
    return contA;
}
int verifica_entrada(const char *frase){
    if (strlen(frase)==6 && *(frase+1)>=97 && *(frase+1)<=104 && *(frase+2)>=49 && *(frase+2)<=56 && *(frase+3)==' '&& *(frase+4)>=97 && *(frase+4)<=104 && *(frase+5)>=49 && *(frase+5)<=56){
        if ((*frase)=='p' || (*frase)=='P'){
            return 1;
        }
    }
    return 0;
}
int contar_fichas(const tablero cont, const jugador *a){
    const bloque **contenedor=cont.plano;
    int contador=0;
    for (int i = 0; i < COLUMNA; ++i) {
        for (int j = 0; j < FILA; ++j) {
            if((*(*(contenedor + i) + j)).peones.propietario == a){
                contador++;
            }
        }
    }
    return contador;
}
int verificar_propietario(const tablero tableroJuego, const jugador *pJugador, const posiciones ubicacion){
    bloque **pPlano=tableroJuego.plano;
    int x=calcular_cordenadaX(ubicacion), y=calcular_cordenadaY(ubicacion);
    if((*(*(pPlano + y) + x)).peones.propietario == pJugador){
        return 1;
    }
    return 0;
}