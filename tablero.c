#include "header.h"

int posiciones_inciciales(int posicion){
    posiciones contenedor = calcular_posicion(posicion);
    posiciones lista[24]={a7, c7, e7, g7, a3, c3, e3, g3, a1, c1, e1, g1, b8, d8, f8, h8, b6, d6, f6, h6, b2, d2, f2, h2};
    for(int i=0; i<24; i++){
        if (contenedor==lista[i]){
            return 1;
        }
    }
    return 0;
}

int posiciones_jugables(int posicion){
    posiciones contenedor = calcular_posicion(posicion);
    posiciones lista[32]={b8, d8, f8, h8, b6, d6, f6, h6, b4, d4, f4, h4, b2, d2, f2, h2, a7, c7, e7, g7, a5, c5, e5, g5, a3, c3, e3, g3, a1, c1, e1, g1};
    for(int i=0; i<32; i++){
        if (contenedor==lista[i]){
            return 1;
        }
    }
    return 0;
}

posiciones calcular_posicion(int posicion){
    posiciones lista[64]={a8, b8, c8, d8, e8, f8, g8, h8, a7, b7, c7, d7, e7, f7, g7, h7, a6, b6, c6, d6, e6, f6, g6, h6, a5, b5, c5, d5, e5, f5, g5, h5, a4, b4, c4, d4, e4, f4, g4, h4, a3, b3, c3, d3, e3, f3, g3, h3, a2, b2, c2, d2, e2, f2, g2, h2, a1, b1, c1, d1, e1, f1, g1, h1};
    return lista[posicion-1];
}

int calcular_cordenadaX(posiciones posicion){
    posiciones lista[64]={a8, b8, c8, d8, e8, f8, g8, h8, a7, b7, c7, d7, e7, f7, g7, h7, a6, b6, c6, d6, e6, f6, g6, h6, a5, b5, c5, d5, e5, f5, g5, h5, a4, b4, c4, d4, e4, f4, g4, h4, a3, b3, c3, d3, e3, f3, g3, h3, a2, b2, c2, d2, e2, f2, g2, h2, a1, b1, c1, d1, e1, f1, g1, h1};
    for(int i=0; i<64; i++){
        if (posicion==lista[i]){
            while (i>=8){
                i-=8;
            }
            return i;
        }
    }
}

int calcular_cordenadaY(posiciones posicion){
    posiciones lista[64]={a8, b8, c8, d8, e8, f8, g8, h8, a7, b7, c7, d7, e7, f7, g7, h7, a6, b6, c6, d6, e6, f6, g6, h6, a5, b5, c5, d5, e5, f5, g5, h5, a4, b4, c4, d4, e4, f4, g4, h4, a3, b3, c3, d3, e3, f3, g3, h3, a2, b2, c2, d2, e2, f2, g2, h2, a1, b1, c1, d1, e1, f1, g1, h1};
    for(int i=0; i<64; i++){
        if (posicion==lista[i]){
            int cont=0;
            while (i>=8){
                i-=8;
                cont++;
            }
            return cont;
        }
    }
}

tablero generar_tablero(jugador *a, jugador *b) {
    bloque ejemplo=creacion_bloque(NULL, 1);
    bloque **bloques = (bloque **) malloc(8 * sizeof(ejemplo));
    for (int i = 0; i<FILA; ++i) {
        *(bloques+i) = (bloque *) malloc(8* sizeof(ejemplo));
    }
    int posicion=1;
    for (int i = 0; i < COLUMNA; i++) {
        for (int j = 0; j < FILA; j++) {
            if (posiciones_inciciales(posicion) && posicion < (FILA * COLUMNA) / 2){
                if(b->representacion==blanco){
                    *(*(bloques+i)+j)= creacion_bloque(b, posicion);
                } else {
                    *(*(bloques+i)+j)= creacion_bloque(a, posicion);
                }
            } else {
                if (posiciones_inciciales(posicion) && posicion > (FILA * COLUMNA) / 2){
                    if(b->representacion!=blanco){
                        *(*(bloques+i)+j)= creacion_bloque(b, posicion);
                    } else {
                        *(*(bloques+i)+j)= creacion_bloque(a, posicion);
                    }
                } else {
                    *(*(bloques+i)+j)= creacion_bloque(NULL, posicion);
                }
            }
            posicion++;
        }
    }
    tablero contenedor={a, 12, b, 12, curso, bloques};
    return contenedor;
}

