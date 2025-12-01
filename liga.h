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
            cout << "Numero de jornada invalido (debe simular la liga primero).\n";
            return;
        }
        cout << "\n=== Resultados de la jornada " << n << " ===\n";
        for (const auto& p : jornadas[n - 1]) {
            cout << p.mostrarResultado() << endl;
        }
    }

    // Mecanismo de consulta de información en la Lista
    // Busca un equipo por nombre recorriendo la lista nodo por nodo.
    // Complejidad: O(n) (Búsqueda Lineal)
    Equipo* consultarEquipo(const string& nombreBuscado) {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->equipo.getNombre() == nombreBuscado) {
                return &(actual->equipo); // Retorna puntero al equipo encontrado
            }
            actual = actual->siguiente;
        }
        return nullptr; // Retorna null si no existe
    }

    /*
     * == ANÁLISIS DE COMPLEJIDAD DE MOSTRAR TABLA ==
     * Esta función realiza tres etapas principales:
     * * 1. Copiado de datos (Lista -> Vector): Se recorre la lista completa para 
     * pasar los datos a un vector temporal. Esto tiene un costo de O(n).
     * * 2. Ordenamiento (std::sort - Introsort): Se ordena el vector.
     * - Introsort garantiza O(n log n) en el peor caso combinando Quicksort,
     * Heapsort e Insertion Sort.
     * * 3. Impresión: Se recorre el vector ordenado para mostrar datos. Costo O(n).
     * * == COMPLEJIDAD FINAL ==
     * T(n) = O(n) [copia] + O(n log n) [sort] + O(n) [impresión]
     * Simplificando términos menores, la complejidad asintótica dominante es:
     * O(n log n)
     */
    void mostrarTablaGeneral() {
        vector<Equipo> tabla;
        Nodo* temp = cabeza;
        
        // Copia de Lista a Vector -> O(n)
        while (temp) {
            tabla.push_back(temp->equipo);
            temp = temp->siguiente;
        }

        // Ordenamiento -> O(n log n)
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

        // Imprime cada equipo -> O(n)
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
