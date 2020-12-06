#include "header.h"

FILE* abrir_archivo(char *nombre, char *modo);
void cerrar_archivo(FILE *archivo);
void escribir_archivo(char *nombre_archivo, int id, jugador *a, jugador *b, posiciones inicial, posiciones final, estado_bloque estado);
void leer_archivo(char*, int);
int cantidad_notaciones(char*);

int nuevo_id(char *nombre_archivo){
    int cantidad_estudiante = cantidad_notaciones(nombre_archivo);
    int cantidad_leida = 0;
    FILE *archivo = abrir_archivo(nombre_archivo, "rb");
    while (cantidad_leida<cantidad_estudiante){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        if(cantidad_leida<cantidad_estudiante){
            cerrar_archivo(archivo);
            if(tmp.contenedor==finalizado){
                return tmp.id_juego+1;
            }
        }
        cantidad_leida++;
    }
}
void leer_archivo(char *nombre_archivo, int id){
    int cantidad_estudiante = cantidad_notaciones(nombre_archivo);
    int cantidad_leida = 0;
    FILE *archivo = abrir_archivo(nombre_archivo, "rb");
    //
    while (cantidad_leida<cantidad_estudiante){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        if(tmp.id_juego==id){
            imprimir_representacion(tmp.a->representacion);
            imprimir_posiciones(tmp.inicial);
            printf(" ");
            imprimir_posiciones(tmp.final);
            printf("\n");
            cantidad_leida++;
        }
    }
    cerrar_archivo(archivo);
}
void escribir_archivo(char *nombre_archivo, int id, jugador *a, jugador *b, posiciones inicial, posiciones final, estado_bloque estado){
    FILE *archivo = abrir_archivo(nombre_archivo, "a+b");
    notacion_algebraica tmp = {id, a, b, inicial, final, estado};
    fwrite(&tmp, sizeof(notacion_algebraica), 1, archivo);
    cerrar_archivo(archivo);
}
int cantidad_notaciones(char *nombre){
    FILE *archivo = abrir_archivo(nombre, "rb");
    fseek(archivo, 0L, SEEK_END);
    int cantidad_estudiantes = ftell(archivo) / sizeof(notacion_algebraica);
    cerrar_archivo(archivo);
    return cantidad_estudiantes;
}
FILE* abrir_archivo(char *nombre_archivo, char *funcion){
    FILE *archivo = fopen(nombre_archivo, funcion);
    if(archivo == NULL){
        printf("\n\n\tERROR CRITICO: EL ARCHIVO NO FUE ABIERTO O ENCONTRADO CORRECTAMENTE\n");
        exit(-1);
    }
    return archivo;
}
void cerrar_archivo(FILE *nombre_archivo){
    int archivo = fclose(nombre_archivo);
    if (archivo != 0){
        printf("\n\tERROR CRITICO: EL ARCHIVO NO FUE CERRADO CORRECTAMENTE\t");
    }
}

