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
    FILE *archivo = abrir_archivo(nombre_archivo, "rb");
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
    cerrar_archivo(archivo);
    printf("\n\n\tINGRESE EL NUMERO DE LA PARTIDA QUE DESEA VISUALIZAR (1-%d) -> ", cantidad_estudiante);
    leer_archivo(nombre_archivo, captura_int(1, cantidad_id(nombre_archivo)));
    printf("\n\n");
}
int nuevo_id(char *nombre_archivo){
    if(!verificar_archivo(nombre_archivo)){
        return 1;
    }
    int cantidad_estudiante = cantidad_notaciones(nombre_archivo);
    int cantidad_leida = 0;
    FILE *archivo = abrir_archivo(nombre_archivo, "rb");
    int contenedor=0;
    while (cantidad_leida<cantidad_estudiante){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        cantidad_leida++;
        if(tmp.id_juego!=contenedor){
            contenedor = tmp.id_juego;
        }
    }
    cerrar_archivo(archivo);
    return contenedor+1;
}
int cantidad_id(char *nombre_archivo){
    if(!verificar_archivo(nombre_archivo)){
        return 1;
    }
    int cantidad_estudiante = cantidad_notaciones(nombre_archivo);
    int cantidad_leida = 0;
    FILE *archivo = abrir_archivo(nombre_archivo, "rb");
    int contenedor=0;
    while (cantidad_leida<cantidad_estudiante){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        cantidad_leida++;
        if(tmp.id_juego!=contenedor){
            contenedor = tmp.id_juego;
        }
    }
    cerrar_archivo(archivo);
    return contenedor;
}
void leer_archivo(char *nombre_archivo, int id){
    int const cantidad_estudiante = cantidad_notaciones(nombre_archivo);
    int cantidad_leida = 0;
    FILE *archivo = abrir_archivo(nombre_archivo, "rb");
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
    cerrar_archivo(archivo);
}
void escribir_archivo(char *nombre_archivo, const notacion_algebraica notacion){
    FILE *archivo = abrir_archivo(nombre_archivo, "a+b");
    fwrite(&notacion, sizeof(notacion_algebraica), 1, archivo);
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
int verificar_archivo(char *nombre_archivo){
    FILE *archivo = fopen(nombre_archivo, "rb");
    if(archivo == NULL){
        return 0;
    } else{
        cerrar_archivo(archivo);
        return 1;
    }
}

int cantidad_registros(char *nombre){

    FILE *archivo = abrir_archivo(nombre, "rb");
    fseek(archivo, 0L, SEEK_END);
    long cantidad_bytes = ftell(archivo);
    int cantidad_estudiantes = cantidad_bytes / sizeof(record_partidas);
    cerrar_archivo(archivo);
    return cantidad_estudiantes;
}
void modificar_registros(char *nombre_archivo, record_partidas cont, int posicion){
    FILE *archivo = abrir_archivo(nombre_archivo, "r+b");
    fseek(archivo, posicion *sizeof(record_partidas),SEEK_SET);
    fwrite(&cont, sizeof(record_partidas), 1, archivo);
    cerrar_archivo(archivo);
}
void escribir_registro(char *nombre_archivo, record_partidas cont){
    FILE *archivo = abrir_archivo(nombre_archivo, "a+b");
    fwrite(&cont, sizeof(record_partidas), 1, archivo);
    cerrar_archivo(archivo);
}
void recorrer_registro(char *nombre_archivo, record_partidas cont){
    int cantidad_leida = 0;
    if(verificar_archivo(nombre_archivo)){
        FILE *archivo = abrir_archivo(nombre_archivo, "rb");
        int cantidad_estudiante = cantidad_registros(nombre_archivo);
        while (cantidad_leida< cantidad_estudiante){
            record_partidas tmp;
            fread(&tmp, sizeof(record_partidas), 1, archivo);
            if(strcmp(cont.nombre, tmp.nombre)){
                cont.total_derrotas+=tmp.total_derrotas;
                cont.total_victorias+=tmp.total_victorias;
                modificar_registros(nombre_archivo, cont, cantidad_leida+1);
                cerrar_archivo(archivo);
                return;
            }
            cantidad_leida++;
        }
        cerrar_archivo(archivo);
    }
    cont.id_jugador=cantidad_leida+1;
    escribir_registro(nombre_archivo, cont);
}
void agregar_registro(char *nombre_archivo, jugador *a, int victorias, int derrotas){
    record_partidas cont;
    strcpy(cont.nombre, a->nombre);
    cont.total_victorias=victorias;
    cont.total_derrotas=derrotas;
    cont.id_jugador=0;
    recorrer_registro(nombre_archivo, cont);
}
void leer_registro(char *nombre_archivo){
    if(!verificar_archivo(nombre_archivo)){
        printf("\n\n\t NO TIENES TODAVIA NINGUN REGISTRO, JUEGA UNA PARTIDA Y INTENTALO MAS TARDE.\n\n\n");
        return;
    }
    int const cantidad_estudiante = cantidad_registros(nombre_archivo);
    int cantidad_leida = 0;
    FILE *archivo = abrir_archivo(nombre_archivo, "rb");
    printf("\n\tTOP JUGADORES\n");
    printf("\nNo.\t\tNombre\t\tVictorias\tDerrotas\tTotal Partidas\n");
    while (cantidad_leida<cantidad_estudiante){
        record_partidas tmp;
        fread(&tmp, sizeof(record_partidas), 1, archivo);
        printf("\n#%02d\t%s\t%02d\t%02d\t%02d", cantidad_leida+1, tmp.nombre, tmp.total_victorias, tmp.total_derrotas, tmp.total_victorias+tmp.total_derrotas);
        printf("\n-> %d", tmp.id_jugador);
        cantidad_leida++;
    }
    cerrar_archivo(archivo);
}


