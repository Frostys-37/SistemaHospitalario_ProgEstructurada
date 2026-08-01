#include <iostream>
#include <string>
#include "reportes.h"
#include "validaciones.h"

using namespace std;

// =========================================================
//  Busquedas locales
//  No se exportan en el header: Reportes solo lee
// =========================================================

static int buscarCitaLocal(Cita citas[], int total, string codigo) {
    for (int i = 0; i < total; i++) {
        if (citas[i].codigo == codigo) return i;
    }
    return -1;
}

static int buscarMedicoLocal(Medico lista[], int total, string codigo) {
    for (int i = 0; i < total; i++) {
        if (lista[i].codigo == codigo) return i;
    }
    return -1;
}

// Convierte "dd/mm/aaaa" a "aaaammdd" para poder comparar fechas
static string fechaComparable(string fecha) {
    if (fecha.size() != 10) return fecha; // formato inesperado, se compara tal cual
    string dia  = fecha.substr(0, 2);
    string mes  = fecha.substr(3, 2);
    string anio = fecha.substr(6, 4);
    return anio + mes + dia;
}

// =========================================================
//  REPORTE 1: Pacientes atendidos
//  "Atendido" = tiene al menos una cita con consulta registrada.
// =========================================================
void reportePacientesAtendidos(Paciente pacientes[], int totalPacientes,
                                Cita citas[], int totalCitas,
                                Consulta consultas[], int totalConsultas) {
    cout << "\n==== REPORTE: PACIENTES ATENDIDOS ====\n";
    int encontrados = 0;

    for (int i = 0; i < totalPacientes; i++) {
        bool atendido = false;

        // Recorre las citas de este paciente
        for (int c = 0; c < totalCitas && !atendido; c++) {
            if (citas[c].codigoPaciente != pacientes[i].codigo) continue;

            // Si alguna de esas citas tiene una consulta registrada, ya fue atendido
            for (int k = 0; k < totalConsultas; k++) {
                if (consultas[k].codigoCita == citas[c].codigo) {
                    atendido = true;
                    break;
                }
            }
        }

        if (atendido) {
            cout << pacientes[i].codigo << " | " << pacientes[i].nombre
                 << " | ID: " << pacientes[i].identidad << "\n";
            encontrados++;
        }
    }

    cout << "Total de pacientes atendidos: " << encontrados << "\n";
}

// =========================================================
//  REPORTE 2: Medico con mas consultas
// =========================================================
void reporteMedicoConMasConsultas(Medico medicos[], int totalMedicos,
                                   Cita citas[], int totalCitas,
                                   Consulta consultas[], int totalConsultas) {
    cout << "\n==== REPORTE: MEDICO CON MAS CONSULTAS ====\n";

    if (totalMedicos == 0) {
        cout << "(No hay medicos registrados)\n";
        return;
    }

    // Un contador paralelo al arreglo de medicos (misma logica que
    // usariamos con cualquier conteo por categoria, sin usar mapas).
    int conteo[MAX_MEDICOS] = {0};

    for (int k = 0; k < totalConsultas; k++) {
        int idxCita = buscarCitaLocal(citas, totalCitas, consultas[k].codigoCita);
        if (idxCita == -1) continue;

        int idxMedico = buscarMedicoLocal(medicos, totalMedicos, citas[idxCita].codigoMedico);
        if (idxMedico == -1) continue;

        conteo[idxMedico]++;
    }

    int mejor = 0;
    for (int i = 1; i < totalMedicos; i++) {
        if (conteo[i] > conteo[mejor]) mejor = i;
    }

    if (conteo[mejor] == 0) {
        cout << "(Todavia no hay consultas registradas)\n";
        return;
    }

    cout << "Medico con mas consultas: " << medicos[mejor].nombre
         << " (" << medicos[mejor].codigo << ")\n";
    cout << "Total de consultas atendidas: " << conteo[mejor] << "\n";

    // Ranking completo, no solo el primero
    cout << "\n-- Ranking completo --\n";
    for (int i = 0; i < totalMedicos; i++) {
        if (conteo[i] > 0) {
            cout << medicos[i].codigo << " | " << medicos[i].nombre
                 << " | Consultas: " << conteo[i] << "\n";
        }
    }
}

// =========================================================
//  REPORTE 3: Total facturado
// =========================================================
void reporteTotalFacturado(Factura facturas[], int totalFacturas) {
    cout << "\n==== REPORTE: TOTAL FACTURADO ====\n";

    if (totalFacturas == 0) {
        cout << "(No hay facturas registradas)\n";
        return;
    }

    float total = 0;
    for (int i = 0; i < totalFacturas; i++) {
        cout << facturas[i].codigo << " | Cita: " << facturas[i].codigoCita
             << " | L. " << facturas[i].total << "\n";
        total += facturas[i].total;
    }

    cout << "\nTOTAL FACTURADO: L. " << total << "\n";
}

