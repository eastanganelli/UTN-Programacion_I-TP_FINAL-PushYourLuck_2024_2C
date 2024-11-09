#pragma once
#include <iostream>
#include "rlutil.h"
#include "juego.h"
#include "estadistica.h"
#include "creditos.h"

using namespace std;

int seleccionarOpcion();

int ejecutarOpcion(int opcion, string nombres[], int puntajes[], string jugadorMejorPuntaje, int mejorPuntaje);

void modalMensaje(string titulo, string msj, int tipo);
