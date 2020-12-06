#include "tablero.c"
#include "juego.c"
#include "jugador.c"





int main() {
    int op=0;
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
                nueva_partida();
                break;
            case 2:
                //estadisticas(a, b);
                break;
            case 3:
                //notacion_algebraica;
                break;
        }
    } while (op!=4);
}








