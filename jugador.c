#include "header.h"
#include "manejo_errores.c"

jugador creacion_jugador(int x){
    jugador cont;
    printf("Ingrese el nombre del jugador #0%d ->\t\t", x+1);gets(cont.nombre);
    printf("\n");
    if(x==1){
        cont.representacion=blanco;
    } else {
        cont.representacion=negro;
    }
    cont.partidas_ganadas=0;
    cont.partidas_total=0;
    return cont;
}
void creacion_jugadores (jugador *a, jugador *b){
    printf("\n");
    (*a)=creacion_jugador(0);
    (*b)=creacion_jugador(1);
}
void actualizacion_jugador(jugador *jugador, int ganador){
    if(ganador){
        (*jugador).partidas_total++;
        (*jugador).partidas_ganadas++;
    }
    if ((*jugador).representacion==negro){
        (*jugador).representacion=blanco;
    } else {
        (*jugador).representacion=negro;
    }

}
void imprimir_color(color cont){
    if (cont==blanco){
        printf("BLANCOS");
    } else {
        printf("NEGRAS");
    };
}
void actualizacion_jugadores(jugador *a, jugador *b, int ganador){ // ENTRAR 0 SI SE CANCELO, 1 SI GANO EL PRIMER JUGADOR, 2 SI GANO EL SEGUNDO
    if (ganador==1){
        actualizacion_jugador(a, 1);
    } else {
        if (ganador==2){
            actualizacion_jugador(b, 1);
        } else {
            actualizacion_jugador(a, 0);
            actualizacion_jugador(a, 0);
        }
    }
}
void inicio(){
    jugador a, b;
    printf("Practica Final de Fundamentos de Programacion - ISC105 - PUCMM\n");
    printf("Presentado por: Disraely Peralta Uceta (10140077)\n");
    creacion_jugadores(&a, &b);
    menu(&a, &b);
}
void menu(jugador *a, jugador *b){
    int op=0;
    tablero contA;
    do {
        printf("\n\tJuego de Damas en Lenguaje C -> Menu de opciones.\n\n");
        printf("1. Nueva partida de damas.\n");
        printf("2. Ver record de jugadores.\n");
        printf("3. Ver notacion algebraica de partidas guardadas.\n");
        printf("4. Salir y guardar registro (reporte.txt).\n");
        printf("\n\t(1-4) ->");
        op=captura_int(1, 4);
        switch (op) {
            case 1:
                contA=generar_tablero(a, b);
                imprimir_tablero(contA);
                //int contB=juego(a, b, &contA);
                //actualizacion_jugadores(a, b, contB);
                break;
            case 2:
                //estadisticas(a, b);
                break;
        }
    } while (op!=4);
}