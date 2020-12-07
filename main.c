#include "tablero.c"
#include "juego.c"
#include "jugador.c"
#include "archivos.c"


int main() {
    int op=0;
    char *archivo_notaciones = "notaciones.dat";
    char *archivo_registros = "registros.dat";
    //printf("\n\tTOP JUGADORES\n");
    //printf("\nNo.\t\tNombre\t\tVictorias\tDerrotas\tTotal Partidas");
    //char nombre[50];
    //strcpy(nombre, archivo_notaciones);
    //printf("%s", nombre);
    //nueva_partida(archivo_notaciones, archivo_registros);
    //lista_notaciones(archivo_notaciones);
    leer_registro(archivo_registros);
}








