#include "header.h"

tablero generar_tablero(const jugador *pJugadorA, const jugador *pJugadorB) {
    bloque **bloques = (bloque **) malloc(8 * sizeof(bloque));
    for (int i = 0; i<FILA; ++i) {
        *(bloques+i) = (bloque *) malloc(8* sizeof(bloque));
    }
    int posicion=1, cont=1;
    for (int i = 0; i < COLUMNA; i++) {
        for (int j = 0; j < FILA; j++) {
            if (ubicaciones_iniciales(posicion) && posicion < (FILA * COLUMNA) / 2){
                if(cont==10){
                    if(pJugadorB->representacion == blancas){
                        *(*(bloques+i)+j)=creacion_bloque(pJugadorB, posicion, 1);
                    } else {
                        *(*(bloques+i)+j)=creacion_bloque(pJugadorA, posicion, 1);
                    }
                } else {
                    cont++;
                    *(*(bloques+i)+j)= creacion_bloque(NULL, posicion, 1);
                }
            } else {
                if (ubicaciones_iniciales(posicion) && posicion > (FILA * COLUMNA) / 2){
                    if(pJugadorB->representacion != blancas){
                        *(*(bloques+i)+j)= creacion_bloque(pJugadorB, posicion, 1);
                    } else {
                        *(*(bloques+i)+j)= creacion_bloque(pJugadorA, posicion, 1);
                    }
                } else {
                    *(*(bloques+i)+j)= creacion_bloque(NULL, posicion, 1);
                }
            }
            posicion++;
        }
    }
    tablero contenedor={pJugadorA, 12, pJugadorB, 12, bloques};
    return contenedor;
}
peon creacion_peon(const jugador *pJugador, const int posicion, const int estado){
    peon contenedor;
    contenedor.propietario=pJugador;
    contenedor.posicion=calcular_posicion(posicion);
    if (estado){
        contenedor.estado=basica;
    } else{
        contenedor.estado=dama;
    }
    return contenedor;
}
bloque creacion_bloque(const jugador *pJugador, const int contB, const int estado){
    bloque contenedor;
    if (ubicaciones_jugables(contB)){
        if(pJugador == NULL){
            contenedor.estado=disponible;
        } else {
            contenedor.estado=bloqueado;
            contenedor.peones=creacion_peon(pJugador, contB, estado);
        }
        contenedor.posicion=calcular_posicion(contB);
    } else {
        contenedor.estado=casilla_blanca;
        contenedor.posicion=calcular_posicion(contB);
    }
    return contenedor;
}
void cambio_posicion(tablero *tableroJuego, const jugador *pJugadorA, const jugador *pJugadorB, const posiciones inicial, const posiciones final, const char *pNombre_archivo, int const id, const char *pNombre_registro){
    bloque **contenedor=tableroJuego->plano;
    int const xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial), xFinal=calcular_cordenadaX(final), yFinal=calcular_cordenadaY(final);
    estado_peon estadoPeon;
    if((*(*(contenedor + yInicial) + xInicial)).peones.estado==dama){
        estadoPeon = dama;
    } else{
        estadoPeon = basica;
    }
    (*(*(contenedor + yInicial) + xInicial))=creacion_bloque(NULL, calcular_ubicacion(inicial), 1);

    if (ubicaciones_externas(final) || estadoPeon == dama){
        (*(*(contenedor + yFinal) + xFinal))=creacion_bloque(pJugadorA, calcular_ubicacion(final), 0);
    } else{
        (*(*(contenedor + yFinal) + xFinal))=creacion_bloque(pJugadorA, calcular_ubicacion(final), 1);
    }
    agregar_notacion(pNombre_archivo, id, pJugadorA, pJugadorB, inicial, final);
    tableroJuego->plano=contenedor;
}
void eliminar_posicion(tablero *tableroJuego, const jugador *pJugadorA, const jugador *pJugadorB, const posiciones inicial, const posiciones final, const char *pNombre_archivo, int const id, const char *pNombre_registro){
    bloque **contenedor=tableroJuego->plano;
    const int xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial), xFinal=calcular_cordenadaX(final), yFinal=calcular_cordenadaY(final);
    const posiciones intermedia =  posicion_intermedia(inicial, final);
    estado_peon estado;
    if((*(*(contenedor + yInicial) + xInicial)).peones.estado==dama){
        estado = dama;
    } else{
        estado = basica;
    }
    (*(*(contenedor + yInicial) + xInicial))=creacion_bloque(NULL, calcular_ubicacion(inicial), 0);
    (*(*(contenedor + calcular_cordenadaY(intermedia)) + calcular_cordenadaX(intermedia)))=creacion_bloque(NULL,
                                                                                                           calcular_ubicacion(
                                                                                                                   intermedia), 0);
    if (ubicaciones_externas(final) || estado == dama){
        (*(*(contenedor + yFinal) + xFinal))=creacion_bloque(pJugadorA, calcular_ubicacion(final), 0);
    } else{
        (*(*(contenedor + yFinal) + xFinal))=creacion_bloque(pJugadorA, calcular_ubicacion(final), 1);
    }
    agregar_notacion(pNombre_archivo, id, pJugadorA, pJugadorB, inicial, final);
    tableroJuego->plano=contenedor;
}
int verificar_posiciones(const tablero tableroJuego, const posiciones inicial, const posiciones final){
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
int verificar_movimiento(tablero *tableroJuego, jugador *pJugadorA, jugador *pJugadorB, const char *movimiento, const char *pNombre_archivo, const int id, const char *pNombre_registros){
    if (verifica_entrada(movimiento)){
        char posicion_inicial[3]={*(movimiento+1), *(movimiento+2), '\0'}, posicion_final[3]={*(movimiento+4), *(movimiento+5), '\0'};
        posiciones inicial = extraer_posiciones(posicion_inicial), final = extraer_posiciones(posicion_final);
        if(posiciones_jugables(inicial) && posiciones_jugables(final)){
            if(recorrer_tablero(*(tableroJuego), pJugadorA, pJugadorB)){
                if(posiciones_diagonales(inicial, final)){
                    if(parametros_eliminar(*(tableroJuego), inicial, final)){
                        if(verificar_propietario(*(tableroJuego), pJugadorA, inicial)){
                            eliminar_posicion(tableroJuego, pJugadorA, pJugadorB, inicial, final, pNombre_archivo, id, pNombre_registros);
                            reajustar_tablero(tableroJuego);
                            if(!recorrer_tablero(*(tableroJuego), pJugadorA, pJugadorB)){
                                return 1;
                            }
                        } else{
                            printf("\n\tERROR: LA FICHA A MOVER, LE PERTENECE A OTRO JUGADOR.\n");
                        }
                    } else {
                        printf("\n\tERROR: EL MOVIMIENTO ES INVALIDO.\n");
                    }
                }else{
                    if(verificar_posiciones(*(tableroJuego), inicial, final)){
                        printf("\n\tERROR: EL MOVIMIENTO ES INVALIDO, DEBIDO A QUE UNA DE TUS FICHAS DEBE ELEMINAR UNA FICHA OPONENTE.\n");
                    } else {
                        printf("\n\tERROR: EL MOVIMIENTO ES INVALIDO.\n");
                    }
                }
            } else {
                if(verificar_posiciones(*(tableroJuego), inicial, final)){
                    if(verificar_propietario(*(tableroJuego), pJugadorA, inicial)){
                        cambio_posicion(tableroJuego, pJugadorA, pJugadorB, inicial, final, pNombre_archivo, id, pNombre_registros);
                        reajustar_tablero(tableroJuego);
                        return 1;
                    } else{
                        printf("\n\tERROR: LA FICHA A MOVER, LE PERTENECE A OTRO JUGADOR.\n");
                    }

                } else{
                    printf("\n\tERROR: EL MOVIMIENTO ES INVALIDO.\n");
                }
            }
        } else {
            printf("\n\tERROR: LAS POSICIONES INGRESADAS NO SON VALIDAS.\n");
        }
    } else {
        printf("\n\tERROR: LA ENTRADA ES INVALIDA, VERIFIQUE EL FORMATO ALGEBRAICO.\n");
    }
    return 0;
}
void reajustar_tablero(tablero *tableroJuego){
    bloque **contenedor=tableroJuego->plano;
    int contador=0;
    for (int i = 0; i < COLUMNA; ++i) {
        for (int j = 0; j < FILA; ++j) {
            (*(*(contenedor + i) + j)).posicion=calcular_posicion(contador+1);
            contador++;
        }
    }
    tableroJuego->plano=contenedor;
    tableroJuego->total_fichasA=contar_fichas(*(tableroJuego), tableroJuego->jugadorA);
    tableroJuego->total_fichasB=contar_fichas(*(tableroJuego), tableroJuego->jugadorB);
}
int recorrer_tablero(const tablero tableroJuego, const jugador *pJugadorA, const jugador *pJugadorB){
    bloque const **contenedor=tableroJuego.plano;
    int contador=0;
    for (int i = 0; i < COLUMNA; ++i) {
        for (int j = 0; j < FILA; ++j) {
            if((*(*(contenedor + i) + j)).estado!=casilla_blanca && (*(*(contenedor + i) + j)).peones.propietario == pJugadorA){
                if(verificar_eliminar(contenedor, pJugadorB, calcular_posicion(contador + 1))) {
                    return 1;
                }
            }
            contador++;
        }
    }
    return 0;
}
int verificar_eliminar(const bloque **bloques, const jugador *pJugador, const posiciones ficha){
    int contador=0;
    for (int i = 0; i < COLUMNA; i++) {
        for (int j = 0; j < FILA; j++) {
            if((*(*(bloques + i) + j)).peones.propietario == pJugador){
                if((*(*(bloques + calcular_cordenadaY(ficha)) + calcular_cordenadaX(ficha))).peones.propietario->representacion == blancas || (*(*(bloques + calcular_cordenadaY(ficha)) + calcular_cordenadaX(ficha))).peones.estado == dama) {
                    if(calcular_cordenadaX(ficha)+1<=7 && calcular_cordenadaX(calcular_posicion(contador + 1))<=7 && calcular_cordenadaY(ficha)+1<=7 && calcular_cordenadaY(calcular_posicion(contador + 1))<=7){
                        if ((calcular_cordenadaX(ficha) + 1 == calcular_cordenadaX(calcular_posicion(contador + 1))) && (calcular_cordenadaY(ficha) + 1 == calcular_cordenadaY(calcular_posicion(contador + 1)))) { // ARREGLAR
                            if((calcular_cordenadaY(ficha)+2)<=7 && (calcular_cordenadaX(ficha)+2)<=7){
                                if ((*(*(bloques + calcular_cordenadaY(ficha) + 2) + calcular_cordenadaX(ficha) + 2)).estado == disponible) {
                                    return 1;
                                }
                            }
                        }
                    }
                    if(calcular_cordenadaX(ficha)-1>=0 && calcular_cordenadaX(calcular_posicion(contador + 1))<=7 && calcular_cordenadaY(ficha)+1<=7 && calcular_cordenadaY(calcular_posicion(contador + 1))<=7){
                        if ((calcular_cordenadaX(ficha)-1 == calcular_cordenadaX(calcular_posicion(contador + 1))) && (calcular_cordenadaY(ficha) + 1 == calcular_cordenadaY(calcular_posicion(contador + 1)))) {
                            if((calcular_cordenadaY(ficha)+2)<=7 && (calcular_cordenadaX(ficha)-2)>=0){
                                if ((*(*(bloques + calcular_cordenadaY(ficha) + 2) + calcular_cordenadaX(ficha) - 2)).estado == disponible) {
                                    return 1;
                                }
                            }
                        }
                    }
                }
                if((*(*(bloques + calcular_cordenadaY(ficha)) + calcular_cordenadaX(ficha))).peones.propietario->representacion == negras || (*(*(bloques + calcular_cordenadaY(ficha)) + calcular_cordenadaX(ficha))).peones.estado == dama) {
                    if(calcular_cordenadaX(ficha)-1>=0 && calcular_cordenadaX(calcular_posicion(contador + 1))<=7 && calcular_cordenadaY(ficha)-1>=0 && calcular_cordenadaY(calcular_posicion(contador + 1))<=7){
                        if((calcular_cordenadaX(ficha)-1 == calcular_cordenadaX(calcular_posicion(contador+1))) && (calcular_cordenadaY(ficha) - 1 == calcular_cordenadaY(calcular_posicion(contador+1)))){
                            if((calcular_cordenadaY(ficha)-2)>=0 && (calcular_cordenadaX(ficha)-2)>=0){
                                if((*(*(bloques + calcular_cordenadaY(ficha) - 2) + calcular_cordenadaX(ficha) - 2)).estado == disponible){
                                    return 1;
                                }
                            }
                        }
                    }
                    if(calcular_cordenadaX(ficha)+1<=7 && calcular_cordenadaX(calcular_posicion(contador + 1))<=7 && calcular_cordenadaY(ficha)-1>=0 && calcular_cordenadaY(calcular_posicion(contador + 1))<=7){
                        if((calcular_cordenadaX(ficha)+1 == calcular_cordenadaX(calcular_posicion(contador+1))) && (calcular_cordenadaY(ficha)-1 == calcular_cordenadaY(calcular_posicion(contador+1)))){ // ARREGLAR
                            if((calcular_cordenadaY(ficha)-2)>=0 && (calcular_cordenadaX(ficha)+2)<=7){
                                if((*(*(bloques + calcular_cordenadaY(ficha) - 2) + calcular_cordenadaX(ficha) + 2)).estado == disponible){
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
            contador++;
        }
    }
    return 0;
}
int parametros_eliminar(const tablero tableroJuego, const posiciones inicial, const posiciones final){
    const bloque **contenedor=tableroJuego.plano;
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
int verificar_ahogado(const tablero tableroJuego){
    bloque **contenedor=tableroJuego.plano;
    for(int i=0; i<64; i++){
        posiciones inicial=calcular_posicion(i+1);
        if(posiciones_jugables(inicial)){
            int xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial);
            if((*(*(contenedor + yInicial) + xInicial)).estado==bloqueado){
                if((*(*(contenedor + yInicial) + xInicial)).peones.propietario->representacion == blancas){
                    if(xInicial-1 >= 0 && yInicial+1 <= 7){
                        if ((*(*(contenedor+(yInicial + 1)) + (xInicial - 1))).estado == disponible){
                            return 1;
                        }
                    }
                    if(xInicial+1 <= 7 && yInicial+1 <= 7){
                        if ((*(*(contenedor+(yInicial + 1)) + (xInicial + 1))).estado == disponible){
                            return 1;
                        }
                    }
                }
                if((*(*(contenedor + yInicial) + xInicial)).peones.propietario->representacion == negras){
                    if(xInicial-1>=0 && yInicial-1>=0){
                        if ((*(*(contenedor+(yInicial - 1)) + (xInicial - 1))).estado == disponible){
                            return 1;
                        }
                    }
                    if(xInicial+1<=7 && yInicial-1>=0){
                        if ((*(*(contenedor+(yInicial - 1)) + (xInicial + 1))).estado == disponible){
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}