// Diego Antonio González Cortés | A01713489
// TC1031 Programación de estructuras de datos y algoritmos fundamentales

#ifndef LIGA_H
#define LIGA_H
#include "equipo.h"



class Liga
{
private:
    vector<Equipo> equipos;
public:

    void agregarEquipo(string nombre) {
        equipos.push_back(Equipo(nombre));
    }

    void simularPartido(int i, int j) {
        int goles1 = rand() % 5; 
        int goles2 = rand() % 5;

        equipos[i].regPartido(goles1, goles2);
        equipos[j].regPartido(goles2, goles1);

        cout << equipos[i].getNombre() << " " << goles1
             << " - " << goles2 << " " << equipos[j].getNombre() << endl;
    }

    void simularJornada() {
        for (int i = 0; i < equipos.size(); i++) {
            for (int j = i + 1; j < equipos.size(); j++) {
                simularPartido(i, j);
            }
        }
    }

    void ordenarTabla() {
        for (int i = 0; i < equipos.size() - 1; i++) {
            for (int j = 0; j < equipos.size() - i - 1; j++) {
                if (equipos[j].getPuntos() < equipos[j+1].getPuntos() ||
                   (equipos[j].getPuntos() == equipos[j+1].getPuntos() &&
                    equipos[j].getDifGoles() < equipos[j+1].getDifGoles())) {
                    swap(equipos[j], equipos[j+1]);
                }
            }
        }
    }
    
    void mostrarTabla() {
        ordenarTabla();
        cout << left << setw(15) << "Equipo"
             << setw(10) << "Puntos"
             << setw(10) << "GF"
             << setw(10) << "GC"
             << setw(10) << "DG" << endl;
        cout << "---------------------------------------------------" << endl;
        for (auto &e : equipos) {
            e.mostrarEquipo();
        }
    }

};

#endif