// Diego Antonio González Cortés

#include <iostream>
#include <limits>
#include "liga.h"
using namespace std;

int main() {
    // Creamos un objeto Liga, que se encarga de manejar los equipos y las jornadas.
    Liga liga; // Complejidad inicial: O(1)
    
    // Cargamos los equipos desde el archivo CSV a la lista ligada.
    // Esta carga recorre el archivo y agrega cada equipo al final de la lista.
    // Cada inserción cuesta O(1), así que todo el proceso es O(n).
    liga.cargarEquiposDesdeCSV("equipos.csv"); // Complejidad Total: O(n)

    bool programaActivo = true; // Controla si el programa sigue en ejecución.
    int opcion = 0; // Guarda la opción que el usuario selecciona en el menú.

    /*
    * == DESGLOSE DE COMPLEJIDAD SEGÚN LA OPCIÓN DEL MENÚ ==
    * El ciclo principal se repite hasta que el usuario elija salir.
    * Dependiendo de la opción seleccionada, cambia el costo:
    *
    * 1. Simular liga (Opción 1) – O(n²)
    *    Es la tarea más pesada porque genera todas las jornadas y partidos.
    *    También guardar los resultados en CSV implica procesar todos los datos.
    *
    * 2. Ver tabla general (Opción 2) – O(n log n)
    *    Copia los equipos a un vector (O(n)) y los ordena con std::sort,
    *    que garantiza O(n log n).
    *
    * 3. Ver jornada (Opción 3) – O(n)
    *    Accede rápidamente a la jornada y luego recorre los partidos de esa fecha,
    *    que son aproximadamente n/2.
    *
    * 4. Reiniciar liga (Opción 4) – O(n)
    *    Recorre la lista ligada para reiniciar los datos de cada equipo.
    *
    * 5. Salir (Opción 5) – O(1)
    *    Solo cambia un valor lógico para terminar el ciclo.
    */

    // Mientras el programa esté activo, el menú se sigue mostrando.
    while (programaActivo) {
        // Mostramos el menú al usuario.
        cout << "\n===== SIMULACION DE LIGA DE FUTBOL =====" << endl;
        cout << "1. Simular liga completa" << endl;
        cout << "2. Ver tabla general" << endl;
        cout << "3. Ver resultados de una jornada" << endl;
        cout << "4. Reiniciar liga" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";

        // Validación básica para evitar que el usuario ingrese letras u otros símbolos.
        if (!(cin >> opcion)) {
            cout << "\nEntrada invalida. Por favor ingrese un numero entre 1 y 5." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Opción 1: Simula toda la liga completa.
        if (opcion == 1) {
            liga.simularLiga();          // O(n²)
            liga.guardarResultadosCSV(); // O(n²)
            cout << "\nLiga simulada correctamente y resultados guardados." << endl;
        } 
        // Opción 2: Muestra la tabla general ordenada por puntos.
        else if (opcion == 2) {
            liga.mostrarTablaGeneral(); // O(n log n)
        } 
        // Opción 3: Muestra los resultados de una jornada específica.
        else if (opcion == 3) {
            int jornada;
            cout << "\nIngrese el numero de jornada (1 - 17): ";
            if (!(cin >> jornada) || jornada < 1 || jornada > 17) {
                cout << "Numero de jornada invalido." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            liga.mostrarJornada(jornada); // O(n)
        } 
        // Opción 4: Reinicia todas las estadísticas de la liga.
        else if (opcion == 4) {
            liga.reiniciarLiga(); // O(n)
            cout << "\nLa liga ha sido reiniciada correctamente." << endl;
        } 
        // Opción 5: Finaliza el programa.
        else if (opcion == 5) {
            cout << "\nSaliendo del programa..." << endl;
            programaActivo = false;
        } 
        // Cualquier número fuera del rango marcado se considera inválido.
        else {
            cout << "\nOpcion invalida. Intente nuevamente." << endl;
        }
    }

    return 0; // Fin del programa.
}
