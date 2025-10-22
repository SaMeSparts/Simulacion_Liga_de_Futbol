// Diego Antonio González Cortés

#include <iostream>
#include <limits>
#include "liga.h"
using namespace std;

int main() {
    Liga liga; // Creamos un objeto de tipo Liga, que maneja todo el sistema de equipos y jornadas
    bool programaActivo = true; // Variable que controla si el programa sigue corriendo o termina
    int opcion = 0; // Aquí se guarda la opción que el usuario elige del menú

    // Mientras el programa esté activo, se repite el menú
    while (programaActivo) {
        // Mostramos las opciones disponibles
        cout << "\n===== SIMULACION DE LIGA DE FUTBOL =====" << endl;
        cout << "1. Simular liga completa" << endl;
        cout << "2. Ver resultados de una jornada" << endl;
        cout << "3. Ver tabla general" << endl;
        cout << "4. Reiniciar liga" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";

        // Validamos que el usuario escriba un número y no una letra u otro símbolo
        if (!(cin >> opcion)) {
            cout << "\nEntrada invalida. Por favor ingrese un numero entre 1 y 5." << endl;
            // Si la entrada no es válida, limpiamos el error y vaciamos el buffer de entrada
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Volvemos al inicio del ciclo sin hacer nada más
        }

        // Si el usuario elige la opción 1, se simula toda la liga
        if (opcion == 1) {
            liga.simularLiga();
            cout << "\nLiga simulada correctamente." << endl;
        } 
        // Si elige la opción 2, se muestran los resultados de una jornada específica
        else if (opcion == 2) {
            int jornada;
            cout << "\nIngrese el numero de jornada (1 - 17): ";
            // Se valida que el número esté dentro del rango correcto
            if (!(cin >> jornada) || jornada < 1 || jornada > 17) {
                cout << "Numero de jornada invalido." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue; // Si no es válido, se regresa al menú
            }
            liga.mostrarJornada(jornada); // Muestra los resultados de esa jornada
        } 
        // Si elige la opción 3, se muestra la tabla general ordenada
        else if (opcion == 3) {
            liga.mostrarTabla();
        } 
        // Si elige la opción 4, se reinician todas las estadísticas
        else if (opcion == 4) {
            liga.reiniciarLiga();
            cout << "\nLa liga ha sido reiniciada correctamente." << endl;
        } 
        // Si elige la opción 5, se sale del programa cambiando la variable de control
        else if (opcion == 5) {
            cout << "\nSaliendo del programa..." << endl;
            programaActivo = false; // Esto hace que el while termine
        } 
        // Si escribe cualquier otra cosa, se muestra un mensaje de error
        else {
            cout << "\nOpcion invalida. Intente nuevamente." << endl;
        }
    }

    return 0; // Fin del programa
}
