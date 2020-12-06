#include "tablero.c"
#include "juego.c"
#include "jugador.c"

int recorrer_eliminar(tablero cont, jugador *a, jugador *b);
int verificar_eliminar(bloque **contenedor, jugador *b, posiciones ficha);
int alrededores(posiciones ficha, posiciones b);

void turno_movimiento(tablero *cont, jugador *a, jugador *b){
    char movimiento[]="pa1 a1";
    do{
        printf("\n\tIndique Jugada *");
        imprimir_color(a->representacion);
        printf("* ->");
        gets(movimiento);
    }while (!verificar_posiciones(cont, a, b, movimiento));
    imprimir_tablero(*(cont));
}


int main() {
    /**
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
    **/

    jugador a={"disraely", blancas};
    jugador b={"hola", negras};
    tablero cont = generar_tablero(&a, &b);
    char movimiento[]="pg3 h4";
    imprimir_tablero(cont);
    int i=0;
    do{
        do {
            turno_movimiento(&cont, &b, &a);
        } while (recorrer_eliminar(cont, &b, &a));

        do {
            turno_movimiento(&cont, &a, &b);
        } while (recorrer_eliminar(cont, &a, &b));

    } while(i!=12);
}








