// Diego Antonio Gonzalez Cortes
#ifndef LIGA_H
#define LIGA_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iomanip>   // Para setw y left
#include "equipo.h"
#include "partido.h"
using namespace std;

/*
 * == EXPLICACIÓN DE POR QUÉ SE ELIGIÓ ESTA ESTRUCTURA DE DATOS ==
 * Se decidió usar una Lista Doblemente Ligada para guardar los equipos.
 * La razón principal es la siguiente:
 *
 * Inserciones rápidas: Al cargar los equipos desde el archivo CSV,
 * cada elemento se agrega al final de la lista. Ese tipo de inserción
 * toma tiempo constante O(1), así que todo el proceso completo
 * termina siendo O(n). Es eficiente y directo.
 */

// Nodo para la lista doblemente ligada
struct Nodo {
    Equipo equipo;
    Nodo* siguiente;
    Nodo* anterior;
    Nodo(Equipo e) : equipo(e), siguiente(nullptr), anterior(nullptr) {}
};

// Clase liga donde se maneja todo
class Liga {
private:
    Nodo* cabeza;
    Nodo* cola;
    vector<vector<Partido>> jornadas;

public:
    // Constructor
    // Complejidad: O(1)
    Liga() {
        cabeza = nullptr;
        cola = nullptr;
        srand(time(0)); // Inicia aleatoriedad
    }

    // Destructor para liberar memoria
    // Complejidad: O(n)
    ~Liga() {
        Nodo* temp = cabeza;
        while(temp) {
            Nodo* next = temp->siguiente;
            delete temp;
            temp = next;
        }
    }

    // Carga los equipos desde un archivo CSV
    // Complejidad: O(n)
    void cargarEquiposDesdeCSV(const string& archivo) {
        ifstream file(archivo);
        string nombre;
        while (getline(file, nombre)) {
            if (nombre.empty()) continue;
            insertarEquipo(Equipo(nombre));
        }
        file.close();
    }
    // Inserta un equipo al final de la lista doblemente ligada.
    // La operación siempre se hace usando el puntero 'cola', por eso:
    // - Mejor caso: O(1)
    // - Caso promedio: O(1)
    // - Peor caso: O(1)
    // La inserción al final es constante en todos los escenarios.


    // Inserta un equipo al final de la lista doblemente ligada
    // Complejidad: O(1)
    void insertarEquipo(const Equipo& e) {
        Nodo* nuevo = new Nodo(e);
        if (!cabeza) {
            cabeza = cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
        }
    }

    // Reinicia los datos de todos los equipos.
// Esta operación siempre requiere recorrer los 'n' nodos de la lista,
// por lo que su complejidad es:
// - Mejor caso: O(n)
// - Caso promedio: O(n)
// - Peor caso: O(n)


    // Reinicia los datos de todos los equipos
    // Complejidad: O(n)
    void reiniciarLiga() {
        Nodo* temp = cabeza;
        while (temp) {
            temp->equipo.reiniciar();
            temp = temp->siguiente;
        }
        jornadas.clear();
    }

    // Simula toda la liga completa (17 jornadas)
    // Complejidad: O(n²)
    void simularLiga() {
        vector<Nodo*> equipos;
        Nodo* temp = cabeza;
        while (temp) {
            equipos.push_back(temp);
            temp = temp->siguiente;
        }

        int numEquipos = equipos.size();

        for (int j = 0; j < numEquipos - 1; j++) {
            vector<Partido> jornada;
            for (int i = 0; i < numEquipos / 2; i++) {
                string local = equipos[i]->equipo.getNombre();
                string visitante = equipos[numEquipos - 1 - i]->equipo.getNombre();

                Partido p(local, visitante);
                p.simular();
                jornada.push_back(p);

                // Actualiza los equipos segun los goles
                equipos[i]->equipo.actualizar(p.getGolesLocal(), p.getGolesVisitante());
                equipos[numEquipos - 1 - i]->equipo.actualizar(p.getGolesVisitante(), p.getGolesLocal());
            }

            jornadas.push_back(jornada);
            // Rota los equipos para el siguiente enfrentamiento
            rotate(equipos.begin() + 1, equipos.begin() + 2, equipos.end());
        }
    }

