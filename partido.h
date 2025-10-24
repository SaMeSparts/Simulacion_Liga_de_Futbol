// Diego Antonio González Cortés

#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Clase partido para simular los juegos
class Partido {
private:
    string local;
    string visitante;
    int golesLocal;
    int golesVisitante;

public:
    // Constructor que recibe los nombres de los equipos
    // Complejidad: O(1)
    Partido(string l = "", string v = "") {
        local = l;
        visitante = v;
        golesLocal = 0;
        golesVisitante = 0;
    }

    // Funcion para simular un partido con goles aleatorios
    // Complejidad: O(1)
    void simular() {
        golesLocal = rand() % 6;       // genera de 0 a 5 goles
        golesVisitante = rand() % 6;
    }

    // Muestra el resultado del partido
    // Complejidad: O(1)
    string mostrarResultado() const {
        return local + " " + to_string(golesLocal) + " - " +
               to_string(golesVisitante) + " " + visitante;
    }

    // Getters para acceder a los datos
    // Complejidad: O(1)
    string getLocal() const { return local; }
    string getVisitante() const { return visitante; }
    int getGolesLocal() const { return golesLocal; }
    int getGolesVisitante() const { return golesVisitante; }

    // Sirve para guardar el resultado en csv
    // Complejidad: O(1)
    string toCSV() const {
        return local + "," + visitante + "," +
               to_string(golesLocal) + "," +
               to_string(golesVisitante);
    }
};

#endif
