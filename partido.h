#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// ===== CLASE PARTIDO =====
class Partido {
private:
    string local;
    string visitante;
    int golesLocal;
    int golesVisitante;

public:
    // ===== CONSTRUCTOR =====
    Partido(string l = "", string v = "") {
        local = l;
        visitante = v;
        golesLocal = 0;
        golesVisitante = 0;
    }

    // ===== SIMULAR PARTIDO (GOLES ALEATORIOS) =====
    void simular() {
        golesLocal = rand() % 6;       // 0 a 5
        golesVisitante = rand() % 6;   // 0 a 5
    }

    // ===== MOSTRAR RESULTADO =====
    string mostrarResultado() const {
        return local + " " + to_string(golesLocal) + " - " +
               to_string(golesVisitante) + " " + visitante;
    }

    // ===== GETTERS =====
    string getLocal() const { return local; }
    string getVisitante() const { return visitante; }
    int getGolesLocal() const { return golesLocal; }
    int getGolesVisitante() const { return golesVisitante; }

    // ===== FORMATO PARA CSV =====
    string toCSV() const {
        return local + "," + visitante + "," +
               to_string(golesLocal) + "," +
               to_string(golesVisitante);
    }
};

#endif
