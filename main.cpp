// Diego Antonio González Cortés

#include <iostream>
#include <limits>
#include "liga.h"
using namespace std;

int main() {
    // Creamos un objeto de tipo Liga, que maneja todos los equipos y jornadas
    Liga liga; // Complejidad inicial: O(1)
    // Cargamos los equipos desde el CSV
    liga.cargarEquiposDesdeCSV("equipos.csv"); // Complejidad: O(n)

    bool programaActivo = true; // Variable que controla si el programa sigue corriendo
    int opcion = 0; // Aqui se guarda la opcion que el usuario elige del menu

    // Ciclo principal del menú
    // Complejidad: depende de las acciones del usuario
    // - Simular liga: O(n²)
    // - Mostrar tabla: O(n log n)
    // - Mostrar jornada: O(n)
    // - Reiniciar liga: O(n)

    // Mientras el programa este activo, se repite el menu
    while (programaActivo) {
        // Mostramos las opciones disponibles
        cout << "\n===== SIMULACION DE LIGA DE FUTBOL =====" << endl;
        cout << "1. Simular liga completa" << endl;
        cout << "2. Ver tabla general" << endl;
        cout << "3. Ver resultados de una jornada" << endl;
        cout << "4. Reiniciar liga" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";

        // Validamos que el usuario escriba un numero y no una letra u otro simbolo
        if (!(cin >> opcion)) {
            cout << "\nEntrada invalida. Por favor ingrese un numero entre 1 y 5." << endl;
            cin.clear(); // limpiamos el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // vaciamos el buffer de entrada
            continue; // volvemos al inicio del ciclo
        }

        // Si el usuario elige la opcion 1, se simula toda la liga
        if (opcion == 1) {
            // simulamos todas las jornadas
            liga.simularLiga();              // O(n²)
            // guardamos los resultados en CSV
            liga.guardarResultadosCSV();     // O(n²) 
            cout << "\nLiga simulada correctamente y resultados guardados." << endl;
        } 
        // Si elige la opcion 2, se muestra la tabla general ordenada
        else if (opcion == 2) {
            liga.mostrarTablaGeneral();     // O(n log n)
        } 
        // Si elige la opcion 3, se muestran los resultados de una jornada especifica
        else if (opcion == 3) {
            int jornada;
            cout << "\nIngrese el numero de jornada (1 - 17): ";
            if (!(cin >> jornada) || jornada < 1 || jornada > 17) {
                cout << "Numero de jornada invalido." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue; // regresamos al menu
            }
            // mostramos la jornada
            liga.mostrarJornada(jornada);   // O(n) 
        } 
        // Si elige la opcion 4, se reinician todas las estadisticas
        else if (opcion == 4) {
            liga.reiniciarLiga();           // O(n)
            cout << "\nLa liga ha sido reiniciada correctamente." << endl;
        } 
        // Si elige la opcion 5, se sale del programa
        else if (opcion == 5) {
            cout << "\nSaliendo del programa..." << endl;
            programaActivo = false; // cambia la variable para terminar el while
        } 
        // Si escribe cualquier otra cosa, se muestra mensaje de error
        else {
            cout << "\nOpcion invalida. Intente nuevamente." << endl;
        }
    }

    return 0; // Fin del programa
}
