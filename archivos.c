#include "header.h"

void imprimir_datos(const jugador *cont){
    printf("%s", cont->nombre);
}
void lista_notaciones(char *nombre_archivo){
    if(!verificar_archivo(nombre_archivo)){
        printf("\n\n\t NO TIENES TODAVIA NINGUN REGISTRO, JUEGA UNA PARTIDA Y INTENTALO MAS TARDE.\n\n\n");
        return;
    }
    int cantidad_estudiante = cantidad_notaciones(nombre_archivo);
    int cantidad_leida = 0;
    FILE *archivo = abrir_archiv(nombre_archivo, "rb");

    int contador=0;
    while (cantidad_leida<cantidad_estudiante){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        imprimir_datos(tmp.a);
        contador++;
        cantidad_leida++;
    }
    cerrar_archiv(archivo);
    printf("\n\n\tINGRLIZA (1-%d) -> ", cantidad_estudiante);
    int op=captura_int(1, cantidad_estudiante);
    leer_archivo(nombre_archivo, op);
    printf("\n\n");
}



int nuevo_id(char *nombre_archivo){
    if(!verificar_archivo(nombre_archivo)){
        return 1;
    }
    int cantidad_estudiante = cantidad_notaciones(nombre_archivo);
    int cantidad_leida = 0;
    FILE *archivo = abrir_archiv(nombre_archivo, "rb");
    while (cantidad_leida<cantidad_estudiante){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        if(cantidad_leida<cantidad_estudiante){
            cerrar_archiv(archivo);
            return tmp.id_juego+1;
        }
        cantidad_leida++;
    }
}
void leer_archivo(char *nombre_archivo, int id){
    int cantidad_estudiante = cantidad_notaciones(nombre_archivo);
    int cantidad_leida = 0;
    FILE *archivo = abrir_archiv(nombre_archivo, "rb");
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
    cerrar_archiv(archivo);
}
void escribir_archivo(char *nombre_archivo, int id, jugador *a, jugador *b, posiciones inicial, posiciones final, estado_bloque estado){
    FILE *archivo = abrir_archiv(nombre_archivo, "a+b");
    notacion_algebraica tmp = {id, a, b, inicial, final, estado};
    fwrite(&tmp, sizeof(notacion_algebraica), 1, archivo);
    cerrar_archiv(archivo);
}
int cantidad_notaciones(char *nombre){
    FILE *archivo = abrir_archiv(nombre, "rb");
    fseek(archivo, 0L, SEEK_END);
    int cantidad_estudiantes = ftell(archivo) / sizeof(notacion_algebraica);
    cerrar_archiv(archivo);
    return cantidad_estudiantes;
}
FILE* abrir_archiv(char *nombre_archivo, char *funcion){
    FILE *archivo = fopen(nombre_archivo, funcion);
    if(archivo == NULL){
        printf("\n\n\tERROR CRITICO: EL ARCHIVO NO FUE ABIERTO O ENCONTRADO CORRECTAMENTE\n");
        exit(-1);
    }
    return archivo;
}
void cerrar_archiv(FILE *nombre_archivo){
    int archivo = fclose(nombre_archivo);
    if (archivo != 0){
        printf("\n\tERROR CRITICO: EL ARCHIVO NO FUE CERRADO CORRECTAMENTE\t");
    }
}
int verificar_archivo(char *nombre_archivo){
    FILE *archivo = fopen(nombre_archivo, "rb");
    if(archivo == NULL){
        return 0;
    } else{
        cerrar_archiv(archivo);
        return 1;
    }
}