    // Muestra los partidos de una jornada
    // Complejidad: O(n)
    void mostrarJornada(int n) const {
        if (n < 1 || n > (int)jornadas.size()) {
            cout << "numero de jornada invalido\n";
            return;
        }
        cout << "\n=== resultados de la jornada " << n << " ===\n";
        for (const auto& p : jornadas[n - 1]) {
            cout << p.mostrarResultado() << endl;
        }
    }
    /*
    * == EXPLICACIÓN DE POR QUÉ SE ELIGIÓ ESTE MÉTODO DE ORDENAMIENTO ==
    * Para ordenar los datos, se decidió usar std::sort (que internamente usa Introsort)
    * aplicado sobre un vector temporal. La elección se basa en puntos prácticos:
    *
    * 1. Es muy rápido: std::sort está altamente optimizado y normalmente trabaja
    *    en O(n log n).
    *
    * 2. Maneja bien los peores casos: a diferencia de un Quicksort común, que puede
    *    volverse muy lento en ciertas situaciones, Introsort detecta eso a tiempo
    *    y cambia a Heapsort, manteniendo un tiempo garantizado de O(n log n).
    *
    * 3. Es más sencillo y seguro: ordenar directamente una lista ligada con un 
    *    algoritmo avanzado (como MergeSort) es más complicado y fácil de equivocarse.
    *    En cambio, pasar los datos a un vector y usar std::sort es más limpio,
    *    más fácil de implementar y usa una función ya optimizada por la STL.
    */

    /*
    * == ANÁLISIS DE COMPLEJIDAD (Introsort) ==
    * std::sort usa Introsort, un algoritmo híbrido que combina varias técnicas
    * para mantener buen rendimiento en todo tipo de casos. Su funcionamiento es así:
    *
    * 1. Comienza usando Quicksort, que es muy rápido en la mayoría de situaciones.
    * 2. Si detecta que la profundidad de recursión se hace muy grande (señal de que
    *    podría caer en el peor caso O(n²)), cambia automáticamente a Heapsort,
    *    asegurando que todo se mantenga en O(n log n).
    * 3. Cuando las partes a ordenar son pequeñas, usa Insertion Sort, que es más
    *    eficiente en esos tamaños.
    *
    * Gracias a esta combinación, el algoritmo logra:
    * - Mejor caso: O(n log n)
    * - Caso promedio: O(n log n)
    * - Peor caso: O(n log n)
    */


    // Muestra la tabla general ordenada
    // Complejidad: O(n log n)
    void mostrarTablaGeneral() {
        vector<Equipo> tabla;
        Nodo* temp = cabeza;
        while (temp) {
            tabla.push_back(temp->equipo);
            temp = temp->siguiente;
        }

        // Ordena usando std::sort (introsort)
        sort(tabla.begin(), tabla.end(), [](const Equipo& a, const Equipo& b) {
            if (a.getPuntos() != b.getPuntos()) return a.getPuntos() > b.getPuntos();
            if (a.getDiferencia() != b.getDiferencia()) return a.getDiferencia() > b.getDiferencia();
            if (a.getGolesFavor() != b.getGolesFavor()) return a.getGolesFavor() > b.getGolesFavor();
            return a.getNombre() < b.getNombre();
        });

        // Encabezado de la tabla
        cout << "\n=== TABLA GENERAL ===\n";
        cout << left << setw(4) << "POS" 
             << setw(20) << "EQUIPO"
             << setw(6) << "PTS"
             << setw(6) << "GF"
             << setw(6) << "GC"
             << setw(6) << "DG" << endl;
        cout << string(48, '-') << endl;

        // Imprime cada equipo con sus datos alineados
        int pos = 1;
        for (auto& e : tabla) {
            cout << left << setw(4) << pos++
                 << setw(20) << e.getNombre()
                 << setw(6) << e.getPuntos()
                 << setw(6) << e.getGolesFavor()
                 << setw(6) << e.getGolesContra()
                 << setw(6) << e.getDiferencia() << endl;
        }

        // Guardamos en CSV
        guardarTablaCSV(tabla);
    }

    // Guarda la tabla general en CSV
    // Complejidad: O(n)
    void guardarTablaCSV(const vector<Equipo>& tabla) const {
        ofstream file("tabla_general.csv");
        file << "equipo,puntos,golesFavor,golesContra,diferencia\n";
        for (auto& e : tabla) {
            file << e.toCSV() << endl;
        }
        file.close();
    }

    // Guarda los resultados en CSV
    // Complejidad: O(n²)
    void guardarResultadosCSV() const {
        ofstream file("resultados.csv");
        file << "jornada,local,visitante,golesLocal,golesVisitante\n";
        for (size_t i = 0; i < jornadas.size(); i++) {
            for (const auto& p : jornadas[i]) {
                file << (i + 1) << "," << p.toCSV() << endl;
            }
        }
        file.close();
    }
};

#endif
