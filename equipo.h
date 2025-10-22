// Diego Antonio González Cortés

#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <string>
using namespace std;


// ===== CLASE EQUIPO =====
// Esta clase representa a un equipo de fútbol.
// Guarda su nombre y todas sus estadísticas de la temporada.

class Equipo {
private:
    string nombre;         // Nombre del equipo
    int puntos;            // Puntos totales obtenidos
    int golesFavor;        // Goles anotados
    int golesContra;       // Goles recibidos
    int diferenciaGoles;   // GolesFavor - GolesContra

public:
    // ===== CONSTRUCTOR =====
    // Crea un equipo con su nombre y estadísticas inicializadas en cero.
    Equipo(string n = "") {
        nombre = n;
        puntos = 0;
        golesFavor = 0;
        golesContra = 0;
        diferenciaGoles = 0;
    }

    // ===== GETTERS =====
    // Devuelven los datos del equipo (sin permitir modificarlos).
    string getNombre() const { return nombre; }
    int getPuntos() const { return puntos; }
    int getGolesFavor() const { return golesFavor; }
    int getGolesContra() const { return golesContra; }
    int getDiferencia() const { return diferenciaGoles; }

    // ===== REINICIAR ESTADÍSTICAS =====
    // Deja todos los valores en cero, como si comenzara una nueva temporada.
    void reiniciar() {
        puntos = 0;
        golesFavor = 0;
        golesContra = 0;
        diferenciaGoles = 0;
    }

    // ===== ACTUALIZAR RESULTADO DE PARTIDO =====
    // Suma los goles del partido y asigna puntos:
    // 3 por ganar, 1 por empatar y 0 por perder.
    void actualizar(int gf, int gc) {
        golesFavor += gf;
        golesContra += gc;
        diferenciaGoles = golesFavor - golesContra;

        if (gf > gc)
            puntos += 3; // Victoria
        else if (gf == gc)
            puntos += 1; // Empate
        // Si pierde, no suma puntos
    }

    // ===== FORMATO PARA GUARDAR EN CSV =====
    // Devuelve un texto con los datos del equipo separados por comas.
    // Esto permite guardar la información fácilmente en un archivo.
    string toCSV() const {
        return nombre + "," + to_string(puntos) + "," +
               to_string(golesFavor) + "," +
               to_string(golesContra) + "," +
               to_string(diferenciaGoles);
    }
};

#endif
