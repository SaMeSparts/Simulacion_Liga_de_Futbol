// Diego Antonio González Cortés | A01713489
// TC1031 Programación de estructuras de datos y algoritmos fundamentales

#ifndef EQUIPO_H
#define EQUIPO_H

using namespace std;
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>



class Equipo
{
private:
    string nombre;
    int puntos;
    int goles;
    int golcont;
public:
    Equipo(string n){
        nombre = n;
        puntos = 0;
        goles = 0;
        golcont = 0;
    }

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

    int getDifGoles() const{
        return goles-golcont;
    }

    void regPartido(int gf, int gc){
        goles += gf;
        golcont += gc;

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