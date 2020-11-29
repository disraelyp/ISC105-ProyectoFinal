#include "tablero.c"
#include "juego.c"
#include "manejo_errores.c"
#include "jugador.c"



int main() {
    jugador a={"disraly", 0, 0, blanco};
    jugador b={"disraly", 0, 0, negro};
    //creacion_jugadores(&a, &b);
    tablero cont=generar_tablero(&a, &b);
    imprimir_tablero(cont);
    char movimiento1[]="pb6 a5";
    printf("", verificar_posiciones(&cont, &a, movimiento1));
    printf("\n\n\n");
    imprimir_tablero(cont);
    char movimiento2[]="pa3 b4";
    printf("", verificar_posiciones(&cont, &b, movimiento2));
    char movimiento3[]="pb4 c5";
    printf("", verificar_posiciones(&cont, &b, movimiento3));
    char movimiento4[]="pc5 b6";
    printf("", verificar_posiciones(&cont, &b, movimiento4));
    imprimir_tablero(cont);


}

