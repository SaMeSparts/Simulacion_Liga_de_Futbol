// Diego Antonio González Cortés

#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <string>
using namespace std;

// Clase equipo que guarda los datos de cada equipo
class Equipo {
private:
    string nombre;
    int puntos;
    int golesFavor;
    int golesContra;
    int diferenciaGoles;

public:
    // Constructor del equipo, inicia con todo en 0
    Equipo(string n = "") {
        nombre = n;
        puntos = 0;
        golesFavor = 0;
        golesContra = 0;
        diferenciaGoles = 0;
    }

    // Getters para acceder a los datos
    string getNombre() const { return nombre; }
    int getPuntos() const { return puntos; }
    int getGolesFavor() const { return golesFavor; }
    int getGolesContra() const { return golesContra; }
    int getDiferencia() const { return diferenciaGoles; }

    // Esta funcion pone todo en 0 para reiniciar el equipo
    void reiniciar() {
        puntos = 0;
        golesFavor = 0;
        golesContra = 0;
        diferenciaGoles = 0;
    }

    // Esta funcion actualiza los datos del equipo despues de un partido
    void actualizar(int gf, int gc) {
        golesFavor += gf;
        golesContra += gc;
        diferenciaGoles = golesFavor - golesContra;

        if (gf > gc) puntos += 3;   // si gana suma 3
        else if (gf == gc) puntos += 1; // si empata suma 1
    }

    // Sirve para guardar en formato csv
    string toCSV() const {
        return nombre + "," + to_string(puntos) + "," +
               to_string(golesFavor) + "," +
               to_string(golesContra) + "," +
               to_string(diferenciaGoles);
    }
};

#endif
