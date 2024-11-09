#include "dosJugadores.h"

int calcularPuntaje(int vDados[], int cantidad, int bloqueadores[], int cantidadBloqueadores){
    int puntos=0, repetidoDuplica=0, cantidadBloqueados=0;
    for(int i=0; i<cantidad; i++){
        if(!estaBloqueado(vDados[i], bloqueadores, cantidadBloqueadores)) { //!false = true
            puntos+=vDados[i];
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
        puntos = 0;
    }
    else if(repetidoDuplica == cantidad) {
        // Doble puntaje rep
        puntos = puntos * 2;
    }
    return puntos;
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
    //string caraDados[6] = { "\u2680", "\u2681", "\u2682", "\u2683", "\u2684", "\u2685" };
    string caraDados[6] = {"1", "2", "3", "4", "5", "6"};
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
                    //Index  0           1        2         3          4         5
    //string caraDados[6] = { "\u2680", "\u2681", "\u2682", "\u2683", "\u2684", "\u2685" };
    string caraDados[6] = {"1", "2", "3", "4", "5", "6"};
                    //Dado    1          2          3       4         5           6
    for(int i=0; i<cantidad; i++){
        cout<<" "<<caraDados[vDados[i] - 1];
    }
}

string ingresarNombre(){
    string nombre;
    cout<<"Ingrese su nombre: ";
    rlutil::setColor(rlutil::BLUE);
    cin>>nombre;
    return nombre;
}

//int unJugador(string nombres[], int puntajes[], int cantidadJugadores)
// devuelve el indice del ganador
void dosJugadores(){
    const int CANTIDAD_DADOS = 5, CANTIDAD_BLOQUEADORES = 2;
    int dados[CANTIDAD_DADOS], puntosTotales = 0;
    char seguirJugando = 's';
    int ronda = 1;
    int tirada = 1;
    string nombre;

    cout<<endl;
    nombre=ingresarNombre();
    system("cls");

    while(true){
        int cantidadDadosActual = CANTIDAD_DADOS, puntajeRonda = 0;
        int bloqueadores[CANTIDAD_BLOQUEADORES] = { 0 };
        rlutil::setColor(rlutil::WHITE);
        cout << "       RONDA " << ronda << endl;
        cout << "----------------------";
        cout << endl << endl;
        cout << "Turno de: ";
        rlutil::setColor(rlutil::BLUE);
        cout<<nombre;
        rlutil::setColor(rlutil::WHITE);
        cout<<endl<<endl;
        cout<<"----------------------";
        cout<<endl<<endl;

        tiradaBloqueadores(bloqueadores, CANTIDAD_BLOQUEADORES);
        cout<<"Bloqueadores:";
        mostrarBloqueadores(bloqueadores, CANTIDAD_BLOQUEADORES);
        cout<<endl<<endl;

        do{
            int puntajeTirada = 0;
            tiradaDeDados(dados, cantidadDadosActual);
            cout<<"Tirada #"<<tirada<<": ";
            mostrarDados(dados, cantidadDadosActual, bloqueadores, CANTIDAD_BLOQUEADORES);
            cout<<endl<<endl;
            cout<<"----------------------";
            cout<<endl<<endl;

            puntajeTirada = calcularPuntaje(dados, cantidadDadosActual, bloqueadores, CANTIDAD_BLOQUEADORES);
            cantidadDadosActual = removerBloqueados(dados, cantidadDadosActual, bloqueadores, CANTIDAD_BLOQUEADORES);

            if(puntajeTirada != 0) {
                puntajeRonda += puntajeTirada;
            } else {
                puntajeRonda = 0;
            }
            cout<<"Puntos Tirada: "<<puntajeRonda;
            cout<<endl<<endl;

            cout<<"Desea seguir jugando en esta ronda? (s/n): ";
            cin>>seguirJugando;
            cout<<endl;
            cout<<"----------------------";

            if (seguirJugando == 's' || seguirJugando == 'S'){
                tirada++;
                cout<<endl<<endl;
            }
            //cantidad > 0
        } while (seguirJugando == 's' || seguirJugando == 'S');


        if (seguirJugando == 'n' || seguirJugando == 'N'){
            ronda++;
            tirada = 1;
            system("cls");
        }

        puntosTotales += puntajeRonda;
        cout<<"Puntos totales: "<<puntosTotales;
        cout<<endl<<endl;
    }
}
