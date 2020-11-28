#ifndef PROYECTO_FINAL_HEADER_H
#define PROYECTO_FINAL_HEADER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int const COLUMNA = 8;
int const FILA = 8;
int const TOTAL_FICHAS = 12;

typedef enum {
    blanco,
    negro
} color;
typedef enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
}posiciones;
typedef enum {
    basica,
    dama,
}estado_peon;
typedef enum {
    curso,
    finalizado,
    interrumpido
} estado_juego;
typedef enum {
    disponible,
    bloqueado,
    casilla_blanca
} estado_bloque;
typedef struct {
    char nombre[50];
    int partidas_ganadas;
    int partidas_total;
    color representacion;
} jugador;
typedef struct{
    jugador *propietario;
    posiciones posicion;
    estado_peon estado;
}peon;
typedef struct {
    peon peones;
    estado_bloque estado;
    posiciones posicion;
}bloque;
typedef struct {
    jugador *jugadorA;
    int total_fichasA;

    jugador *jugadorB;
    int total_fichasB;

    estado_juego estado;

    bloque **plano; // MATRIS 8*8 DE TODAS LAS FICHAS
} tablero;


// JUGADOR
jugador creacion_jugador(int x);
void creacion_jugadores(jugador*, jugador*);
void actualizacion_jugador(jugador *jugador, int);
void actualizacion_jugadores(jugador*, jugador*, int);
void estadisticas(jugador*, jugador*);
void inicio();
void menu(jugador*, jugador*);
int juego(jugador*, jugador*, tablero*);
void imprimir_color(color);

//MANEJO DE ERRORES
int verificar_char_to_int (char frase[]);
int captura_int(int limiteA, int limiteB);
int char_to_int (char[]);

// TABLERO Y PIEZAS
int posiciones_inciciales(int);
int posiciones_jugables(int);
posiciones calcular_posicion(int);
int calcular_cordenadaX(posiciones);
int calcular_cordenadaY(posiciones);
tablero generar_tablero(jugador*, jugador*);
peon creacion_peon(jugador*, int);
bloque creacion_bloque(jugador*, int);
void imprimir_bloque(bloque);
void imprimir_tablero(tablero);

int verificar_movimiento(tablero, posiciones, posiciones);


#endif
