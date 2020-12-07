#include "header.h"
void agregar_notacion(const char *nombre_archivo, int const id, jugador *a, jugador *b, posiciones inicial, posiciones final){
    notacion_algebraica contA;
    strcpy(contA.nombreA, a->nombre);
    contA.colorA=a->representacion;
    strcpy(contA.nombreB, b->nombre);
    contA.id_juego=id;
    contA.inicial=calcular_ubicacion(inicial);
    contA.final=calcular_ubicacion(final);
    escribir_archivo(nombre_archivo, contA);
};
void lista_notaciones(char *nombre_archivo){
    if(!verificar_archivo(nombre_archivo)){
        printf("\n\n\t NO TIENES TODAVIA NINGUN REGISTRO, JUEGA UNA PARTIDA Y INTENTALO MAS TARDE.\n\n\n");
        return;
    }
    int cantidad_estudiante = cantidad_notaciones(nombre_archivo);
    int cantidad_leida = 0;
    FILE *archivo = abrir_archiv(nombre_archivo, "rb");
    printf("\n\t\tLISTA DE PATIDAS.\n");
    int contador=0, seguro=0;
    while (cantidad_leida<cantidad_estudiante){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        if(seguro!=tmp.id_juego){
            printf("\n#%02d - %s vs %s", contador+1, tmp.nombreA, tmp.nombreB);
            seguro=tmp.id_juego;
        }
        contador++;
        cantidad_leida++;
    }
    cerrar_archiv(archivo);
    printf("\n\n\tINGRESE EL NUMERO DE LA PARTIDA QUE DESEA VISUALIZAR (1-%d) -> ", cantidad_estudiante);
    leer_archivo(nombre_archivo, captura_int(1, cantidad_estudiante));
    printf("\n\n");
}
int nuevo_id(char *nombre_archivo){
    if(!verificar_archivo(nombre_archivo)){
        return 1;
    }
    int cantidad_estudiante = cantidad_notaciones(nombre_archivo);
    int cantidad_leida = 0;
    FILE *archivo = abrir_archiv(nombre_archivo, "rb");
    int contenedor=0;
    while (cantidad_leida<cantidad_estudiante){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        cantidad_leida++;
        if(tmp.id_juego!=contenedor){
            contenedor = tmp.id_juego;
        }
    }
    cerrar_archiv(archivo);
    return contenedor+1;
}
void leer_archivo(char *nombre_archivo, int id){
    int const cantidad_estudiante = cantidad_notaciones(nombre_archivo);
    int cantidad_leida = 0;
    FILE *archivo = abrir_archiv(nombre_archivo, "rb");
    printf("\n");
    while (cantidad_leida<cantidad_estudiante){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        if(tmp.id_juego==id){
            imprimir_posiciones(calcular_posicion(tmp.inicial));
            printf(" ");
            imprimir_posiciones(calcular_posicion(tmp.final));
            printf("\n");
        }
        cantidad_leida++;
    }
    cerrar_archiv(archivo);
}
void escribir_archivo(char *nombre_archivo, const notacion_algebraica notacion){
    printf("%s", notacion.nombreA);
    FILE *archivo = abrir_archiv(nombre_archivo, "a+b");
    fwrite(&notacion, sizeof(notacion_algebraica), 1, archivo);
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

