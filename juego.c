#include "header.h"
// 1: VACIA
int cambio_posicion(tablero *cont, jugador *a, posiciones const inicial, posiciones const final){
    bloque **contenedor=cont->plano;
    int const xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial), xFinal=calcular_cordenadaX(final), yFinal=calcular_cordenadaY(final);
    estado_peon estadoPeon;
    if((*(*(contenedor + yInicial) + xInicial)).peones.estado==dama){
        estadoPeon = dama;
    } else{
        estadoPeon = basica;
    }
    (*(*(contenedor + yInicial) + xInicial))=creacion_bloque(NULL, calcular_cordenada(inicial), 1);

    if (cordenadas_externas(final) || estadoPeon == dama){
        (*(*(contenedor + yFinal) + xFinal))=creacion_bloque(a, calcular_cordenada(final), 0);
    } else{
        (*(*(contenedor + yFinal) + xFinal))=creacion_bloque(a, calcular_cordenada(final), 1);
    }
    cont->plano=contenedor;
}
int verificar_movimiento(tablero const tableroJuego, posiciones const inicial, posiciones const final){
    bloque **pPlano=tableroJuego.plano;
    int xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial), xFinal=calcular_cordenadaX(final), yFinal=calcular_cordenadaY(final);
    if((*(*(pPlano + yInicial) + xInicial)).estado == bloqueado){
        if ((((*(*(pPlano + yInicial) + xInicial)).peones.estado==dama) || ((*(*(pPlano + yInicial) + xInicial)).peones.propietario->representacion == blancas)) && (*(*(pPlano + yInicial) + xInicial)).estado != casilla_blanca){
            if ((yInicial+1)==yFinal && (xInicial-1)==xFinal && (*(*(pPlano + (yInicial + 1)) + (xInicial - 1))).estado == disponible && xInicial >= 0 && yInicial <= 7){
                return 1;
            }
            if ((yInicial+1)==yFinal && (xInicial+1)==xFinal && (*(*(pPlano + (yInicial + 1)) + (xInicial + 1))).estado == disponible && xInicial <= 7 && yInicial <= 7){
                return 1;
            }
        }
        if((((*(*(pPlano + yInicial) + xInicial)).peones.estado==dama) || ((*(*(pPlano + yInicial) + xInicial)).peones.propietario->representacion == blancas)) && (*(*(pPlano + yInicial) + xInicial)).estado != casilla_blanca){
            if ((yInicial-1)==yFinal && (xInicial-1)==xFinal && (*(*(pPlano + (yInicial - 1)) + (xInicial - 1))).estado == disponible && xInicial >= 0 && yInicial <= 7){
                return 1;
            }
            if ((yInicial-1)==yFinal && (xInicial+1)==xFinal && (*(*(pPlano + (yInicial - 1)) + (xInicial + 1))).estado == disponible && xInicial <= 7 && yInicial >= 0){
                return 1;
            }
        }
        if((((*(*(pPlano + yInicial) + xInicial)).peones.estado==dama) || ((*(*(pPlano + yInicial) + xInicial)).peones.propietario->representacion == negras)) && (*(*(pPlano + yInicial) + xInicial)).estado != casilla_blanca){
            if ((yInicial-1)==yFinal && (xInicial-1)==xFinal && (*(*(pPlano + (yInicial - 1)) + (xInicial - 1))).estado == disponible && xInicial >= 0 && yInicial <= 7){
                return 1;
            }
            if ((yInicial-1)==yFinal && (xInicial+1)==xFinal && (*(*(pPlano + (yInicial - 1)) + (xInicial + 1))).estado == disponible && xInicial <= 7 && yInicial >= 0){
                return 1;
            }
        }

        if((((*(*(pPlano + yInicial) + xInicial)).peones.estado==dama) || ((*(*(pPlano + yInicial) + xInicial)).peones.propietario->representacion == negras)) && (*(*(pPlano + yInicial) + xInicial)).estado != casilla_blanca){
            if ((yInicial+1)==yFinal && (xInicial-1)==xFinal && (*(*(pPlano + (yInicial + 1)) + (xInicial - 1))).estado == disponible && xInicial >= 0 && yInicial <= 7){
                return 1;
            }
            if ((yInicial+1)==yFinal && (xInicial+1)==xFinal && (*(*(pPlano + (yInicial + 1)) + (xInicial + 1))).estado == disponible && xInicial <= 7 && yInicial <= 7){
                return 1;
            }
        }
    }
    return 0;
}

