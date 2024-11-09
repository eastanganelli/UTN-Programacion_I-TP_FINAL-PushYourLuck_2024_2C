#include "juego.h"

int calcularPuntaje(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores){
    int puntos=0, repetidoDuplica=0, cantidadBloqueados=0;

    for(int i=0; i<cantidad; i++){
        if(!estaBloqueado(vDados[i], bloqueadores, cantidadBloqueadores)) {
            puntos+=vDados[i];
        }
    }

    return puntos;
}

int duplicaOpierde(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores) {
    int multiplicador = 1, repetidoDuplica = 0, cantidadBloqueados = 0;
    for(int i=0; i<cantidad; i++){
        if(!estaBloqueado(vDados[i], bloqueadores, cantidadBloqueadores)) { //!false = true
            // 3 < 4 [5 - 1]  Y  Actual == Siguiente
            // 4 < 5 [5 - 1]  Y  Actual == Siguiente -> explota => vDados[5]
            /*if(i < cantidad - 1 && vDados[i] == vDados[i+1]) {
                    repetidoDuplica++;
                }*/

            if(i > 0 && vDados[i] == vDados[i-1]) {
                // 0 > 0  Y  Actual == Anterior => FALSO
                //    F Y => skip
                // 1 > 0  Y  Actual == Anterior -> vDados[0] = vDados[1-1] == vDados[1]
                // 2 > 0  Y  Actual == Anterior -> vDados[1] = vDados[2-1] == vDados[2]
                // 3 > 0  Y  Actual == Anterior -> vDados[2] = vDados[3-1] == vDados[3]
                // 4 > 0  Y  Actual == Anterior -> vDados[3] = vDados[4-1] == vDados[4]
                if(i == 1) {
                    repetidoDuplica = 2;
                } else {
                    repetidoDuplica++;
                }
            }
        } else {
            cantidadBloqueados++;
        }
    }

    if(cantidadBloqueados == cantidad) {
        // Todos bloqueados
        multiplicador = 0;
    }
    else if(repetidoDuplica == cantidad) {
        // Doble puntaje rep
        multiplicador = 2;
    }

    return multiplicador;
}

int removerBloqueados(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores) {
    int removidosDados = cantidad;
    for(int i=0; i<cantidad; i++){
        if(estaBloqueado(vDados[i], bloqueadores, cantidadBloqueadores)) {
            removidosDados--;
        }
    }
    return removidosDados;
}

bool estaBloqueado(int dado, int bloqueadores[], int cantidadBloqueadores) {
    for(int j=0; j<cantidadBloqueadores; j++){
        if(dado ==  bloqueadores[j]) {
            return true;
        }
    }
    return false;
}

int tirarDado(){
    return rand() % 6 + 1;
}

void tiradaDeDados(int vDados[], int cantidad){
    for(int i=0; i<cantidad; i++){
        vDados[i] = tirarDado();
    }
}

void mostrarDados(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores){
    string caraDados[6] = { "\u2680", "\u2681", "\u2682", "\u2683", "\u2684", "\u2685" };
    //string caraDados[6] = {"1", "2", "3", "4", "5", "6"};
    for(int i=0; i<cantidad; i++){
        rlutil::setColor(rlutil::WHITE);
        if(estaBloqueado(vDados[i], bloqueadores, cantidadBloqueadores)) {
            rlutil::setColor(rlutil::RED);
        }
        cout<<" "<<caraDados[vDados[i] - 1];
    }
    rlutil::setColor(rlutil::WHITE);
}

void tiradaBloqueadores(int vDados[], int cantidad){
    for(int i=0; i<cantidad; i++){
        vDados[i] = tirarDado();
    }
}

void mostrarBloqueadores(int vDados[], int cantidad) {
    //Dado                     1          2          3        4         5         6
    //Index                    0          1          2        3         4         5
    string caraDados[6] = { "\u2680", "\u2681", "\u2682", "\u2683", "\u2684", "\u2685" };
    //string caraDados[6] = {"1", "2", "3", "4", "5", "6"};
    for(int i=0; i<cantidad; i++){
        cout << " " << caraDados[vDados[i] - 1];
    }
}

