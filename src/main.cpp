#include <iostream>
#include "estructuras.h"
#include "paciente.h"

using namespace std;

// Main.cpp de PRUEBA PERSONAL - no se sube al repositorio del equipo.
// Sirve solo para probar tu modulo de Paciente de forma aislada.

int main() {
    Paciente pacientes[MAX_PACIENTES];
    int totalPacientes = 0;

    cargarPacientes(pacientes, totalPacientes);
    cout << "Pacientes cargados desde archivo: " << totalPacientes << "\n";

    menuPacientes(pacientes, totalPacientes);

    guardarPacientes(pacientes, totalPacientes);
    cout << "Datos guardados. Hasta luego.\n";
    return 0;
}