void reajustar_tablero(tablero *cont){
    bloque **contenedor=cont->plano;
    int contador=0;
    for (int i = 0; i < COLUMNA; ++i) {
        for (int j = 0; j < FILA; ++j) {
            (*(*(contenedor + i) + j)).posicion=calcular_posicion(contador+1);
            contador++;
        }
    }
    cont->plano=contenedor;
}

int verificar_posiciones(tablero *cont, jugador *a, jugador *b, char const *movimiento){
    if (verificar_frase(movimiento)){
        char posicion_inicial[3]={*(movimiento+1), *(movimiento+2), '\0'}, posicion_final[3]={*(movimiento+4), *(movimiento+5), '\0'};
        posiciones inicial =posiciones_char(posicion_inicial), final =posiciones_char(posicion_final);
        if(posiciones_jugables(inicial) && posiciones_jugables(final)){
            if(recorrer_eliminar(*(cont), a, b)){
                if(posiciones_diagonales(inicial, final)){
                    if(reconfirmar_eliminar(*(cont), inicial, final)){
                        if(verificar_propietario(*(cont), a, inicial)){
                            verificar_posiciones_eliminar(cont, a, inicial, final);
                            reajustar_tablero(cont);
                            return 1;
                        } else{
                            printf("\n\tERORR: LA FICHA A MOVER, LE PERTENECE A OTRO JUGADOR.\n");
                        }
                    } else {
                        printf("\n\tERORR: EL MOVIMIENTO ES INVALIDO.\n");
                    }
                }else{
                    if(verificar_movimiento(*(cont), inicial, final)){
                        printf("\n\tERORR: EL MOVIMIENTO ES INVALIDO, DEBIDO A QUE UNA DE TUS FICHAS DEBE ELEMINAR UNA FICHA OPONENTE.\n");
                    } else {
                        printf("\n\tERORR: EL MOVIMIENTO ES INVALIDO.\n");
                    }
                }
            } else {
                if(verificar_movimiento(*(cont), inicial, final)){
                    if(verificar_propietario(*(cont), a, inicial)){
                        cambio_posicion(cont, a, inicial, final);
                        reajustar_tablero(cont);
                        return 1;
                    } else{
                        printf("\n\tERORR: LA FICHA A MOVER, LE PERTENECE A OTRO JUGADOR.\n");
                    }

                } else{
                    printf("\n\tERORR: EL MOVIMIENTO ES INVALIDO.\n");
                }
            }
        } else {
            printf("\n\tERORR: LAS POSICIONES INGRESADAS NO SON VALIDAS.\n");
        }
    } else {
        printf("\n\tERORR: LA ENTRADA ES INVALIDAD, VERIFIQUE EL FORMATO ALGEBRAICO.\n");
    }
    return 0;
}
int verificar_propietario(tablero const tableroJuego, jugador *pJugador, posiciones const ubicacion){
    bloque **pPlano=tableroJuego.plano;
    int x=calcular_cordenadaX(ubicacion), y=calcular_cordenadaY(ubicacion);
    if((*(*(pPlano + y) + x)).peones.propietario == pJugador){
        return 1;
    }
    return 0;
}
int verificar_ahogado(tablero const tableroJuego, posiciones const inicial){
    bloque **contenedor=tableroJuego.plano;
    int xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial);
    if((*(*(contenedor + yInicial) + xInicial)).peones.propietario->representacion == blancas && (*(*(contenedor + yInicial) + xInicial)).estado != casilla_blanca){
        if ((*(*(contenedor+(yInicial + 1)) + (xInicial - 1))).estado == disponible && xInicial >= 0 && yInicial <= 7){
            if ((*(*(contenedor+(yInicial + 1)) + (xInicial + 1))).estado == disponible && xInicial <= 7 && yInicial <= 7){
                return 2;
            }
            return 1;
        }
        if ((*(*(contenedor+(yInicial + 1)) + (xInicial + 1))).estado == disponible && xInicial <= 7 && yInicial <= 7){
            return 1;
        }
    }
    if((*(*(contenedor + yInicial) + xInicial)).peones.propietario->representacion == negras && (*(*(contenedor + yInicial) + xInicial)).estado != casilla_blanca){
        if ((*(*(contenedor+(yInicial - 1)) + (xInicial - 1))).estado == disponible && xInicial >= 0 && yInicial <= 7){
            if ((*(*(contenedor+(yInicial - 1)) + (xInicial + 1))).estado == disponible && xInicial <= 7 && yInicial >= 0){
                return 2;
            }
            return 1;
        }
        if ((*(*(contenedor+(yInicial - 1)) + (xInicial + 1))).estado == disponible && xInicial <= 7 && yInicial >= 0){
            return 1;
        }
    }
    return 0;
}
int contar_fichas(tablero const cont, jugador *a){
    bloque **contenedor=cont.plano;
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

int posiciones_diagonales(posiciones const inicial, posiciones const final){
    int const xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial), xFinal=calcular_cordenadaX(final), yFinal=calcular_cordenadaY(final);
    if((xInicial-2==xFinal && yInicial-2==yFinal)||(xInicial-2==xFinal && yInicial+2==yFinal)||(xInicial+2==xFinal && yInicial-2==yFinal)||(xInicial+2==xFinal && yInicial+2==yFinal)){
        return 1;
    }
    return 0;
}