void cargarJugadores(string nombres[], int cantidadJugadores) {
    rlutil::setColor(rlutil::WHITE);
    const int anchoPantalla = rlutil::tcols(), altoPantalla = rlutil::trows();
    const int anchoEncabezado = 40, altoEncabezado = 5;
    int posX = (anchoPantalla - anchoEncabezado) / 2,
        posY = (altoPantalla - altoEncabezado) / 2;
    const bool soloJugador = cantidadJugadores < 2;
    int i = 0;
    string nombre = "\0", textoImprimir = "\0";

    rlutil::locate(posX, posY);
    rlutil::setBackgroundColor(rlutil::CYAN);
    cout << "Seleccionado modo de juego: ";
    if(soloJugador) {
        cout << "Un jugador";
    } else {
        cout << "Multijugador";
    }
    rlutil::setBackgroundColor(rlutil::LIGHTBLUE);

    do {
        nombre=ingresarNombre(soloJugador, i, posX, posY + i + 2);
        nombres[i] = nombre;
        i++;
    } while(i < cantidadJugadores);
    rlutil::cls();
}

string ingresarNombre(bool soloJugador, int indice, int posX, int posY) {
    string nombre;

    rlutil::locate(posX, posY);
    rlutil::setBackgroundColor(rlutil::BLUE);
    if(!soloJugador) {
        cout << "Jugador Nro " << indice + 1 << " ingrese su nombre:";
    }
    else {
        cout << "Ingrese su nombre:";
    }
    rlutil::setBackgroundColor(rlutil::LIGHTBLUE);

    cout << " ";

    rlutil::setColor(rlutil::BLUE);
    cin>>nombre;
    rlutil::setColor(rlutil::WHITE);
    return nombre;
}

// void unJugador() {
void juego(string nombres[], int puntajes[], int cantidadJugadores) {
    const int CANTIDAD_RONDAS = 2, CANTIDAD_DADOS = 5, CANTIDAD_BLOQUEADORES = 2;
    int dados[CANTIDAD_DADOS];
    char seguirJugando = 's';
    int ronda = 1, jugadorActual = 0;

    cargarJugadores(nombres, cantidadJugadores);

    while(ronda <= CANTIDAD_RONDAS) {
        rlutil::setColor(rlutil::WHITE);
        for(jugadorActual = 0; jugadorActual < cantidadJugadores; jugadorActual++) {
            int cantidadDadosActual = CANTIDAD_DADOS, puntajeRonda = 0;
            int bloqueadores[CANTIDAD_BLOQUEADORES] = { 0 };
            int posYCursor = 0, posYCursorFila = 0, tirada = 1, valorMutiplicador;

            tiradaBloqueadores(bloqueadores, CANTIDAD_BLOQUEADORES);
            posYCursor = imprimirEncabezado(ronda, nombres[jugadorActual], puntajes[jugadorActual], puntajeRonda, bloqueadores, CANTIDAD_BLOQUEADORES);
            posYCursorFila = posYCursor;
            do{
                int puntajeTirada = 0;
                valorMutiplicador = 1;

                tiradaDeDados(dados, cantidadDadosActual);
                puntajeTirada = calcularPuntaje(dados, cantidadDadosActual, bloqueadores, CANTIDAD_BLOQUEADORES);
                valorMutiplicador = duplicaOpierde(dados, cantidadDadosActual, bloqueadores, CANTIDAD_BLOQUEADORES);

                if(valorMutiplicador != 0) {
                    puntajeRonda += puntajeTirada * valorMutiplicador;
                } else {
                    puntajeRonda = 0;
                }

                (void)imprimirEncabezado(ronda, nombres[jugadorActual], puntajes[jugadorActual], puntajeRonda, bloqueadores, CANTIDAD_BLOQUEADORES);
                seguirJugando = imprimirTabla(posYCursorFila, tirada, dados, cantidadDadosActual, CANTIDAD_DADOS, bloqueadores, CANTIDAD_BLOQUEADORES, puntajeRonda, valorMutiplicador);
                cantidadDadosActual = removerBloqueados(dados, cantidadDadosActual, bloqueadores, CANTIDAD_BLOQUEADORES);


                if (cantidadDadosActual > 0 && (seguirJugando == 's' || seguirJugando == 'S')){
                    tirada++;
                    posYCursorFila++;
                }
            } while (cantidadDadosActual > 0 && (seguirJugando == 's' || seguirJugando == 'S'));

            puntajes[jugadorActual] += puntajeRonda;

            cout << "Presione la tecla Enter para continuar...";
            rlutil::anykey();
            rlutil::cls();
        }
        ronda++;
    }
}

