// Diego Antonio González Cortés

#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Clase Partido para representar un juego entre dos equipos.
// Esta clase solo guarda información y todas sus operaciones
// se hacen en tiempo constante.
class Partido {
private:
    string local;
    string visitante;
    int golesLocal;
    int golesVisitante;

public:
    // Constructor que recibe los nombres de los equipos.
    // Solo asigna valores a las variables, así que siempre toma O(1).
    Partido(string l = "", string v = "") {
        local = l;
        visitante = v;
        golesLocal = 0;
        golesVisitante = 0;
    }

    // Simula un partido generando goles aleatorios.
    // Usa operaciones simples, por eso su costo es O(1).
    void simular() {
        golesLocal = rand() % 6;       // Goles entre 0 y 5
        golesVisitante = rand() % 6;
    }

    // Devuelve el resultado del partido como texto.
    // Solo construye un string corto, por eso también es O(1).
    string mostrarResultado() const {
        return local + " " + to_string(golesLocal) + " - " +
               to_string(golesVisitante) + " " + visitante;
    }

    // Getters para obtener los datos del partido.
    // Son accesos directos, así que siempre cuestan O(1).
    string getLocal() const { return local; }
    string getVisitante() const { return visitante; }
    int getGolesLocal() const { return golesLocal; }
    int getGolesVisitante() const { return golesVisitante; }

    // Devuelve el resultado en formato CSV.
    // Solo arma un string pequeño, por lo que es O(1).
    string toCSV() const {
        return local + "," + visitante + "," +
               to_string(golesLocal) + "," +
               to_string(golesVisitante);
    }
};

#endif