posiciones posicion_intermedia(posiciones inicial, posiciones final){
    int inicial_cordenada=calcular_cordenada(inicial), final_cordenada=calcular_cordenada(final);
    return calcular_posicion((final_cordenada+inicial_cordenada)/2);
}

int verificar_posiciones_eliminar(tablero *cont, jugador *a, posiciones inicial, posiciones final){
    bloque **contenedor=cont->plano;
    const int xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial), xFinal=calcular_cordenadaX(final), yFinal=calcular_cordenadaY(final);
    const posiciones intermedia =  posicion_intermedia(inicial, final);
    estado_peon estado;
    if((*(*(contenedor + yInicial) + xInicial)).peones.estado==dama){
        estado = dama;
    } else{
        estado = basica;
    }
    (*(*(contenedor + yInicial) + xInicial))=creacion_bloque(NULL, calcular_cordenada(inicial), 0);
    (*(*(contenedor + calcular_cordenadaY(intermedia)) + calcular_cordenadaX(intermedia)))=creacion_bloque(NULL, calcular_cordenada(intermedia), 0);

    if (cordenadas_externas(final) || estado == dama){
        (*(*(contenedor + yFinal) + xFinal))=creacion_bloque(a, calcular_cordenada(final), 0);
    } else{
        (*(*(contenedor + yFinal) + xFinal))=creacion_bloque(a, calcular_cordenada(final), 1);
    }

    cont->plano=contenedor;
    reajustar_tablero(cont);
}


