#include <iostream>
#include <ctime>
#include "menu.h"

using namespace std;

int main(){
    int opcion; // Seleccion de item del menu
    const int CANTIDAD_MAXIMA_JUGADORES = 2; // Cantidad maxima de jugadores posibles
    string jugadorMejorPuntaje = "Vacio"; // Nombre del jugador con puntaje maximo
    int mejorPuntaje = 0; // Puntaje maximo del jugador con mejor puntaje

    srand(time(0)); // Inicializa el generador de numeros

    do {
        string nombres[CANTIDAD_MAXIMA_JUGADORES]; // Nombres de los jugadores
        int puntajes[CANTIDAD_MAXIMA_JUGADORES] = { 0 }, // Puntajes de los jugadores
            posicion = -1; // Posicion del jugador con mejor puntaje

        opcion=seleccionarOpcion();
        rlutil::cls();
        int cantidadJugadores = ejecutarOpcion(opcion, nombres, puntajes, jugadorMejorPuntaje, mejorPuntaje);
        rlutil::cls();

        /*
         * Verifica que existan jugadores para actualizar la estadistica del jugador con mejor puntaje
         * Si la cantidad de jugadores es mayor a 0, se actualiza la estadistica del jugador con mejor puntaje
        */
        if(cantidadJugadores > 0) {
            /*
             * Verifica si el jugador con mejor puntaje se encuentra en la lista de jugadores
             * Si devuelve un valor mayor a -1, significa que el jugador con mejor puntaje se encuentra en la lista de jugadores
             * Si devuelve un valor igual a -1, significa que el jugador con mejor puntaje no se encuentra en la lista de jugadores
            */
            posicion = actualizarEstadistica(mejorPuntaje, puntajes, cantidadJugadores);
            if(posicion > -1) {
                /*
                 * Actualiza el nombre del jugador con mejor puntaje
                 * Actualiza el puntaje del jugador con mejor puntaje
                */
                jugadorMejorPuntaje = nombres[posicion];
                mejorPuntaje = puntajes[posicion];
            }
        }
    } while(opcion != 0);

    return 0;
}
