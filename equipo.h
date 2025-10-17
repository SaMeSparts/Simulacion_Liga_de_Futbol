// Diego Antonio González Cortés | A01713489
// TC1031 Programación de estructuras de datos y algoritmos fundamentales

#ifndef EQUIPO_H
#define EQUIPO_H

using namespace std;
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>


// Clase Equipo
class Equipo
{
private:
    string nombre; // Nombre del Equipo
    int puntos; // Puntos acumulados
    int goles; // Goles a favor
    int golcont; // Goles en contra
public:

    // Constructor: inicializa el equipo con su nombre y estadísticas en cero
    Equipo(string n){
        nombre = n;
        puntos = 0;
        goles = 0;
        golcont = 0;
    }

    // Getters

    string getNombre(){
        return nombre;
    }

    int getPuntos(){
        return puntos;
    }

    int getGoles(){
        return goles;
    }
    
    int getGolesContra(){
        return golcont;
    }

    // Calcula la diferencia de goles
    int getDifGoles() const{
        return goles-golcont;
    }

    // Registra el partido con los goles a favor y goles en contra
    void regPartido(int gf, int gc){
        goles += gf;
        golcont += gc;

        // Se calcula el resultado y se compara para dar un resultado, agrgando puntos
        if (gf > gc) puntos += 3;  
        else if (gf == gc) puntos += 1;
    }

    // Mostrar datos
    void mostrarEquipo() const {
        cout << left << setw(15) << nombre
             << setw(10) << puntos
             << setw(10) << goles
             << setw(10) << golcont
             << setw(10) << getDifGoles() << endl;
    }


};


#endif