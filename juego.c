#include "header.h"

tablero generar_tablero(const jugador *jugadorA, const jugador *jugadorB) {
    bloque **bloques = (bloque **) malloc(8 * sizeof(bloque));
    for (int i = 0; i<FILA; ++i) {
        *(bloques+i) = (bloque *) malloc(8* sizeof(bloque));
    }
    int posicion=1;
    for (int i = 0; i < COLUMNA; i++) {
        for (int j = 0; j < FILA; j++) {
            if (ubicaciones_iniciales(posicion) && posicion < (FILA * COLUMNA) / 2){
                if(jugadorB->representacion == blancas){
                    *(*(bloques+i)+j)=creacion_bloque(jugadorB, posicion, 1);
                } else {
                    *(*(bloques+i)+j)=creacion_bloque(jugadorA, posicion, 1);
                }
            } else {
                if (ubicaciones_iniciales(posicion) && posicion > (FILA * COLUMNA) / 2){
                    if(jugadorB->representacion != blancas){
                        *(*(bloques+i)+j)= creacion_bloque(jugadorB, posicion, 1);
                    } else {
                        *(*(bloques+i)+j)= creacion_bloque(jugadorA, posicion, 1);
                    }
                } else {
                    *(*(bloques+i)+j)= creacion_bloque(NULL, posicion, 1);
                }
            }
            posicion++;
        }
    }
    tablero contenedor={jugadorA, 12, jugadorB, 12, bloques};
    return contenedor;
}
peon creacion_peon(const jugador *jugadorA, const int posicion, const int estado){
    peon contenedor;
    contenedor.propietario=jugadorA;
    contenedor.posicion=calcular_posicion(posicion);
    if (estado){
        contenedor.estado=basica;
    } else{
        contenedor.estado=dama;
    }
    return contenedor;
}
bloque creacion_bloque(const jugador *jugador, const int contB, const int estado){
    bloque contenedor;
    if (ubicaciones_jugables(contB)){
        if(jugador==NULL){
            contenedor.estado=disponible;
        } else {
            contenedor.estado=bloqueado;
            contenedor.peones=creacion_peon(jugador, contB, estado);
        }
        contenedor.posicion=calcular_posicion(contB);
    } else {
        contenedor.estado=casilla_blanca;
        contenedor.posicion=calcular_posicion(contB);
    }
    return contenedor;
}

void cambio_posicion(tablero *cont, const jugador *a, const jugador *b, const posiciones inicial, const posiciones final, const char *nombre_archivo, int const id){
    bloque **contenedor=cont->plano;
    int const xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial), xFinal=calcular_cordenadaX(final), yFinal=calcular_cordenadaY(final);
    estado_peon estadoPeon;
    if((*(*(contenedor + yInicial) + xInicial)).peones.estado==dama){
        estadoPeon = dama;
    } else{
        estadoPeon = basica;
    }
    (*(*(contenedor + yInicial) + xInicial))=creacion_bloque(NULL, calcular_ubicacion(inicial), 1);

    if (ubicaciones_externas(final) || estadoPeon == dama){
        (*(*(contenedor + yFinal) + xFinal))=creacion_bloque(a, calcular_ubicacion(final), 0);
    } else{
        (*(*(contenedor + yFinal) + xFinal))=creacion_bloque(a, calcular_ubicacion(final), 1);
    }
    escribir_archivo(nombre_archivo, id, a, b, inicial, final, curso);
    cont->plano=contenedor;
}
void eliminar_posicion(tablero *cont, const jugador *a, const jugador *b, const posiciones inicial, const posiciones final, const char *nombre_archivo, int const id){
    bloque **contenedor=cont->plano;
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
        (*(*(contenedor + yFinal) + xFinal))=creacion_bloque(a, calcular_ubicacion(final), 0);
    } else{
        (*(*(contenedor + yFinal) + xFinal))=creacion_bloque(a, calcular_ubicacion(final), 1);
    }
    escribir_archivo(nombre_archivo, id, a, b, inicial, final, curso);
    cont->plano=contenedor;
    reajustar_tablero(cont);
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

