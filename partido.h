// Diego Antonio González Cortés

#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


// ===== CLASE PARTIDO =====
// Esta clase representa un partido de futbol entre dos equipos.
// Guarda los nombres de los equipos y los goles de cada uno.

class Partido {
private:
    string local;          // Nombre del equipo local
    string visitante;      // Nombre del equipo visitante
    int golesLocal;        // Goles del equipo local
    int golesVisitante;    // Goles del equipo visitante

public:

    // ===== CONSTRUCTOR =====
    // Cuando se crea un partido, se indican los equipos
    // y los goles inician en 0.
    Partido(string l = "", string v = "") {
        local = l;
        visitante = v;
        golesLocal = 0;
        golesVisitante = 0;
    }

    
    // ===== SIMULAR PARTIDO =====
    // Genera goles aleatorios para cada equipo (de 0 a 5)
    // usando la funcion rand(). 
    // Esto sirve para simular un resultado realista.
    
    void simular() {
        golesLocal = rand() % 6;       // Goles aleatorios de 0 a 5
        golesVisitante = rand() % 6;   // Goles aleatorios de 0 a 5
    }

    
    // ===== MOSTRAR RESULTADO =====
    // Devuelve un texto con el formato:
    // "Local X - Y Visitante"
    // Ejemplo: "America 2 - 1 Chivas"
    
    string mostrarResultado() const {
        return local + " " + to_string(golesLocal) + " - " +
               to_string(golesVisitante) + " " + visitante;
    }

    
    // ===== GETTERS =====
    // Sirven para obtener los valores de los atributos
    // sin permitir modificarlos directamente.
    
    string getLocal() const { return local; }
    string getVisitante() const { return visitante; }
    int getGolesLocal() const { return golesLocal; }
    int getGolesVisitante() const { return golesVisitante; }

    
    // ===== FORMATO PARA CSV =====
    // Devuelve los datos del partido separados por comas
    // para poder guardarlos en un archivo CSV.
    // Ejemplo: "America,Chivas,2,1"
    
    string toCSV() const {
        return local + "," + visitante + "," +
               to_string(golesLocal) + "," +
               to_string(golesVisitante);
    }
};

#endif
