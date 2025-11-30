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
     * Es la tarea más pesada porque genera todas las jornadas y partidos.
     *
     * 2. Ver tabla general (Opción 2) – O(n log n)
     * Implica copiar lista a vector (O(n)) y ordenar (O(n log n)).
     *
     * 3. Ver jornada (Opción 3) – O(n)
     * Accede y recorre los partidos de esa fecha.
     * * 4. Consultar equipo (Opción 4) - O(n)
     * Realiza una búsqueda lineal en la lista ligada para encontrar al equipo.
     *
     * 5. Reiniciar liga (Opción 5) – O(n)
     * Recorre la lista ligada para reiniciar los datos de cada equipo.
     *
     * 6. Salir (Opción 6) – O(1)
     */

    // Mientras el programa esté activo, el menú se sigue mostrando.
    while (programaActivo) {
        // Mostramos el menú al usuario.
        cout << "\n===== SIMULACION DE LIGA DE FUTBOL =====" << endl;
        cout << "1. Simular liga completa" << endl;
        cout << "2. Ver tabla general" << endl;
        cout << "3. Ver resultados de una jornada" << endl;
        cout << "4. Consultar estadisticas de un equipo" << endl; // NUEVA OPCION
        cout << "5. Reiniciar liga" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";

        // Validación básica para evitar que el usuario ingrese letras u otros símbolos.
        if (!(cin >> opcion)) {
            cout << "\nEntrada invalida. Por favor ingrese un numero entre 1 y 6." << endl;
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
        // Opción 4: [NUEVA] Consulta datos de un equipo específico
        else if (opcion == 4) {
            string nombreBuscado;
            cout << "\nIngrese el nombre del equipo (Tal cual aparece en la lista): ";
            cin.ignore(); // Limpiar el buffer del enter anterior
            getline(cin, nombreBuscado);

            // Llamamos a la función de búsqueda de la lista
            Equipo* e = liga.consultarEquipo(nombreBuscado);

            if (e != nullptr) {
                cout << "\n=== ESTADISTICAS DE: " << e->getNombre() << " ===" << endl;
                cout << "Puntos:          " << e->getPuntos() << endl;
                cout << "Goles a Favor:   " << e->getGolesFavor() << endl;
                cout << "Goles en Contra: " << e->getGolesContra() << endl;
                cout << "Diferencia:      " << e->getDiferencia() << endl;
            } else {
                cout << "\nError: No se encontro al equipo '" << nombreBuscado << "'." << endl;
            }
        }
        // Opción 5: Reinicia todas las estadísticas de la liga.
        else if (opcion == 5) {
            liga.reiniciarLiga(); // O(n)
            cout << "\nLa liga ha sido reiniciada correctamente." << endl;
        } 
        // Opción 6: Finaliza el programa.
        else if (opcion == 6) {
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