#include <iostream>
#include <ctime>
#include <windows.h>
#include "menu.h"

using namespace std;

int main(){
    int opcion;
    const int CANTIDAD_MAXIMA_JUGADORES = 2;
    string jugadorMejorPuntaje = "Ariel";
    int mejorPuntaje = 144;

    srand(time(0));
    SetConsoleOutputCP(CP_UTF8);

    do {
        string nombres[CANTIDAD_MAXIMA_JUGADORES];
        int puntajes[CANTIDAD_MAXIMA_JUGADORES] = { 0 }, posicion = -1;

        opcion=seleccionarOpcion();
        rlutil::cls();
        int cantidadJugadores = ejecutarOpcion(opcion, nombres, puntajes, jugadorMejorPuntaje, mejorPuntaje);
        rlutil::cls();

        if(cantidadJugadores > 0) {
            posicion = actualizarEstadistica(mejorPuntaje, puntajes, cantidadJugadores);
            if(posicion > -1) {
                jugadorMejorPuntaje = nombres[posicion];
                mejorPuntaje = puntajes[posicion];
            }
        }
    } while(opcion != 0);

    return 0;
}
