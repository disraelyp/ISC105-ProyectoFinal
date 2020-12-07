#include "header.h"

void agregar_notacion(const char *ppNombre_archivo, int const id, jugador *a, jugador *b, posiciones inicial, posiciones final){
    notacion_algebraica contA;
    strcpy(contA.nombreA, a->nombre);
    contA.colorA=a->representacion;
    strcpy(contA.nombreB, b->nombre);
    contA.id_juego=id;
    contA.inicial=calcular_ubicacion(inicial);
    contA.final=calcular_ubicacion(final);
    escribir_archivo(ppNombre_archivo, contA);
}
void lista_notaciones(const char *pNombre_archivo){
    if(!verificar_archivo(pNombre_archivo)){
        printf("\n\n\tERROR: NO TIENES TODAVIA NINGUN REGISTRO, JUEGA UNA PARTIDA Y DESPUES INTENTALO.\n\n\n");
        return;
    }
    int cantidad_elementos = cantidad_notaciones(pNombre_archivo);
    int contL = 0;
    FILE *archivo = abrir_archivo(pNombre_archivo, "rb");
    printf("\n\n\n\t\tLISTA DE PARTIDAS GUARDADAS.\n");
    int contador=0, seguro=0;
    while (contL<cantidad_elementos){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        if(seguro!=tmp.id_juego){
            printf("\n#%02d - %s vs %s", contador+1, tmp.nombreA, tmp.nombreB);
            seguro=tmp.id_juego;
        }
        contador++;
        contL++;
    }
    cerrar_archivo(archivo);
    printf("\n\n\tINGRESE EL NUMERO DE LA PARTIDA QUE DESEA VISUALIZAR (1-%d) -> ", cantidad_id(pNombre_archivo));
    leer_archivo(pNombre_archivo, captura_int(1, cantidad_id(pNombre_archivo)));
    printf("\n\n\n");
}
int nuevo_id(const char *pNombre_archivo){
    if(!verificar_archivo(pNombre_archivo)){
        return 1;
    }
    int cantidad_estudiante = cantidad_notaciones(pNombre_archivo);
    int contL = 0;
    FILE *archivo = abrir_archivo(pNombre_archivo, "rb");
    int contenedor=0;
    while (contL<cantidad_estudiante){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        contL++;
        if(tmp.id_juego!=contenedor){
            contenedor = tmp.id_juego;
        }
    }
    cerrar_archivo(archivo);
    return contenedor+1;
}
int cantidad_id(const char *pNombre_archivo){
    if(!verificar_archivo(pNombre_archivo)){
        return 1;
    }
    int cantidad_estudiante = cantidad_notaciones(pNombre_archivo);
    int contL = 0;
    FILE *archivo = abrir_archivo(pNombre_archivo, "rb");
    int contenedor=0;
    while (contL<cantidad_estudiante){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        contL++;
        if(tmp.id_juego!=contenedor){
            contenedor = tmp.id_juego;
        }
    }
    cerrar_archivo(archivo);
    return contenedor;
}
void leer_archivo(const char *pNombre_archivo, int id){
    int const cantidad_estudiante = cantidad_notaciones(pNombre_archivo);
    int contL = 0;
    FILE *archivo = abrir_archivo(pNombre_archivo, "rb");
    printf("\n\n\n\t\tHISTORIAL DE LA PARTIDA:\n\n");
    while (contL<cantidad_estudiante){
        notacion_algebraica tmp;
        fread(&tmp, sizeof(notacion_algebraica), 1, archivo);
        if(tmp.id_juego==id){
            imprimir_representacion(tmp.colorA);
            imprimir_posiciones(calcular_posicion(tmp.inicial));
            printf(" ");
            imprimir_posiciones(calcular_posicion(tmp.final));
            printf("\n");
        }
        contL++;
    }
    cerrar_archivo(archivo);
}
void escribir_archivo(const char *pNombre_archivo, const notacion_algebraica notacion){
    FILE *archivo = abrir_archivo(pNombre_archivo, "a+b");
    fwrite(&notacion, sizeof(notacion_algebraica), 1, archivo);
    cerrar_archivo(archivo);
}
int cantidad_notaciones(const char *nombre){
    FILE *archivo = abrir_archivo(nombre, "rb");
    fseek(archivo, 0L, SEEK_END);
    int total_elementos = ftell(archivo) / sizeof(notacion_algebraica);
    cerrar_archivo(archivo);
    return total_elementos;
}
FILE* abrir_archivo(const char *pNombre_archivo, char *funcion){
    FILE *archivo = fopen(pNombre_archivo, funcion);
    if(archivo == NULL){
        printf("\n\n\tERROR CRITICO: EL ARCHIVO NO FUE ABIERTO O ENCONTRADO CORRECTAMENTE\n");
        exit(-1);
    }
    return archivo;
}
void cerrar_archivo(FILE *pNombre_archivo){
    int archivo = fclose(pNombre_archivo);
    if (archivo != 0){
        printf("\n\tERROR CRITICO: EL ARCHIVO NO FUE CERRADO CORRECTAMENTE\t");
    }
}
int verificar_archivo(const char *pNombre_archivo){
    FILE *archivo = fopen(pNombre_archivo, "rb");
    if(archivo == NULL){
        return 0;
    } else{
        cerrar_archivo(archivo);
        return 1;
    }
}
int cantidad_registros(const char *pNombre_archivo){
    FILE *archivo = abrir_archivo(pNombre_archivo, "rb");
    fseek(archivo, 0L, SEEK_END);
    long contA = ftell(archivo);
    int total_elementos = contA / sizeof(record_partidas);
    cerrar_archivo(archivo);
    return total_elementos;
}
void modificar_registros(const char *pNombre_archivo, record_partidas cont, int posicion){
    FILE *archivo = abrir_archivo(pNombre_archivo, "r+b");
    fseek(archivo, posicion *sizeof(record_partidas),SEEK_SET);
    fwrite(&cont, sizeof(record_partidas), 1, archivo);
    cerrar_archivo(archivo);
}
void escribir_registro(const char *pNombre_archivo, record_partidas cont){
    FILE *archivo = abrir_archivo(pNombre_archivo, "a+b");
    fwrite(&cont, sizeof(record_partidas), 1, archivo);
    cerrar_archivo(archivo);
}
void recorrer_registro(const char *pNombre_archivo, record_partidas cont){
    int contL = 0;
    if(verificar_archivo(pNombre_archivo)){
        FILE *archivo = abrir_archivo(pNombre_archivo, "rb");
        int cantidad_estudiante = cantidad_registros(pNombre_archivo);
        while (contL< cantidad_estudiante){
            record_partidas tmp;
            fread(&tmp, sizeof(record_partidas), 1, archivo);
            if(!strcmpi(cont.nombre, tmp.nombre)){
                cont.total_derrotas+=tmp.total_derrotas;
                cont.total_victorias+=tmp.total_victorias;
                cont.id_jugador=tmp.id_jugador;
                modificar_registros(pNombre_archivo, cont, contL);
                cerrar_archivo(archivo);
                return;
            }
            contL++;
        }
        cont.id_jugador=cantidad_estudiante+1;
        cerrar_archivo(archivo);
    }
    escribir_registro(pNombre_archivo, cont);
}
void agregar_registro(const char *pNombre_archivo, jugador *pJugador, int victorias, int derrotas){
    record_partidas contA;
    strcpy(contA.nombre, pJugador->nombre);
    contA.total_victorias=victorias;
    contA.total_derrotas=derrotas;
    contA.id_jugador=0;
    recorrer_registro(pNombre_archivo, contA);
}
int funcion_ordenamiento(const void *valorA, const void *valorB){
    const record_partidas *a=(const record_partidas *) valorA;
    const record_partidas *b=(const record_partidas *) valorB;
    return (b->total_victorias)-(a->total_victorias);
}
void leer_registro(const char *pNombre_archivo){
    if(!verificar_archivo(pNombre_archivo)){
        printf("\n\n\tERROR: NO TIENES TODAVIA NINGUN REGISTRO, JUEGA UNA PARTIDA Y DESPUES INTENTALO.\n\n\n");
        return;
    }
    int const total_elementos = cantidad_registros(pNombre_archivo);
    record_partidas *lista_elementos = (record_partidas *) malloc(8 * sizeof(record_partidas));
    int contA = 0;
    FILE *archivo = abrir_archivo(pNombre_archivo, "rb");
    printf("\n\n\n-------------------------------------------------------------------------------\n\t\tRECORD JUGADORES (TOP VICTORIAS)\n-------------------------------------------------------------------------------");
    printf("\nNo.\t\tNombre\t\tVictorias\tDerrotas\tTotal Partidas\n");
    while (contA < total_elementos){
        record_partidas contB;
        fread(&contB, sizeof(record_partidas), 1, archivo);
        *(lista_elementos + contA)=contB;
        contA++;
    }
    cerrar_archivo(archivo);
    qsort(lista_elementos, total_elementos, sizeof(record_partidas), funcion_ordenamiento);
    for(int i=0; i < total_elementos; i++){
        if(strlen((*(lista_elementos + i)).nombre) > 6){
            printf("\n#%02d\t\t%s\t%02d\t\t%02d\t\t%02d", i+1, (*(lista_elementos + i)).nombre, (*(lista_elementos + i)).total_victorias, (*(lista_elementos + i)).total_derrotas, (*(lista_elementos + i)).total_victorias + (*(lista_elementos + i)).total_derrotas);
        } else{
            printf("\n#%02d\t\t%s\t\t%02d\t\t%02d\t\t%02d", i+1, (*(lista_elementos + i)).nombre, (*(lista_elementos + i)).total_victorias, (*(lista_elementos + i)).total_derrotas, (*(lista_elementos + i)).total_victorias + (*(lista_elementos + i)).total_derrotas);
        }
    }
    free(lista_elementos);
    printf("\n-------------------------------------------------------------------------------\n\n\n");
}


