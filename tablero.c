#include "header.h"


int posiciones_jugables(posiciones posicion){
    posiciones lista[32]={b8, d8, f8, h8, b6, d6, f6, h6, b4, d4, f4, h4, b2, d2, f2, h2, a7, c7, e7, g7, a5, c5, e5, g5, a3, c3, e3, g3, a1, c1, e1, g1};
    for(int i=0; i<32; i++){
        if (posicion==lista[i]){
            return 1;
        }
    }
    return 0;
}
posiciones calcular_posicion(int posicion){
    posiciones lista[64]={a8, b8, c8, d8, e8, f8, g8, h8, a7, b7, c7, d7, e7, f7, g7, h7, a6, b6, c6, d6, e6, f6, g6, h6, a5, b5, c5, d5, e5, f5, g5, h5, a4, b4, c4, d4, e4, f4, g4, h4, a3, b3, c3, d3, e3, f3, g3, h3, a2, b2, c2, d2, e2, f2, g2, h2, a1, b1, c1, d1, e1, f1, g1, h1};
    return lista[posicion-1];
}
int cordenadas_externas(posiciones posicion){
    posiciones lista[16] ={a8, b8, c8, d8, e8, f8, g8, h8, a1, b1, c1, d1, e1, f1, g1, h1};
    for (int i=0; i<16; i++){
        if(posicion==(*(lista+i))){
            return 1;
        }
    }
    return 0;
}
int cordenadas_iniciales(int posicion){
    posiciones contenedor = calcular_posicion(posicion);
    posiciones *lista[24]={a7, c7, e7, g7, a3, c3, e3, g3, a1, c1, e1, g1, b8, d8, f8, h8, b6, d6, f6, h6, b2, d2, f2, h2};
    for(int i=0; i<24; i++){
        if (contenedor==*(lista+i)){
            return 1;
        }
    }
    return 0;
}
int cordenadas_jugables(int posicion){
    posiciones contenedor = calcular_posicion(posicion);
    posiciones lista[32]={b8, d8, f8, h8, b6, d6, f6, h6, b4, d4, f4, h4, b2, d2, f2, h2, a7, c7, e7, g7, a5, c5, e5, g5, a3, c3, e3, g3, a1, c1, e1, g1};
    for(int i=0; i<32; i++){
        if (contenedor==lista[i]){
            return 1;
        }
    }
    return 0;
}
int calcular_cordenada(posiciones posicion){
    posiciones lista[64]={a8, b8, c8, d8, e8, f8, g8, h8, a7, b7, c7, d7, e7, f7, g7, h7, a6, b6, c6, d6, e6, f6, g6, h6, a5, b5, c5, d5, e5, f5, g5, h5, a4, b4, c4, d4, e4, f4, g4, h4, a3, b3, c3, d3, e3, f3, g3, h3, a2, b2, c2, d2, e2, f2, g2, h2, a1, b1, c1, d1, e1, f1, g1, h1};
    for(int i; i<64; i++){
        if(lista[i]==posicion){
            return i+1;
        }
    }
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
tablero generar_tablero(jugador *jugadorA, jugador *jugadorB) {
    bloque **bloques = (bloque **) malloc(8 * sizeof(bloque));
    for (int i = 0; i<FILA; ++i) {
        *(bloques+i) = (bloque *) malloc(8* sizeof(bloque));
    }
    int posicion=1, contador=0;
    for (int i = 0; i < COLUMNA; i++) {
        for (int j = 0; j < FILA; j++) {
            if (cordenadas_iniciales(posicion) && posicion < (FILA * COLUMNA) / 2){
                contador++;
                if(contador==11){
                    if(jugadorB->representacion == blancas){
                        *(*(bloques+i)+j)= creacion_bloque(jugadorB, posicion, 1);
                    } else {
                        *(*(bloques+i)+j)= creacion_bloque(jugadorA, posicion, 1);
                    }
                } else{
                    *(*(bloques+i)+j)= creacion_bloque(NULL, posicion, 1);
                }

            } else {
                if (cordenadas_iniciales(posicion) && posicion > (FILA * COLUMNA) / 2){
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
    tablero contenedor={jugadorA, 12, jugadorB, 12, curso, bloques};
    return contenedor;
}
peon creacion_peon(jugador *jugadorA, int posicion, int estado){
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

bloque creacion_bloque(jugador *jugador, int contB, int estado){
    bloque contenedor;
    if (cordenadas_jugables(contB)){
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
void imprimir_bloque(bloque cont){
    if(cont.estado==casilla_blanca){
        printf("  .");
    } else {
        if (cont.estado==disponible){
            printf("  *");
        } else {
            if(cont.peones.propietario->representacion == blancas){
                if (cont.peones.estado==basica){
                    printf("  b");
                } else{
                    printf("  B");
                }
            } else {
                if (cont.peones.estado==basica){
                    printf("  n");
                } else{
                    printf("  N");;
                }
            }
        }
    }
}
void imprimir_tablero(tablero cont){
    bloque **contenedor=cont.plano;
    printf("\n\t   ");
    for(int h=0; h<FILA; ++h){
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
    for(int h=0; h<FILA; ++h){
        printf("  %c", h+65);
    }
    printf("\n");
}