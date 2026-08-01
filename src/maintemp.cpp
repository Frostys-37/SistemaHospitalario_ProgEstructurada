#include <iostream>
#include <string>
#include "estructuras.h"
#include "config.h"
#include "cita.h"
#include "paciente.h"
#include "medico.h"

using namespace std;

// Declaraciones manuales alineadas con la implementacion real de consulta.cpp
bool cargarConsultas(Consulta consultas[], int &totalConsultas);
bool guardarConsultas(Consulta consultas[], int totalConsultas);
int buscarConsultaPorCodigo(Consulta consultas[], int totalConsultas, string codigo);
string generarCodigoConsulta(Consulta consultas[], int totalConsultas);
bool validarCodigoCita(Cita citas[], int totalCitas, string codigoCita, int &indice);
void registrarConsulta(Cita citas[], int totalCitas, Consulta consultas[], int &totalConsultas);

bool cargarFacturas(Factura facturas[], int &totalFacturas);
bool guardarFacturas(Factura facturas[], int totalFacturas);
string generarCodigoFactura(Factura facturas[], int totalFacturas);
void registrarFactura(Cita citas[], int totalCitas, Factura facturas[], int &totalFacturas);

int main() {
    Cita citas[MAX_CITAS];
    Consulta consultas[MAX_CONSULTAS];
    Factura facturas[MAX_FACTURAS];
    Paciente pacientes[MAX_PACIENTES];
    Medico medicos[MAX_MEDICOS];

    int totalCitas = 0;
    int totalConsultas = 0;
    int totalFacturas = 0;
    int totalPacientes = 0;
    int totalMedicos = 0;

    cargarCitas(citas, totalCitas);
    cargarConsultas(consultas, totalConsultas);
    cargarFacturas(facturas, totalFacturas);
    cargarPacientes(pacientes, totalPacientes);
    cargarMedicos(medicos, totalMedicos);

    cout << "=== PRUEBA TEMPORAL DE CONSULTAS ===\n";
    cout << "Citas cargadas: " << totalCitas << "\n";
    cout << "Consultas cargadas: " << totalConsultas << "\n";
    cout << "Facturas cargadas: " << totalFacturas << "\n";

    registrarConsulta(citas, totalCitas, consultas, totalConsultas);
    registrarFactura(citas, totalCitas, facturas, totalFacturas);

    guardarConsultas(consultas, totalConsultas);
    guardarFacturas(facturas, totalFacturas);

    return 0;
}
