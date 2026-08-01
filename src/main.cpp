#include <iostream>
#include "estructuras.h"
#include "config.h"
#include "paciente.h"
#include "medico.h"
#include "cita.h"
#include "consulta.h"
#include "reportes.h"
#include "validaciones.h"

using namespace std;

// =========================================================
//  MAIN.CPP - Menu principal del Sistema de Gestion Hospitalaria
// =========================================================

int main() {
    //Arreglos
    Paciente     pacientes[MAX_PACIENTES];
    Medico       medicos[MAX_MEDICOS];
    Especialidad especialidades[MAX_ESPECIALIDADES];
    Cita         citas[MAX_CITAS];
    Consulta     consultas[MAX_CONSULTAS];
    Factura      facturas[MAX_FACTURAS];

    int totalPacientes = 0, totalMedicos = 0, totalEspecialidades = 0;
    int totalCitas = 0, totalConsultas = 0, totalFacturas = 0;

    // Carga automatica al iniciar
    cargarEspecialidades(especialidades, totalEspecialidades);
    cargarMedicos(medicos, totalMedicos);
    cargarPacientes(pacientes, totalPacientes);
    cargarCitas(citas, totalCitas);
    cargarConsultas(consultas, totalConsultas);
    cargarFacturas(facturas, totalFacturas);

    cout << "===========================================\n";
    cout << "  SISTEMA DE GESTION HOSPITALARIA\n";
    cout << "===========================================\n";
    cout << "Datos cargados: " << totalPacientes << " pacientes, "
         << totalMedicos << " medicos, " << totalCitas << " citas, "
         << totalConsultas << " consultas, " << totalFacturas << " facturas.\n";

    int opcion;
    do {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1. Pacientes\n";
        cout << "2. Medicos\n";
        cout << "3. Citas\n";
        cout << "4. Consultas\n";
        cout << "5. Reportes\n";
        cout << "0. Salir\n";
        opcion = leerEntero("Opcion: ", 0, 5);

        switch (opcion) {
            case 1:
                menuPacientes(pacientes, totalPacientes);
                break;
            case 2:
                menuMedicos(medicos, totalMedicos, especialidades, totalEspecialidades);
                break;
            case 3:
                menuCitas(citas, totalCitas, pacientes, totalPacientes, medicos, totalMedicos);
                break;
            case 4:
                menuConsultas(citas, totalCitas, consultas, totalConsultas, facturas, totalFacturas);
                break;
            case 5:
                menuReportes(pacientes, totalPacientes, medicos, totalMedicos,
                             citas, totalCitas, consultas, totalConsultas,
                             facturas, totalFacturas);
                break;
            case 0:
                cout << "Guardando datos...\n";
                guardarEspecialidades(especialidades, totalEspecialidades);
                guardarMedicos(medicos, totalMedicos);
                guardarPacientes(pacientes, totalPacientes);
                guardarCitas(citas, totalCitas);
                guardarConsultas(consultas, totalConsultas);
                guardarFacturas(facturas, totalFacturas);
                cout << "Cerrando.\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}
