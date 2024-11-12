#include "creditos.h"

/*
 * Muestra los creditos del juego
*/
void mostrarCreditos() {
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);

    int anchoPantalla = rlutil::tcols();
    int posXMenu = (anchoPantalla - 43) / 2;  // Acomoda a un ancho promedio

    rlutil::locate(posXMenu + 14, rlutil::trows() / 4);
    cout << "EL GRAN ROMANO";

    rlutil::setColor(rlutil::BLUE);
    rlutil::locate(posXMenu, rlutil::trows() / 4 + 1);
    cout << "==========================================";
    rlutil::setColor(rlutil::WHITE);

    rlutil::locate(posXMenu, rlutil::trows() / 4 + 2);
    cout << "Integrantes";


    rlutil::locate(posXMenu + 35, rlutil::trows() / 4 + 2);
    cout << "Legajos";

    rlutil::locate(posXMenu, rlutil::trows() / 4 + 4);
    cout << "Francisco Daniel Salas";

    rlutil::locate(posXMenu + 35, rlutil::trows() / 4 + 4);
    cout << "28888";

    rlutil::locate(posXMenu, rlutil::trows() / 4 + 5);
    cout << "Marcos Elias Cardoso";

    rlutil::locate(posXMenu + 35, rlutil::trows() / 4 + 5);
    cout << "29727";

    rlutil::locate(posXMenu, rlutil::trows() / 4 + 6);
    cout << "Erika Ayelen Alliana";

    rlutil::locate(posXMenu + 35, rlutil::trows() / 4 + 6);
    cout << "27100";

    rlutil::locate(posXMenu, rlutil::trows() / 4 + 7);
    cout << "Ezequiel Augusto Stanganelli";

    rlutil::locate(posXMenu + 35, rlutil::trows() / 4 + 7);
    cout << "31723";

    rlutil::setColor(rlutil::WHITE);
}
