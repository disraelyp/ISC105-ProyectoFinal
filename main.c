#include "tablero.c"
#include "juego.c"
#include "jugador.c"
#include "archivos.c"


int main() {
    int op=0;
    char *archivo_notaciones = "notaciones.dat";
    //char nombre[50];
    //strcpy(nombre, archivo_notaciones);
    //printf("%s", nombre);
    //nueva_partida(archivo_notaciones);
    lista_notaciones(archivo_notaciones);
}








