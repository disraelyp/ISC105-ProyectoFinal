#include "jugador.c"
#include "tablero.c"

int main() {
    jugador a = {"Disraely", 0, 1, blanco};
    jugador b = {"Disraely", 0, 1, negro};
    tablero cont;
    cont=generar_tablero(&a, &b);
    imprimir_tablero(cont);

    //int **tablero;
    //generar(tablero);
    return 0;
}