int verificar_movimiento(tablero *cont, jugador *a, jugador *b, const char *movimiento, const char *nombre_archivo, const int id){
    if (verifica_entrada(movimiento)){
        char posicion_inicial[3]={*(movimiento+1), *(movimiento+2), '\0'}, posicion_final[3]={*(movimiento+4), *(movimiento+5), '\0'};
        posiciones inicial = extraer_posiciones(posicion_inicial), final = extraer_posiciones(posicion_final);
        if(posiciones_jugables(inicial) && posiciones_jugables(final)){
            if(recorrer_tablero(*(cont), a, b)){
                if(posiciones_diagonales(inicial, final)){
                    if(parametros_eliminar(*(cont), inicial, final)){
                        if(verificar_propietario(*(cont), a, inicial)){
                            eliminar_posicion(cont, a, b, inicial, final, nombre_archivo, id);
                            reajustar_tablero(cont);
                            printf("\n%d / %d\n", cont->total_fichasA, cont->total_fichasB);
                            if(!recorrer_tablero(*(cont), a, b)){
                                return 1;
                            }
                        } else{
                            printf("\n\tERORR: LA FICHA A MOVER, LE PERTENECE A OTRO JUGADOR.\n");
                        }
                    } else {
                        printf("\n\tERORR: EL MOVIMIENTO ES INVALIDO.\n");
                    }
                }else{
                    if(verificar_posiciones(*(cont), inicial, final)){
                        printf("\n\tERORR: EL MOVIMIENTO ES INVALIDO, DEBIDO A QUE UNA DE TUS FICHAS DEBE ELEMINAR UNA FICHA OPONENTE.\n");
                    } else {
                        printf("\n\tERORR: EL MOVIMIENTO ES INVALIDO.\n");
                    }
                }
            } else {
                if(verificar_posiciones(*(cont), inicial, final)){
                    if(verificar_propietario(*(cont), a, inicial)){
                        cambio_posicion(cont, a, b, inicial, final, nombre_archivo, id);
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
    cont->total_fichasA=contar_fichas(*(cont), cont->jugadorA);
    cont->total_fichasB=contar_fichas(*(cont), cont->jugadorB);
}
int recorrer_tablero(const tablero cont, const jugador *a, const jugador *b){
    bloque const **contenedor=cont.plano;
    int contador=0;

    for (int i = 0; i < COLUMNA; ++i) {
        for (int j = 0; j < FILA; ++j) {
            if((*(*(contenedor + i) + j)).estado!=casilla_blanca && (*(*(contenedor + i) + j)).peones.propietario == a){
                if(verificar_eliminar(contenedor, b, calcular_posicion(contador + 1))) {
                    return 1;
                }
            }
            contador++;
        }
    }
    return 0;
}
int verificar_eliminar(const bloque **contenedor, const jugador *b, const posiciones ficha){
    int contador=0;
    for (int i = 0; i < COLUMNA; i++) {
        for (int j = 0; j < FILA; j++) {
            if((*(*(contenedor + i) + j)).peones.propietario == b){
                if((*(*(contenedor + calcular_cordenadaY(ficha)) + calcular_cordenadaX(ficha))).peones.propietario->representacion==blancas || (*(*(contenedor + calcular_cordenadaY(ficha)) + calcular_cordenadaX(ficha))).peones.estado==dama) {
                    if(calcular_cordenadaX(ficha)+1<=7 && calcular_cordenadaX(calcular_posicion(contador + 1))<=7 && calcular_cordenadaY(ficha)+1<=7 && calcular_cordenadaY(calcular_posicion(contador + 1))<=7){
                        if ((calcular_cordenadaX(ficha) + 1 == calcular_cordenadaX(calcular_posicion(contador + 1))) && (calcular_cordenadaY(ficha) + 1 == calcular_cordenadaY(calcular_posicion(contador + 1)))) { // ARREGLAR
                            if((calcular_cordenadaY(ficha)+2)<=7 && (calcular_cordenadaX(ficha)+2)<=7){
                                if ((*(*(contenedor + calcular_cordenadaY(ficha) + 2) + calcular_cordenadaX(ficha)+2)).estado == disponible) {
                                    return 1;
                                }
                            }
                        }
                    }
                    if(calcular_cordenadaX(ficha)-1>=0 && calcular_cordenadaX(calcular_posicion(contador + 1))<=7 && calcular_cordenadaY(ficha)+1<=7 && calcular_cordenadaY(calcular_posicion(contador + 1))<=7){
                        if ((calcular_cordenadaX(ficha)-1 == calcular_cordenadaX(calcular_posicion(contador + 1))) && (calcular_cordenadaY(ficha) + 1 == calcular_cordenadaY(calcular_posicion(contador + 1)))) {
                            if((calcular_cordenadaY(ficha)+2)<=7 && (calcular_cordenadaX(ficha)-2)>=0){
                                if ((*(*(contenedor + calcular_cordenadaY(ficha) + 2) + calcular_cordenadaX(ficha)-2)).estado == disponible) {
                                    return 1;
                                }
                            }
                        }
                    }
                }
                if((*(*(contenedor + calcular_cordenadaY(ficha)) + calcular_cordenadaX(ficha))).peones.propietario->representacion==negras || (*(*(contenedor + calcular_cordenadaY(ficha)) + calcular_cordenadaX(ficha))).peones.estado==dama) {
                    if(calcular_cordenadaX(ficha)-1>=0 && calcular_cordenadaX(calcular_posicion(contador + 1))<=7 && calcular_cordenadaY(ficha)-1>=0 && calcular_cordenadaY(calcular_posicion(contador + 1))<=7){
                        if((calcular_cordenadaX(ficha)-1 == calcular_cordenadaX(calcular_posicion(contador+1))) && (calcular_cordenadaY(ficha) - 1 == calcular_cordenadaY(calcular_posicion(contador+1)))){
                            if((calcular_cordenadaY(ficha)-2)>=0 && (calcular_cordenadaX(ficha)-2)>=0){
                                if((*(*(contenedor + calcular_cordenadaY(ficha)-2) + calcular_cordenadaX(ficha)-2)).estado==disponible){
                                    return 1;
                                }
                            }
                        }
                    }
                    if(calcular_cordenadaX(ficha)+1<=7 && calcular_cordenadaX(calcular_posicion(contador + 1))<=7 && calcular_cordenadaY(ficha)-1>=0 && calcular_cordenadaY(calcular_posicion(contador + 1))<=7){
                        if((calcular_cordenadaX(ficha)+1 == calcular_cordenadaX(calcular_posicion(contador+1))) && (calcular_cordenadaY(ficha)-1 == calcular_cordenadaY(calcular_posicion(contador+1)))){ // ARREGLAR
                            if((calcular_cordenadaY(ficha)-2)>=0 && (calcular_cordenadaX(ficha)+2)<=7){
                                if((*(*(contenedor + calcular_cordenadaY(ficha)-2) + calcular_cordenadaX(ficha)+2)).estado==disponible){
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
int parametros_eliminar(const tablero cont, const posiciones inicial, const posiciones final){
    const bloque **contenedor=cont.plano;
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



// PENDIENTE
int verificar_ahogado(const tablero tableroJuego, posiciones const inicial){
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