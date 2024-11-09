#pragma once
#include <iostream>
#include <string>
#include "rlutil.h"

using namespace std;

void dosJugadores();
int tirarDado();
void tiradaDeDados(int vDados[], int cantidad);
void mostrarDados(int vDados[], int cantidad);
void tiradaBloqueadores(int vDados[], int cantidad);
void mostrarBloqueadores(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores);
bool estaBloqueado(int dado, int bloqueadores[], int cantidadBloqueadores);
int removerBloqueados(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores);
int calcularPuntaje(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores);
string ingresarNombre();