// =========================================================
//  REPORTE 4: Historial de un paciente
// =========================================================
void reporteHistorialPaciente(Paciente pacientes[], int totalPacientes,
                               Cita citas[], int totalCitas,
                               Consulta consultas[], int totalConsultas,
                               Medico medicos[], int totalMedicos) {
    cout << "\n==== REPORTE: HISTORIAL DE UN PACIENTE ====\n";

    string identidad = leerIdentidad("Identidad del paciente (13 digitos): ");
    int idxPaciente = -1;
    for (int i = 0; i < totalPacientes; i++) {
        if (pacientes[i].identidad == identidad) { idxPaciente = i; break; }
    }

    if (idxPaciente == -1) {
        cout << "No se encontro ningun paciente con esa identidad.\n";
        return;
    }

    cout << "\nPaciente: " << pacientes[idxPaciente].nombre
         << " (" << pacientes[idxPaciente].codigo << ")\n";
    cout << "-----------------------------------------\n";

    int citasEncontradas = 0;
    for (int c = 0; c < totalCitas; c++) {
        if (citas[c].codigoPaciente != pacientes[idxPaciente].codigo) continue;
        citasEncontradas++;

        int idxMedico = buscarMedicoLocal(medicos, totalMedicos, citas[c].codigoMedico);
        cout << "Cita " << citas[c].codigo << " | " << citas[c].fecha << " " << citas[c].hora
             << " | Medico: " << (idxMedico != -1 ? medicos[idxMedico].nombre : "(desconocido)")
             << " | Estado: " << citas[c].estado << "\n";

        // Busca la consulta asociada a esta cita, si existe
        for (int k = 0; k < totalConsultas; k++) {
            if (consultas[k].codigoCita == citas[c].codigo) {
                cout << "   Diagnostico:  " << consultas[k].diagnostico << "\n";
                cout << "   Tratamiento:  " << consultas[k].tratamiento << "\n";
            }
        }
    }

    if (citasEncontradas == 0) {
        cout << "Este paciente no tiene citas registradas.\n";
    }
}

// =========================================================
//  REPORTE 5: Consultas por rango de fechas
// =========================================================
void reporteConsultasPorRangoFechas(Cita citas[], int totalCitas,
                                     Consulta consultas[], int totalConsultas) {
    cout << "\n==== REPORTE: CONSULTAS POR RANGO DE FECHAS ====\n";

    string fechaInicio, fechaFin;
    cout << "Fecha inicial (dd/mm/aaaa): ";
    getline(cin, fechaInicio);
    cout << "Fecha final (dd/mm/aaaa): ";
    getline(cin, fechaFin);

    string inicioComp = fechaComparable(fechaInicio);
    string finComp    = fechaComparable(fechaFin);

    int encontradas = 0;
    for (int k = 0; k < totalConsultas; k++) {
        int idxCita = buscarCitaLocal(citas, totalCitas, consultas[k].codigoCita);
        if (idxCita == -1) continue;

        string fechaComp = fechaComparable(citas[idxCita].fecha);
        if (fechaComp >= inicioComp && fechaComp <= finComp) {
            cout << consultas[k].codigo << " | Cita: " << citas[idxCita].codigo
                 << " | Fecha: " << citas[idxCita].fecha
                 << " | Diagnostico: " << consultas[k].diagnostico << "\n";
            encontradas++;
        }
    }

    if (encontradas == 0) cout << "(No hay consultas en ese rango de fechas)\n";
    else cout << "Total encontradas: " << encontradas << "\n";
}

// =========================================================
//  SUB-MENU
// =========================================================
void menuReportes(Paciente pacientes[], int totalPacientes,
                  Medico medicos[], int totalMedicos,
                  Cita citas[], int totalCitas,
                  Consulta consultas[], int totalConsultas,
                  Factura facturas[], int totalFacturas) {
    int opcion;
    do {
        cout << "\n===== SUB-MENU REPORTES =====\n";
        cout << "1. Pacientes atendidos\n";
        cout << "2. Medico con mas consultas\n";
        cout << "3. Total facturado\n";
        cout << "4. Historial de un paciente\n";
        cout << "5. Consultas por rango de fechas\n";
        cout << "0. Volver al menu principal\n";
        opcion = leerEntero("Opcion: ", 0, 5);

        switch (opcion) {
            case 1: reportePacientesAtendidos(pacientes, totalPacientes, citas, totalCitas, consultas, totalConsultas); break;
            case 2: reporteMedicoConMasConsultas(medicos, totalMedicos, citas, totalCitas, consultas, totalConsultas); break;
            case 3: reporteTotalFacturado(facturas, totalFacturas); break;
            case 4: reporteHistorialPaciente(pacientes, totalPacientes, citas, totalCitas, consultas, totalConsultas, medicos, totalMedicos); break;
            case 5: reporteConsultasPorRangoFechas(citas, totalCitas, consultas, totalConsultas); break;
            case 0: cout << "Volviendo al menu principal...\n"; break;
        }
    } while (opcion != 0);
}
