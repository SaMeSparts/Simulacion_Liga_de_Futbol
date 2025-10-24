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
    Liga() {
        cabeza = nullptr;
        cola = nullptr;
        srand(time(0)); // Inicia aleatoriedad
    }

    // Destructor para liberar memoria
    ~Liga() {
        Nodo* temp = cabeza;
        while(temp) {
            Nodo* next = temp->siguiente;
            delete temp;
            temp = next;
        }
    }

    // Carga los equipos desde un archivo CSV
    void cargarEquiposDesdeCSV(const string& archivo) {
        ifstream file(archivo);
        string nombre;
        while (getline(file, nombre)) {
            if (nombre.empty()) continue;
            insertarEquipo(Equipo(nombre));
        }
        file.close();
    }

    // Inserta un equipo al final de la lista doblemente ligada
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
    void reiniciarLiga() {
        Nodo* temp = cabeza;
        while (temp) {
            temp->equipo.reiniciar();
            temp = temp->siguiente;
        }
        jornadas.clear();
    }

    // Simula toda la liga completa (17 jornadas)
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

    // Muestra la tabla general ordenada (formato bonito como antes)
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
    void guardarTablaCSV(const vector<Equipo>& tabla) const {
        ofstream file("tabla_general.csv");
        file << "equipo,puntos,golesFavor,golesContra,diferencia\n";
        for (auto& e : tabla) {
            file << e.toCSV() << endl;
        }
        file.close();
    }

    // Guarda los resultados en CSV
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
