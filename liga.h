// Diego Antonio González Cortés

#ifndef LIGA_H
#define LIGA_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "equipo.h"  
using namespace std;

// =========================================================
// ===== ESTRUCTURA PARTIDO =====
// Representa un partido entre dos equipos, guardando los
// nombres y los goles que hizo cada uno.
// =========================================================
struct Partido {
    string local;          // Nombre del equipo local
    string visitante;      // Nombre del equipo visitante
    int golesLocal;        // Goles anotados por el local
    int golesVisitante;    // Goles anotados por el visitante
};


// ===== CLASE LIGA =====
// Controla todo el funcionamiento de la liga:
// - Carga los equipos desde un CSV
// - Simula las jornadas con resultados aleatorios
// - Guarda y muestra la tabla general
// - Permite reiniciar la liga

class Liga {
private:
    vector<Equipo> equipos;              // Lista de los 18 equipos
    vector<vector<Partido>> jornadas;    // Resultados de las 17 jornadas

public:
    // ===== CONSTRUCTOR =====
    // Al crear la liga, se cargan los equipos desde el CSV
    // y se inicializa el generador aleatorio.

    Liga() {
        srand((unsigned)time(0));  // Inicializa aleatoriedad
        cargarEquipos();
    }

    // ===== CARGAR EQUIPOS DESDE CSV =====
    // Lee los nombres de los equipos desde un archivo
    // llamado "equipos.csv" y los guarda en el vector.

    void cargarEquipos() {
        equipos.clear();
        ifstream archivo("equipos.csv");
        string linea;

        if (!archivo.is_open()) {
            cout << "Error: no se encontro el archivo equipos.csv" << endl;
            return;
        }

        while (getline(archivo, linea)) {
            if (linea.empty()) continue;      // Ignora líneas vacías
            equipos.push_back(Equipo(linea)); // Crea el objeto Equipo
        }
        archivo.close();
    }

    // ===== SIMULAR UNA JORNADA =====
    // Se emparejan los equipos de forma aleatoria y se
    // generan goles aleatorios entre 0 y 5.

    vector<Partido> simularJornada() {
        vector<Partido> jornada;
        vector<int> indices;

        // Crea una lista con los índices de los equipos
        for (int i = 0; i < equipos.size(); i++) indices.push_back(i);

        // Mezcla aleatoriamente los índices
        random_shuffle(indices.begin(), indices.end());

        // Empareja los equipos de 2 en 2
        for (int i = 0; i < 18; i += 2) {
            Partido p;
            p.local = equipos[indices[i]].getNombre();
            p.visitante = equipos[indices[i + 1]].getNombre();
            p.golesLocal = rand() % 6;
            p.golesVisitante = rand() % 6;

            // Actualiza las estadísticas de cada equipo
            equipos[indices[i]].actualizar(p.golesLocal, p.golesVisitante);
            equipos[indices[i + 1]].actualizar(p.golesVisitante, p.golesLocal);

            jornada.push_back(p);
        }

        return jornada;
    }

    // ===== SIMULAR TODA LA LIGA =====
    // Genera 17 jornadas completas, como en la Liga MX.

    void simularLiga() {
        jornadas.clear();
        reiniciarEstadisticas();
        for (int i = 0; i < 17; i++) {
            jornadas.push_back(simularJornada());
        }
    }

    // ===== MOSTRAR RESULTADOS DE UNA JORNADA =====
    // Muestra en pantalla los partidos y sus resultados
    // de la jornada seleccionada por el usuario.

    void mostrarJornada(int numJornada) {
        if (numJornada < 1 || numJornada > jornadas.size()) {
            cout << "Numero de jornada invalido." << endl;
            return;
        }

        cout << "\n===== RESULTADOS JORNADA " << numJornada << " =====" << endl;
        cout << left << setw(20) << "Local"
             << setw(6) << "Goles"
             << setw(20) << "Visitante"
             << setw(6) << "Goles" << endl;
        cout << string(52, '-') << endl;

        for (const auto& p : jornadas[numJornada - 1]) {
            cout << left << setw(20) << p.local
                 << setw(6) << p.golesLocal
                 << setw(20) << p.visitante
                 << setw(6) << p.golesVisitante << endl;
        }
    }

    // ===== MOSTRAR TABLA GENERAL =====
    // Ordena a los equipos por puntos, diferencia de goles
    // y goles a favor, y muestra la tabla completa.

    void mostrarTabla() {
        sort(equipos.begin(), equipos.end(), [](const Equipo& a, const Equipo& b) {
            if (a.getPuntos() != b.getPuntos()) return a.getPuntos() > b.getPuntos();
            if (a.getDiferencia() != b.getDiferencia()) return a.getDiferencia() > b.getDiferencia();
            if (a.getGolesFavor() != b.getGolesFavor()) return a.getGolesFavor() > b.getGolesFavor();
            return a.getNombre() < b.getNombre();
        });

        cout << "\n===== TABLA GENERAL =====" << endl;
        cout << left << setw(20) << "Equipo"
             << setw(8) << "Puntos"
             << setw(8) << "GF"
             << setw(8) << "GC"
             << setw(8) << "DG" << endl;
        cout << string(52, '-') << endl;

        for (const auto& e : equipos) {
            cout << left << setw(20) << e.getNombre()
                 << setw(8) << e.getPuntos()
                 << setw(8) << e.getGolesFavor()
                 << setw(8) << e.getGolesContra()
                 << setw(8) << e.getDiferencia() << endl;
        }
    }

    // ===== REINICIAR LIGA =====
    // Borra las jornadas jugadas y reinicia todas las
    // estadísticas de los equipos a cero.

    void reiniciarLiga() {
        reiniciarEstadisticas();
        jornadas.clear();
    }

private:
    // ===== REINICIAR ESTADISTICAS =====
    // Recorre todos los equipos y los deja como al inicio.

    void reiniciarEstadisticas() {
        for (auto& e : equipos) {
            e.reiniciar();
        }
    }
};

#endif