peon creacion_peon(jugador *contA, int contC){
    peon contenedor;
    contenedor.propietario=contA;
    contenedor.posicion=calcular_posicion(contC);
    contenedor.estado=basica;
    return contenedor;
}

bloque creacion_bloque(jugador *jugador, int contB){
    bloque contenedor;
    if (posiciones_jugables(contB)){
        if(jugador==NULL){
            contenedor.estado=disponible;
        } else {
            contenedor.estado=bloqueado;
            contenedor.peones=creacion_peon(jugador, contB);
        }
        contenedor.posicion=calcular_posicion(contB);
    } else {
        contenedor.estado=casilla_blanca;
        contenedor.posicion=calcular_posicion(contB);
    }
    return contenedor;
}

void imprimir_bloque(bloque cont){
    if(cont.estado==casilla_blanca){
        printf("  .");
    } else {
        if (cont.estado==disponible){
            printf("  *");
        } else {
            if(cont.peones.propietario->representacion==blanco){
                printf("  b");
            } else {
                printf("  n");
            }
        }
    }

}

void imprimir_tablero(tablero cont){
    bloque **contenedor=cont.plano;
    printf("\n\t   ");
    for(int h=0; h<COLUMNA; ++h){
        printf("  %c", h+65);
    }
    printf("\n\n");
    for (int i = 0; i < COLUMNA; ++i) {
        printf("\t%d  ", 8-i);
        for (int j = 0; j < FILA; ++j) {
            imprimir_bloque(*(*(contenedor+i)+j));
        }
        printf("    %d", 8-i);
        printf("\n");
    }
    printf("\n\t   ");
    for(int h=0; h<COLUMNA; ++h){
        printf("  %c", h+65);
    }
}

int verificar_movimiento(tablero cont, posiciones inicial, posiciones final){
    bloque **contenedor=cont.plano;
    int xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial);
    int xFinal=calcular_cordenadaX(final), yFinal=calcular_cordenadaY(final);

    if((*(*(contenedor + yInicial) + xInicial)).peones.propietario->representacion == blanco && (*(*(contenedor + yInicial) + xInicial)).estado != casilla_blanca){
        if ((yInicial+1)==yFinal && (xInicial-1)==xFinal && (*(*(contenedor+(yInicial + 1)) + (xInicial - 1))).estado == disponible && xInicial >= 0 && yInicial <= 7){
            return 1;
        }
        if ((yInicial+1)==yFinal && (xInicial+1)==xFinal && (*(*(contenedor+(yInicial + 1)) + (xInicial + 1))).estado == disponible && xInicial <= 7 && yInicial <= 7){
            return 1;
        }
    }

    if((*(*(contenedor + yInicial) + xInicial)).peones.propietario->representacion == negro && (*(*(contenedor + yInicial) + xInicial)).estado != casilla_blanca){
        if ((yInicial-1)==yFinal && (xInicial-1)==xFinal && (*(*(contenedor+(yInicial - 1)) + (xInicial - 1))).estado == disponible && xInicial >= 0 && yInicial <= 7){
            return 1;
        }
        if ((yInicial-1)==yFinal && (xInicial+1)==xFinal && (*(*(contenedor+(yInicial - 1)) + (xInicial + 1))).estado == disponible && xInicial <= 7 && yInicial >= 0){
            return 1;
        }
    }
    return 0;
}


int verificar_ahogado(tablero cont, posiciones inicial, posiciones final){
    bloque **contenedor=cont.plano;
    int xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial);
    int xFinal=calcular_cordenadaX(final), yFinal=calcular_cordenadaY(final);

    if((*(*(contenedor + yInicial) + xInicial)).peones.propietario->representacion == blanco && (*(*(contenedor + yInicial) + xInicial)).estado != casilla_blanca){
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
    if((*(*(contenedor + yInicial) + xInicial)).peones.propietario->representacion == negro && (*(*(contenedor + yInicial) + xInicial)).estado != casilla_blanca){
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