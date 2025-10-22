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
using namespace std;

// =========================================================
// ===== CLASE EQUIPO =====
// Representa a un equipo con sus estadisticas
// =========================================================
class Equipo {
private:
    string nombre;
    int puntos;
    int golesFavor;
    int golesContra;
    int diferenciaGoles;

public:
    // ===== Constructor =====
    Equipo(string n = "") {
        nombre = n;
        puntos = 0;
        golesFavor = 0;
        golesContra = 0;
        diferenciaGoles = 0;
    }

    // ===== Getters =====
    string getNombre() const { return nombre; }
    int getPuntos() const { return puntos; }
    int getGolesFavor() const { return golesFavor; }
    int getGolesContra() const { return golesContra; }
    int getDiferenciaGoles() const { return diferenciaGoles; }

    // ===== Actualizar estadisticas =====
    void actualizar(int gf, int gc) {
        golesFavor += gf;
        golesContra += gc;
        diferenciaGoles = golesFavor - golesContra;

        if (gf > gc)
            puntos += 3; // victoria
        else if (gf == gc)
            puntos += 1; // empate
        // sin puntos en derrota
    }

    // ===== Reiniciar estadisticas =====
    void reiniciar() {
        puntos = 0;
        golesFavor = 0;
        golesContra = 0;
        diferenciaGoles = 0;
    }

    // ===== Comparador para ordenamiento =====
    bool operator<(const Equipo& otro) const {
        if (puntos != otro.puntos)
            return puntos > otro.puntos; // mas puntos primero
        if (diferenciaGoles != otro.diferenciaGoles)
            return diferenciaGoles > otro.diferenciaGoles; // mejor diferencia
        if (golesFavor != otro.golesFavor)
            return golesFavor > otro.golesFavor; // mas goles
        return nombre < otro.nombre; // alfabetico
    }
};

// =========================================================
// ===== ESTRUCTURA PARTIDO =====
// Representa un enfrentamiento entre dos equipos
// =========================================================
struct Partido {
    string local;
    string visitante;
    int golesLocal;
    int golesVisitante;
};

// =========================================================
// ===== CLASE LIGA =====
// Gestiona equipos, jornadas y resultados
// =========================================================
class Liga {
private:
    vector<Equipo> equipos;
    vector<vector<Partido>> jornadas;

public:
    // ===== Constructor =====
    Liga() {
        srand((unsigned)time(0));
        cargarEquipos();
    }

    // ===== Cargar equipos desde CSV =====
    void cargarEquipos() {
        equipos.clear();
        ifstream archivo("equipos.csv");
        string linea;

        if (!archivo.is_open()) {
            cout << "Error: no se encontro el archivo equipos.csv" << endl;
            return;
        }

        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            equipos.push_back(Equipo(linea));
        }
        archivo.close();
    }

    // ===== Simular una jornada completa =====
    vector<Partido> simularJornada() {
        vector<Partido> jornada;
        vector<int> indices;
        for (int i = 0; i < equipos.size(); i++) indices.push_back(i);
        random_shuffle(indices.begin(), indices.end());

        for (int i = 0; i < 18; i += 2) {
            Partido p;
            p.local = equipos[indices[i]].getNombre();
            p.visitante = equipos[indices[i + 1]].getNombre();
            p.golesLocal = rand() % 6;
            p.golesVisitante = rand() % 6;

            equipos[indices[i]].actualizar(p.golesLocal, p.golesVisitante);
            equipos[indices[i + 1]].actualizar(p.golesVisitante, p.golesLocal);

            jornada.push_back(p);
        }

        return jornada;
    }

    // ===== Simular toda la liga (17 jornadas) =====
    void simularLiga() {
        jornadas.clear();
        reiniciarEstadisticas();
        for (int i = 0; i < 17; i++) {
            jornadas.push_back(simularJornada());
        }
    }

    // ===== Mostrar resultados de una jornada =====
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

    // ===== Mostrar tabla general ordenada =====
    void mostrarTabla() {
        sort(equipos.begin(), equipos.end());

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
                 << setw(8) << e.getDiferenciaGoles() << endl;
        }
    }

    // ===== Reiniciar liga =====
    void reiniciarLiga() {
        reiniciarEstadisticas();
        jornadas.clear();
    }

private:
    // ===== Reiniciar estadisticas de todos los equipos =====
    void reiniciarEstadisticas() {
        for (auto& e : equipos) {
            e.reiniciar();
        }
    }
};

#endif