int recorrer_eliminar(tablero const cont, jugador *a, jugador *b){
    bloque **contenedor=cont.plano;
    int contador=0;
    for (int i = 0; i < COLUMNA; ++i) {
        for (int j = 0; j < FILA; ++j) {
            if((*(*(contenedor + i) + j)).peones.propietario == a){
                if(verificar_eliminar(contenedor, b, calcular_posicion(contador + 1))) {
                    return 1;
                }
            }
            contador++;
        }
    }
    return 0;
}
int verificar_eliminar(bloque **contenedor, jugador *b, posiciones const ficha){
    int contador=0;
    for (int i = 0; i < COLUMNA; ++i) {
        for (int j = 0; j < FILA; ++j) {
            if((*(*(contenedor + i) + j)).peones.propietario == b){
                if((*(*(contenedor + calcular_cordenadaY(ficha)) + calcular_cordenadaX(ficha))).peones.propietario->representacion==blancas || (*(*(contenedor + calcular_cordenadaY(ficha)) + calcular_cordenadaX(ficha))).peones.estado==dama) {

                    if ((calcular_cordenadaX(ficha) + 1 == calcular_cordenadaX(calcular_posicion(contador + 1))) && (calcular_cordenadaY(ficha) + 1 == calcular_cordenadaY(calcular_posicion(contador + 1)))) { // ARREGLAR
                        if ((*(*(contenedor + calcular_cordenadaY(ficha) + 2) + calcular_cordenadaX(ficha) +
                               2)).estado == disponible) {
                            return 1;
                        }
                    }
                    if ((calcular_cordenadaX(ficha) - 1 == calcular_cordenadaX(calcular_posicion(contador + 1))) && (calcular_cordenadaY(ficha) + 1 == calcular_cordenadaY(calcular_posicion(contador + 1)))) {
                        if ((*(*(contenedor + calcular_cordenadaY(ficha) + 2) + calcular_cordenadaX(ficha) -
                               2)).estado == disponible) {
                            return 1;
                        }
                    }
                }

                if((*(*(contenedor + calcular_cordenadaY(ficha)) + calcular_cordenadaX(ficha))).peones.propietario->representacion==negras || (*(*(contenedor + calcular_cordenadaY(ficha)) + calcular_cordenadaX(ficha))).peones.estado==dama) {
                    if((calcular_cordenadaX(ficha)-1 == calcular_cordenadaX(calcular_posicion(contador+1))) && (calcular_cordenadaY(ficha) - 1 == calcular_cordenadaY(calcular_posicion(contador+1)))){
                        if((*(*(contenedor + calcular_cordenadaY(ficha)-2) + calcular_cordenadaX(ficha)-2)).estado==disponible){
                            return 1;
                        }
                    }
                    if((calcular_cordenadaX(ficha)+1 == calcular_cordenadaX(calcular_posicion(contador+1))) && (calcular_cordenadaY(ficha)-1 == calcular_cordenadaY(calcular_posicion(contador+1)))){ // ARREGLAR
                        if((*(*(contenedor + calcular_cordenadaY(ficha)-2) + calcular_cordenadaX(ficha)+2)).estado==disponible){
                            return 1;
                        }
                    }
                }
            }
            contador++;
        }
    }
    return 0;
}

int reconfirmar_eliminar(tablero cont, posiciones const inicial, posiciones const final){
    bloque **contenedor=cont.plano;
    posiciones intermedia = posicion_intermedia(inicial, final);
    int xIntermedia=calcular_cordenadaX(intermedia), yIntermedia=calcular_cordenadaY(intermedia);
    int xInicial =calcular_cordenadaX(inicial), yFinal=calcular_cordenadaY(final), yInicial=calcular_cordenadaY(inicial), xFinal=calcular_cordenadaX(final);
    if((*(*(contenedor + yFinal) + xFinal)).estado==disponible && (*(*(contenedor + yInicial) + xInicial)).estado==bloqueado && (*(*(contenedor + yIntermedia) + xIntermedia)).estado==bloqueado){
        if ((*(*(contenedor + yInicial) + xInicial)).peones.propietario!=(*(*(contenedor + yIntermedia) + xIntermedia)).peones.propietario){
            return 1;
        }
    }
    return 0;
}