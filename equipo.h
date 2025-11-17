// Diego Antonio González Cortés

#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <string>
using namespace std;

// Clase que representa a un equipo con toda su información
// Todas las operaciones son O(1) porque solo trabajan con datos propios.
class Equipo {
private:
    string nombre;
    int puntos;
    int golesFavor;
    int golesContra;
    int diferenciaGoles;

public:
    // Crea un equipo nuevo con todo en 0
    // Complejidad: O(1)
    Equipo(string n = "") {
        nombre = n;
        puntos = 0;
        golesFavor = 0;
        golesContra = 0;
        diferenciaGoles = 0;
    }

    // Devuelve los datos del equipo
    // Complejidad: O(1)
    string getNombre() const { return nombre; }
    int getPuntos() const { return puntos; }
    int getGolesFavor() const { return golesFavor; }
    int getGolesContra() const { return golesContra; }
    int getDiferencia() const { return diferenciaGoles; }

    // Regresa al equipo a su estado inicial (todo en 0)
    // Complejidad: O(1)
    void reiniciar() {
        puntos = 0;
        golesFavor = 0;
        golesContra = 0;
        diferenciaGoles = 0;
    }

    // Actualiza los datos del equipo después de un partido
    // Suma goles y asigna puntos según el resultado
    // Complejidad: O(1)
    void actualizar(int gf, int gc) {
        golesFavor += gf;
        golesContra += gc;
        diferenciaGoles = golesFavor - golesContra;

        if (gf > gc) {
            puntos += 3;  // gana
        } else if (gf == gc) {
            puntos += 1;  // empate
        }
        // si pierde no suma puntos
    }

    // Devuelve los datos del equipo en formato CSV
    // Complejidad: O(1)
    string toCSV() const {
        return nombre + "," + to_string(puntos) + "," +
               to_string(golesFavor) + "," +
               to_string(golesContra) + "," +
               to_string(diferenciaGoles);
    }
};

#endif
