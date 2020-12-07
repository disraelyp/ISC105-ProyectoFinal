#ifndef PROYECTO_FINAL_HEADER_H
#define PROYECTO_FINAL_HEADER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int const COLUMNA = 8;
int const FILA = 8;

typedef enum {
    blancas,
    negras
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
    disponible,
    bloqueado,
    casilla_blanca
} estado_bloque;

typedef struct {
    char nombre[50];
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

    jugador *jugadorB; //
    int total_fichasB;

    bloque **plano; // MATRIS 8*8 DE TODAS LAS FICHAS
} tablero;



typedef struct {
    int id_juego; // NUMERO DE PARTIDA
    char nombreA[50];
    color colorA;
    char nombreB[50];
    int inicial;
    int final;
} notacion_algebraica;

typedef struct {
    int id_jugador; // NUMERO DE PARTIDA
    char nombre[50];
    int total_victorias;
    int total_derrotas;
} record_partidas;



void agregar_notacion(const char *nombre_archivo, int const id, jugador *a, jugador *b, posiciones inicial, posiciones final);
void lista_notaciones(char *nombre_archivo);
int nuevo_id(char *nombre_archivo);
int cantidad_id(char *nombre_archivo);
void leer_archivo(char *nombre_archivo, int id);
void escribir_archivo(char *nombre_archivo, const notacion_algebraica notacion);
int cantidad_notaciones(char *nombre);
FILE* abrir_archivo(char *nombre_archivo, char *funcion);
void cerrar_archivo(FILE *nombre_archivo);
int verificar_archivo(char *nombre_archivo);

int cantidad_registros(char *nombre);
void modificar_registros(char *nombre_archivo, record_partidas cont, int posicion);
void escribir_registro(char *nombre_archivo, record_partidas cont);
void recorrer_registro(char *nombre_archivo, record_partidas cont);
void agregar_registro(char *nombre_archivo, jugador *a, int victorias, int derrotas);

void leer_registro(char *nombre_archivo);





// FUNCIONES - JUGADOR.C
jugador captura_jugador(const int);
void creacion_jugadores (jugador*, jugador*);
int verificar_char_int (const char*);
int captura_int(const int, const int);
int char_int (const char*);
int verifica_entrada(const char*);
int contar_fichas(const tablero, const jugador*);
int verificar_propietario(const tablero, const jugador*, const posiciones);
void turno_movimiento(tablero *, jugador *, jugador*, char*, const int, const char*);
int turno(tablero*, jugador*, jugador*, const int, char*, const int, const char*);

// FUNCIONES - TABLERO.C
posiciones extraer_posiciones(const char*);
int posiciones_jugables(const posiciones);
int posiciones_diagonales(const posiciones, const posiciones);
posiciones posicion_intermedia(const posiciones, const posiciones);
posiciones calcular_posicion(const int);
int ubicaciones_externas(const posiciones);
int ubicaciones_iniciales(const int);
int ubicaciones_jugables(const int);
int calcular_ubicacion(const posiciones);
int calcular_cordenadaX(const posiciones);
int calcular_cordenadaY(const posiciones);
void imprimir_bloque(const bloque);
void imprimir_tablero(const tablero);
void imprimir_color(const color);
void imprimir_representacion(const color);
void imprimir_posiciones(const posiciones);

//FUNCIONES - JUEGO.C
tablero generar_tablero(const jugador*, const jugador*);
peon creacion_peon(const jugador*, const int, const int);
bloque creacion_bloque(const jugador*, const int, const int);
void cambio_posicion(tablero*, const jugador*, const jugador*, const posiciones, const posiciones, const char*, const int, const char*);
void eliminar_posicion(tablero*, const jugador*, const jugador*, const posiciones, const posiciones, const char*, const int, const char*);
int verificar_posiciones(const tablero, const posiciones, const posiciones);
int verificar_movimiento(tablero*, jugador*, jugador*, const char*, const char*, int const id, const char *nombre_registro);
void reajustar_tablero(tablero*);
int recorrer_tablero(const tablero, const jugador*, const jugador*);
int verificar_eliminar(const bloque**, const jugador*, const posiciones);
int parametros_eliminar(const tablero, const posiciones, const posiciones);
int verificar_ahogado(const tablero, posiciones const);










#endif