void informarJugadorGanador(string nombres[], int puntajes[], int cantidadJugadores) {
    rlutil::setColor(rlutil::WHITE);
    const int anchoPantalla = rlutil::tcols(), altoPantalla = rlutil::trows();
    const int anchoEncabezado = 40, altoEncabezado = 5;
    int posXEncabezado = (anchoPantalla - anchoEncabezado) / 2,
        posYEncabezado = (altoPantalla - altoEncabezado) / 2;

    int mayorPuntaje = puntajes[0], indiceGanador = 0;
    for(int i=0; i<cantidadJugadores; i++){
        if(puntajes[i] > mayorPuntaje){
            mayorPuntaje = puntajes[i];
            indiceGanador = i;
        }
    }

    rlutil::locate(posXEncabezado, posYEncabezado - 4);
    rlutil::setBackgroundColor(rlutil::BLACK);
    cout << "FIN DEL JUEGO";
    rlutil::setBackgroundColor(rlutil::LIGHTBLUE);

    rlutil::locate(posXEncabezado, posYEncabezado - 2);
    rlutil::setBackgroundColor(rlutil::BLACK);
    cout << "Resultados";
    rlutil::setBackgroundColor(rlutil::LIGHTBLUE);

    rlutil::locate(posXEncabezado, posYEncabezado - 1);
    cout << "Jugador";

    rlutil::locate(posXEncabezado + 20, posYEncabezado - 1);
    cout  << "|" << "Puntaje";

    rlutil::locate(posXEncabezado, posYEncabezado);
    cout << "----------------------------";

    for(int i = 0, h = 1; i < cantidadJugadores; i++, h += 2) {
        if(i == indiceGanador) {
            rlutil::setBackgroundColor(rlutil::GREEN);
        }
        rlutil::locate(posXEncabezado, posYEncabezado + h);
        cout << nombres[i];

        rlutil::locate(posXEncabezado + 20, posYEncabezado + h);
        cout << "|" << puntajes[i];

        rlutil::setBackgroundColor(rlutil::LIGHTBLUE);

        rlutil::locate(posXEncabezado, posYEncabezado+ h + 1);
        cout << "----------------------------";
    }
}

