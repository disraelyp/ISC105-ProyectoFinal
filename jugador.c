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
        gets(contA);
        if (verificar_char_int(contA) == 0){
            printf("\n\tERROR: ENTRADA INVALIDA, INTENTELO NUEVAMENTE. NOTA: NO INGRESE LETRAS NI SIMBOLOS, SOLO NUMEROS\n");
            printf("\t->");
        } else{
            contB= char_int(contA);
        }
    } while(verificar_char_int(contA) == 0);

    if (contB < limiteA || contB>limiteB){
        do {
            printf("\n\tERROR: ENTRADA INVALIDA, INTENTELO NUEVAMENTE. NOTA: INGRESE UN NUMERO DENTRO DEL RANGO (%d-%d)\n", limiteA, limiteB);
            printf("\t->");

            do {
                gets(contA);
                if (verificar_char_int(contA) == 0){
                    printf("\n\tERROR: ENTRADA INVALIDA, INTENTELO NUEVAMENTE. NOTA: NO INGRESE LETRAS NI SIMBOLOS, SOLO NUMEROS\n", limiteA, limiteB);
                    printf("\t->");
                } else{
                    contB= char_int(contA);
                }
            } while(verificar_char_int(contA) == 0);


        } while(contB<limiteA || contB>limiteB);
    }
    return contB;
}
int captura_charSN() {
    char contA[]="a";
    gets(contA);
    int cont=contA[0];
    if (cont != 110 && cont != 115 && cont != 78 && cont != 83){
        do {
            printf("\n\tERROR: ENTRADA INVALIDA, INTENTELO NUEVAMENTE.\n");
            printf("\tRECORDATORIO: SI SU RESPUESTA ES UN SI, INGRESE 'S'. DE LO CONTRARIO INGRESE 'N'\n\n");
            printf("->");
            scanf("%s", &cont);
            cont=contA[0];
        } while(cont != 110 && cont != 115 && cont != 78 && cont != 83);
    }
    if (cont == 115 || cont == 83){
        return 1;
    } else {
        return 0;
    }
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
        if ((*frase)=='p' || (*frase)=='P' || (*frase)=='n' || (*frase)=='N' || (*frase)=='b' || (*frase)=='B'){
            return 1;
        }
    }
    return 0;
}
int contar_fichas(const tablero cont, const jugador *pJugadorA){
    const bloque **contenedor=cont.plano;
    int contador=0;
    for (int i = 0; i < COLUMNA; ++i) {
        for (int j = 0; j < FILA; ++j) {
            if((*(*(contenedor + i) + j)).peones.propietario == pJugadorA){
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
int turno(tablero *cont, jugador *pJugadorA, jugador *pJugadorB, const int contador, char *nombre_archivo, const int id, const char *nombre_registro){
    int op;
    do{
        imprimir_tablero(*(cont));
        printf("\n\nTurno #%02d, Jugador: %s. OPCIONES: 1) Jugar, 2) Rendirse, 3) Solicitar Empate. \t->", contador, pJugadorA->nombre);
        op=captura_int(1, 3);
        switch (op) {
            case 1:
                turno_movimiento(cont, pJugadorA, pJugadorB, nombre_archivo, id, nombre_registro);
                if(!contar_fichas(*(cont), pJugadorB)){
                    return 4;
                }
                if(!verificar_ahogado(*(cont))){
                    return 5;
                }
                return 1;
            case 2:
                return 2;
            case 3:
                printf("\n\t\tJUGADOR, %s: Tu contrincante a solicitado un empate. %cAceptas su solicitud? ->", pJugadorB->nombre, 168);
                if(captura_charSN()){
                    return 3;
                }
        }
    } while (op!=5);
}
void turno_movimiento(tablero *cont, jugador *pJugadorA, jugador *pJugadorB, char *nombre_archivo, const int id, const char *nombre_registro){
    char movimiento[]="pa1 a1";
    do{
        printf("\n\tIndique Jugada *");
        imprimir_color(pJugadorA->representacion);
        printf("* ->");
        gets(movimiento);
    }while (!verificar_movimiento(cont, pJugadorA, pJugadorB, movimiento, nombre_archivo, id, nombre_registro));
}
void nueva_partida(const char *nombre_archivo, const char *nombre_registro){
    int id=nuevo_id(nombre_archivo);
    jugador contA, contB;
    creacion_jugadores(&contA, &contB);
    tablero contC=generar_tablero(&contA, &contB);
    int contador=1, ciclo=1;
    do{
        if(!verificar_ahogado(contC)){
            printf("\n\n\tLA PARTIDA A FINALIZADO DEBIDO A QUE YA NO HAY MOVIMIENTOS DISPONIBLES\n\n");
            break;
        }
        switch (turno(&contC, &contA, &contB, contador, nombre_archivo, id, nombre_registro)) {
            case 1:
                break;
            case 4:
                printf("\n\n\tEL JUGADOR '%s', HA GANADO LA PARTIDA DEBIDO A QUE SU CONTRINCANTE SE A QUEDADO SIN FICHAS\n\n\n\n\n", contA.nombre);
                agregar_registro(nombre_registro, &contB, 0, 1);
                agregar_registro(nombre_registro, &contA, 1, 0);
                ciclo=0;
                break;
            case 2:
                printf("\n\n\tEL JUGADOR '%s', HA GANADO LA PARTIDA DEBIDO A QUE SU CONTRINCANTE SE A RENDIDO\n\n\n\n\n", contB.nombre);
                agregar_registro(nombre_registro, &contB, 1, 0);
                agregar_registro(nombre_registro, &contA, 0, 1);
                ciclo=0;
                break;
            case 3:
                printf("\n\n\tLA PARTIDA A FINALIZADO DEBIDO A QUE LOS JUGADORES HAN ACORDADO UN EMPATE\n\n\n\n\n");
                ciclo=0;
                break;
            case 5:
                printf("\n\n\tLA PARTIDA A FINALIZADO DEBIDO A QUE YA NO HAY MOVIMIENTOS DISPONIBLES\n\n\n\n\n");
                ciclo=0;
                break;
        }
        if(ciclo!=0){
            switch (turno(&contC, &contB, &contA, contador, nombre_archivo, id, nombre_registro)) {
                case 1:
                    break;
                case 4:
                    printf("\n\n\tEL JUGADOR '%s', HA GANADO LA PARTIDA DEBIDO A QUE SU CONTRINCANTE SE A QUEDADO SIN FICHAS\n\n\n\n\n", contB.nombre);
                    agregar_registro(nombre_registro, &contB, 1, 0);
                    agregar_registro(nombre_registro, &contA, 0, 1);
                    ciclo=0;
                    break;
                case 2:
                    printf("\n\n\tEL JUGADOR '%s', HA GANADO LA PARTIDA DEBIDO A QUE SU CONTRINCANTE SE A RENDIDO\n\n\n\n\n", contA.nombre);
                    agregar_registro(nombre_registro, &contB, 0, 1);
                    agregar_registro(nombre_registro, &contA, 1, 0);
                    ciclo=0;
                    break;
                case 3:
                    printf("\n\n\tLA PARTIDA A FINALIZADO DEBIDO A QUE LOS JUGADORES HAN ACORDADO UN EMPATE\n\n\n\n\n");
                    ciclo=0;
                    break;
                case 5:
                    printf("\n\n\tLA PARTIDA A FINALIZADO DEBIDO A QUE YA NO HAY MOVIMIENTOS DISPONIBLES\n\n\n\n\n");
                    ciclo=0;
                    break;
            }
        }
        contador++;
    } while (ciclo!=0);
}