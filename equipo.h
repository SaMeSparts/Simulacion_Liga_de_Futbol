#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <string>
using namespace std;

// ===== CLASE EQUIPO =====
class Equipo {
private:
    string nombre;
    int puntos;
    int golesFavor;
    int golesContra;
    int diferenciaGoles;

public:
    // ===== CONSTRUCTOR =====
    Equipo(string n = "") {
        nombre = n;
        puntos = 0;
        golesFavor = 0;
        golesContra = 0;
        diferenciaGoles = 0;
    }

    // ===== GETTERS =====
    string getNombre() const { return nombre; }
    int getPuntos() const { return puntos; }
    int getGolesFavor() const { return golesFavor; }
    int getGolesContra() const { return golesContra; }
    int getDiferencia() const { return diferenciaGoles; }

    // ===== REINICIAR ESTADÍSTICAS =====
    void reiniciar() {
        puntos = 0;
        golesFavor = 0;
        golesContra = 0;
        diferenciaGoles = 0;
    }

    // ===== ACTUALIZAR RESULTADO DE PARTIDO =====
    void actualizar(int gf, int gc) {
        golesFavor += gf;
        golesContra += gc;
        diferenciaGoles = golesFavor - golesContra;

        if (gf > gc) puntos += 3;
        else if (gf == gc) puntos += 1;
    }

    // ===== FORMATO PARA GUARDAR EN CSV =====
    string toCSV() const {
        return nombre + "," + to_string(puntos) + "," +
               to_string(golesFavor) + "," +
               to_string(golesContra) + "," +
               to_string(diferenciaGoles);
    }
};

#endif
