#pragma once
#include <string>
#include <iostream>
#include "rlutil.h"

using namespace std;
using namespace std::string_literals;

void juego(string nombres[], int puntajes[], int cantidadJugadores);

void cargarJugadores(string nombres[], int cantidadJugadores);

void informarJugadorGanador(string nombres[], int puntajes[], int cantidadJugadores);

string ingresarNombre(bool soloJugador, int indice, int posX, int posY);

int tirarDado();

void tiradaDeDados(int vDados[], int cantidad);

void tiradaBloqueadores(int vDados[], int cantidad);

bool estaBloqueado(int dado, int bloqueadores[], int cantidadBloqueadores);

int removerBloqueados(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores);

int calcularPuntaje(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores);

int duplicaOpierde(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores);

int imprimirEncabezado(int nroRonda, string jugador, int puntosTotales, int puntosRonda, int bloqueadores[], int cantidadBloqueadores);

char imprimirTabla(int posY, int nroTirada, int dados[], int cantidadDados, int cantidadTotal, int bloqueadores[], int cantidadBloqueadores, int puntos, int estado);
