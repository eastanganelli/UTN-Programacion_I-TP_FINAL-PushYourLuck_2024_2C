#include "juego.h"

/*
 * Calcula el puntaje de una tirada de dados.
 * Recibe un listado de dados y la cantidad de mismos.
 * Tambien recibe el listado de bloqueadores y la cantidad.
 * Retorna un entero con el puntaje de la tirada sin sumar los bloqueados.
*/
int calcularPuntaje(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores){
    int puntos=0, repetidoDuplica=0, cantidadBloqueados=0;

    for(int i=0; i<cantidad; i++){
        if(!estaBloqueado(vDados[i], bloqueadores, cantidadBloqueadores)) {
            puntos+=vDados[i];
        }
    }

    return puntos;
}

/*
 * Calcula el multiplicador de la tirada.
 * Recibe un listado de dados y la cantidad de mismo,
 * un listado de bloqueadores y la cantidad de mismos, y
 * retorna un entero con el multiplicador.
 * 0: Se bloquearon todos los dados.
 * 1: No hay repetidos.
 * 2: Todos los dados son iguales.
*/
int duplicaOpierde(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores) {
    int multiplicador = 1, repetidoDuplica = 0, cantidadBloqueados = 0;
    for(int i=0; i<cantidad; i++){
        if(!estaBloqueado(vDados[i], bloqueadores, cantidadBloqueadores)) {
            if(i > 0 && vDados[i] == vDados[i-1]) {
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
        multiplicador = 0;
    }
    else if(repetidoDuplica == cantidad) {
        multiplicador = 2;
    }

    return multiplicador;
}

/*
 * Remueve los dados bloqueados.
 * Recibe un listado de dados y la cantidad de mismos,
 * un listado de bloqueadores y la cantidad de mismos, y
 * retorna la cantidad de dados actuales.
*/
int removerBloqueados(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores) {
    int removidosDados = cantidad;
    for(int i=0; i<cantidad; i++){
        if(estaBloqueado(vDados[i], bloqueadores, cantidadBloqueadores)) {
            removidosDados--;
        }
    }
    return removidosDados;
}

/*
 * Verifica si un dado esta bloqueado.
 * Recibe el dado a verificar y
 * el listado y la cantidad de bloqueadores.
*/
bool estaBloqueado(int dado, int bloqueadores[], int cantidadBloqueadores) {
    for(int j=0; j<cantidadBloqueadores; j++){
        if(dado ==  bloqueadores[j]) {
            return true;
        }
    }
    return false;
}

/*
 * Genera un dado.
*/
int tirarDado() { return rand() % 6 + 1; }

/*
 * Realiza la tirada de dados.
*/
void tiradaDeDados(int vDados[], int cantidad){
    for(int i=0; i<cantidad; i++){
        vDados[i] = tirarDado();
    }
}

/*
 * Realiza la tirada de dados bloqueadores.
*/
void tiradaBloqueadores(int vDados[], int cantidad){
    for(int i=0; i<cantidad; i++){
        vDados[i] = tirarDado();
    }
}

/*
 * Carga los nombres de los jugadores segun la cantidad.
 * Verifica si es un jugador o multijugador o jugador vs bot.
*/
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

/*
 * Genera el ingreso del nombre del jugador.
*/
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
    cin >> nombre;
    rlutil::setColor(rlutil::WHITE);
    return nombre;
}

/*
 * Inicia el juego.
 * Recibe los nombres, los puntajes y la cantidad de jugadores.
 * Inicia el juego y recorre las rondas.
 * Imprime el encabezado y la tabla.
 * Realiza las tiradas y calcula los puntajes.
 * Actualiza los puntajes.
*/
void juego(string nombres[], int puntajes[], int cantidadJugadores) {
    const int CANTIDAD_RONDAS = 6, CANTIDAD_DADOS = 5, CANTIDAD_BLOQUEADORES = 2;
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

/*
 * Informa el jugador ganador.
 * Recibe los nombres, los puntajes y la cantidad de jugadores.
 * Imprime el encabezado y los resultados.
 * Imprime el nombre del jugador ganador en verde.
*/
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

/*
 * Imprime el encabezado de la ronda.
 * Recibe el numero de ronda, el nombre del jugador, los puntos totales,
 * los puntos de la ronda, los bloqueadores y la cantidad de bloqueadores.
 * Retorna la posicion en Y.
*/
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

/*
 * Imprime la tabla de los dados.
 * Recibe la posicion en Y, el numero de tirada, los dados,
 * la cantidad de dados, la cantidad total de dados, los bloqueadores,
 * la cantidad de bloqueadores, los puntos y el estado.
 * Retorna un char con la respuesta del jugador.
 * s: Sigue jugando.
 * n: No sigue jugando.
 * Si el estado es 0, jugada bloqueada completa, imprime n.
 * Si el estado es 2, jugada duplicada y con tirada obligatoria, imprime s.
*/
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
                // Si esta bloqueado, imprime en rojo.
                // 0: Todos dados bloqueados.
                rlutil::setColor(rlutil::RED);
            } else if(estado == 2) {
                // Si es 2, imprime en Negro.
                // 2: Todos dados iguales.
                rlutil::setColor(rlutil::BLACK);
            }
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
        /*
         * Valida la respuesta del jugador.
         * Si la respuesta no es 's' o 'n', vuelve a pedir la respuesta.
        */
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
