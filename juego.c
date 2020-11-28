#include "header.h"

int juego(jugador *a, jugador *b, tablero *contenedor){
    int ciclo=0, cont=0;
    do{
        if(a->representacion==negro){
            cont++;
            printf("Turno #02d, Jugador: %s", cont, a->nombre);
            imprimir_color(a->representacion);
            printf(" 1) Jugar. 2) Rendirse. 3) Solicitar Empate.\t\t->");
        }
    } while (ciclo!=1);
}