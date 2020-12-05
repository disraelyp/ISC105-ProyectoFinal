#include "tablero.c"
#include "juego.c"
#include "jugador.c"

int verificar_eliminar(tablero, jugador*, jugador*);
int verificar_plano(bloque**, jugador*, posiciones);
int alrededores(posiciones ficha, posiciones b);



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
    imprimir_tablero(cont);
    char movimiento[]="pa5 b5";
    int i=0;
    do{

        do{
            verificar_eliminar(cont, &a, &b); // VERIFICA SI LAS BLANCAS COMEN
            verificar_eliminar(cont, &b, &a); // VERIFICA SI LAS BLANCAS COMEN
            printf("\n\t->");
            gets(movimiento);
        }while (!verificar_posiciones(&cont, &b, movimiento));
        imprimir_tablero(cont);



        //do{
          //  verificar_eliminar(cont, &a, &b); // VERIFICA SI LAS BLANCAS COMEN
           // printf("\n\t->");
           // gets(movimiento);
        //}while (!verificar_posiciones(&cont, &a, movimiento));
        //imprimir_tablero(cont);


    } while(i!=12);



}
int verificar_eliminar(tablero cont, jugador *a, jugador *b){
    bloque **contenedor=cont.plano;
    int contador=0;
    for (int i = 0; i < COLUMNA; ++i) {
        for (int j = 0; j < FILA; ++j) {
            if((*(*(contenedor + i) + j)).peones.propietario == a){
                verificar_plano(contenedor, b, calcular_posicion(contador+1));
            }
            contador++;
        }
    }
    return 0;
}



int verificar_plano(bloque **contenedor, jugador *b, posiciones ficha){
    int contador=0;
    for (int i = 0; i < COLUMNA; ++i) {
        for (int j = 0; j < FILA; ++j) {
            if((*(*(contenedor + i) + j)).peones.propietario == b){
                if((*(*(contenedor + i) + j)).peones.propietario->representacion == blancas || (*(*(contenedor + i) + j)).peones.estado==dama) {
                    if ((calcular_cordenadaX(ficha) + 1 == calcular_cordenadaX(calcular_posicion(contador + 1))) &&
                        (calcular_cordenadaY(ficha) + 1 ==
                         calcular_cordenadaY(calcular_posicion(contador + 1)))) { // ARREGLAR
                        if ((*(*(contenedor + calcular_cordenadaY(ficha) + 2) + calcular_cordenadaX(ficha) +
                               2)).estado == disponible) {
                            printf("\nLa ficha (%d, %d) se come a la (%d, %do) D %d", calcular_cordenadaX(ficha),
                                   calcular_cordenadaY(ficha), calcular_cordenadaX(calcular_posicion(contador + 1)),
                                   calcular_cordenadaY(calcular_posicion(contador + 1)), contador + 1);
                            return 1;
                        }
                    }
                    if ((calcular_cordenadaX(ficha) - 1 == calcular_cordenadaX(calcular_posicion(contador + 1))) &&
                        (calcular_cordenadaY(ficha) + 1 == calcular_cordenadaY(calcular_posicion(contador + 1)))) {
                        if ((*(*(contenedor + calcular_cordenadaY(ficha) + 2) + calcular_cordenadaX(ficha) -
                               2)).estado == disponible) {
                            printf("\nLa ficha (%d, %d) se come a la (%d, %do) D %d", calcular_cordenadaX(ficha),
                                   calcular_cordenadaY(ficha), calcular_cordenadaX(calcular_posicion(contador + 1)),
                                   calcular_cordenadaY(calcular_posicion(contador + 1)), contador + 1);
                            return 1;
                        }
                    }
                }

                if((*(*(contenedor + i) + j)).peones.propietario->representacion == blancas || (*(*(contenedor + i) + j)).peones.estado==dama) {
                    if((calcular_cordenadaX(ficha)-1 == calcular_cordenadaX(calcular_posicion(contador+1))) && (calcular_cordenadaY(ficha) - 1 == calcular_cordenadaY(calcular_posicion(contador+1)))){
                        if((*(*(contenedor + calcular_cordenadaY(ficha)-2) + calcular_cordenadaX(ficha)-2)).estado==disponible){
                            printf("\nLa ficha (%d, %d) se come a la (%d, %do) D %d", calcular_cordenadaX(ficha), calcular_cordenadaY(ficha), calcular_cordenadaX(calcular_posicion(contador+1)), calcular_cordenadaY(calcular_posicion(contador+1)), contador+1);
                            return 1;
                        }
                    }
                    if((calcular_cordenadaX(ficha)+1 == calcular_cordenadaX(calcular_posicion(contador+1))) && (calcular_cordenadaY(ficha)-1 == calcular_cordenadaY(calcular_posicion(contador+1)))){ // ARREGLAR
                        if((*(*(contenedor + calcular_cordenadaY(ficha)-2) + calcular_cordenadaX(ficha)+2)).estado==disponible){
                            printf("\nLa ficha (%d, %d) se come a la (%d, %do) D %d", calcular_cordenadaX(ficha), calcular_cordenadaY(ficha), calcular_cordenadaX(calcular_posicion(contador+1)), calcular_cordenadaY(calcular_posicion(contador+1)), contador+1);
                            return 1;
                        }
                    }
                }
            }
            contador++;
        }
    }
    return 0;
}



