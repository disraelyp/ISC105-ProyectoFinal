#include "header.h"

int cambio_posicion(tablero *cont, jugador *a, posiciones inicial, posiciones final){
    bloque **contenedor=cont->plano;
    int xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial), xFinal=calcular_cordenadaX(final), yFinal=calcular_cordenadaY(final);
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
int verificar_movimiento(tablero tableroJuego, posiciones inicial, posiciones final){
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
int verificar_posiciones(tablero *cont, jugador *a, char *movimiento){
    if (verificar_frase(movimiento)){
        char posicion_inicial[3]={*(movimiento+1), *(movimiento+2), '\0'}, posicion_final[3]={*(movimiento+4), *(movimiento+5), '\0'};
        posiciones inicial =posiciones_char(posicion_inicial), final =posiciones_char(posicion_final);
        if(posiciones_jugables(inicial) && posiciones_jugables(final)){
            if(verificar_movimiento(*(cont), inicial, final)){
                if(verificar_propietario(*(cont), a, inicial)){
                    cambio_posicion(cont, a, inicial, final);
                    return 1;
                } else{
                    printf("\n\tERORR: LA FICHA A MOVER, LE PERTENECE A OTRO JUGADOR.\n");
                }

            } else{
                printf("\n\tERORR: EL MOVIMIENTO ES INVALIDO.\n");
            }
        } else {
            printf("\n\tERORR: LAS POSICIONES INGRESADAS NO SON VALIDAS.\n");
        }
    } else {
        printf("\n\tERORR: LA ENTRADA ES INVALIDAD, VERIFIQUE EL FORMATO ALGEBRAICO.\n");
    }
    return 0;
}
int verificar_propietario(tablero tableroJuego, jugador *pJugador, posiciones ubicacion){
    bloque **pPlano=tableroJuego.plano;
    int x=calcular_cordenadaX(ubicacion), y=calcular_cordenadaY(ubicacion);
    if((*(*(pPlano + y) + x)).peones.propietario == pJugador){
        return 1;
    }
    return 0;
}
int verificar_ahogado(tablero tableroJuego, posiciones inicial){
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
int contar_fichas(tablero cont, jugador *a){
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