int imprimirEncabezado(int nroRonda, string jugador, int puntosTotales, int puntosRonda, int bloqueadores[], int cantidadBloqueadores) {
    rlutil::setColor(rlutil::WHITE);
    const int anchoPantalla = rlutil::tcols(), altoPantalla = rlutil::trows();
    const int anchoEncabezado = 66, altoEncabezado = 5;
    int posXEncabezado = (anchoPantalla - anchoEncabezado) / 2,
        posYEncabezado = (altoPantalla - altoEncabezado) / 6;


    rlutil::locate(posXEncabezado, posYEncabezado);
    rlutil::setBackgroundColor(rlutil::BLUE);
    cout << "Ronda " << nroRonda << " [" << jugador << "]";
    rlutil::setBackgroundColor(rlutil::LIGHTBLUE);

    rlutil::locate(posXEncabezado, posYEncabezado + 1);
    cout << "Puntos Totales";

    rlutil::locate(posXEncabezado, posYEncabezado + 2);
    cout << "Puntos Ronda";

    rlutil::locate(posXEncabezado + 16, posYEncabezado + 1);
    cout << puntosTotales;

    rlutil::locate(posXEncabezado + 16, posYEncabezado + 2);
    cout << puntosRonda << '\0';

    rlutil::locate(posXEncabezado, posYEncabezado + 4);
    cout << "Bloqueadores |";
    for(int i = 0; i < cantidadBloqueadores; i++) {
        cout << " ";
        // imprimirDado(bloqueadores[i]);
        cout << bloqueadores[i];
        cout << " |";
    }

    return posYEncabezado + 6;
}

char imprimirTabla(int posY, int nroTirada, int dados[], int cantidadDados, int cantidadTotal, int bloqueadores[], int cantidadBloqueadores, int puntos, int estado) {
    rlutil::setColor(rlutil::WHITE);
    char seguirJugando = '\0';
    const int anchoPantalla = rlutil::tcols(),
              anchoEncabezado = 66, altoEncabezado = 5;
    int posXEncabezado = (anchoPantalla - anchoEncabezado) / 2;

    if(nroTirada < 2) {
        int auxPosXEncabezado = posXEncabezado;
        rlutil::locate(auxPosXEncabezado, posY);
        cout << "Tirada";

        auxPosXEncabezado += 25;
        rlutil::locate(auxPosXEncabezado , posY);
        cout << "Suma";

        auxPosXEncabezado += 11;
        rlutil::locate(auxPosXEncabezado, posY);
        cout << "Seguir Jugando? (s/n)";
    }

    int auxPosXFila = posXEncabezado;

    rlutil::locate(auxPosXFila, posY + 2);
    cout << "#" << nroTirada;
    auxPosXFila += 4;
    rlutil::locate(auxPosXFila, posY + 2);

    for(int i = 0, j = 0; i < cantidadTotal; i++) {
        if(i == 0) {
            auxPosXFila += 1;
            rlutil::locate(auxPosXFila, posY + 2);
            cout << "|";
        }

        auxPosXFila += 1;
        if(j < cantidadDados) {
            rlutil::locate(auxPosXFila, posY + 2);
            if(estaBloqueado(dados[j], bloqueadores, cantidadBloqueadores)) {
                rlutil::setColor(rlutil::RED);
            } else if(estado == 2) {
                rlutil::setColor(rlutil::BLACK);
            }
            // imprimirDado(dados[j]);
            cout << dados[j];
            j++;
            rlutil::setColor(rlutil::WHITE);
        }

        auxPosXFila += 1;
        rlutil::locate(auxPosXFila, posY + 2);
        cout << "|";
    }

    rlutil::locate(posXEncabezado + 25, posY + 2);
    cout << puntos;

    rlutil::locate(posXEncabezado + 36, posY + 2);

    if(estado == 0) {
        cout << "n";
        seguirJugando = 'n';
    } else if(estado == 2) {
        cout << "s";
        seguirJugando = 's';
    } else if(estado == 1 && cantidadDados > 0) {
        do {
            cin >> seguirJugando;
            if((seguirJugando == 's'|| seguirJugando == 'S') || (seguirJugando == 'n' || seguirJugando == 'N')) {
                break;
            }
            rlutil::locate(posXEncabezado + 36, posY + 2);
        } while((seguirJugando != 's'|| seguirJugando != 'S') && (seguirJugando != 'n' || seguirJugando != 'N'));
    }
    rlutil::locate(posXEncabezado, posY + 4);
    return seguirJugando;
}

void imprimirDado(int nroDado) {
    string caraDados[6] = { "\u2680", "\u2681", "\u2682", "\u2683", "\u2684", "\u2685" };
    cout << caraDados[nroDado - 1];
}
