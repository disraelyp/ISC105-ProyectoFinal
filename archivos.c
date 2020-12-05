#include <stdio.h>
#include <stdlib.h>
/**
 * Proceso para trabajar archivo:
 * 1. Referencia al puntero FILE.
 * 2. Apertura del archivo según el modo de operación, con su validación.
 * 3. Realizar el proceso deseado (Leer, Escribir, crear o borrar).
 * 4. Cerrar el archivo.
 */
typedef struct {
    int matricula; //4 bytes del entero
    char nombre[100]; //100 bytes... total 104.
} Estudiante;
//
FILE* abrir_archivo(char *nombre, char *modo);
void cerrar_archivo(FILE *archivo);
void escribir_texto_archivo(char *nombre);
void escribir_caracter_en_texto(char *nombre);
void leer_texto_archivo(char *nombre);
void escribir_estudiante_archivo(char *nombre);
int cantidad_estudiante_archivo(char *nombre);


void escribir_estudiante_archivo(char *nombre){
    FILE *archivo = abrir_archivo(nombre, "a+b"); //crear archivo tipo binario y mueve al final
    //completando desde una funcion para obtener el estudiante..
    Estudiante tmp = {20011136, "Carlos Camacho"};
    //guardar la estructurua en un archivo....
    fwrite(&tmp, sizeof(Estudiante), 1, archivo);
    //cerrando el archivo....
    cerrar_archivo(archivo);
}
void leer_texto_archivo(char *nombre){
    FILE *archivo = abrir_archivo(nombre, "r");
    printf("======= Información del archivo =========\n");
    char caracter;
    while ((caracter = fgetc(archivo)) != EOF){
        fputc(caracter, stdout);
    }
    printf("======= Fin Información del archivo =========\n");
    cerrar_archivo(archivo);
}
void escribir_caracter_en_texto(char *nombre) {
    FILE *archivo = abrir_archivo(nombre, "r+"); //modo: r+ posición de inicio del archivo, a+ al final de archivo.
    //mover al final sin usar el modo: a+
    fseek(archivo, 0L, SEEK_END);
//Operación archivo.
    printf("Digite el texto para el archivo:");
    char caracter;
    while ((caracter = getc(stdin)) != '\n') {
        fputc(caracter, archivo);
    }
    fputc('\n', archivo);
//
    cerrar_archivo(archivo);
}
void escribir_texto_archivo(char *nombre){
    FILE *archivo = abrir_archivo(nombre, "w");
//
    printf("Escribiendo en el archivo.....\n");
    fputs("Hola Mundo en C desde Archivo :-D", archivo);
//cierre
    cerrar_archivo(archivo);
}
FILE* abrir_archivo(char *nombre, char *modo){
    FILE *archivo = fopen(nombre, modo);
    if(archivo == NULL){
        fputs("Archivo no abierto, verificar...", stderr);
        exit(-1);
    }
    printf("Archivo abierto\n");
    return archivo;
}
void cerrar_archivo(FILE *archivo){
    int cerrado = fclose(archivo);
    cerrado == 0 ? printf("Archivo Cerrado\n") : printf("Error Archivo No Cerrado\n");
}