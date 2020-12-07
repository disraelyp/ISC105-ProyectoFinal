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
    jugador *jugadorB;
    int total_fichasB;
    bloque **plano;
} tablero;
typedef struct {
    int id_juego;
    char nombreA[50];
    color colorA;
    char nombreB[50];
    int inicial;
    int final;
} notacion_algebraica;
typedef struct {
    int id_jugador;
    char nombre[50];
    int total_victorias;
    int total_derrotas;
} record_partidas;

// FUNCIONES 'ARCHIVOS.C'
void agregar_notacion(const char*, int const id, jugador*, jugador*, posiciones, posiciones); // CREA UNA ESTRUCTURA DE TIPO NOTACION Y LA AGREGA
void lista_notaciones(const char*); // PRESENTA UNA LISTA DE NOTACIONES
int nuevo_id(const char*); // CREA UN NUEVO ID
int cantidad_id(const char*); // CUENTA LA CANTIDAD DE ID EN UN ARCHIVO
void lista_records(const char*, int id); // PRESENTA UNA LISTA DE RECORD DE JUGADORES
void agregar_record(const char*, notacion_algebraica); // AGREGA UN REGISTRO EN EL ARCHIVO DE RECORDS
int cantidad_notaciones(const char*); // CANTIDAD DE NOTACIONES
FILE* abrir_archivo(const char*, char *funcion); // ABRIR UN ARCHIVO
void cerrar_archivo(FILE*); // CERRAR UN ARCHIVO
int verificar_archivo(const char*); // VERIFICAR SI UN ARCHIVO EXISTE
int cantidad_registros(const char*); // CANTIDAD DE RECORDS
void modificar_registros(const char*, record_partidas, int posicion); // ACTUALIZA UN RECORD
void escribir_registro(const char*, record_partidas); // CREA UNA ESTRUCTURA DE TIPO RECORDS
void recorrer_registro(const char*, record_partidas); // RECORRE EL ARCHIVO DE RECORDS
void agregar_registro(const char*, jugador*, int, int); // AGREGA UN REGISTRO EN EL ARCHIVO DE NOTACIONES
int funcion_ordenamiento(const void*, const void*); // FUNCION DE ORDENAMIENTO PARA EL QSORT
void leer_registro(const char*); // IMPRIME LA LISTA DE RECORD

//ARCHIVO 'JUGADOR.C'
jugador captura_jugador(const int); // CREA UNA ESTRUCTURA TIPO JUGADOR
void creacion_jugadores (jugador*, jugador *); // CREA DOS ESTRUCTURAS TIPO JUGADOR CON DISTINTO COLOR
int verificar_char_int (const char*); // VERIFICA SI UN CHAR PUEDE CONVERTIRSE A UN INT
int captura_int(const int, const int); // CAPTURA UN VALOR TIPO INT
int captura_charSN(); // CAPTURA UNA RESPUESTA TIPO CHAR
int char_int (const char*); // CONVIERTE UN ELEMENTO TIPO CHAR A TIPO INT
int verifica_entrada(const char*); // VERIFICIA LA ENTRADA DE NOTACIONES ALGEBRAICA
int contar_fichas(const tablero, const jugador*); // CUENTA LAS FICHAS DE UN JUGADOR
int verificar_propietario(const tablero, const jugador*, const posiciones); // VERIFICA EL PROPETARIO DE UNA FICHA
int turno(tablero*, jugador*, jugador*, const int, char*, const int, const char*); // TURNO DE UN JUGADOR
void turno_movimiento(tablero*, jugador*, jugador*, char*, const int, const char*); // MOVIMIENTO DE UNA FICHA
void nueva_partida(const char*, const char*); // NUEVA PARTIDA

//ARCHIVO 'juego.c'
tablero generar_tablero(const jugador*, const jugador*); // GENERA UNA ESTRUCTURA DE TIPO TABLERO
peon creacion_peon(const jugador*, const int, const int); // GENERA UNA ESTRUCTURA DE TIPO PEON
bloque creacion_bloque(const jugador*, const int, const int); // GENERA UNA ESTRUCTURA DE TIPO BLOQUE
void cambio_posicion(tablero*, const jugador*, const jugador*, const posiciones, const posiciones, const char*, int const, const char*); // CAMBIA DE POSICION DOS FICHAS
void eliminar_posicion(tablero*, const jugador*, const jugador*, const posiciones, const posiciones, const char*, int const, const char*); // CAMBIA DE POSCION DOS FICHAS Y ELIMINA UNA
int verificar_posiciones(const tablero, const posiciones, const posiciones); // VERIFICA SI DOS POSICIONES SON ACCESIBLES POR UNA FICHA
int verificar_movimiento(tablero*, jugador*, jugador*, const char*, const char*, const int, const char*); // VERIFICA SI EL MOVIMIENTO ES VALIDO
void reajustar_tablero(tablero*); // REAJUSTA EL TABLERO Y LAS ESTADISTICAS
int recorrer_tablero(const tablero, const jugador*, const jugador*); // RECORRE TODAS LAS FICHAS DEL TABLERO
int verificar_eliminar(const bloque**, const jugador*, const posiciones); // VERIFICA SI SE PUEDE ELIMINAR UNA FICHA
int parametros_eliminar(const tablero, const posiciones, const posiciones); // VERIFICA SI UNA ELIMINACION CUMPLE TODOS LOS PARAMETROS ANTES DE REALIZARLA
int verificar_ahogado(const tablero); // VERIFICA SI HAY MOVIMIENTOS DISPONIBLES PARA LS FICHAS

//ARCHIVO 'tablero.c'
posiciones extraer_posiciones(const char*); // EXTRAE LAS POSICIONES UNA CADENA DE TEXTO
void imprimir_posiciones(const posiciones); // IMPRIME POSCICIONES
int posiciones_jugables(const posiciones); // CALCULA SI UNA POSICION ES JUGABLE
int posiciones_diagonales(const posiciones, const posiciones); // CALCULA SI DOS POSICIONES ESTAN EN UNA DIAGONAL
posiciones posicion_intermedia(const posiciones, const posiciones); // CALCULA LA POSICION INTERMEDIA DE DOS FICHAS
posiciones calcular_posicion(const int); // CALCULA LA POSCION EXACTA DE UNA UBICACION
int ubicaciones_externas(const posiciones); // CALCULA SI UNA POSCICION ES UNA UBICACION EXTERNA
int ubicaciones_iniciales(const int); // CALCULA SI UNA POSCICION ES UNA UBICACION INICIAL
int ubicaciones_jugables(const int); // CALCULA SI UNA POSCICION ES UNA UBICACION JUGABLE
int calcular_ubicacion(const posiciones); // CALCULA UNA UBICACION
int calcular_cordenadaX(const posiciones); //CALCULA LAS CORDENADAS DE UNA POSICION
int calcular_cordenadaY(const posiciones);//CALCULA LAS CORDENADAS DE UNA POSICION
void imprimir_bloque(const bloque); // IMPRIME UN BLOQUE
void imprimir_tablero(const tablero); // IMPRIME EL TABLERO
void imprimir_color(const color); // IMPRIME EL COLOR
void imprimir_representacion(const color); // IMPRIME LA PRIMERA LETRA DE UNA REPRESENTACION



#endif
