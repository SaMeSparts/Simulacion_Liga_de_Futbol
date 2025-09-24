#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

class Equipo {
private:
    string nombre;
    int puntos;
    int golesFavor;
    int golesContra;

public:
    Equipo(string n) {
        nombre = n;
        puntos = 0;
        golesFavor = 0;
        golesContra = 0;
    }

    // Métodos getters
    string getNombre() const { return nombre; }
    int getPuntos() const { return puntos; }
    int getGolesFavor() const { return golesFavor; }
    int getGolesContra() const { return golesContra; }
    int getDiferenciaGoles() const { return golesFavor - golesContra; }

    // Actualizar estadísticas
    void registrarPartido(int gf, int gc) {
        golesFavor += gf;
        golesContra += gc;

        if (gf > gc) puntos += 3;     // Victoria
        else if (gf == gc) puntos += 1; // Empate
        // Si pierde no suma puntos
    }

    // Mostrar datos
    void mostrarEquipo() const {
        cout << left << setw(15) << nombre
             << setw(10) << puntos
             << setw(10) << golesFavor
             << setw(10) << golesContra
             << setw(10) << getDiferenciaGoles() << endl;
    }
};

class Liga {
private:
    vector<Equipo> equipos;

public:
    // Agregar equipo a la liga
    void agregarEquipo(string nombre) {
        equipos.push_back(Equipo(nombre));
    }

    // Simular un partido aleatorio entre dos equipos
    void simularPartido(int i, int j) {
        int goles1 = rand() % 5; // marcador aleatorio entre 0 y 4
        int goles2 = rand() % 5;

        equipos[i].registrarPartido(goles1, goles2);
        equipos[j].registrarPartido(goles2, goles1);

        cout << equipos[i].getNombre() << " " << goles1
             << " - " << goles2 << " " << equipos[j].getNombre() << endl;
    }

    // Simular una jornada (todos contra todos una vez)
    void simularJornada() {
        for (int i = 0; i < equipos.size(); i++) {
            for (int j = i + 1; j < equipos.size(); j++) {
                simularPartido(i, j);
            }
        }
    }

    // Ordenar la tabla de posiciones (por puntos y diferencia de goles)
    void ordenarTabla() {
        for (int i = 0; i < equipos.size() - 1; i++) {
            for (int j = 0; j < equipos.size() - i - 1; j++) {
                if (equipos[j].getPuntos() < equipos[j+1].getPuntos() ||
                   (equipos[j].getPuntos() == equipos[j+1].getPuntos() &&
                    equipos[j].getDiferenciaGoles() < equipos[j+1].getDiferenciaGoles())) {
                    swap(equipos[j], equipos[j+1]);
                }
            }
        }
    }

    // Mostrar la tabla de posiciones
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

// Programa principal
int main() {
    srand(time(0));

    Liga liga;
    liga.agregarEquipo("Barcelona");
    liga.agregarEquipo("Real Madrid");
    liga.agregarEquipo("Atletico");
    liga.agregarEquipo("Sevilla");

    cout << "Simulando partidos..." << endl;
    liga.simularJornada();

    cout << "\nTabla de posiciones:\n";
    liga.mostrarTabla();

    return 0;
}
