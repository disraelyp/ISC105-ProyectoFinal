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

typedef struct {
    jugador *a;
    jugador *b;
    int numJugada;
    posiciones inicial;
    posiciones final;
    int estado_juego;
} notacion_algebraica;


// TABLERO

int posiciones_jugables(posiciones);
posiciones calcular_posicion(int);
int cordenadas_iniciales(int);
int cordenadas_jugables(int);
int calcular_cordenada(posiciones);
int calcular_cordenadaX(posiciones);
int calcular_cordenadaY(posiciones);
tablero generar_tablero(jugador*, jugador*);
peon creacion_peon(jugador*, int, int);
bloque creacion_bloque(jugador*, int, int);
void imprimir_bloque(bloque);
void imprimir_tablero(tablero);


// JUEGO
int cambio_posicion(tablero*, jugador*, posiciones, posiciones);
int verificar_movimiento(tablero, posiciones, posiciones);
int verificar_posiciones(tablero*, jugador*, char *movimiento);
int verificar_propietario(tablero cont, jugador*, posiciones);


// JUGADOR
jugador creacion_jugador(int);  //  CREA UNA ESTRUCTURA TIPO JUGADOR
void creacion_jugadores (jugador*, jugador*);  //  CREA DOS ESTRUCTURAS TIPO JUGADOR CON DISTINTA REPRESENTACION
void imprimir_color(color); // IMPRIME EL COLOR
void nueva_partida();
int verificar_char_to_int (char*);
int captura_int(int, int);
int char_to_int (char*);
int verificar_frase(char*);
posiciones posiciones_char(char*);

#endif
