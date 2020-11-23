#include "header.h"

jugador creacion_jugador(int x){
    jugador cont;
    printf("\tIngrese el nombre del jugador #0%d -> ", x+1); gets(cont.nombre);
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
    jugador contA=creacion_jugador(0);
    jugador contB=creacion_jugador(1);
    (*a)=contA;
    (*b)=contB;
}
void actualizacion_jugador(jugador *jugador){
    if ((*jugador).representacion==negro){
        (*jugador).representacion=blanco;
    } else {
        (*jugador).representacion=negro;
    }

}
void actualizacion_jugadores(jugador *a, jugador *b){
    actualizacion_jugador(a);
    actualizacion_jugador(b);
}