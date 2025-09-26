// Diego Antonio González Cortés | A01713489
// TC1031 Programación de estructuras de datos y algoritmos fundamentales

#include "liga.h"


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
};