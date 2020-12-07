#include "header.h"

posiciones extraer_posiciones(const char *posicion) {
    posiciones lista_enum[64] = {a8, b8, c8, d8, e8, f8, g8, h8, a7, b7, c7, d7, e7, f7, g7, h7, a6, b6, c6, d6, e6, f6, g6, h6, a5, b5, c5, d5, e5, f5, g5, h5, a4, b4, c4, d4, e4, f4, g4, h4, a3, b3, c3, d3, e3, f3, g3, h3, a2, b2, c2, d2, e2, f2, g2, h2, a1, b1, c1, d1, e1, f1, g1, h1};
    char lista_char[][64] = {"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"};
    int i;
    for (i = 0; strcmp(lista_char[i], posicion); i++);
    return lista_enum[i];
}
void imprimir_posiciones(const posiciones posicion) {
    posiciones lista_enum[64] = {a8, b8, c8, d8, e8, f8, g8, h8, a7, b7, c7, d7, e7, f7, g7, h7, a6, b6, c6, d6, e6, f6, g6, h6, a5, b5, c5, d5, e5, f5, g5, h5, a4, b4, c4, d4, e4, f4, g4, h4, a3, b3, c3, d3, e3, f3, g3, h3, a2, b2, c2, d2, e2, f2, g2, h2, a1, b1, c1, d1, e1, f1, g1, h1};
    char lista_char[][64] = {"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"};
    for(int i=0; i<64; i++){
        if (posicion==lista_enum[i]){
            printf("%s", lista_char[i]);
        }
    }
}
int posiciones_jugables(const posiciones posicion){
    posiciones const lista[32]={b8, d8, f8, h8, b6, d6, f6, h6, b4, d4, f4, h4, b2, d2, f2, h2, a7, c7, e7, g7, a5, c5, e5, g5, a3, c3, e3, g3, a1, c1, e1, g1};
    for(int i=0; i<32; i++){
        if (posicion==lista[i]){
            return 1;
        }
    }
    return 0;
}
int posiciones_diagonales(const posiciones inicial, const posiciones final){
    int const xInicial=calcular_cordenadaX(inicial), yInicial=calcular_cordenadaY(inicial), xFinal=calcular_cordenadaX(final), yFinal=calcular_cordenadaY(final);
    if((xInicial-2==xFinal && yInicial-2==yFinal)||(xInicial-2==xFinal && yInicial+2==yFinal)||(xInicial+2==xFinal && yInicial-2==yFinal)||(xInicial+2==xFinal && yInicial+2==yFinal)){
        return 1;
    }
    return 0;
}
posiciones posicion_intermedia(const posiciones inicial, const posiciones final){
    int inicial_cordenada= calcular_ubicacion(inicial), final_cordenada= calcular_ubicacion(final);
    return calcular_posicion((final_cordenada+inicial_cordenada)/2);
}
posiciones calcular_posicion(const int posicion){
    posiciones lista[64]={a8, b8, c8, d8, e8, f8, g8, h8, a7, b7, c7, d7, e7, f7, g7, h7, a6, b6, c6, d6, e6, f6, g6, h6, a5, b5, c5, d5, e5, f5, g5, h5, a4, b4, c4, d4, e4, f4, g4, h4, a3, b3, c3, d3, e3, f3, g3, h3, a2, b2, c2, d2, e2, f2, g2, h2, a1, b1, c1, d1, e1, f1, g1, h1};
    return lista[posicion-1];
}
int ubicaciones_externas(const posiciones posicion){
    posiciones lista[16] ={a8, b8, c8, d8, e8, f8, g8, h8, a1, b1, c1, d1, e1, f1, g1, h1};
    for (int i=0; i<16; i++){
        if(posicion==(lista[i])){
            return 1;
        }
    }
    return 0;
}
int ubicaciones_iniciales(const int posicion){
    posiciones const contenedor = calcular_posicion(posicion);
    posiciones lista[24]={a7, c7, e7, g7, a3, c3, e3, g3, a1, c1, e1, g1, b8, d8, f8, h8, b6, d6, f6, h6, b2, d2, f2, h2};
    for(int i=0; i<24; i++){
        if (contenedor==lista[i]){
            return 1;
        }
    }
    return 0;
}
int ubicaciones_jugables(const int posicion){
    posiciones const contenedor = calcular_posicion(posicion);
    posiciones lista[32]={b8, d8, f8, h8, b6, d6, f6, h6, b4, d4, f4, h4, b2, d2, f2, h2, a7, c7, e7, g7, a5, c5, e5, g5, a3, c3, e3, g3, a1, c1, e1, g1};
    for(int i=0; i<32; i++){
        if (contenedor==lista[i]){
            return 1;
        }
    }
    return 0;
}
int calcular_ubicacion(const posiciones posicion){
    posiciones lista[64]={a8, b8, c8, d8, e8, f8, g8, h8, a7, b7, c7, d7, e7, f7, g7, h7, a6, b6, c6, d6, e6, f6, g6, h6, a5, b5, c5, d5, e5, f5, g5, h5, a4, b4, c4, d4, e4, f4, g4, h4, a3, b3, c3, d3, e3, f3, g3, h3, a2, b2, c2, d2, e2, f2, g2, h2, a1, b1, c1, d1, e1, f1, g1, h1};
    for(int i=0; i<64; i++){
        if(lista[i]==posicion){
            return i+1;
        }
    }
}
int calcular_cordenadaX(const posiciones posicion){
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
int calcular_cordenadaY(const posiciones posicion){
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
void imprimir_bloque(const bloque cont){
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
void imprimir_tablero(const tablero cont){
    bloque **contenedor=cont.plano;
    printf("\n\n\t   ");
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
        if(8-i==8){
            printf("\tFichas BLANCAS: %d", contar_fichas(cont, cont.jugadorB));
        }
        if(8-i==7){
            printf("\tFichas NEGRAS: %d", contar_fichas(cont, cont.jugadorA));
        }
        printf("\n");
    }
    printf("\n\t   ");
    for(int h=0; h<FILA; ++h){
        printf("  %c", h+65);
    }
    printf("\n");
}
void imprimir_color(const color representacion){
    if (representacion == blancas){
        printf("BLANCAS");
    } else {
        printf("NEGRAS");
    };
}
void imprimir_representacion(const color representacion){
    if (representacion == blancas){
        printf("b");
    } else {
        printf("n");
    };
}


