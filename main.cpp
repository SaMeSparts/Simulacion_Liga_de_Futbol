#include <iostream>
#include <limits>
#include "liga.h"
using namespace std;

int main() {
    Liga liga; // Objeto principal
    bool programaActivo = true;
    int opcion = 0;

    while (programaActivo) {
        cout << "\n===== SIMULACION DE LIGA DE FUTBOL =====" << endl;
        cout << "1. Simular liga completa" << endl;
        cout << "2. Ver resultados de una jornada" << endl;
        cout << "3. Ver tabla general" << endl;
        cout << "4. Reiniciar liga" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            // Limpia la entrada si no es un numero
            cout << "\nEntrada invalida. Por favor ingrese un numero entre 1 y 5." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcion == 1) {
            liga.simularLiga();
            cout << "\nLiga simulada correctamente." << endl;
        } 
        else if (opcion == 2) {
            int jornada;
            cout << "\nIngrese el numero de jornada (1 - 17): ";
            if (!(cin >> jornada) || jornada < 1 || jornada > 17) {
                cout << "Numero de jornada invalido." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            liga.mostrarJornada(jornada);
        } 
        else if (opcion == 3) {
            liga.mostrarTabla();
        } 
        else if (opcion == 4) {
            liga.reiniciarLiga();
            cout << "\nLa liga ha sido reiniciada correctamente." << endl;
        } 
        else if (opcion == 5) {
            cout << "\nSaliendo del programa..." << endl;
            programaActivo = false; 
        } 
        else {
            cout << "\nOpcion invalida. Intente nuevamente." << endl;
        }
    }

    return 0;
}
