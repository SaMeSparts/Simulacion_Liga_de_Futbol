using namespace std;
#include <iostream>
#include <string>
#ifndef EQUIPO_H
#define EQUIPO_H


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

    int getDifGoles(){
        return goles-golcont;
    }

    void regPartido(int gf, int gc){
        goles += gf;
        golcont += gc;
    }


};


#endif