#include "tablero.c"
#include "juego.c"
#include "jugador.c"
#include "archivos.c"

int main() {
    int op=0;
    char *archivo_notaciones = "notaciones.dat";
    char *archivo_registros = "registros.dat";
    do{
        printf("\nPractica Final - Fundamentos de Programacion - ISC-105 - PUCMM\n");
        printf("Presentado por: Disraely Peralta Uceta (ID: 10140077)\n\n");
        printf("Juego de Las Damas en Lenguaje C -- Menu de Opciones:\n\n");
        printf("\t\t 1 - Jugar Partida de Damas.\n");
        printf("\t\t 2 - Ver record de jugadores.\n");
        printf("\t\t 3 - Ver notacion algebraica de partidas guardadas.\n");
        printf("\t\t 4 - Salir y guardar todo.\n");
        printf("\nOpcion:"); op=captura_int(1, 4);
        switch (op) {
            case 1:
                nueva_partida(archivo_notaciones, archivo_registros);
                break;
            case 2:
                leer_registro(archivo_registros);
                break;
            case 3:
                lista_notaciones(archivo_notaciones);
                break;
        }
    } while (op!=4);
}








