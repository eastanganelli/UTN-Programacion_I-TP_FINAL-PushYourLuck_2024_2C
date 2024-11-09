﻿#include "estadistica.h"

int actualizarEstadistica(int actual, int puntajes[], int cantidad) {
    int i = 0, indice = -1, valorMax = actual;
    do {
        if(valorMax < puntajes[i]) {
            indice = i;
            valorMax = puntajes[i];
        }
        i++;
    } while(i < cantidad);
    return indice;
}

void imprimirEstadistica(string Jugador, int puntaje) {
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);

    int anchoPantalla = rlutil::tcols();
    int posXMenu = (anchoPantalla - 30) / 2;  // Acomoda a un ancho promedio

    rlutil::locate(posXMenu + 8, rlutil::trows() / 4);
    rlutil::setBackgroundColor(rlutil::BLACK);
    cout << "Estadisticas";
    rlutil::setBackgroundColor(rlutil::LIGHTBLUE);

    rlutil::setColor(rlutil::BLUE);
    rlutil::locate(posXMenu, rlutil::trows() / 4 + 1);
    cout << "===========================";
    rlutil::setColor(rlutil::WHITE);

    rlutil::locate(posXMenu, rlutil::trows() / 4 + 2);
    cout << "Jugador";

    rlutil::locate(posXMenu + 20, rlutil::trows() / 4 + 2);
    cout << "Puntaje";

    rlutil::locate(posXMenu, rlutil::trows() / 4 + 4);
    cout << Jugador;

    rlutil::locate(posXMenu + 20, rlutil::trows() / 4 + 4);
    cout << puntaje;

    rlutil::setColor(rlutil::WHITE);
    cout << endl << endl << endl;
}
