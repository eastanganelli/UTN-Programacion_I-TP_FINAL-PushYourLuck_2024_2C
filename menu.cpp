#include "menu.h"

int seleccionarOpcion()
{
    int opcion;
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);
    rlutil::setBackgroundColor(rlutil::LIGHTBLUE);
    int anchoPantalla = rlutil::tcols();
    int altoPantalla = rlutil::trows();
    int anchoMenu = 30;
    int posXMenu = (anchoPantalla - anchoMenu) / 2;
    int posYMenu = altoPantalla / 4;

    rlutil::cls();

    rlutil::locate(posXMenu, posYMenu);
    cout << "==============================";
    rlutil::locate(posXMenu + 12, posYMenu + 1);
    cout << "GREED";
    rlutil::locate(posXMenu, posYMenu + 2);
    cout << "==============================";

    rlutil::locate(posXMenu + 4, posYMenu + 4);
    cout << "1) MODO UN JUGADOR";
    rlutil::locate(posXMenu + 4, posYMenu + 5);
    cout << "2) MODO DOS JUGADORES";
    rlutil::locate(posXMenu + 4, posYMenu + 6);
    cout << "3) ESTADISTICAS";
    rlutil::locate(posXMenu + 4, posYMenu + 7);
    cout << "4) CREDITOS";
    rlutil::locate(posXMenu + 4, posYMenu + 8);
    cout << "0) SALIR";

    rlutil::locate(posXMenu, posYMenu + 10);
    cout << "==============================";

    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(posXMenu + 4, posYMenu + 12);
    cout << "Ingrese una opcion: ";
    rlutil::setColor(rlutil::WHITE);

    cin>>opcion;
    return opcion;
}

int ejecutarOpcion(int opcion, string nombres[], int puntajes[], string jugadorMejorPuntaje, int mejorPuntaje) {
    int cantidadJugadores = -1; // Cantidad de jugadores

    switch(opcion) {
    case 1:
        cantidadJugadores = 1; // Cantidad de jugadores para el modo un jugador
        juego(nombres, puntajes, cantidadJugadores); // Inicia el juego
        informarJugadorGanador(nombres, puntajes, cantidadJugadores); // Informa el jugador ganador
        rlutil::anykey();
        break;

    case 2:
        cantidadJugadores = 2; // Cantidad de jugadores para el modo dos jugadores
        juego(nombres, puntajes, cantidadJugadores); // Inicia el juego
        informarJugadorGanador(nombres, puntajes, cantidadJugadores); // Informa el jugador ganador
        rlutil::anykey();
        break;

    case 3:
        imprimirEstadistica(jugadorMejorPuntaje, mejorPuntaje); // Imprime la estadistica del jugador con mejor puntaje
        rlutil::anykey();
        break;

    case 4:
        mostrarCreditos(); // Muestra los creditos
        rlutil::anykey();
        break;

    case 0:
        modalMensaje("Adios!", "Gracias por usar nuestro juego!", 1);
        break;

    default:
        modalMensaje("Menu Error", "Opcion incorrecta, por favor intente de nuevo!", 2);
        break;

    }

    // Retorna la cantidad de jugadores
    return cantidadJugadores;
}

/*
 * Función que imprime mensaje estilo un modal.
 * Recibe titulo, mensaje y tipo.
 * Tipo: 1 (Black: Normal), 2 (Red: Error), 3 (Yellow: Advertencia).
*/
void modalMensaje(string titulo, string msj, int tipo) {
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);
    int anchoPantalla = rlutil::tcols();
    int altoPantalla = rlutil::trows();
    int anchoModal = 30;
    int altoModal = 5;

    if(anchoModal < msj.length()) {
        anchoModal = msj.length() + 4;
    }

    int posXModal = (anchoPantalla - anchoModal) / 2;
    int posYModal = (altoPantalla - altoModal) / 2;

    rlutil::cls();
    rlutil::setBackgroundColor(rlutil::LIGHTBLUE);

    switch(tipo) {
    case 1: // Normal
        rlutil::setColor(rlutil::BLACK);
        break;
    case 2: // Error
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::RED);
        break;
    case 3: // Advertencia
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::YELLOW);
        break;
    }

    rlutil::locate(posXModal, posYModal);
    for(int i = 0; i< anchoModal; i++) {
        cout << "=";
    }

    rlutil::locate(posXModal + 2, posYModal + 1);
    cout << titulo;

    rlutil::locate(posXModal, posYModal + 2);
    for(int i = 0; i< anchoModal; i++) {
        cout << "=";
    }

    rlutil::locate(posXModal + 2, posYModal + 4);
    cout << msj;
    rlutil::locate(posXModal, posYModal + 6);
    for(int i = 0; i< anchoModal; i++) {
        cout << "=";
    }

    rlutil::setColor(rlutil::WHITE);
    rlutil::setBackgroundColor(rlutil::LIGHTBLUE);
    rlutil::anykey();
}
