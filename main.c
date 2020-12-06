#include "tablero.c"
#include "juego.c"
#include "jugador.c"
#include "archivos.c"


int main() {
    int op=0;
    char *archivo_notaciones = "notaciones.dat";
    do {
        printf("\n\tJuego de Damas en Lenguaje C -> Menu de opciones.\n\n");
        printf("1. Nueva partida de damas.\n");
        printf("2. Ver record de jugadores.\n");
        printf("3. Ver notacion algebraica de partidas guardadas.\n");
        printf("4. Salir y guardar registro (reporte.txt).\n");
        printf("\n\t(1-4) ->");
        op=captura_int(1, 4);
        switch (op) {
            case 1:
                nueva_partida(archivo_notaciones);
                break;
            case 2:
                //estadisticas(a, b);
                break;
            case 3:
                lista_notaciones(archivo_notaciones);
                break;
        }
    } while (op!=4);
}








